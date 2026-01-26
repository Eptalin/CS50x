import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Create list of dictionaries for each stock
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE userid = ? GROUP BY symbol HAVING SUM(shares) > 0;",
         session["user_id"])

    # Iterate over the list to find the prices and totals for each row, then add them to the dictionaries
    for row in rows:
        stock_price = lookup(row["symbol"])
        row["price"] = stock_price["price"]
        row["total"] = usd(row["price"] * row["shares"])

    # Get cash balance and portfolio value
    cash = db.execute("SELECT cash FROM users WHERE users.id = ?", session["user_id"])[0]["cash"]
    portfolio = cash + sum(row["price"] * row["shares"] for row in rows)

    return render_template("index.html", entries=rows, cash=usd(cash), total=usd(portfolio))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Store user data in variables
        symbol = request.form.get("symbol").upper()
        check = lookup(symbol)
        if check is None:
            return apology("Invalid symbol")

        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("Please enter whole numbers")
        shares = int(shares)

        # Verify user input
        if not symbol:
            return apology("Enter stock symbol")
        if not shares or shares <= 0:
            return apology("Enter no. shares")

        # Store 1st item in the cash list of dictionaries as an object.
        cash = db.execute("SELECT cash FROM users WHERE users.id = ?",
                          session["user_id"])[0]["cash"]
        price = check["price"]
        total = shares * price

        # Confirm user has enough cash for the purchase
        if cash < total:
            return apology("Insufficient cash")

        # Enter transaction into db and update user's cash balance
        db.execute("INSERT INTO transactions (userid, symbol, shares, price) VALUES (?, ?, ?, ?);",
                   session["user_id"], symbol, shares, price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash - total, session["user_id"])
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE userid = ?;", session["user_id"])

    for row in rows:
        row["type"] = "buy" if row["shares"] > 0 else "sell"

    return render_template("history.html", entries=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Use form to get stock quote
        symbol = request.form.get("symbol")

        try:
            # Display the price of the symbol
            print(lookup(symbol))
            return render_template("quoted.html", price=lookup(symbol)["price"], symbol=lookup(symbol)["symbol"])
        except Exception as e:
            print(e)
            return apology("Symbol not found")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Store user input in variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Verify user input
        if not username:
            return apology("Username required")
        if not password or password != confirmation:
            return apology("Passwords don't match")

        # Add new user to database and redirect to login page
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?);",
                       username, generate_password_hash(password))
            return redirect("/login")
        # If the username is taken, apologise
        except Exception as e:
            print(e)
            return apology("Username already taken")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """sell shares of stock"""

    # Create list of symbols the user owns (not dictionaries)
    symbol_list = [
        symbol["symbol"]
        for symbol in db.execute(
            "SELECT DISTINCT symbol FROM transactions WHERE userid = ? AND shares >0 ORDER BY symbol;",
            session["user_id"]
        )
    ]

    if request.method == "POST":

        # Store user data in variables and verify
        symbol = request.form.get("symbol")
        if not symbol or symbol not in symbol_list:
            return apology("Select owned stock")
        check = lookup(symbol)
        if check is None:
            return apology("Invalid symbol")

        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("Please enter whole numbers")
        shares = int(shares) * -1
        if not shares or shares >= 0:
            return apology("Enter number of shares")

        held_shares = db.execute("SELECT SUM(shares) FROM transactions WHERE symbol = ? AND userid = ?;",
                                 symbol, session["user_id"])[0]["SUM(shares)"]
        if (shares * -1) > held_shares:
            return apology("You don't own enough shares")

        cash = db.execute("SELECT cash FROM users WHERE users.id = ?",
                          session["user_id"])[0]["cash"]
        price = check["price"]
        total = (shares * -1) * price

        # Insert user data into db
        db.execute("INSERT INTO transactions (userid, symbol, shares, price) VALUES (?, ?, ?, ?);",
                   session["user_id"], symbol, shares, price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", cash + total, session["user_id"])
        return redirect("/")

    else:
        return render_template("sell.html", list=symbol_list)

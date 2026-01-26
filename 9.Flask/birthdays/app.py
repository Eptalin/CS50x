import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    # Add user's entry into the database
    if request.method == "POST":

        # Extract user input from the form into objects
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Verify user input
        is_name_valid = name and name.isalpha()
        is_month_valid = month and int(month) <= 12 and int(month) >= 1
        is_day_valid = day and int(day) <= 31 and int(day) >= 1

        # IF data is invalid, redirect user back to the form
        if not is_name_valid or not is_month_valid or not is_day_valid:
            return redirect("/")

        # ELSE, insert verified data into database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);", name, month, day)
        return redirect("/")

    else:

        # Display all entries in the database on index.html
        rows = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays=rows)

from cs50 import get_float


def main():
    change = get_change()
    coins = calc_coins(change * 100)        # multiply by 100 to avoid floating point errors
    print(f"{coins:.0f}")                   # :.0f is how many decimal places to print


def get_change():
    while True:
        n = get_float("Change: ")
        if n > 0:
            return n


def calc_coins(change):
    coins = [25, 10, 5, 1]
    n = 0

    for coin in coins:
        n += change // coin                 # '//' is floor division. Rounds down to the neearest whole number.
        change %= coin                      # % returns the remainder after dividing (uses floor division).

    return n


main()

# Prompt user for card number
# Check card number using Luhn algorithm
# Print results
def main():
    card_number = input("Card number: ")
    if luhn(card_number) == False:
        print("INVALID")
    else:
        print(card_type(card_number))


# Use list comprehension to split the card number in two
# Double every second digit from the right (even digits)
# Returns True if == 0, or False if != 0
def luhn(card):
    even = [int(i) * 2 if int(i) * 2 <= 9 else int(i) * 2 - 9 for i in card[-2::-2]]
    odd = [int(j) for j in card[-1::-2]]
    return (sum(even + odd) % 10) == 0


# Check length of card, and starting digits
# Use a list comprehension within the any function
# An any function returns True if at least 1 element in the iterable is true
# Return results as a string to be printed in main
def card_type(card):
    if len(card) in (13, 16) and card.startswith("4"):
        return "VISA"
    elif len(card) == 16 and any(card.startswith(str(i)) for i in range(51, 56)):
        return "MASTERCARD"
    elif len(card) == 15 and card.startswith(("34", "37")):
        return "AMEX"
    else:
        return "INVALID"


main()

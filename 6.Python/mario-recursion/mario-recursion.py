def main():
    height = int(input('Enter Height: '))
    print_top(height, height)
    print()
    print_bottom(height, height)
    print()
    print_diamond(height, height)


# Print a normal pyramid
def print_top(height, total):
    # End once height is 0
    if height == 0:
        return
    # Recursive call for the row above:
    print_top(height-1, total)
    # Print current row:
    print_row(height, total)


# Print an upside down pyramid
def print_bottom(height, total):
    # End once height is 0
    if height == 0:
        return
    # Print current row
    print_row(height, total)
    # Recursive call for next row
    print_bottom(height - 1, total)


# Print a full diamond
def print_diamond(height, total):
        print_top(height, total)
        print_bottom(height - 1, total)


# Print a single row of spaces and hashes
def print_row(height, total):
    hashes = '#' * height
    print(hashes.rjust(total) + ' ' + hashes)
    # .rjust() = right justify


# Calls main when the file is run (but not when imported as a module)
if __name__ == "__main__":
    main()
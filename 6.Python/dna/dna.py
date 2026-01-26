import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna.py database.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []

    # Fill the list with dictionaries
    with open(sys.argv[1]) as file1:
        reader = csv.DictReader(file1)
        keys = reader.fieldnames
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file2:
        sequence = file2.read()

    # Find longest match of each STR in DNA sequence
    # Create a 2nd dict to compare against the database using list comprehension
    # Cast the results of longest_match as a str to match the database
    suspect = dict()
    suspect["name"] = "Suspect"
    suspect = {key: str((longest_match(sequence, key))) for key in keys[1:]}

    # Check database for matching profiles
    # Set a flag to 0 and change it if a profile doesn't match
    for profile in database:
        flag = 0
        for key in keys[1:]:
            if profile[key] != suspect[key]:
                flag = 1

    # If a match is found, print their name
        if flag == 0:
            print(profile["name"])
            return

    # If no match is found
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()

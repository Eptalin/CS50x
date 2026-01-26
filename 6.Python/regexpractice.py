import re

def main():
    email = input("What's your email? ").strip()
    if re.search(r"^[^@ ]+@[^@ ]+\.edu$", email):
        print("valid")
    else:
        print("invalid")

main()

# ^[^@ ]+@[^@]+\.edu$

# ^ ... $ means the match has to fit the pattern 
# from the 1st character to the last character of the string.

# [^@ ]+ matches any character except @ or space. + makes it 'greedy'

# \.edu escapes the . and ensures the email ends with .edu
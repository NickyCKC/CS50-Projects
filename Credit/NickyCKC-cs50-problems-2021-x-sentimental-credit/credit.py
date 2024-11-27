# Import get_int function from cs50
from cs50 import get_int

# Prompt user for credit card no.
def main():
    # Get card no.
    number = get_positive_int()
    # Copy card no. into another variable
    card_no = number
    # Convert number from int to str to allow len() to work
    no_len = str(number)
    # Calculate card length
    length = len(no_len)

    # Initialise values
    sum2 = 0
    sum1 = 0

    # Execute Luhn’s Algorithm
    while number > 0:
        # Get every other digit, starting with the number’s last digit
        no2 = number % 10
        # Get sum
        sum2 += no2
        # Remove last digit from card no.
        number = int(number / 10)

        if number >= 1:
            # Get every other digit, starting with the number’s second-to-last digit
            no1 = number % 10
            # Multiply by 2
            no1 = no1 * 2

            # Add products' digits
            if no1 >= 10:
                d2 = no1 % 10
                d1 = int(no1 / 10)
                sum1 += (d2 + d1)

            else:
                # Get sum
                sum1 += no1

            # Remove last digit from card no.
            number = int(number / 10)

    # Calculate the total
    total = sum2 + sum1

    # Check if last digit is 0
    if (total % 10 != 0):
        print("INVALID\n")

    else:
        # Check if card is AMEX
        if length == 15:
            digits = AnM(card_no)
            if digits == 34 or digits == 37:
                print("AMEX\n")

        # Check if card is MASTERCARD or VISA for 16 digit no.
        elif length == 16:
            digits = AnM(card_no)
            if digits == 51 or digits == 52 or digits == 53 or digits == 54 or digits == 55:
                print("MASTERCARD\n")
            digit = Visa(card_no)
            if digit == 4:
                print("VISA\n")

        # Check if card is VISA
        elif length == 13:
            digit = Visa(card_no)
            if digit == 4:
                print("VISA\n")

        # If card is not any, print INVALID
        else:
            print("INVALID\n")


# Create function to loop input until int obtained
def get_positive_int():
    while True:
        n = get_int("Number: ")
        if n > 0:
            break
    return n


# Create function to get first two no.s of AMEX and MASTERCARD card no.s
def AnM(card_no):
    while card_no >= 100:
        card_no = int(card_no / 10)
    return card_no


# Create function to get first no. of VISA card no.
def Visa(card_no):
    while card_no >= 10:
        card_no = int(card_no / 10)
    return card_no


# Run main function
main()
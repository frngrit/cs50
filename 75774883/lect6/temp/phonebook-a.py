import csv
from cs50 import get_string


# file = open("phonebook.csv", "a")

# name = get_string("Name: ")
# number = get_string("Number: ")

# writer = csv.writer(file)
# writer.writerow([name, number])

# file.close()

name = get_string("Name: ")
number = get_string("Number: ")

with open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, number])

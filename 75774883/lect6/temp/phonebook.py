from cs50 import get_string
import sys

people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

name = get_string("Name: ")
if name in people:
    print(f"Number: {people[name]}")
    sys.exit(0)

print("Not found")
sys.exit(1)
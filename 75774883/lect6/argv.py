from sys import argv, exit

if len(argv) != 2:
    print("Usage: python argv.py [Your name]")
    exit(1)

print(f"Hello {argv[1]}")
exit(0)

# for arg in argv:
#     print(arg)
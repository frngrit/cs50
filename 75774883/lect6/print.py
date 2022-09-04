try:
    x = int(input("x: "))
    y = int(input("y: "))
except ValueError:
    print('This is not int!')
    exit()


print(x + y)
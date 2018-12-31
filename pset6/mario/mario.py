from cs50 import get_int

height = -1
space = ' '
block = '#'

while height < 0 or height > 23:
    print('Height: ')
    height = get_int()

for x in range(height):
    for y in range(height):
        if y < height - x - 1:
            print(space, end='')
        else:
            print(block, end='')
    print(block)
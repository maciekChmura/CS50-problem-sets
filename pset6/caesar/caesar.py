from cs50 import get_string
import sys


def main():
    if len(sys.argv) is not 2:
        print('Invalid number of arguments')
        exit(1)
    print('plaintext: ', end='')
    # ask for input
    string = get_string()
    if string is not None:
        print('ciphertext: ', end='')
        # print('ciphertext: {}'.format(k))
        # calculate key
        k = int(sys.argv[1]) % 26
        for i in string:
            # check for upper case letter
            if i.isupper() is True:
                newChar = chr((ord(i) - ord('A') + k) % 26 + ord('A'))
                print(newChar, end='')
            # check for lower case letter
            elif i.islower() is True:
                newChar = chr((ord(i) - ord('a') + k) % 26 + ord('a'))
                print(newChar, end='')
            # reprint non letter character
            else:
                print(i, end='')
        print()
        exit(0)

if __name__ == '__main__':
    main()

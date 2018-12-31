from cs50 import get_float
from math import *

changeAmountFloat = -1

while changeAmountFloat < 0:
    print("O hai! How much change is owed?")
    changeAmountFloat = get_float()
changeAmountInt = changeAmountFloat * 100
coinsNumber = 0
rest = changeAmountInt
totalCoins = 0

coinsNumber = floor(changeAmountInt / 25)
rest -= coinsNumber * 25
totalCoins += coinsNumber
coinsNumber = 0

coinsNumber = floor(rest / 10)
rest -= coinsNumber * 10
totalCoins += coinsNumber
coinsNumber = 0

coinsNumber = floor(rest / 5)
rest -= coinsNumber * 5
totalCoins += coinsNumber
coinsNumber = 0

coinsNumber = floor(rest / 1)
totalCoins += coinsNumber
coinsNumber = 0
print(totalCoins)

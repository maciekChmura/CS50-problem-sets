#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    double changeAmountFloat;
    do {
        printf("O hai! How much change is owed?\n");
        changeAmountFloat = get_float();
    } while ( changeAmountFloat < 0 );
    //printf("%f\n", changeAmountFloat);
    int changeAmountInt = round(changeAmountFloat * 100);
    //printf("%i\n", changeAmountInt);
    int coinsNumber = 0;
    int rest = changeAmountInt;
    int totalCoins = 0;
    
    coinsNumber = changeAmountInt / 25;
    rest -= coinsNumber * 25;
    totalCoins += coinsNumber;
    coinsNumber = 0;
    
    coinsNumber = rest / 10;
    rest -= coinsNumber * 10;
    totalCoins += coinsNumber;
    coinsNumber = 0;
    
    coinsNumber = rest / 5;
    rest -= coinsNumber * 5;
    totalCoins += coinsNumber;
    coinsNumber = 0;
    
    coinsNumber = rest / 1;
    totalCoins += coinsNumber;
    coinsNumber = 0;
    printf("%i\n", totalCoins);
}
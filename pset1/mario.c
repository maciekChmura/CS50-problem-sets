#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    char space = ' ';
    char hash = '#';
    do {
        printf("Height: ");
        height = get_int();
    } while ( height < 0 || height > 23);
    int i;
    int j;
    for (i = 1; i <= height; i++) {
        for (j = 1; j <= height; j++) {
            if ( j <= height - i) {
                printf("%c", space);
            } else {
                printf("%c", hash);
            }
        }
    printf("%c", hash);
    printf("\n");
    }
}
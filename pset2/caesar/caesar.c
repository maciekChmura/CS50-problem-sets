#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    //check arguments
    if(argc != 2) {
        printf("Invalid number of arguments");
        return 1;
    };
    //ask user for input
    printf("plaintext: ");
    string s = get_string();
    if (s != NULL) {
        printf("ciphertext: ");
        //calculate key
        int k = atoi(argv[1]) % 26;
        for (int i = 0, n = strlen(s); i < n; i++) {
            //operate on uppercase letters
            if((s[i] >= 'A' && s[i] <= 'Z')) {
                printf("%c", (char) ((s[i] -'A' + k)%26+'A')); 
            }
            //operate on lowercase letters
            else if(s[i] >= 'a' && s[i] <= 'z') {
                printf("%c", (char) ((s[i] -'a' + k)%26+'a'));
            } else {
                //reprint non alphabetic letter
                printf("%c", (char) s[i]);
            }
        };
    };
    printf("\n");
    return 0;
};
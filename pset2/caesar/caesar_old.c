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
                //check for rotation of letters
                // if (((char) s[i] + k ) < 'Z') {
                //     //cipher without rotation
                //     printf("%c", (char) s[i] + k);    
                // } else {
                //     //cipher with rotation
                //     printf("%c", (char) s[i] + k - 26);
                // }
            }
            //operate on lowercase letters
            else if(s[i] >= 'a' && s[i] <= 'z') {
                printf("%c", (char) ((s[i] -'a' + k)%26+'a'));
                //check for rotation of letters
            //if (((char) s[i] + k ) < 'z') {
                
                //     //cipher without rotation
                //     printf("%c", (char) s[i] + k);    
                // } else {
                //     //cipher with rotation
                //     printf("%c", (char) s[i] + k - 26);
               // }
            } else {
                //reprint non alphabetic letter
                printf("%c", (char) s[i]);
            }
        };
    };
    printf("\n");
    return 0;
};

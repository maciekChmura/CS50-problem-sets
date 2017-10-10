#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    //check arguments
    if(argc != 2 || argv[1] == NULL ) {
        printf("Invalid number of arguments");
        return 1;
    };
    for (int a = 0; a < strlen(argv[1]); a++) {
        if (!isalpha(argv[1][a])) {
            printf("Argument is not valid keyword");
            return 1;    
        }
    }
    
    int helper = 0; // helper variable for holding loop counter while reprinting non alpha characer
    //ask user for input
    printf("plaintext: ");
    string s = get_string();
    if (s != NULL) {
        printf("ciphertext: ");
        //calculate key
        string k = argv[1];
        for (int i = 0, n = strlen(s); i < n; i++) {
            int j = i + helper;
            char currentKey = tolower(k[(j%strlen(k))]) - 97;
            //operate on uppercase letters
            if((s[i] >= 'A' && s[i] <= 'Z')) {
                printf("%c", (char) ((s[i] - 'A' + currentKey)%26+'A'));
            }
            //operate on lowercase letters
            else if(s[i] >= 'a' && s[i] <= 'z') {
                printf("%c", (char) ((s[i] - 'a' + currentKey)%26+'a'));
            } else {
                //reprint non alphabetic letter
                printf("%c", (char) s[i]);
                helper--;
            }
        };
    };
    printf("\n");
    return 0;
};

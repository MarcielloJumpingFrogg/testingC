#include <stdio.h>
#include <stdbool.h>


int checkAlpha(char letter) {
    if(letter >= 65 && letter <= 90)
    {
        //caps
        //return letter in lowercase
        return true;
    }

    if(letter >= 97 && letter <= 122)
    {
        return true;
    }

    return false;
}


char getInput() {
    char input;
    

    while(true) {
        printf("Insert a char:");
        scanf(" %c", &input);

        if(input == ' ' || input == '\n')
        {
            printf("\nEmpty space, insert another character. \n");
        }
        else{
            
            if(checkAlphaNum(input)) {
                printf("\nAlphabetic\n");            
                return input;

            }
            else {
                printf("\ninvalid\n");
            }

        }
    }
}


int main() {
    char input = getInput();

    printf("Input is: %c\n", input);
}
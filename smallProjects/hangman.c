#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int randomizeWord(int n) { 
    srand(time(NULL));
    return (rand() % (n + 1));
}

char* copyString(char s[])
{
    char* s2;
    s2 = (char*)malloc(20);

    strcpy(s2, s);
    return (char*)s2;
}

char askInput() {
    char input;
    printf("pick a letter:");
    scanf("%s", &input);
    return input;
}

int checkContained(char input, char* word, char *foundByPlayer){ 
    
    printf("check: %s, \n", *foundByPlayer);

    int len = sizeof(word);
    for (int i = 0; i < len; i++ ){
        if (input == word[i]) {
            printf("Correct!\n");

            return i;
        }
    }

    return -1;
} 

int main() { 

    char possibleWords[][20] = {"watch", "truck", "tree", "computer", "c sucks", "i wanna go home" };
    int random = randomizeWord(sizeof(possibleWords) / sizeof(possibleWords[0])); 
    char* currentWord;
    char foundByPlayer[200] = {}; 
    
    currentWord = copyString(possibleWords[random]); 


    //

    for (int letter = 0; letter < strlen(currentWord); letter++)
    {
        foundByPlayer[letter] = '_' ;
    }

    printf("%s\n", currentWord);

    printf("%s\n", foundByPlayer); 



    int errors = 0;
    bool gameIsPlaying = true;      



    while (gameIsPlaying)
    {
        char input = askInput();

        //checkInputInCurrentWord
        
        if (sizeof(input) == 1)
        {
            if (checkContained(input, currentWord, *foundByPlayer) >= 0)
            {
                printf("gg\n");
                //add to the list of found characters
            }
            
        }
        
        //display error

        /* 
        if wrong
            tell player 
            increase errors 

        else:
            show _______ with found letter 
            
            display errors
        
        if letters > 1 
            "are you sure this is your guess?"
                if yes check if it's the same word
                    if correct: 
                        win
                    else:
                        lose
                if no restart "round"
        if 0 letters reamin win
        

        
        
            */
    }
    

    return 0;
}
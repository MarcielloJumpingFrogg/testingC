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


void separate() {
    int linelenght = 15;
    printf("\n");
    for (int i = 0; i < linelenght; i ++){
        printf("~");
    }
    printf("\n\n");
}



void normalize(char *target) {

    for (int i = 0; *(target + i) != '\0'; i++) {
        if (*(target + i) >= 65 && *(target + i) <= 90)
        {
            *(target + i) = (*(target + i)) + 32;
        }
    }
}

int checkAlpha(char *letter) {
    if(*letter >= 65 && *letter <= 90)
    {
        normalize(&(*letter));
        printf("%c\n",*letter);
        return true;
    }

    if(*letter >= 97 && *letter <= 122)
    {
        return true;
    }

    return false;
}

char askInput() {
    char input;
    

    while(true) {



        printf("\nInsert a char:");
        scanf(" %c", &input);

        if(input == ' ' || input == '\n')
        {
            printf("\nEmpty space, insert another character. \n");
        }
        else{
            
            if(checkAlpha(&input)) {          
                return input;

            }
            else {
                printf("\ninvalid\n");
            }

        }
    }
}


int checkContained(char input, char* word, char *foundByPlayer, int *errors){ 
    

    bool foundSomething = false;

    int len = strlen(word);
    for (int i = 0; i <= len; i++ ){
        if (input == word[i]) {

            if(!foundSomething)
            {
                printf("Correct!\n");
            }
            
            foundSomething = true;

            *(foundByPlayer + i) = input;

            
        }
    }

    if (!foundSomething)
    {
        *errors = *errors + 1;
        printf("Wrong, you have made %d errors\n", *errors);
    }


} 


int checkAllCharactersFound(char *foundByPlayer) {
    for(int i = 0; *(foundByPlayer + i ) != '\0'; i++) {
        if(*(foundByPlayer + i) == '_')
        {
            return false;
        }
    }
    return true;
}


char getTextFromFile(char (*possibleWords)[100], int *size) {
    FILE *fpointer;

    fpointer = fopen("txtForHangman.txt", "r");
    
    char string[100];

    if(fpointer != NULL) {
        while (fgets(string, 100 ,fpointer))
        {
            strcpy(possibleWords[*size], string);   // same as: strcpy(*(possibleWords + numberOfWords), string); 

            (*size) = (*size) + 1;
        }
        

    }
}


int main() { 

    char possibleWords[100][100];  //= {"watch", "truck", "tree", "computer", "c sucks", "i wanna go home" };
    int size = 0;
    getTextFromFile(possibleWords, &size);

    /* for (int i = 0; i < size; i ++) {
        printf("%s\n", possibleWords[i]);
    } */

    int random = randomizeWord(size); 
    char* currentWord;
    char foundByPlayer[200] = {};  
    
    currentWord = copyString(possibleWords[random]); 

    normalize(&currentWord[0]);

    //printf("currentWord: %s\n", currentWord);

    separate();

    for (int letter = 0; letter < strlen(currentWord) - 1; letter++)
    {

        if(currentWord[letter] == ' '){
            foundByPlayer[letter] = ' ';
        }
        else{
            foundByPlayer[letter] = '_' ;
        }
    }


    printf("%s\n", foundByPlayer); 



    int errors = 0;
    int gameOver = 8;
    bool gameIsPlaying = true;      



    while (gameIsPlaying)
    {

        
        char input = askInput();
        
        if (sizeof(input) == 1)
        {
            checkContained(input, currentWord, &foundByPlayer[0], &errors);
            
            printf("%s\n", foundByPlayer);

            if(checkAllCharactersFound(&foundByPlayer[0]))
            {
                separate();
                printf("\n\nYou Won! GG!\n\n\n");
                separate();
                gameIsPlaying = false;
            }
            
            if (errors >= gameOver) {
                separate();
                printf("\n\nGAME OVER, YOU LOST \n\n\n");
                separate();
                gameIsPlaying = false;
            }
        }

    }
    

    return 0;
}
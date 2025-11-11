#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct sudokuTemplate
{
    int horizontalGroup;
    int verticalGroup;
    int blockGroup;
    char possibleCharacters[10];
    char confirmedChar;
};


void getInitialSudokuFromOneLine(struct sudokuTemplate (*destination)[9]);

void visualizeSudoku(struct sudokuTemplate (*sudoku)[9]);

void separateByGroups(struct sudokuTemplate (*sudoku)[9]);

void cleanPossibleCharsWholeTable(struct sudokuTemplate (*sudoku)[9]);

void cleanPossChars(struct sudokuTemplate (*sudoku)[9], int i, int j);

void insertSinglePossChar(struct sudokuTemplate (*sudoku)[9]);

void wholeTableDebug(struct sudokuTemplate (*sudoku)[9]);

void checkHiddenSingleCharsInBlocks(struct sudokuTemplate (*sudoku)[9]);


int copyWithout(int *array, int num);

int main() {
    bool resolving = true;

    struct sudokuTemplate sudoku[9][9];

    getInitialSudokuFromOneLine(sudoku);

    separateByGroups(sudoku);

    visualizeSudoku(sudoku);

    cleanPossibleCharsWholeTable(sudoku);

    while(resolving) {
        insertSinglePossChar(sudoku); 
        //wholeTableDebug(sudoku);
    }


    
    
}

void copyWithoutChar(char *array, char element) {

    if(array[0] == '0') {
        return;
    }

    char *newArray = malloc(sizeof(array));
    int counter = 0; 
    
    for (int i = 0 ; i<9; i++) {
        if(array[i] != element) {
            newArray[counter] = array[i];
            counter++;
        }
    }
    newArray[counter + 1] = '\0';

        
    strcpy(array, newArray);
    free(newArray);
}


void debugPossChar(struct sudokuTemplate (*sudoku)[9], int i, int j) {

    if(sudoku[i][j].possibleCharacters[0] == '0') {
        return;
    }

    printf("Remaining possible Characters at i[%d] j[%d]: ", i, j);
    for(int x = 0; sudoku[i][j].possibleCharacters[x] != '\0'; x++) {
        printf(" %c ", sudoku[i][j].possibleCharacters[x]);
    }

    printf("\n");
}

void wholeTableDebug(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0 ; j < 9; j++) {
            debugPossChar(sudoku, i, j);
        }
    }
}


int horizontalRemovalOfPossChars(struct sudokuTemplate (*sudoku)[9], int coord, char toRemove) {
    for(int i = 0; i < 9; i++){
        copyWithoutChar(sudoku[coord][i].possibleCharacters, toRemove);
    }
}

int verticalRemovalOfPossChars(struct sudokuTemplate (*sudoku)[9], int coord, char toRemove) {
    for(int j = 0; j < 9; j++){
        copyWithoutChar(sudoku[j][coord].possibleCharacters, toRemove);
    }
}

int blockRemovalOfPossChars(struct sudokuTemplate (*sudoku)[9], int group, char toRemove) {
    for (int i = 0 ; i < 9; i++) {
        for (int j = 0; j < 9; j++ ) {
            if (sudoku[i][j].blockGroup == group) {
                copyWithoutChar(sudoku[i][j].possibleCharacters, toRemove);
            }
        }
    }
}


void cleanPossChars(struct sudokuTemplate (*sudoku)[9], int i, int j) {
    char toRemove = sudoku[i][j].confirmedChar;
    int groupOfConfirmedChar = sudoku[i][j].blockGroup;
    
    horizontalRemovalOfPossChars(sudoku, i, toRemove);
    verticalRemovalOfPossChars(sudoku, j , toRemove);
    blockRemovalOfPossChars(sudoku, groupOfConfirmedChar, toRemove);
}



void cleanPossibleCharsWholeTable(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j].confirmedChar >= 49 && sudoku[i][j].confirmedChar <= 57) {
                //printf("confirmed char for i[%d] and j[%d] is : %c \n", i, j, sudoku[i][j].confirmedChar);
                cleanPossChars(sudoku, i, j);
                
            }//debugPossChar(sudoku,i,j);
        }
    }

    //wholeTableDebug(sudoku);
}



void insertSinglePossChar(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(strlen(sudoku[i][j].possibleCharacters) == 1 && sudoku[i][j].possibleCharacters[0] != '0') {
                printf("single char: %c\n",sudoku[i][j].possibleCharacters[0]);
                sudoku[i][j].confirmedChar = sudoku[i][j].possibleCharacters[0];
                strcpy(sudoku[i][j].possibleCharacters, "0");

                printf("debug: i = %d, j = %d \n", i, j);
                printf("poss.chars = %c\n", sudoku[i][j].possibleCharacters[0]);
                
                cleanPossChars(sudoku, i, j);

                visualizeSudoku(sudoku);

            }
        }
    }
}

void checkHiddenSingleCharsInBlocks(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i = i + 3) {
        for (int j = 0; j < 9; j = j + 3) {
            //viaggia di gruppo in gruppo //   sinistra => destra && alto => basso

            char charsToFind = "123456789";

            for (int k = 0; k < 3; k++) {
                for (int y = 0; y < 3; y++) {
                    //viaggia interno ad un blocchetto
                    
                }
                printf("\n");
            }
                printf("\n");
            
        }
    }
}




void getInitialSudokuFromOneLine(struct sudokuTemplate (*destination)[9]) {
    char string[] = "..7..93..4..7.81..1...3..4..5...78.6....41.9....6....5......76.........8.89......";
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (string[counter] == '.'){
            
                strcpy(destination[i][j].possibleCharacters, "123456789");
            }
            else {
                strcpy(destination[i][j].possibleCharacters, "0\0");
            }
            
            destination[i][j].confirmedChar = string[counter];

            counter++;
        }
    }
}


void separateByGroups(struct sudokuTemplate (*sudoku)[9]) {


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            
            sudoku[i][j].horizontalGroup = i;
            sudoku[i][j].verticalGroup = j;

            sudoku[i][j].blockGroup = 0;


            //separating by the coordinates since the order is 012345678 i add the coordinates
            //it's the only way i found and i don't know how to write it cleaner
            if (i >= 3 && i <= 5){
                sudoku[i][j].blockGroup += 1;
            }
            else{
                if(i >= 6){
                    sudoku[i][j].blockGroup += 2;
                }
            }

            if (j >= 3 && j <= 5){
                sudoku[i][j].blockGroup += 3;
            }
            else{
                if(j >= 6){
                    sudoku[i][j].blockGroup += 6;
                }
            }

            //set horizontal j
            //set vertical i

            //add the 2 differences in coords from i and j
        }
    }
}



void visualizeSudoku(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%c ", sudoku[i][j].confirmedChar);
            if( j ==2  || j == 5) {
                printf(" | ");
            }
        }
        printf("\n");

        if(i == 2 || i == 5) {
            for ( int x = 0; x < 23; x++) {
                if (x == 7 || x == 16){
                    printf("+");
                }
                else{
                    printf("-");
                }
            }
            printf("\n");
            //printf("------------------------\n");
        }

    }
    printf("\v");
}

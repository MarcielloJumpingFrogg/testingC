#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void getInitialSudokuFromOneLine(char destination[9][9]);
void copyWithoutChar(char *array, char element);

void visualizeSudoku(char sudoku[9][9]);

void checkGameStatus(char sudoku[9][9], bool *resolving); 
void recursiveInsertion(char sudoku[9][9]);

int main() {
    char sudoku[9][9];
    getInitialSudokuFromOneLine(sudoku);
    visualizeSudoku(sudoku);
    recursiveInsertion(sudoku);
}

void getInitialSudokuFromOneLine(char destination[9][9]) {
    char string[] = "..7..93..4..7.81..1...3..4..5...78.6....41.9....6....5......76.........8.89......";
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
           
            destination[i][j] = string[counter];
            counter++;
        }
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


void visualizeSudoku(char sudoku[9][9]) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%c ", sudoku[i][j]);
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
        }

    }
    printf("\v");
}

void checkGameStatus(char sudoku[9][9], bool *resolving) {
    for (int i = 0; i < 9; i++ ){
        for (int j = 0; j < 9; j++){
            if (sudoku[i][j] == '.') {
                return;
            }
        }
    }
    *resolving = false;
}



void verticalCharsFound(char sudoku[9][9], int xCoord, char *possChars) {
    for (int i = 0; i < 9; i++) {
        copyWithoutChar(possChars, sudoku[i][xCoord]);
    }
}

void horizontalCharsFound(char sudoku[9][9], int yCoord, char *possChars) {
    for (int i = 0; i < 9; i++) {
        copyWithoutChar(possChars, sudoku[yCoord][i]);
    }
}

void blockCharsFound(char sudoku[9][9], int xCoord, int yCoord, char *possChars) {
    int xfirstCoord = 3 * floor(xCoord/3);
    int yfirstCoord = 3 * floor(yCoord/3);
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(xfirstCoord + i != xCoord || yfirstCoord + j != yCoord)
            {
                copyWithoutChar(possChars, sudoku[i][xCoord]);
            }
                
        }
    }
}



void getPossibleChars(char sudoku[9][9], int xCoord, int yCoord, char *possChars) {
    verticalCharsFound(sudoku, xCoord , possChars);
    horizontalCharsFound(sudoku, yCoord, possChars);
    blockCharsFound(sudoku, xCoord, yCoord, possChars);
}

void recursiveInsertion(char sudoku[9][9]) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if(sudoku[i][j] == '.'){
                char possChars[9] = {"123456789"};
                getPossibleChars(sudoku, i, j, possChars);
                printf("i[%d], j[%d], poss: %s \n", i, j, possChars);
            }

        }
    }

    //getPossibleChars and then use one of them to insert and blabla
    //qua voglio inserire uno dei caratteri che sono disponibili all'interno di possChars 
    //
    //
    //
    //e andare avanti fino a quando non trovo che non posso inserire altri caratteri 
}


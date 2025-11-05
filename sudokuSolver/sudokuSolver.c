#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct sudokuTemplate
{
    int horizontalGroup;
    int verticalGroup;
    int blockGroup;
    int possibleCharacters[9];
    char confirmedChar;
};


void getInitialSudokuFromOneLine(struct sudokuTemplate (*destination)[9]);

void visualizeSudoku(struct sudokuTemplate (*sudoku)[9]);

void separateByGroups(struct sudokuTemplate (*sudoku)[9]);

void cleanPossibleCharsWholeTable(struct sudokuTemplate (*sudoku)[9]);


int copyWithout(int *array, int num);

int main() {
    struct sudokuTemplate sudoku[9][9];

    getInitialSudokuFromOneLine(sudoku);

    separateByGroups(sudoku);

    visualizeSudoku(sudoku);

    cleanPossibleCharsWholeTable(sudoku);
}

int copyWithout(int *array, int num) {
    int *newArray = malloc((sizeof(*array) - 1)*sizeof(int));
    int counter = 0;
    for (int i = 0; i < sizeof(*array); i++) {
        if(array[i] != num){
            newArray[counter] = array[i];
            counter++;
        }
    }

    /* 
        array from a to z is array[n]
            
    */

    return newArray;//cant return an array bcs it's multiple characters
}


void removeCharFromHorGroup(struct sudokuTemplate (*sudoku)[9], int coord, int num) {
    for(int j = 0; j < 9; j++){
        sudoku[coord][j].possibleCharacters;
    }
}


void cleanPossibleCharsWholeTable(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j].confirmedChar != '.') {
                char toRemove = sudoku[i][j].confirmedChar;
                int intToRemove = toRemove - '0';
                removeCharFromHorGroup(sudoku, i, intToRemove);
            }
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
}


void getInitialSudokuFromOneLine(struct sudokuTemplate (*destination)[9]) {
    char string[] = "..7..93..4..7.81..1...3..4..5...78.6....41.9....6....5......76.........8.89......";
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (string[counter] == '.'){
                //strcpy(destination[i][j].possibleCharacters[], {'1', 2});

                for (int num = 1; num <= 9; num++) {
                    destination[i][j].possibleCharacters[num] = num;
                }
                destination[i][j].confirmedChar = '.';
            }
            else {
                destination[i][j].confirmedChar = string[counter];
            }
            //destination[i][j] = string[counter];
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
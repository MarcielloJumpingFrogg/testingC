#include <stdio.h>
#include <string.h>



struct sudokuTemplate
{
    int horizontalGroup;
    int verticalGroup;
    int blockGroup;
    char possibleCharacters[10];
    char confirmedChar;
};


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
                
            }
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


void insertChar(struct sudokuTemplate(*sudoku)[9], int i, int j) {
    sudoku[i][j].confirmedChar = sudoku[i][j].possibleCharacters[0];
    strcpy(sudoku[i][j].possibleCharacters, "0");
    cleanPossChars(sudoku, i , j);
}

void checkGameStatus(struct sudokuTemplate (*sudoku)[9], bool *resolving) {
    for (int i = 0; i < 9; i++ ){
        for (int j = 0; j < 9; j++){
            if (sudoku[i][j].confirmedChar == '.') {
                return;
            }
        }
    }
    *resolving = false;
}

int main() {

}



void recursiveInsertion(struct sudokuTemplate (*sudoku)[9]) {
    //qua voglio inserire uno dei caratteri che sono disponibili all'interno di possChars 
    //
    //e andare avanti fino a quando non trovo che non posso inserire altri caratteri 
}

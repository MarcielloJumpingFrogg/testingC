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




void visualizeBlockGroups(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i = i + 3) {
        for (int j = 0; j < 9; j = j + 3) {
            //viaggia di gruppo in gruppo // alto => basso && sinistra => destra

            for (int k = 0; k < 3; k++) {
                for (int y = 0; y < 3; y++) {
                    //viaggia interno ad un blocchetto
                    printf(" %c ", sudoku[i + k][j + y].confirmedChar);
                }
                printf("\n");
            }
                printf("\n");
            
        }
    }
}



int main() {

    struct sudokuTemplate sudoku[9][9];
    
    getInitialSudokuFromOneLine(sudoku);

    separateByGroups(sudoku);

    visualizeSudoku(sudoku);

    visualizeBlockGroups(sudoku);

}
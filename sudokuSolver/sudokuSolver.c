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

//secondo te se mi metto ad ascoltare musica mi dice qualcosa?
//non e' come quella la dici? 


void getInitialSudokuFromOneLine(struct sudokuTemplate (*destination)[9]);

void visualizeSudoku(struct sudokuTemplate (*sudoku)[9]);

void separateByGroups(struct sudokuTemplate (*sudoku)[9]);

void cleanPossibleCharsWholeTable(struct sudokuTemplate (*sudoku)[9]);

void cleanPossChars(struct sudokuTemplate (*sudoku)[9], int i, int j);

void insertSinglePossChar(struct sudokuTemplate (*sudoku)[9]);

void wholeTableDebug(struct sudokuTemplate (*sudoku)[9]);

void findCandidateInBlock(struct sudokuTemplate (*sudoku)[9]);



int main() {
    bool resolving = true;

    struct sudokuTemplate sudoku[9][9];

    getInitialSudokuFromOneLine(sudoku);

    separateByGroups(sudoku);

    visualizeSudoku(sudoku);

    cleanPossibleCharsWholeTable(sudoku);

    while(resolving) {
        insertSinglePossChar(sudoku); 
        findCandidateInBlock(sudoku);
        /*insertSinglePossChar(sudoku);
        
        
         
        findCandidateInBlock(sudoku);
         insertSinglePossChar(sudoku); 
        findCandidateInBlock(sudoku);
        insertSinglePossChar(sudoku); 
        findCandidateInBlock(sudoku);
        insertSinglePossChar(sudoku); 
        findCandidateInBlock(sudoku);
        insertSinglePossChar(sudoku); */
        resolving = false;
    }
    //wholeTableDebug(sudoku);
    

    
    
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


void insertChar(struct sudokuTemplate(*sudoku)[9], int i, int j);


int positionContained(char *array, char element) {
    for (int i = 0; array[i] != '\0'; i++) {
        if(array[i] == element){
            return i;
        }
    }
    return -1;
}


void debugPossChar(struct sudokuTemplate (*sudoku)[9], int i, int j) {

    if(sudoku[i][j].confirmedChar != '.') {
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


void findHidden(struct sudokuTemplate (*sudoku)[9], int i, int j, char *array, int coordX, int coordY ) {
  
    for(int x = 0; x < 3; x++) {
        for (int y = 0; y < 3 ; y++) {

            if(sudoku[i + x][j + y].confirmedChar == '.') {
                printf("the current array is %s", array);
                printf("we are working on: i[%d], j[%d]\n", coordX, coordY   );
                for (int n = 0; sudoku[i + x][j + y].possibleCharacters[n] != '\0'; n++) {
                    if((i+x) != coordX || (j+y) != coordY ) {
                        int result = positionContained(array, sudoku[i + x][j + y].possibleCharacters[n]);
                        printf ("the result is: %d, from the line of poss chars of :%s, in the array: %s\n", result, sudoku[i + x][j + y].possibleCharacters, array);
                        printf("")
                        //what do you mean, positionContained in here, isnt it supposed to do it's own stuff
                        //this way i am changing the value of x and y, which means i am rescribing on top of something else since
                        //the coords are thrown off
                        if(result != -1) {
                            printf("the poss char is: %c, while the coords of said char are: 1[%d] 2[%d] \n",sudoku[i + x][j + y].possibleCharacters[result], i + x, j + y);
                            printf("idk: i[%d] x[%d] j[%d] y[%d]", i,x,j,y);
                            printf("Coords: i[%d] j[%d] (conf: %c)",coordX,coordY, sudoku[coordX][coordY].confirmedChar);
                            printf("array: %s, char: %c\n", array, array[result]);
                            copyWithoutChar(array, array[result]);
                            printf("After: %s \n", array);
                        }
                        
                    }
                }
            }

            //check array in array
            //modify the pointer to the COPY of the possible chars, and then once it finishes
            // i will check the lenght 
            // if len == 1 then i will change the conf char to that ecc 
            //i wanna sleep now
        }
    }

    
}

void findCandidateInBlock(struct sudokuTemplate (*sudoku)[9]) {  
    for (int i = 0; i < 9; i = i + 3) {         // Big block
        for (int j = 0; j < 9; j = j + 3) {     // Big block


            for (int x = 0; x < 3; x ++) {          //small block
                for ( int y = 0; y < 3; y ++) {     //small block
                    //sum toghether to obtain the coords

                    if(sudoku[i + x][j + y].confirmedChar =='.') {
                        char *copyOfCandidate = malloc(strlen(sudoku[i + x][j + y].possibleCharacters));
                        strcpy(copyOfCandidate,  sudoku[i + x][j + y].possibleCharacters);
//                        printf("the copy is: %s \n", copyOfCandidate);
                        int coordX = i + x;
                        int coordY = j + y;
                        findHidden(sudoku, i, j, copyOfCandidate,coordX, coordY);
                        //printf("copy[%s] at: i[%d]j[%d]\n", copyOfCandidate , i  + x ,j + y);
                        if(strlen(copyOfCandidate) == 1) {
                            printf("found at i[%d]j[%d]\n",coordX, coordY);
                            insertChar(sudoku, coordX, coordY);
                            cleanPossChars(sudoku, coordX, coordY);
                            visualizeSudoku(sudoku);
                        }
                        free(copyOfCandidate);
                    }

                }
            }

    }

}}


/* 
    TODO: should be: insert single poss {if len == 1 allora insert}

    and change the other part of the function with:
    
    function removeLine&Col
    {
        blabla
    }
        
*/


void insertChar(struct sudokuTemplate(*sudoku)[9], int i, int j) {
    sudoku[i][j].confirmedChar = sudoku[i][j].possibleCharacters[0];
    strcpy(sudoku[i][j].possibleCharacters, "0");
}


void insertSinglePossChar(struct sudokuTemplate (*sudoku)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(strlen(sudoku[i][j].possibleCharacters) == 1 && sudoku[i][j].possibleCharacters[0] != '0') {
                printf("single char: %c\n",sudoku[i][j].possibleCharacters[0]);
                insertChar(sudoku, i, j);

                printf("debug: i = %d, j = %d \n", i, j);
                printf("poss.chars = %c\n", sudoku[i][j].possibleCharacters[0]);
                
                cleanPossChars(sudoku, i, j);   //TODO: cleanPossChars is a great example of why insertSingleChar should be global #facepalm

                visualizeSudoku(sudoku);

            }
        }
    }
}



/* void checkHiddenSingleCharsInBlocks(struct sudokuTemplate (*sudoku)[9]) {
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
} */




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

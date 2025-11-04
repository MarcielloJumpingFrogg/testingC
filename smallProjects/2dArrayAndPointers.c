#include <stdio.h>

int numTest() {
    int matrix[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

        int (*ptr)[3] = {matrix};

        
        for(int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", ptr[i][j]); //printf("%d ", *(ptr[i] + j)) //printf("%d ", *(*(ptr + i) + j))
            }
            printf("\n");
        }
}

void complementaryStringThing(char (*test)[20]) {
    for (int i = 0; i < 3; i++) {
        printf("%s \n", test[i]);
        
    }
}


void stringTest(){
    char matrix[20][20] = {"ciao", "bella", "ciaoo"};


    /* char (*pointer)[20] = matrix;

    for (int i = 0; i < 3; i++) {
        printf("%s \n", pointer[i]);
    } */

    complementaryStringThing(matrix);
}


int main() {
    stringTest();
}
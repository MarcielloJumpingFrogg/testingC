#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyWithout(int *array, int num) {
    int *newArray = malloc((sizeof(*array) - 1)*sizeof(int));
    int counter = 0;
    for (int i = 0; i < sizeof(*array); i++) {
        if(array[i] != num){
            newArray[counter] = array[i];
            counter++;
        }
    }

    

    for (int i = 0; i < sizeof(*array); i ++) {
        array[i] = newArray[i];
        printf("%d ", array[i]);
    }
    printf("\n");

    /* 
        array from a to z is array[n]
            
    */

    

    //return newArray;//cant return an array bcs it's multiple characters
}


void copyStringWithout(char *array, char toRemove) {
    char newArray[10];
    printf("newArray: %s\n", newArray);
    int counter = 0;
    for(int i = 0; array[i] != '\0'; i++) {
        if(array[i] != toRemove) {
            newArray[counter] = array[i];
            counter++;
        }
    } 


    strcpy(array, newArray);
}


int main() {

    char array[] = {"123456789"};

    printf("string : %s\n", array);

    copyStringWithout(array, '5');

    for (int i = 0; i < 9; i++) {
        printf("%c ", array[i]);
    }

    printf("\nstring: %s\n", array);


    printf("\n");

}
#include <stdio.h>
#include <stdlib.h>

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

int main() {

    int array[] = {1,2,3,4,5,6,7,8,9};

    copyWithout(array, 5);

}
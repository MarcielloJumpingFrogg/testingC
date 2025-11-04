#include <stdio.h>


void call(char *pointer) {

    for (int i = 0; *(pointer + i) != '\0'; i++) {
        printf("%c", *(pointer + i));
    }
    printf("\n");
}



int main() {
    char test[] = "hello";

    call(&test[0]);
}
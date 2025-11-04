#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* copyString(char s[])
{
    char* s2;
    s2 = (char*)malloc(20);

    strcpy(s2, s);
    return (char*)s2;
}

char getTxtFromFile(char (*point)[100]) {
    FILE *fpointer;

    fpointer = fopen("txtForHangman.txt", "r");

    printf("size: %ld\n", sizeof(*fpointer) / sizeof(fpointer[0]));
    
    char string[100];

    if(fpointer != NULL) {
        int numberOfWords = 0;
        while (fgets(string, 100 ,fpointer))
        {            
            strcpy(point[numberOfWords], string) ;

            numberOfWords++;
        }
        fclose(fpointer);
    }
}


int main() {
    char pw[100][100];

    getTxtFromFile(pw);

}
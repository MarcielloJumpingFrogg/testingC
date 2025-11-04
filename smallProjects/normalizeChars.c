#include <stdio.h>


void normalize(char *target) {

    for (int i = 0; *(target + i) != '\0'; i++) {
        if (*(target + i) >= 65 && *(target + i) <= 90)
        {
            *(target + i) = (*(target + i)) + 32;
        }
    }
}


int main() {

    char string[] = "jojo SiWa SuckS";

    normalize(&string[0]);

    printf("string: %s\n", string);
}

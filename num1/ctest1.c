#include <stdio.h>
#include <math.h>

int main() {
    double num;
    printf("give me something to work with: ");
    scanf("%lf", &num);

    double hallo = sqrt(num);

    printf("%lf\n", hallo);
}
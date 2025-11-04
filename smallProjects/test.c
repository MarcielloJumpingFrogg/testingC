// C program to copy the string using
// strcpy function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to copy the string
char* copyString(char s[])
{
    char* s2;
    s2 = (char*)malloc(20);

    strcpy(s2, s);
    return (char*)s2;
}

// Driver Code
int main()
{
    char s1[20] = "GeeksforGeeks";
    char* s2;

    // Function Call
    s2 = copyString(s1);
    printf("%s", s2);
    return 0;
}
#include <stdio.h>
#include <string.h>

/* 
    structs are built similarly to classes, however they can only contain data

    so no functions are allowed

    they can however be built "funnier"
    ex: myStruct = {data1, data2, data3};


*/



struct testing
{
    int number;
    char name[10]; 
}; 


int main() { 
    
    struct testing memory[100];

    memory[0].number = 3;
    strcpy(memory[0].name, "Paolo");

    memory[1].number = 12;
    strcpy(memory[1].name, "Luca");

    memory[2].number = 1;
    strcpy(memory[2].name, "Scemo");

    //struct testing memory[1] = {12, "luca"};

    //struct testing memory[2] = {3, "scemoScemo"};


    for (int i = 0; i < 3; i++){
        printf("%s has %d neurons\n", memory[i].name, memory[i].number);
    }

}
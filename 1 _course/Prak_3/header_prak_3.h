#pragma once 

using namespace std;
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int typeitem;

struct typeX{
    unsigned int n = 0;
    typeitem* x = nullptr;
    typeX(int n1){
        n = n1;
        x = (typeitem*)malloc(n * sizeof(typeitem));
    } 
    typeX() { n = 0; }
};

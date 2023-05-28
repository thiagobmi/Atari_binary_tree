#ifndef ARRAYS_H
#define ARRAYS_H 1

#include"base.h"

char *newCharArr(int size);
char **newChar2dArr(int rows, int cols);
char ***newChar3dArr(int layers, int rows, int cols);
char *strToLower(char *str);

#endif
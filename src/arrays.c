#include"../include/arrays.h"

char *newCharArr(int size)
{
    char *arr = malloc(sizeof(char) * size);
    return arr;
}

char **newChar2dArr(int rows, int cols)
{
    char **arr = malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; i++)
        arr[i] = newCharArr(cols);

    return arr;
}

char ***newChar3dArr(int layers, int rows, int cols)
{
    char ***arr = malloc(sizeof(char **) * layers);
    for (int i = 0; i < layers; i++)
        arr[i] = newChar2dArr(rows, cols);

    return arr;
}

char *strToLower(char *str)
{
    char *buffer = newCharArr(strlen(str) + 1);
    strcpy(buffer, str);

    for (int i = 0; i < strlen(str); i++)
        buffer[i] = tolower(buffer[i]);

    return buffer;
}
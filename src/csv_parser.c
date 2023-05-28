#include"../include/csv_parser.h"

char ***parseCSV(char *file_path, int *num_lines)
{
    FILE *fp;
    char row[MAXLINES][LINELENGHT], pointer;
    char ***field = newChar3dArr(MAXLINES, FIELDS, FIELDLENGHT);
    int field_count = 0, flag = 0, lines, lenght;

    fp = fopen(file_path, "r");

    if (fp == NULL)
        return NULL;

    for (lines = 0; feof(fp) != 1; lines++)
    {
        pointer = ' ';
        for (lenght = 0; pointer != '\n' && feof(fp) != 1; lenght++)
        {
            fscanf(fp, "%c", &pointer);
            row[lines][lenght] = pointer;
        }
    }

    for (int i = 0; i < lines; i++)
    {
        field_count = 0;
        for (int j = 0; j < strlen(row[i]); j++)
        {
            if (row[i][j] == '\n')
            {
                flag = 0;
                break;
            }
            if (row[i][j] == '"')
                switch (flag)
                {
                case 1:
                    flag = 0;
                    break;
                case 0:
                    flag = 1;
                    break;
                }

            if ((row[i][j] == ',') && flag == 0)
                field_count++;

            else if (row[i][j] != '"')
                strncat(field[i][field_count], &row[i][j], 1);
        }
    }

    *num_lines = lines;
    return field;
}
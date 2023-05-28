#ifndef FILEHANDLER_H
#define FILEHANDLER_H 1

#include"game_tree.h"
#include"csv_parser.h"

node_t *loadCSV(node_t *root, char *file_path);
node_t *loadImageLinks(node_t *root, char *file_path);
void writeTreeAux(node_t *root, FILE *fp);
void writeTree(node_t *root, char *file_path);
void writeImageLinksAux(node_t *root, FILE *fp);
void writeImageLinks(node_t *root, char *file_path);

#endif
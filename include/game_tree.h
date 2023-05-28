#ifndef GAMETREE_H
#define GAMETREE_H 1

#include"arrays.h"

struct game_s
{
    char *title;
    char *creators;
    char *publishers;
    char *year;
    char *genre;
    char *notes;
    char *game_image;
    char *box_image;
};

typedef struct game_s game_t;

struct node_s
{
    game_t *game;
    struct node_s *left;
    struct node_s *right;
};

typedef struct node_s node_t;

node_t *newNode(char **fields);
node_t *insertTree(node_t *root, char **fields);
node_t *findNodebyTitle(node_t *root, char *title);
node_t *freeTree(node_t *root);
node_t *removeNode(node_t *root, char *key);
node_t *addNewGame(node_t *root);
node_t *getPointerbyTitle(node_t *root);
int treeIsEmpty(node_t *root);
int belongsToTree(node_t *root, char *key);
void freeNode(node_t *node);
void queryAux(node_t *root, char *key, int switcher);
void queryTree(node_t *root);
void printGameswithImage(node_t *root);
void changeData(node_t *node);
void printGames(node_t *root);
void openImage(node_t *node);
void printNode(node_t *root);
void addImagetoGame(node_t *node);

#endif
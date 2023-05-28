#include"../include/file_handler.h"

void writeTreeAux(node_t *root, FILE *fp)
{
    if (root != NULL)
    {
        char buffer[FIELDLENGHT];

        if (strstr(root->game->title, ",") != NULL)
            fprintf(fp, "\"%s\",", root->game->title);
        else
            fprintf(fp, "%s,", root->game->title);

        if (strstr(root->game->creators, ",") != NULL)
            fprintf(fp, "\"%s\",", root->game->creators);
        else
            fprintf(fp, "%s,", root->game->creators);

        if (strstr(root->game->publishers, ",") != NULL)
            fprintf(fp, "\"%s\",", root->game->publishers);
        else
            fprintf(fp, "%s,", root->game->publishers);

        if (strstr(root->game->year, ",") != NULL)
            fprintf(fp, "\"%s\",", root->game->year);
        else
            fprintf(fp, "%s,", root->game->year);

        if (strstr(root->game->genre, ",") != NULL)
            fprintf(fp, "\"%s\",", root->game->genre);
        else
            fprintf(fp, "%s,", root->game->genre);

        if (strstr(root->game->notes, ",") != NULL)
        {
            strcpy(buffer, root->game->notes);
            buffer[strlen(buffer) - 1] = '\0';
            fprintf(fp, "\"%s\"\n", buffer);
        }
        else
        {
            strcpy(buffer, root->game->notes);
            buffer[strlen(buffer) - 1] = '\0';
            fprintf(fp, "%s\n", buffer);
        }

        writeTreeAux(root->left, fp);
        writeTreeAux(root->right, fp);
    }
}

void writeTree(node_t *root, char *file_path)
{
    FILE *fp;
    fp = fopen(file_path, "w");
    if (fp == NULL)
        return;
    writeTreeAux(root, fp);
    fclose(fp);
}

void writeImageLinksAux(node_t *root, FILE *fp)
{
    if (root != NULL)
    {
        if (root->game->game_image != NULL || root->game->box_image != NULL)
        {
            fprintf(fp, "%s", root->game->title);
            if (root->game->game_image == NULL)
                fprintf(fp, ",,%s\n", root->game->box_image);
            else if (root->game->box_image == NULL)
                fprintf(fp, ",%s,\n", root->game->game_image);
            else
                fprintf(fp, ",%s,%s\n", root->game->game_image, root->game->box_image);
        }
        writeImageLinksAux(root->left, fp);
        writeImageLinksAux(root->right, fp);
    }
}

void writeImageLinks(node_t *root, char *file_path)
{
    FILE *fp;
    fp = fopen(file_path, "w");
    if (fp == NULL)
        return;
    writeImageLinksAux(root, fp);
    fclose(fp);
}

node_t *loadCSV(node_t *root, char *file_path)
{
    int lines = 0;
    char ***games = parseCSV(file_path, &lines);

    if (games == NULL)
        return root;

    if (strstr(games[lines - 1][0], "\0"))
        lines--;

    root=insertTree(root,games[lines/2]);

    for (int i = 0; i < lines; i++)
        root = insertTree(root, games[i]);

    return root;
}

node_t *loadImageLinks(node_t *root, char *file_path)
{
    int lines = 0;
    node_t *temp = NULL;
    char ***links = parseCSV(file_path, &lines);

    if (links == NULL)
        return root;

    if (strstr(links[lines - 1][0], "\0"))
        lines--;

    for (int i = 0; i < lines; i++)
    {
        temp = findNodebyTitle(root, links[i][0]);
        if (temp != NULL)
        {
            if (strcmp(links[i][1], "\0") != 0)
                temp->game->game_image = links[i][1];
            if (strcmp(links[i][2], "\0") != 0)
                temp->game->box_image = links[i][2];
        }
    }

    return root;
}

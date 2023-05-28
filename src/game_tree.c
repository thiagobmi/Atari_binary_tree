#include "../include/game_tree.h"

node_t *newNode(char **fields)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->game = (game_t *)malloc(sizeof(game_t));
    newNode->game->title = fields[0];
    newNode->game->creators = fields[1];
    newNode->game->publishers = fields[2];
    newNode->game->year = fields[3];
    newNode->game->genre = fields[4];
    newNode->game->notes = fields[5];
    newNode->game->game_image = NULL;
    newNode->game->box_image = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node_t *insertTree(node_t *root, char **fields)
{
    if (root == NULL)
        root = newNode(fields);

    else if (strcmp(root->game->title, fields[0]) < 0)
        root->left = insertTree(root->left, fields);

    else if (strcmp(root->game->title, fields[0]) > 0)
        root->right = insertTree(root->right, fields);

    return root;
}

int treeIsEmpty(node_t *root)
{
    if (root == NULL)
        return 1;
    else
        return 0;
}

int belongsToTree(node_t *root, char *key)
{
    if (treeIsEmpty(root))
        return 0;
    else if (root->game->title != NULL)
        return (strcmp(strToLower(root->game->title), strToLower(key)) == 0) || belongsToTree(root->left, key) || belongsToTree(root->right, key);
    else
        return 0;
}

node_t *findNodebyTitle(node_t *root, char *key)
{
    node_t *aux = root;

    if (aux == NULL)
        return NULL;

    else if (strcmp(strToLower(aux->game->title), strToLower(key)) < 0)
        findNodebyTitle(aux->left, key);

    else if (strcmp(strToLower(aux->game->title), strToLower(key)) > 0)
        findNodebyTitle(aux->right, key);
    else
        return aux;
}

void freeNode(node_t *node)
{
    free(node->game->title);
    free(node->game->creators);
    free(node->game->publishers);
    free(node->game->year);
    free(node->game->genre);
    free(node->game->notes);
    if (node->game->game_image != NULL)
        free(node->game->game_image);
    if (node->game->box_image != NULL)
        free(node->game->box_image);
    free(node->game);
    free(node);
}

void queryAux(node_t *root, char *key, int switcher)
{
    if (root == NULL)
        return;
    else
    {
        char *field = NULL;
        char field_name[20];
        switch (switcher)
        {
        case 0:
            field = root->game->title;
            break;
        case 1:
            strcpy(field_name, "Criadores");
            field = root->game->creators;
            break;
        case 2:
            strcpy(field_name, "Editora");
            field = root->game->publishers;
            break;
        case 3:
            strcpy(field_name, "Ano");
            field = root->game->year;
            break;
        case 4:
            strcpy(field_name, "Genero");
            field = root->game->genre;
            break;
        case 5:
            strcpy(field_name, "Notas");
            field = root->game->notes;
            break;
        }

        if (field != NULL)
            if (strstr(strToLower(field), strToLower(key)) != NULL)
            {
                if (switcher != 0)
                    printf("\n\tJogo: %s\n\t%s: %s\n", root->game->title, field_name, field);
                else
                    printf("\n\tJogo: %s\n", root->game->title);
            }
        queryAux(root->right, key, switcher);
        queryAux(root->left, key, switcher);
    }
}

node_t *freeTree(node_t *root)
{
    if (!treeIsEmpty(root))
    {
        freeTree(root->left);
        freeTree(root->right);
        freeNode(root);
    }
    return NULL;
}

void queryTree(node_t *root)
{
    int select;
    char *keyword = newCharArr(FIELDLENGHT);

    if (root == NULL)
        return;
    else
    {
        printf("\n\n\n");
        printf(
            "\nDeseja pesquisar por qual campo?"
            "\n1) Titulo"
            "\n2) Criadores"
            "\n3) Editora"
            "\n4) Ano de lancamento"
            "\n5) Genero"
            "\n6) Notas"
            "\n\n9) Voltar"
            "\nDigite:");

        scanf("%d", &select);
        getchar();
        printf("Digite as palavras chave desejadas:  ");
        fgets(keyword, FIELDLENGHT, stdin);
        keyword[strlen(keyword) - 1] = '\0';
        printf("\nJogos que correspondem a pesquisa:\n");
        queryAux(root, keyword, select - 1);
    }
}

void changeData(node_t *node)
{
    node_t *temp = node;
    if (temp == NULL)
        return;
    char *field = newCharArr(FIELDLENGHT);
    int select = 0;

    printf("\nQual campo deseja alterar?"
           "\n1) Titulo"
           "\n2) Criadores"
           "\n3) Editora"
           "\n4) Ano de lancamento"
           "\n5) Genero"
           "\n6) Notas"
           "\n7) Imagem do jogo"
           "\n8) Imagem da caixa"
           "\n\n9) Voltar\n\n");
    scanf("%d", &select);
    getchar();

    if (select < 9 && select > 0)
    {
        switch (select)
        {
        case 1:
            printf("Digite o novo titulo para o jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->title);
            temp->game->title = field;
            break;
        case 2:
            printf("Digite os novos criadores para o jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->creators);
            temp->game->creators = field;
            break;
        case 3:
            printf("Digite a nova editora para o jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->publishers);
            temp->game->publishers = field;
            break;
        case 4:
            printf("Digite o novo ano de lancamento para o jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->year);
            temp->game->year = field;
            break;
        case 5:
            printf("Digite o novo genero para o jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->genre);
            temp->game->genre = field;
            break;
        case 6:
            printf("Digite as novas notas para %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            free(temp->game->notes);
            temp->game->notes = field;
            break;

        case 7:
            printf("Digite o novo caminho para a imagem do jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            if (temp->game->game_image != NULL)
                free(temp->game->game_image);
            temp->game->game_image = field;
            break;

        case 8:
            printf("Digite o novo caminho para a imagem da caixa do jogo %s: ", temp->game->title);
            fgets(field, FIELDLENGHT, stdin);
            field[strlen(field) - 1] = '\0';
            if (temp->game->box_image != NULL)
                free(temp->game->box_image);
            temp->game->box_image = field;
            break;
        }
    }
}

void printGames(node_t *root)
{
    if (root != NULL)
    {
        printGames(root->left);
        printf("\n\t%s", root->game->title);
        printGames(root->right);
    }
}

node_t *removeNode(node_t *root, char *key)
{
    if (root == NULL)
        return NULL;

    else if (strcmp(strToLower(root->game->title), strToLower(key)) < 0)
        root->left = removeNode(root->left, key);

    else if (strcmp(strToLower(root->game->title), strToLower(key)) > 0)
        root->right = removeNode(root->right, key);

    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            freeNode(root);
            root = NULL;
            printf("\nJogo removido com sucesso!\n");
        }

        else if (root->left == NULL)
        {
            node_t *tmp = root;
            root = root->right;
            freeNode(tmp);
            printf("\nJogo removido com sucesso!\n");
        }

        else if (root->right == NULL)
        {
            node_t *tmp = root;
            root = root->left;
            freeNode(tmp);
            printf("\nJogo removido com sucesso!\n");
        }

        else
        {
            node_t *tmp = root->left;
            while (tmp->right != NULL)
                tmp = tmp->right;

            strcpy(root->game->title, tmp->game->title);
            strcpy(root->game->creators, tmp->game->creators);
            strcpy(root->game->publishers, tmp->game->publishers);
            strcpy(root->game->year, tmp->game->year);
            strcpy(root->game->genre, tmp->game->genre);
            strcpy(root->game->notes, tmp->game->notes);
            if (tmp->game->game_image != NULL)
            {
                if (root->game->game_image == NULL)
                    root->game->game_image = newCharArr(FIELDLENGHT);
                strcpy(root->game->game_image, tmp->game->game_image);
            }
            if (tmp->game->box_image != NULL)
            {
                if (root->game->box_image == NULL)
                    root->game->box_image = newCharArr(FIELDLENGHT);
                strcpy(root->game->box_image, tmp->game->box_image);
            }

            root->left = removeNode(root->left, tmp->game->title);
        }
    }
    return root;
}

void openImage(node_t *node)
{
    int select = 0;
    char *path;

    if (node == NULL)
        return;

    printf("Deseja abrir a imagem da caixa ou do jogo?"
           "\n1) Jogo"
           "\n2) Caixa"
           "\nDigite: ");
    scanf("%d", &select);
    getchar();

    switch (select)
    {
    case 1:
        path = node->game->game_image;
        break;
    case 2:
        path = node->game->box_image;
        break;
    }
    if (path == NULL)
        printf("\n\nNenhuma imagem cadastrada\n\n");

    else
    {
        char command[FIELDLENGHT] = "xdg-open ";
        strcat(command, path);
        system(command);
    }
}

void printNode(node_t *root)
{
    int image_exists[2] = {0, 0};
    char select = '0';

    if (root != NULL)
    {
        printf("\n\tTitulo: %s"
               "\n\tCriadores: %s"
               "\n\tEditora: %s"
               "\n\tAno de lancamento: %s"
               "\n\tGenero: %s"
               "\n\tNotas: %s"
               "\n",
               root->game->title,
               root->game->creators,
               root->game->publishers,
               root->game->year,
               root->game->genre, root->game->notes);

        if (root->game->game_image != NULL)
            printf("\tLink para imagem do jogo: %s\n", root->game->game_image), image_exists[0] = 1;
        if (root->game->box_image != NULL)
            printf("\tLink para imagem da caixa: %s\n", root->game->box_image), image_exists[1] = 1;

        else if (root->game->game_image == NULL && root->game->box_image == NULL)
            printf("\tNenhuma imagem cadastrada\n");

        if (image_exists[0] == 1 || image_exists[1] == 1)
        {
            printf("\n\n\t1) Abrir Imagem");
            printf("\n\tOutro caractere) Voltar\n");
            printf("\tDigite: ");
            scanf("%c", &select);
            getchar();
            if (select == '1')
                openImage(root);
        }
    }
    else
        printf("\nNenhum jogo com esse nome foi encontrado\n");
    printf("\n\n");
}

void addImagetoGame(node_t *node)
{
    int select = 0;
    node_t *temp = node;
    if (temp == NULL)
        return;
    char *path = newCharArr(FIELDLENGHT);

    printf("\n\nDeseja adicionar foto da caixa ou do jogo?"
           "\n1) Jogo"
           "\n2) Caixa"
           "\n3) Ambas"
           "\nDigite: ");

    scanf("%d", &select);
    getchar();

    if (select != 3)
    {
        printf("\nDigite o path da imagem: ");
        fgets(path, FIELDLENGHT, stdin);
        path[strlen(path) - 1] = '\0';

        switch (select)
        {
        case 1:
            temp->game->game_image = path;
            break;
        case 2:
            temp->game->box_image = path;
            break;
        }
    }
    else
    {
        char *path_caixa = newCharArr(FIELDLENGHT);
        printf("\nDigite o path da imagem do jogo: ");
        fgets(path, FIELDLENGHT, stdin);
        path[strlen(path) - 1] = '\0';
        temp->game->game_image = path;

        printf("\nDigite o path da imagem da caixa: ");
        fgets(path_caixa, FIELDLENGHT, stdin);
        path_caixa[strlen(path_caixa) - 1] = '\0';
        temp->game->box_image = path_caixa;
    }
}

void printGameswithImage(node_t *root)
{
    if (root != NULL)
    {
        if (root->game->game_image != NULL || root->game->box_image != NULL)
        {
            printf("\n\t%s", root->game->title);
        }
        printGameswithImage(root->left);
        printGameswithImage(root->right);
    }
}

node_t *addNewGame(node_t *root)
{
    char **game = newChar2dArr(FIELDS, FIELDLENGHT);
    char select;

    printf("\nDigite o nome do novo jogo: ");
    fgets(game[0], FIELDLENGHT, stdin);

    printf("\nDigite os criadores do novo jogo: ");
    fgets(game[1], FIELDLENGHT, stdin);

    printf("\nDigite a editora do novo jogo: ");
    fgets(game[2], FIELDLENGHT, stdin);

    printf("\nDigite o ano de lancamento do novo jogo: ");
    fgets(game[3], FIELDLENGHT, stdin);

    printf("\nDigite o genero do novo jogo: ");
    fgets(game[4], FIELDLENGHT, stdin);

    printf("\nDigite notas do novo jogo: ");
    fgets(game[5], FIELDLENGHT, stdin);

    for (int i = 0; i < FIELDS - 1; i++)
        game[i][strlen(game[i]) - 1] = '\0';

    game[5][strlen(game[5])] = '\0';

    root = insertTree(root, game);

    printf("\nDeseja adicionar imagem? (y = Sim / outro caractere = nao)\n");
    scanf("%c", &select);
    getchar();

    if (select == 'y')
        addImagetoGame(findNodebyTitle(root, game[0]));

    return root;
}

node_t *getPointerbyTitle(node_t *root)
{
    if (root == NULL)
        return NULL;

    char buffer[FIELDLENGHT];
    printf("Digite o titulo do jogo: ");
    fgets(buffer, FIELDLENGHT, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    return findNodebyTitle(root, buffer);
}
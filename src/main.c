#include "../include/file_handler.h"

void menu(node_t *root)
{
    int select;
    char buffer[FIELDLENGHT];
    do
    {
        printf("\n\n");
        printf("Escolha uma opcao:\n"
               "1) Mostrar todos os jogos cadastrados\n"
               "2) Consultar jogos\n"
               "3) Mostrar dados de um jogo\n"
               "4) Adicionar novo jogo\n"
               "5) Alterar dados de um jogo\n"
               "6) Remover jogo\n"
               "7) Abrir imagem de um jogo\n"
               "8) Adicionar imagem a um jogo\n"
               "9) Carregar jogos de arquivo CSV\n"
               "10) Salvar jogos em arquivo CSV\n"
               "11) Carregar links de imagens de arquivo CSV\n"
               "12) Salvar links de imagens em arquivo CSV\n"
               "13) Mostrar jogos que possuem imagem\n"
               "0) Sair\n"
               "Digite: ");
        scanf("%d", &select);
        getchar();
        switch (select)
        {
        case 1:
            printf("\nJogos cadastrados:");
            printGames(root);
            break;
        case 2:
            queryTree(root);
            break;
        case 3:
            printNode(getPointerbyTitle(root));
            break;
        case 4:
            root = addNewGame(root);
            printf("\nJogo adicionado com sucesso\n");
            break;
        case 5:
            changeData(getPointerbyTitle(root));
            break;
        case 6:
            printf("\nDigite o titulo do jogo: ");
            fgets(buffer, FIELDLENGHT, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            if (belongsToTree(root, buffer))
                root = removeNode(root, buffer);
            break;
        case 7:
            openImage(getPointerbyTitle(root));
            break;
        case 8:
            addImagetoGame(getPointerbyTitle(root));
            break;
        case 9:
            printf("\nDigite o path do arquivo: ");
            fgets(buffer, FIELDLENGHT, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            root = loadCSV(root, buffer);
            break;
        case 10:
            printf("\nDigite o path do novo arquivo: ");
            fgets(buffer, FIELDLENGHT, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            writeTree(root, buffer);
            break;
        case 11:
            printf("\nDigite o path do arquivo: ");
            fgets(buffer, FIELDLENGHT, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            root = loadImageLinks(root, buffer);
            break;
        case 12:
            printf("\nDigite o path do novo arquivo: ");
            fgets(buffer, FIELDLENGHT, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            writeImageLinks(root, buffer);
            break;
        case 13:
            printf("\n\nOs seguintes jogos possuem imagem:\n");
            printGameswithImage(root);
            break;
        case 0:
            freeTree(root);
            return;
            break;
        }
        printf("\n\nPressione enter para continuar...\n");
        getchar();
    } while (1);
}

int main(int argc, char **argv)
{
    node_t *root = NULL;
    if (argc == 2)
        root = loadCSV(root, argv[1]);

    else if (argc == 3)
    {
        root = loadCSV(root, argv[1]);
        root = loadImageLinks(root, argv[2]);
    }

    menu(root);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    CollList **list, **list2;
    CollList *actor, *actoraux;
    EdgeList *edge, *path;
    int option, id, id2, count;
    char name[100];
    list2 = hash_new();
    readTxtActors(list2);
    do
    {
        system("cls");
        list = hash_new();
        readTxtActors(list);
        system("cls");
        printf("=======================================\n===              MENU               ===\n=======================================\n");
        printf("\n-> (1) Obter Infos Ator por Nome\n-> (2) Obter contracenadores por ID \n-> (3) Apresentar atores que contracenaram apenas com mulheres\n-> (4) Ator que contracenou com mais pessoas\n-> (5) Obter relacao entre dois atores\n\n -> (0) Sair\n\n");
        printf(" > ");
        scanf("%d", &option);
        system("cls");
        switch (option)
        {
        case 1:
            printf(" -> Informacoes de um ator \n\n");
            printf(" - Nome a pesquisar: ");
            getchar();
            gets(name);
            system("cls");
            printf("- ID dos atores com o nome: %s\n", name);
            count = count_names(list, name);
            printf("\n\nQuantidade de atores com esse nome: %d", count);
            break;

        case 2:
            printf(" -> Contracenadores de um ator \n\n");
            printf(" - ID do ator a pesquisar: ");
            scanf("%d", &id);
            actor = hash_search(list2, id);
            if (actor)
            {
                printf("Ator %d: %s", actor->id, actor->name);
                if (actor->edges)
                {
                    for (edge = actor->edges; edge; edge = edge->next_edge)
                    {
                        actoraux = hash_search(list2, edge->target);
                        if (actoraux)
                            printf("\n Contracenou com:  %-9d| %-30s| %s", actoraux->id, actoraux->name, actoraux->gender);
                    }
                }
            }
            else
                printf("ID nao encontrado.\n");
            break;

        case 3:
            printf(" -> Atores que apenas contracenaram com mulheres\n\n| %-10s| %s\n| %10s|", "ID", "Nome", "");
            only_womans(list, list2);
            break;

        case 4:
            mostACT(list);
            break;

        case 5:
            printf(" -> Relacao entre dois atores\n\n");
            printf(" - ID do ator 1: ");
            scanf("%d", &id);
            if (!hash_search(list2, id))
            {
                printf("\n- ID %d nao existe.");
                break;
            }
            printf(" - ID do ator 2: ");
            scanf("%d", &id2);
            if (!hash_search(list2, id2))
            {
                printf("\n- ID %d nao existe.");
                break;
            }
            else
            {
                printf("\nA calcular relacao mais curta...");
                path = path_find(list, id, id2);
                system("cls");
                if (path)
                {
                    printf("- Existe um caminho entre os dois atores:\n\n");
                    for (; path; path = path->next_edge)
                    {
                        actor = hash_search(list2, path->target);
                        printf(" -> %s (%d)", actor->name, actor->id);
                    }
                }
                else
                    printf("\n- Nao existe um caminho entre os dois atores.\n");
            }
            break;

        default:
            break;
        }
        if (option != 0)
        {
            printf("\n\n(1) VOLTAR AO MENU");
            printf("\n(0) SAIR\n > ");
            scanf("%d", &option);
            system("cls");
        }
    } while (option != 0);
    return 0;
}
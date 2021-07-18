#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    Auditoria auditoria[TAM]; /*Abrir a struct principal do trabalho*/
    int menu, id = 0;
    id = carregaSave(auditoria); /*executar a funcao do "CarregarSave" binario*/
    do                           /*Fazer o Menu enquanto o utilizador nao pressionar para sair (6)*/
    {
        system("cls");
        printf("=======================================================\n=====================Menu_Inicial======================\n=======================================================\n\n");
        printf("1-Inserir Nova auditoria\n\n2-Editar dados\n\n3-DashBoard\n\n4-Listagens\n\n5-Estado da Resolucao das Vulnerabilidades\n\n6-Atividade dos colaboradores\n\n7-Gravar e Sair\n\nDe momento existe %d Auditorias registadas\n=======================================================\n", id);
        printf("\n\nDigite o numero da opcao que deseja: ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            system("cls");
            if (id >= TAM) /*limitar a adicicao de novas auditorias*/
            {
                break;
            }
            *auditoria = novaAuditoria(auditoria, id); /*executar a funcao para adicionar novas auditorias*/
            id++;
            break;
        case 2:
            if (id != 0)
            {
                system("cls");
                *auditoria = editarAuditoriaID(auditoria, id); /*executar a funcao para editar auditorias*/
                break;
            }
            else /*Caso nao haja auditorias registadas, entao: */
            {
                printf("\n\nAinda nao existe nenhuma auditoria!\n\n");
                system("pause");
                break;
            }

        case 3:
            system("cls");
            dashboard(auditoria, id); /*executar a funcao da dashboard*/
            system("pause");
            break;
        case 4:
            system("cls");
            listagem(auditoria, id); /*executar a funcao do menu de listagens*/
            break;
        case 5:
            system("cls");
            tabelaAuditoriasTodas(auditoria, id);      /*executar a funcao da tabela de auditorias para facilitar a pesquisa*/
            *auditoria = resolucaoVuln(auditoria, id); /*executar a funcao do Estado de Resolucao de Vulnerabilidades*/
            break;
        case 6:
            system("cls");
            tabelaAuditoriasTodas(auditoria, id);        /*executar a funcao da tabela de auditorias para facilitar a pesquisa*/
            *auditoria = remocaoIntegral(auditoria, id); /*executar a funcao da Atividade dos Colaboradores e a sua remoçao*/
            break;
        case 7:
            inserirSave(auditoria, id); /*executar a funcao para guardar as informacoes em binario*/
            break;
        default:
            do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                scanf("%d", &menu);
            } while (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6 && menu != 7);
        }
    } while (menu != 7);
    return 0;
}

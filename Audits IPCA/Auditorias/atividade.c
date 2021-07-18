#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Atividade do colaborador*/

Auditoria remocaoIntegral(Auditoria *auditoria, int id)
{
    int n, menuRemin, comp;
    char nomeAux[50]; /*As variaveis Aux sao para auxiliar a recolha de informcao*/
    getchar();
    printf("\n\nDigite o nome que prentede pesquisar: ");
    fgets(nomeAux, 50, stdin);
    for (int i = 0; i < id; i++) /*percorrer todas as auditorias*/
    {
        comp = stricmp(nomeAux, auditoria[i].colaborador.nome); /*Procurar pelo nome digitado pelo utilizador*/
        if (comp == 0)
        {
            do
            {
                system("cls");
                printf("=====================================================\n==================Menu_Atividade=====================\n=====================================================");
                if (auditoria[i].colaborador.atividade == 0) /*Se for ativo: */
                {
                    printf("\n\nO colaborador: %sencontra-se ativo de momento\n\n", auditoria[i].colaborador.nome);
                }
                if (auditoria[i].colaborador.atividade == 1) /*Se for inativo*/
                {
                    printf("\n\nO colaborador: %sencontra-se inativo de momento\n\n", auditoria[i].colaborador.nome);
                }
                printf("=====================================================\n\n");
                printf("1-Mudar o estado de atividade do Colaborador\n\n2-Remover colaborador(Para remover-lo, tem de garantir que ele esta inativo)\n\n3-Voltar ao Menu Principal\n\nDigite o opcao que deseja: ");
                scanf("%d", &menuRemin);
                switch (menuRemin)
                {
                case 1:
                    *auditoria = alterarIntegral(auditoria, i); /*executar a funcao em que a atividade muda*/
                    break;
                case 2:
                    *auditoria = removerColabIntegridadeReferencial(auditoria, i, id); /*executar a funcao em que se remove o colaborador do pograma caso este estaja inativo*/
                    break;
                case 3:
                    break;
                default:
                    do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
                    {
                        printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                        scanf("%d", &menuRemin);
                    } while (menuRemin != 1 && menuRemin != 2 && menuRemin != 3);

                    break;
                }
            } while (menuRemin != 3);
            i = id; /*Para parar de percorrer auditorias pois ja encontramos o colaborador*/
            return *auditoria;
        }
    }
}

/*Alterar atividade do colaborador*/

Auditoria alterarIntegral(Auditoria *auditoria, int id)
{
    if (auditoria[id].colaborador.atividade == 1) /*Se colaborador for inativo, entao torna-se ativo*/
    {
        auditoria[id].colaborador.atividade = 0;
    }
    else
    {
        auditoria[id].colaborador.atividade = 1; /*Se o colaborador for ativo, entao torna-se inativo*/
    }
    return *auditoria;
}

/*Remover Colaboradores tendo em conta a integridade  referencial*/

Auditoria removerColabIntegridadeReferencial(Auditoria *auditoria, int t, int id)
{
    char nomeAuxi[50];
    strcpy(nomeAuxi, auditoria[t].colaborador.nome); /*Igualar o auxiliar ao nome do colaborador pedido*/
    int compar;
    if (auditoria[t].colaborador.atividade == 1) /*Se este tiver for um colaborador inativo, entao: */
    {
        for (int i = 0; i < id; i++) /*percorrer todas as auditorias*/
        {
            compar = strcmp(nomeAuxi, auditoria[i].colaborador.nome); /*Procurar pelo nome digitado pelo utilizador*/
            if (compar == 0)
            {
                strcpy(auditoria[i].colaborador.nome, "=====UTILIZADOR REMOVIDO(inativo)=====\n"); /*Eliminar o colaborador*/
            }
        }
    }
    if (auditoria[t].colaborador.atividade == 0) /*Se este for um colaborador ativo, entao: */
    {
        printf("\n\nColaborador nao pode ser removido pois esta ATIVO de momento!!\n\n\n");
        system("pause");
    }
    return *auditoria;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Mostrar o estado de resolução das vulnerabilidades*/

Auditoria resolucaoVuln(Auditoria *auditoria, int id)
{
    int t = 0, cod, menuRes;
    printf("\n\nDigite o codigo da audotira que pretende Verificar ou alterar o seu estado de Resolucao: ");
    scanf("%d", &cod);
    while (cod != auditoria[t].codigoAudi && t < id + 1) /*Percorrer todos os arrays ate o codigo que o utilizar digitar for o pedido, quando este for igual ao digitado ou atingir o limite de auditorias, passa para o "if" asseguir*/
    {
        t++; /*Avançar para o array asseguir*/
    }
    if (t >= id + 1) /*Se nao existir nenhuma auditoria com o codigo digitado pelo utilizador: */
    {
        printf("\n\nO codigo nao existe de momento!!\n\n");
        system("pause");
    }
    if (t < id + 1) /*Se existir alguma auditoria com o codigo digitado pelo utilizador */
    {
        do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (2)*/
        {
            system("cls");
            printf("=======================================================\n===================Estado_Resolucao====================\n=======================================================\n");
            printf("\n||Por Resolver|| Vulnerabilidades: \n\n");
            for (int i = 0; i < auditoria[t].vuln[0].numero; i++) /*Percorrer todas as vulnerabilidades*/
            {
                if (auditoria[t].vuln[i].descricao.resoluc == 0) /*Se o estado de resolucao for igual a 0(estiver por resolver), entao mostrar na consola*/
                {
                    printf("|%d- %10d |Data: %d-%d-%d\n", i + 1, auditoria[t].vuln[i].descricao.codigoVuln, auditoria[t].data.dia, auditoria[t].data.mes, auditoria[t].data.ano);
                }
            }
            printf("\n||Resolvido|| Vulnerabilidades: \n\n");
            for (int i = 0; i < auditoria[t].vuln[0].numero; i++) /*Percorrer todas as vulnerabilidades*/
            {
                if (auditoria[t].vuln[i].descricao.resoluc == 1) /*Se o estado de resolucao for igual a 1(estiver resolvido), entao mostrar na consola*/
                {
                    printf("|%d- %10d |Data: %d-%d-%d\n", i + 1, auditoria[t].vuln[i].descricao.codigoVuln, auditoria[t].data.dia, auditoria[t].data.mes, auditoria[t].data.ano);
                }
            }

            printf("\n\n\n1-Mudar o estado de alguma Vulnerabilidade\n\n2-Voltar ao Menu Principal\n\nDigite o opcao que deseja: ");
            scanf("%d", &menuRes);
            switch (menuRes)
            {
            case 1:
                *auditoria = alterarEstadoReso(auditoria, t); /*executar a funcao em que o estado da resolucao muda*/
                break;
            case 2:
                break;
            default:
                do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
                {
                    printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                    scanf("%d", &menuRes);
                } while (menuRes != 1 && menuRes != 2);

                break;
            }

        } while (menuRes != 2);
    }
    return *auditoria;
}

/*Alterar o estado de resolução das vulnerabilidades*/

Auditoria alterarEstadoReso(Auditoria *auditoria, int id)
{
    int x;
    printf("\n\nDigite qual a vulnerabilidade que deseja alterar o estado: ");
    scanf("%d", &x);
    x = x - 1;                                        /*Recuar uma posicao no array, pois o utilizador irá sempre colocar a posicao asseguir da que queria alterar*/
    if (auditoria[id].vuln[x].descricao.resoluc == 1) /*Se o estado de resolucao estiver resolvido, entao passa para resolver*/
    {
        auditoria[id].vuln[x].descricao.resoluc = 0;
    }
    else
    {
        auditoria[id].vuln[x].descricao.resoluc = 1; /*Se estiver por resolver, passa para resolvido*/
    }
    return *auditoria;
}
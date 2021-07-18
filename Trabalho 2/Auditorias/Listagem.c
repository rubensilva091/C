#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Menu listagem*/

void listagem(Auditoria *auditoria, int id)
{
    int menu_listagem;
    do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (4)*/
    {
        system("cls");
        printf("=====================================================\n===================Menu_Listagem=====================\n=====================================================\n");
        printf("\n1-Ordem decrescente Vulnerabilidades\n\n2-Colaborador\n\n3-Vulnerabilidades agrupadas Nivel de Impacto\n\n4-Voltar ao Menu Inicial\n\nDigite o opcao que deseja: ");
        scanf("%d", &menu_listagem);
        switch (menu_listagem)
        {
        case 1:
            system("cls");
            listaColabAudi(auditoria, id); /*executar a funcao que mostra a lista de auditorias e colaboradores por ordem decrescente de Vulnerabilidades*/
            system("pause");
            break;
        case 2:
            system("cls");
            tabelaAuditoriasTodas(auditoria, id);        /*executar a funcao em mostra a tabela com as auditorias todas para auxiliar a pesquisa na funcao seguida*/
            listaAuditoriasColaboradores(auditoria, id); /*executar a funcao que procura nos arrays todos o nome inserido pelo utilizador e mostra a quantidade de auditorias efectuada*/
            system("pause");
            break;
        case 3:
            system("cls");
            tabelaAuditoriasTodas(auditoria, id);         /*executar a funcao em mostra a tabela com as auditorias todas para auxiliar a pesquisa na funcao seguida*/
            listaVulnerabilidadesNImpacto(auditoria, id); /*executar a funcao que organiza as vulnerabilidades da auditoria pedida pelo utilizador, por nivel de impacto*/
            system("pause");
            break;
        case 4:
            break;

        default:
            do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                scanf("%d", &menu_listagem);
            } while (menu_listagem != 1 && menu_listagem != 2 && menu_listagem != 3 && menu_listagem != 4);
        }
    } while (menu_listagem != 4);
}

/*Lista ordenada de colaboradores por ordem decrescente de vulnerabilidades*/

void listaColabAudi(Auditoria *auditoria, int id)
{
    Auditoria aux; /*Abrir uma variavel para auxiliar a troca de informacao no ciclo*/
    printf("=========================Todas_Auditorias==============================\n");
    for (int i = 0; i < id - 1; i++) /*Percorre todas as auditorias apartir da posicao 1 ate à posicao "id-1"*/
    {
        for (int j = i + 1; j < id; j++) /*Percorre todas as auditorias apartir da posicao 2 ate à posicao "id"*/
        {
            if (auditoria[i].vuln[0].numero < auditoria[j].vuln[0].numero) /*Organiza as auditorias pela quantidade de vulnerabilidades decrescentemente*/
            {
                aux = auditoria[i];
                auditoria[i] = auditoria[j]; /*Estes 3 passos trocam a posicao do array i com o array j sempre que o numero de i for menor que j*/
                auditoria[j] = aux;
            }
        }
    }
    printf("\n|Auditoria numero|Vulnerabidades|Colaborador \n         ");
    for (int i = 0; i < id; i++) /*Apresenta todas as auditorias ordenada pela funcao de cima*/
    {
        printf("\n|%16d|%14d|%s", auditoria[i].codigoAudi, auditoria[i].vuln[0].numero, auditoria[i].colaborador.nome);
    }
}

/*Informacoes de Colaborador*/

void listaAuditoriasColaboradores(Auditoria *auditoria, int id)
{
    Data dataAux[21];
    int n = 0, codigoAux[21], vulnAux[21], comp;
    char nomeAux[50]; /*As variaveis Aux sao para auxiliar a recolha de informcao*/
    getchar();
    printf("\n\nDigite o nome que prentede pesquisar: ");
    fgets(nomeAux, 50, stdin);
    for (int i = 0; i < id; i++) /*percorrer todas as auditorias*/
    {
        comp = stricmp(nomeAux, auditoria[i].colaborador.nome); /*Procurar pelo nome digitado pelo utilizador*/
        if (comp == 0)
        {
            system("cls");
            codigoAux[n] = auditoria[i].codigoAudi;
            dataAux[n].dia = auditoria[i].data.dia;
            dataAux[n].mes = auditoria[i].data.mes; /*Auxiliares para gravar informacoes*/
            dataAux[n].ano = auditoria[i].data.ano;
            vulnAux[n] = auditoria[i].vuln[0].numero;
            n++;
            printf("\nO colaborador %stem %d auditorias! \n\n", auditoria[i].colaborador.nome, n);
        }
    }
    for (int c = 0; c < n; c++) /*Mostrar todas as informacoes gravadas em cima*/
    {
        printf("\n=====Auditoria Nr=====\n");
        printf("\nCodigo: %d", codigoAux[c]);
        printf("\nData: %d-%d-%d", dataAux[c].dia, dataAux[c].mes, dataAux[c].ano);
        printf("\nNr de Vulnerabilidades: %d\n", vulnAux[c]);
    }
    if (n == 0) /*Caso o nome digitado nao exista*/
    {
        system("cls");
        printf("\nO colaborador digitado nao existe na base de dados!!!!\n\n");
    }
}

/*Lista de Vulnerabilidades por Impacto*/

void listaVulnerabilidadesNImpacto(Auditoria *auditoria, int id)
{
    int t = 0, cod;
    printf("\n\nDigite o codigo da audotira que pretende agrupar as vulnerabilidades por Nivel Impacto: ");
    scanf("%d", &cod);
    while (cod != auditoria[t].codigoAudi && t < id + 1) /*Percorrer todos os arrays ate o codigo que o utilizar digitar for o pedido, quando este for igual ao digitado ou atingir o limite de auditorias, passa para o "if" asseguir*/
    {
        t++; /*Avancar para o array asseguir*/
    }
    if (t >= id + 1) /*Se nao existir nenhuma auditoria com o codigo digitado pelo utilizador: */
    {
        printf("\n\nO codigo nao existe de momento!!\n\n");
        system("pause");
    }
    if (t < id + 1) /*Se existir alguma auditoria com o codigo digitado pelo utilizador */
    {
        system("cls");
        printf("=========================Todas as Vulnerabilidades==============================\n");
        printf("\n||Alto  Impacto|| Vulnerabilidades: ");
        for (int i = 0; i < auditoria[t].vuln[0].numero + 1; i++) /*Percorrer todas as auditorias*/
        {
            if (auditoria[t].vuln[i].nivelImpact == 3) /*Caso o nivel de impacto for Elevado, apresentar na consola*/
            {
                printf("| %15d |", auditoria[t].vuln[i].descricao.codigoVuln);
            }
        }
        printf("\n||Medio Impacto|| Vulnerabilidades: ");
        for (int i = 0; i < auditoria[t].vuln[0].numero + 1; i++) /*Percorrer todas as auditorias*/
        {
            if (auditoria[t].vuln[i].nivelImpact == 2) /*Caso o nivel de impacto for Media, apresentar na consola*/
            {
                printf("| %15d |", auditoria[t].vuln[i].descricao.codigoVuln);
            }
        }
        printf("\n||Baixo Impacto|| Vulnerabilidades: ");
        for (int i = 0; i < auditoria[t].vuln[0].numero + 1; i++) /*Percorrer todas as auditorias*/
        {
            if (auditoria[t].vuln[i].nivelImpact == 1) /*Caso o nivel de impacto for Baixo, apresentar na consola*/
            {
                printf("| %15d |", auditoria[t].vuln[i].descricao.codigoVuln);
            }
        }
    }
}

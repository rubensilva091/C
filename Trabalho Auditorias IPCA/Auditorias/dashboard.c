#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*DashBoard*/

void dashboard(Auditoria *auditoria, int id)
{
    float media;
    int maiorVuln, menosVuln, menu_dashboard;
    printf("=======================================================\n======================Dashboard========================\n=======================================================\n");
    printf("\nDe momento existe %d Auditorias registadas\n", id);
    maiorVuln = auditoriaComMaisVuln(auditoria, id);  /*executar a funcao da Auditoria maior quantidade de Vulnerabilidade*/
    menosVuln = auditoriaComMenosVuln(auditoria, id); /*executar a funcao da Auditoria menor quantidade de Vulnerabilidade*/
    printf("\nA auditoria com mais vulnerabilidades encontradas e nr%d (Codigo-%d  Data-%d-%d-%d) com %d Vulnerabilidades\n", auditoria[maiorVuln].codigoAudi, auditoria[maiorVuln].codigoAudi, auditoria[maiorVuln].data.dia, auditoria[maiorVuln].data.mes, auditoria[maiorVuln].data.ano, auditoria[maiorVuln].vuln[0].numero);
    printf("\nA auditoria com menos vulnerabilidades encontradas e nr%d (Codigo-%d  Data-%d-%d-%d) com %d Vulnerabilidades\n", auditoria[menosVuln].codigoAudi, auditoria[menosVuln].codigoAudi, auditoria[menosVuln].data.dia, auditoria[menosVuln].data.mes, auditoria[menosVuln].data.ano, auditoria[menosVuln].vuln[0].numero);
    media = mediaVulnerabilidadesAuditorias(auditoria, id); /*executar a funcao da media das Vulnerabilidades*/
    printf("\nEm media, existe %0.2f Vulnerabilidades detetadas por auditoria!!!\n", media);
}

/*Vulnerabilidades media*/

float mediaVulnerabilidadesAuditorias(Auditoria *auditoria, int id)
{
    float soma = 0;
    for (int i = 0; i < id; i++) /*Somar o resultado anterior ao mais recente ate percorrer todas as auditorias*/
    {
        soma += auditoria[i].vuln[0].numero;
    }
    soma = soma / id; /*Dividir as quantidades de vulnerabilidades pelo numero total de auditorias*/
    return soma;
}

/*Auditoria com Mais Vulnerabilidades*/

int auditoriaComMaisVuln(Auditoria *auditoria, int id)
{
    int numeroMaior = 0;
    int maior = auditoria[0].vuln[0].numero; /*Igualar uma variavel à primeira quantidade de vulnerabilidades da primeria auditoria para servir de referencia para o for asseguir*/

    for (int i = 0; i < id + 1; i++) /*Sempre que a quantidade de vulnerabilidades for maior que a variavel "maior", entao a variavel "maior" passa a ser o numero comparado*/
    {
        if (auditoria[i].vuln[0].numero > maior)
        {
            maior = auditoria[i].vuln[0].numero;
            numeroMaior = i; /*Guardar a posiçao do array onde existe maior quantidade de vulnerabilidades para asseguir returnar*/
        }
    }
    return numeroMaior;
}

/*Auditoria com Menos Vulnerabilidades*/

int auditoriaComMenosVuln(Auditoria *auditoria, int id)
{
    int numeroMenor = 0;
    int menor = auditoria[0].vuln[0].numero; /*Igualar uma variavel à primeira quantidade de vulnerabilidades da primeria auditoria para servir de referencia para o for asseguir*/

    for (int i = 0; i < id + 1; i++) /*Sempre que a quantidade de vulnerabilidades for menor que a variavel "menor", entao a variavel "menor" passa a ser o numero comparado*/
    {
        if (auditoria[i].vuln[0].numero < menor)
        {
            menor = auditoria[i].vuln[0].numero;
            numeroMenor = i; /*Guardar a posiçao do array onde existe menor quantidade de vulnerabilidades para asseguir returnar*/
        }
    }
    return numeroMenor;
}

/*Dados da Auditoria*/

int dadosAuditoria(Auditoria *auditoria, int cod)
{
    printf("======================================================\n====================Dados======================\n=======================================================\n");
    printf("\n\n......._.......Colaborador......._.......\n\n");
    printf("Nome: %s", auditoria[cod].colaborador.nome);
    printf("\nCodigo: %d", auditoria[cod].colaborador.codigoColab);
    printf("\n\n......._.......Auditoria......._.......\n\n");
    printf("Codigo da auditoria: %d", auditoria[cod].codigoAudi);
    printf("\n\nData: %d-%d-%d", auditoria[cod].data.dia, auditoria[cod].data.mes, auditoria[cod].data.ano);
    printf("\n\nDuracao: %d minutos\n\n", auditoria[cod].duracao);
    return 0;
}

/*Dados das Vulnerabilidades da Auditoria*/

int dadosVulnerabilidade(Auditoria *auditoria, int cod)
{
    printf("======================================================\n========================Dados=========================\n=======================================================\n");
    printf("\n\n......._.......Vulnerabilidades......._.......\n\n");
    printf("Numero de Vulnerabilidades da Auditoria: %d", auditoria[cod].vuln[0].numero);
    for (int i = 0; i < auditoria[cod].vuln[0].numero; i++) /*Percorrer todas as vulnerabilidades da auditoria*/
    {
        printf("\n\n====================Vulnerabilidade NR%d======================\n\n", i + 1);
        printf("\nNivel de impacto que esta vulnerabilidade provocou: %d\n ", auditoria[cod].vuln[i].nivelImpact);
        printf("\nCodigo do Equipamento onde foi encontrada a vulnerabilidade nr%d: %d\n", i + 1, auditoria[cod].vuln[i].descricao.codigoVuln);
        printf("\nTipo do Equipamento onde foi encontrada a vulnerabilidade nr%d: %s", i + 1, auditoria[cod].vuln[i].descricao.tipo);
        printf("\nMarca do Equipamento onde foi encontrada a vulnerabilidade nr%d: %s", i + 1, auditoria[cod].vuln[i].descricao.marca);
        printf("\nModelo do Equipamento onde foi encontrada a vulnerabilidade nr%d: %s", i + 1, auditoria[cod].vuln[i].descricao.modelo);
        printf("\nData de aquisicao do Equipamento onde foi encontrada a vulnerabilidade nr%d: %d-%d-%d\n\n", i + 1, auditoria[cod].vuln[i].descricao.data.dia, auditoria[cod].vuln[i].descricao.data.mes, auditoria[cod].vuln[i].descricao.data.ano);
    }
    return 0;
}

/*Tabela Auditorias para ajudar a pesquisar*/

void tabelaAuditoriasTodas(Auditoria *auditoria, int id)
{
    printf("\n|Auditoria codigo|Vulnerabidades|Colaborador \n         ");
    for (int i = 0; i < id; i++) /*Mostrar todas as auditorias por ordem*/
    {
        printf("\n|%16d|%14d|%s", auditoria[i].codigoAudi, auditoria[i].vuln[0].numero, auditoria[i].colaborador.nome);
    }
}
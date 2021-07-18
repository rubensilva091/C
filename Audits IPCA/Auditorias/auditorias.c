#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Inserir Nova Auditoria*/

Auditoria novaAuditoria(Auditoria *auditoria, int id)
{
    auditoria[id].colaborador.atividade = 0; /*Igualar a variavel a 0 sempre que insiro uma nova auditoria*/
    auditoria[id].codigoAudi = id + 1;       /*O Codigo auditoria tem sempre de ser 1 acima do id, pois a primeira posiçao é id=0 */
    printf("================================================================\n====================Inserir_Nova_Auditoria======================\n================================================================\n");
    printf("\nDigite o nome do colaborador da auditoria: ");
    getchar();
    fgets(auditoria[id].colaborador.nome, 50, stdin);
    printf("\n\nDigite o codigo do colaborador da auditoria: ");
    scanf("%d", &auditoria[id].colaborador.codigoColab);
    do /*Fazer  enquanto o dia e o mes nao corresponderam ao pedido embaixo*/
    {
        printf("\n\nDigite a data (Dia-Mes-Ano) da auditoria: ");
        scanf("%d-%d-%d", &auditoria[id].data.dia, &auditoria[id].data.mes, &auditoria[id].data.ano);
    } while ((auditoria[id].data.dia < 1 || auditoria[id].data.dia > 31) || (auditoria[id].data.mes < 1 || auditoria[id].data.mes > 12));
    printf("\n\nDigite a duracao em minutos da auditoria: ");
    scanf("%d", &auditoria[id].duracao);
    printf("\n\n================================================================\n====================Inserir_Vulnerabilidades====================\n================================================================\n");
    printf("\n\nDigite o numero de vulnerabilidades encontrada na auditoria: ");
    scanf("%d", &auditoria[id].vuln[0].numero);
    for (int i = 0; i < auditoria[id].vuln[0].numero; i++) /*Percorrer o numero de vulnerabilidades que eu inseri em cima*/
    {
        auditoria[id].vuln[i].descricao.resoluc = 0;
        printf("\n\nDigite o codigo da Vulnerabilidade nr%d da auditoria: ", i + 1);
        scanf("%d", &auditoria[id].vuln[i].descricao.codigoVuln);
        printf("\n\nDigite 1, 2 ou 3 para escolher o nivel de impacto da Vulnerabilidade(1-Baixo, 2-Moderado, 3-Elevado): ");
        scanf("%d", &auditoria[id].vuln[i].nivelImpact);
        printf("\n\nDigite o tipo de produto onde a vulnerabilidade nr%d foi encontrada: ", i + 1);
        getchar();
        fgets(auditoria[id].vuln[i].descricao.tipo, 50, stdin);
        printf("\n\nDigite a marca do equipamento informatico onde a vulnerabilidade nr%d foi encontrada: ", i + 1);
        fgets(auditoria[id].vuln[i].descricao.marca, 50, stdin);
        printf("\n\nDigite o modelo do equipamento informatico onde a vulnerabilidade nr%d foi encontrada: ", i + 1);
        fgets(auditoria[id].vuln[i].descricao.modelo, 50, stdin);
        do /*Fazer  enquanto o dia e o mes nao corresponderam ao pedido embaixo*/
        {
            printf("\n\nDigite a data (Dia-Mes-Ano) da aquisicao do produto onde a vulnerabilidade nr%d foi encontrada: ", i + 1);
            scanf("%d-%d-%d", &auditoria[id].vuln[i].descricao.data.dia, &auditoria[id].vuln[i].descricao.data.mes, &auditoria[id].vuln[i].descricao.data.ano);
        } while ((auditoria[id].vuln[i].descricao.data.dia < 1 || auditoria[id].vuln[i].descricao.data.dia > 31) || (auditoria[id].vuln[i].descricao.data.mes < 1 || auditoria[id].vuln[i].descricao.data.mes > 12));
    }
    printf("\nAuditoria adicionada com sucesso!!\nA auditoria foi guardada com o codigo nr%d\n\n", auditoria[id].codigoAudi);
    system("pause");
    return *auditoria;
}

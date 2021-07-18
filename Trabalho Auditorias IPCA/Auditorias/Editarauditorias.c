#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Menu editar dados*/

Auditoria editarAuditoriaID(Auditoria *auditoria, int id)
{
    int i = 0, cod;
    tabelaAuditoriasTodas(auditoria, id);
    printf("\n\nDigite o codigo da audotira que pretende editar: ");
    scanf("%d", &cod);
    while (cod != auditoria[i].codigoAudi && i < id + 1) /*Percorrer todos os arrays ate o codigo que o utilizar digitar for o pedido, quando este for igual ao digitado ou atingir o limite de auditorias, passa para o "if" asseguir*/
    {
        i++; /*Avancar para o array asseguir*/
    }
    if (i >= id + 1) /*Se nao existir nenhuma auditoria com o codigo digitado pelo utilizador: */
    {
        printf("\n\nO codigo nao existe de momento!!\n\n");
        system("pause");
    }
    if (i < id + 1) /*Se existir alguma auditoria com o codigo digitado pelo utilizador */
    {
        int menu_Ed, n;
        do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (4)*/
        {
            system("cls");
            printf("=======================================================\n=====================Menu_Editar=======================\n=======================================================\n");
            printf("1-Visualizar/Editar Auditoria nr%d/Colaborador\n\n2-Visualizar/Editar Vulnerabilidades nr%d\n\n3-Adicionar/Remover Vulnerabilidades\n\n4-Voltar ao menu Iniciar\n=======================================================\n", cod, cod);
            printf("\nDigite o opcao que deseja visualizar: ");
            scanf("%d", &menu_Ed);
            switch (menu_Ed)
            {
            case 1:
                system("cls");
                dadosAuditoria(auditoria, i); /*executar a funcao para mostrar os dados da auditoria pedida*/
                system("pause");
                *auditoria = edicaoColaborador(auditoria, i); /*executar a funcao para editar a auditoria*/
                break;
            case 2:
                system("cls");
                dadosVulnerabilidade(auditoria, i); /*executar a funcao para mostrar as vulnerabilidades e as suas descricoes da auditoria pedida*/
                do                                  /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
                {
                    printf("\n\nDigite o numero de qual vulnerabilidade que deseja editar da auditoria nr%d: ", cod);
                    scanf("%d", &n);
                } while (n < 1 || n > 50);

                *auditoria = edicaoVulnerabilidades(auditoria, i, n); /*executar a funcao para editar as vulnerabilidades da auditoria pedida*/
                break;
            case 3:
                system("cls");
                *auditoria = adicionarRemoverVulnerabilidades(auditoria, i); /*executar a funcao para adicionar ou remover vulnerabilidades de uma auditoria*/
                break;
            case 4:
                break;
            default:
                do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
                {
                    printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                    scanf("%d", &menu_Ed);
                } while (menu_Ed != 1 && menu_Ed != 2 && menu_Ed != 3 && menu_Ed != 4);
            }
        } while (menu_Ed != 4);
    }
    return *auditoria;
}

/*Editar o Colaborador*/

Auditoria edicaoColaborador(Auditoria *auditoria, int cod)
{
    int menu_edi_colab;
    do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (3)*/
    {
        system("cls");
        printf("=======================================================\n=================Menu_Editar_Auditoria===================\n=======================================================\n");
        printf("1-Editar Nome do Colaborador\n\n2-Editar Codigo do colaborador\n\n3-Voltar ao menu Editar\n\nDigite a opcao que deseja: ");
        scanf("%d", &menu_edi_colab);
        switch (menu_edi_colab)
        {
        case 1: /*Alterar o nome do colaborador*/
            getchar();
            printf("\nQual o novo colaborador para a auditoria nr%d: ", cod + 1);
            fgets(auditoria[cod].colaborador.nome, 50, stdin);
            printf("\nO novo colaborador foi alterado na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 2: /*Alterar o codigo do colaborador*/
            printf("\nQual o novo codigo do colaborador para a auditoria nr%d: ", cod + 1);
            scanf("%d", &auditoria[cod].colaborador.codigoColab);
            printf("\nO novo codigo do Colaborador foi alterado na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 3:
            break;
        default:
            do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                scanf("%d", &menu_edi_colab);
            } while (menu_edi_colab != 1 && menu_edi_colab != 2 && menu_edi_colab != 3);
        }
    } while (menu_edi_colab != 3);
    return *auditoria;
}

/*Editar as Vulnerabilidades da Auditoria*/ /*Crash ERRO*/

Auditoria edicaoVulnerabilidades(Auditoria *auditoria, int cod, int n)

{
    n = n - 1; /*Recuar uma posicao na variavel, pois a posicao digitada pelo utilizador é a seguinte da requerida pelo mesmo*/
    int menu_edi_vuln;
    do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (7)*/
    {
        system("cls");
        printf("================================================================\n=================Menu_Editar_Vulnerabilidades===================\n=============================================================\n");
        printf("\n\n1-Editar Codigo da Vulnerabildade\n\n2-Editar Marca do Produto\n\n3-Editar Modelo do Produto\n\n4-Editar tipo do Produto\n\n5-Editar data da aquisicao do Produto\n\n6-Editar o nivel de Impacto da Vulnerabilidade\n\n7-Voltar ao menu Editar\n\n Digite a opcao que deseja: ");
        scanf("%d", &menu_edi_vuln);
        getchar();
        switch (menu_edi_vuln)
        {
        case 1: /*Alterar o codigo da Vulnerabildade*/
            printf("\nQual o novo codigo da Vulnerabilidade para a auditoria nr%d: ", cod + 1);
            scanf("%d", &auditoria[cod].vuln[n].descricao.codigoVuln);
            printf("\nO novo codigo da Vulnerabilidade foi alterado na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 2: /*Alterar a Marca do Produtor da Vulnerabildade*/
            printf("\nQual a nova Marca do Produto da Vulnerabilidade para a auditoria nr%d: ", cod + 1);
            fgets(auditoria[cod].vuln[n].descricao.marca, 50, stdin);
            printf("\nA nova Marca do Produto foi alterada na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 3: /*Alterar o Modelo do Produto da Vulnerabildade*/
            printf("\nQual o novo Modelo do Produto da Vulnerabilidade para a auditoria nr%d: ", cod + 1);
            fgets(auditoria[cod].vuln[n].descricao.modelo, 50, stdin);
            printf("\nO novo Modelo do Produto foi alterado na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 4: /*Alterar o Tipo do Produto da Vulnerabildade*/
            printf("\nQual o novo Tipo do Produto da Vulnerabilidade para a auditoria nr%d: ", cod + 1);
            fgets(auditoria[cod].vuln[n].descricao.tipo, 50, stdin);
            printf("\nO novo Tipo do Produto foi alterado na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 5: /*Alterar a Data da aquisicao do Produto da Vulnerabildade*/
            do  /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("\n\nDigite a nova Data (Dia-Mes-Ano) da aquisicao do Produto onde a vulnerabilidade nr%d foi encontrada: ", cod + 1);
                scanf("%d-%d-%d", &auditoria[cod].vuln[n].descricao.data.dia, &auditoria[cod].vuln[n].descricao.data.mes, &auditoria[cod].vuln[n].descricao.data.ano);
            } while ((auditoria[cod].vuln[n].descricao.data.dia < 1 || auditoria[cod].vuln[n].descricao.data.dia > 31) || (auditoria[cod].vuln[n].descricao.data.mes < 1 || auditoria[cod].vuln[n].descricao.data.mes > 12));
            printf("\nA nova Data da aquisicao do Produto foi alterada na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 6: /*Alterar o Nivel de Impacto do Produto da Vulnerabildade*/
            printf("\nQual o novo Nivel de Impacto da Vulnerabilidade (1-Baixo  2-Moderado  3-Elevado) para a auditoria nr%d: ", cod + 1);
            scanf("%d", &auditoria[cod].vuln[n].nivelImpact);
            printf("\nA nova Marca do Produto foi alterada na auditoria nr%d!!!!! \n\n", cod + 1);
            system("pause");
            break;
        case 7:
            break;
        default:
            do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                scanf("%d", &menu_edi_vuln);
            } while (menu_edi_vuln != 1 && menu_edi_vuln != 2 && menu_edi_vuln != 3 && menu_edi_vuln != 4 && menu_edi_vuln != 5 && menu_edi_vuln != 6 && menu_edi_vuln != 7);
        }
    } while (menu_edi_vuln != 7);
    return *auditoria;
}

/* Menu para adicionar ou remover vulnerabilidades de alguma auditoria*/

Auditoria adicionarRemoverVulnerabilidades(Auditoria *auditoria, int cod)
{
    int menuAddRem;
    do /*Fazer o Menu enquanto o utilizador nao pressionar para sair (3)*/
    {
        system("cls");
        printf("=======================================================\n=====================Menu_Add/Rem=======================\n=======================================================\n");
        printf("1-Adicionar Vulnerabilidade\n\n2-Remover Vulnerabilidade\n\n3-Voltar ao Menu Editar\n\nDigite a opcao que deseja: ");
        scanf("%d", &menuAddRem);
        switch (menuAddRem)
        {
        case 1:
            system("cls");
            *auditoria = addVulnerabilidades(auditoria, cod); /*executar a funcao para adicionar vulnerabilidades a uma auditoria*/
            system("pause");
            break;
        case 2:
            system("cls");
            dadosVulnerabilidade(auditoria, cod);
            *auditoria = remVulnerabilidades(auditoria, cod); /*executar a funcao para remover vulnerabilidades a uma auditoria*/
            system("pause");
            break;
        case 3:
            break;
        default:
            do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
            {
                printf("Opcao inexistente ou invalida, por favor escolha outra opcao: ");
                scanf("%d", &menuAddRem);
            } while (menuAddRem != 1 && menuAddRem != 2 && menuAddRem != 3);
        }

    } while (menuAddRem != 3);
    return *auditoria;
}

/*Adicionar Vulnerabilidades a alguma auditoira*/

Auditoria addVulnerabilidades(Auditoria *auditoria, int id)
{
    int novasVuln;
    printf("Digite o numero de auditorias que deseja adicionar: ");
    scanf("%d", &novasVuln);
    novasVuln = novasVuln + auditoria[id].vuln[0].numero; /*igualar a variavel ao numero de vulnerabilidades da auditoria pedida*/
    for (int i = auditoria[id].vuln[0].numero; i < novasVuln; i++)
    {
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
        do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
        {
            printf("\n\nDigite a data (Dia-Mes-Ano) da aquisicao do produtor onde a vulnerabilidade nr%d foi encontrada: ", i + 1);
            scanf("%d-%d-%d", &auditoria[id].vuln[i].descricao.data.dia, &auditoria[id].vuln[i].descricao.data.mes, &auditoria[id].vuln[i].descricao.data.ano);
        } while ((auditoria[id].vuln[i].descricao.data.dia < 1 || auditoria[id].vuln[i].descricao.data.dia > 31) || (auditoria[id].vuln[i].descricao.data.mes < 1 || auditoria[id].vuln[i].descricao.data.mes > 12));
    }
    printf("\nAs Novas vulnerabilidades foram adicionadas com sucesso\n");
    auditoria[id].vuln[0].numero = novasVuln; /*igualar o numero de vulnerabilidades da auditoria pedida para a variavel inicial(acrescenta auditorias)*/
    return *auditoria;
}

/*Remover Vulnerabilidades de uma certa auditoria*/

Auditoria remVulnerabilidades(Auditoria *auditoria, int id)
{
    int remVuln;
    do /*Fazer enquanto o opcao do menu digitada for diferente das possibilidades apresentadas*/
    {
        printf("Digite o numero da vulnerabilidade que deseja remover: ");
        scanf("%d", &remVuln);
    } while (remVuln < 1 || remVuln > 50);
    remVuln = remVuln - 1; /*Recuar uma posicao na variavel, pois a posicao digitada pelo utilizador é a seguinte da requerida pelo mesmo*/
    for (int i = remVuln; i < auditoria[id].vuln[0].numero; i++)
    {
        auditoria[id].vuln[i] = auditoria[id].vuln[i + 1]; /*Recuar uma posicao no array para apagar a vulnerabilidade desejada*/
    }
    auditoria[id].vuln[0].numero = auditoria[id].vuln[0].numero - 1; /*Diminiur o numero de vulnerabilidades da auditoria pedida para a variavel inicial(diminui auditorias)*/
    printf("\n\nVulnerabilidade removida com sucesso!!!!!");
    return *auditoria;
}
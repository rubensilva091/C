#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

int main()
{
    int menuMain;
    gramm *gra = NULL;
    wordLen *wrdlen = NULL;
    wordFreq *wrdfreq = NULL;
    Histo his[1];
    do
    {
        printf("=======================================\n=============   MENU   ================\n=======================================\n");
        printf("\n-> (1) Tabela Categoria Gramatical\n-> (2) Tabela Tamanho Palavras\n-> (3) Certeza - Media e Desvio Padrao\n-> (4) Tamanho de Palavras - Medidas\n-> (5) Frequencias de Palavras - Quartis\n-> (6) Histograma das Probabilidades\n\n -> (0) Sair\n\n");
        printf(" > ");
        scanf("%d", &menuMain);
        system("cls");
        switch (menuMain)
        {
        case 1:
            if (!gra)
            {
                printf("Loading...");
                gra = readTxtGramm(gra);
                system("cls");
            }
            list_gram(gra);
            break;
        case 2:
            printf("Loading...");
            wrdlen = readTxtWordLen(wrdlen);
            system("cls");
            list_wordLen(wrdlen);
            break;
        case 3:
            if (!gra)
            {
                printf("Loading...");
                gra = readTxtGramm(gra);
                system("cls");
            }
            averageMorfo(gra);
            break;
        case 4:
            printf("Loading...");
            wrdlen = readTxtWordLen(wrdlen);
            system("cls");
            localWords(wrdlen);
            break;
        case 5:
            if (!wrdfreq)
            {
                printf("Loading...");
                wrdfreq = readTxtWordFreq(wrdfreq);
                system("cls");
            }
            list_wordFreq(wrdfreq);
            break;
        case 6:
            printf("Loading...");
            his[0] = readTxtHistogram(his[0]);
            system("cls");
            printHistogram(his[0]);
            break;
        case 0:
            break;
        default:
            printf("\t       ERRO!\n\t  Tente novamente!\n");
            break;
        }
        if (menuMain != 0)
        {
            printf("\n\n(1) VOLTAR AO MENU");
            printf("\n(0) SAIR\n > ");
            scanf("%d", &menuMain);
            system("cls");
        }
    } while (menuMain != 0);
    return 0;
}

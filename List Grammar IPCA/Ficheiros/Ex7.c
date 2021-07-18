#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*Increments each class*/
Histo saveHistogram(Histo his, double certain)
{
    int i;
    double x;
    x = 1 / (float)his.classes;

    for (i = 0; i < his.classes; i++)
    {
        if (certain < x * (i + 1) && certain > x * i)
        {
            his.count[i]++;
        }
    }
    return his;
}

/*Logarithmic function*/
double Log2n(int n)
{
    return (n > 1) ? 1 + Log2n(n / 2) : 1;
}

/*Gets the quantity of classes*/
Histo calcHistogram(Histo his)
{
    his.classes = (int)(1 + Log2n(his.total) + 0.5);
    return his;
}

/*Presents the histogram*/
void printHistogram(Histo his)
{
    int i, j, value;
    double x;
    x = 1 / (float)his.classes;
    printf("> Histograma da Medida de certeza de Etiquetacao.\n\n");
    for (i = 0; i < his.classes; i++)
    {
        printf("[%1.2f; %1.2f[ %-9d| ", i * x, (i + 1) * x, his.count[i]);

        value = (int)((float)his.count[i] / 10000 + 0.5);
        for (j = 0; j < value; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("\n%85sUnidades", "");
    printf("\nLegenda: ");
    printf("\n * = 10000 Unidades");
}
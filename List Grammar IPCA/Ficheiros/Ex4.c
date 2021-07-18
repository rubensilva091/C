#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*Lists morphological analysis details*/
void averageMorfo(gramm *gra)
{
  double average, deviation, aux;
  printf("|%-22s|%-22s|%-22s|\n", " Analise Morfologica", " Media Aritmetica da", "   Desvio Padrao da");
  printf("|%-22s|%-22s|%-22s|\n", "", "    Etiquetacao", "     Etiquetacao");
  for (; gra; gra = gra->next)
  {
    average = gra->sum / gra->counter;
    aux = (gra->sum2 / gra->counter) - (average * average);
    if (aux < 0)
    {
      aux = -aux;
    }
    deviation = sqrt(aux);
    printf("| %-21s| %-21f| %-21lf|\n", gra->name, average, deviation);
  }
}
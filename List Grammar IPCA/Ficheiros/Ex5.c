#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*Lists WordLenght's details*/
void localWords(wordLen *wrdlenght)
{
  float total = 0, average, deviation, sum = 0, x = 0, median, aux3, aux4;
  int mode, div = 0, i;
  wordLen *aux = wrdlenght;
  wordLen *aux2 = wrdlenght;
  printf("| %-21s| %-21s| %-21s| %-21s|\n", "Media Aritmetica ", "Mediana", "Moda", "Desvio Padrao");
  for (; aux2; aux2 = aux2->next)
  {
    total += ((aux2->wordSize) * (aux2->counterLen));
    div += aux2->counterLen;
    
    aux3 = (aux2->wordSize) * (aux2->wordSize);
    sum += (aux3 * aux2->counterLen);
    /*mode*/
    if (x < aux2->counterLen)
    {
      x = aux2->counterLen;
      mode = aux2->wordSize;
    }
  }
  /*Median*/
  if (div % 2 == 0)
  {
    for (i = 0; i < div / 2; i++)
    {
      if (aux->counterLen > 0)
      {
        aux->counterLen--;
      }
      else
      {
        aux = aux->next;
      }
    }

    if (aux->counterLen > 0)
    {
      median = (float)(aux->wordSize + aux->wordSize) / 2.0;
    }
    else
    {
      median = (float)(aux->wordSize + aux->next->wordSize) / 2.0;
    }
  }
  else
  {
    for (i = 0; i < div / 2; i++)
    {
      if (aux->counterLen > 0)
      {
        aux->counterLen--;
      }
      else
      {
        aux = aux->next;
      }
    }
    median = aux->wordSize;
  }

  average = total / (float)div;
  aux4 = (sum / (float)div) - (average * average);
  if (aux4 < 0)
  {
    aux4 = -aux4;
  }
  deviation = sqrt(aux4);
  printf("| %-21f| %-21f| %-21d| %-21f|\n", average, median, mode, deviation);
}
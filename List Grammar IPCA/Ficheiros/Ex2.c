#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*First function of Grammatical Category Counter*/
gramm *grammaticalCategoryCounter(gramm *gra, char *wordMorf, double certain)
{
  int aux = 0;
  if (gra)
  {
    aux = grammScanner(gra, wordMorf);
  }
  gra = gram_Insert(gra, wordMorf, certain, aux);
  return gra;
}

/*Scan Grammatical column of lines and verifies if it already exists*/
int grammScanner(gramm *gra, char *wordMorf)
{
  if (strcmp(wordMorf, gra->name) == 0)
  {
    return 1;
  }
  if (gra->next == NULL)
  {
    return 0;
  }
  return grammScanner(gra->next, wordMorf);
}

/*Insert the "wordMorfossintaxe" neatly and count it*/
gramm *gram_Insert(gramm *gra, char *wordMorf, double certain, int aux)
{
  gramm *new = (gramm *)malloc(sizeof(gramm));
  if (aux == 0)
  {
    new->name = strdup(wordMorf);
    new->counter = 1;
    new->sum = certain;
    new->sum2 = (certain * certain);
    new->next = NULL;
    new->next = gra;
    return new;
  }
  if (aux == 1)
  {
    if (gra != NULL)
    {
      new = gra;
      for (; new; new = new->next)
      {
        if (strcmp(new->name, wordMorf) == 0)
        {
          new->counter++;
          new->sum += certain;
          new->sum2 += (certain * certain);
          break;
        }
      }
      return gra;
    }
  }
  return gra;
}

/*Sort by amount of words in each category*/
gramm *sortGrammaticalOrder(gramm *gra)
{
  int x;
  float a, b;
  char *y;
  gramm *aux;
  gramm *aux2 = gra;
  gramm *empty = NULL;

  for (; aux2; aux2 = aux2->next)
  {
    aux = gra;
    while (aux->next != empty)
    {
      if ((aux->counter) >= (aux->next->counter))
      {
        /*Change Counter*/
        x = aux->counter;
        aux->counter = aux->next->counter;
        aux->next->counter = x;
        /*Change Name*/
        y = strdup(aux->name);
        aux->name = strdup(aux->next->name);
        aux->next->name = strdup(y);
        /*Change Sum*/
        a = aux->sum;
        aux->sum = aux->next->sum;
        aux->next->sum = a;
        /*Change Sum2*/
        b = aux->sum2;
        aux->sum2 = aux->next->sum2;
        aux->next->sum2 = b;
      }
      aux = aux->next;
    }
    empty = aux;
  }
  return empty;
}

/*List gramatical neatly and counted*/
void list_gram(gramm *gra)
{
  gramm *aux = gra;

  int total = 0, absoluteacc = 0, absolute;
  double relative = 0, relativeacc = 0;
  printf("|%-22s|%-22s|%-22s|%-22s|%-22s|\n", " Categoria Gramatical", " Frequencia Absoluta", " Frequencia Relativa", " Frequencia Absoluta", " Frequencia Relativa");
  printf("|%-22s|%-22s|%-22s|%-22s|%-22s|\n", "", "", "", "      Acumulada", "      Acumulada");

  while (gra)
  {
    total = total + gra->counter;
    gra = gra->next;
  }

  while (aux)
  {
    absolute = aux->counter;
    relative = absolute / (float)total;
    absoluteacc = absoluteacc + absolute;
    relativeacc = relativeacc + relative;
    printf("| %-21s| %-21d| %-21f| %-21d| %-21f|\n", aux->name, absolute, relative, absoluteacc, relativeacc);
    aux = aux->next;
  }
}
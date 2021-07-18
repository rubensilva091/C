#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*First function of Word Finder*/
wordFreq *wordFinder(wordFreq *wrdfreq, char *wordOri)
{
  int aux = 0;
  if (wrdfreq)
  {
    aux = wordFreqScanner(wrdfreq, wordOri);
  }
  wrdfreq = wordFreq_Insert(wrdfreq, wordOri, aux);
  return wrdfreq;
}

/*Scan Words column of lines and verifies if it already exists*/
int wordFreqScanner(wordFreq *wrdfreq, char *wordOri)
{
  if (stricmp(wordOri, wrdfreq->name) == 0)
  {
    return 1;
  }
  if (wrdfreq->next == NULL)
  {
    return 0;
  }
  return wordFreqScanner(wrdfreq->next, wordOri);
}

/*Insert the "Original word" neatly and count it*/
wordFreq *wordFreq_Insert(wordFreq *wrdfreq, char *wordOri, int aux)
{
  wordFreq *new = (wordFreq *)malloc(sizeof(wordFreq));
  if (aux == 0)
  {
    new->name = strdup(wordOri);
    new->counter = 1;
    new->next = NULL;
    new->next = wrdfreq;
    return new;
  }
  if (aux == 1)
  {
    new = wrdfreq;
    for (; new; new = new->next)
    {
      if (stricmp(new->name, wordOri) == 0)
      {
        new->counter++;
        break;
      }
    }
    return wrdfreq;
  }
  return wrdfreq;
}

/*Sort by Alphabetical Order*/
wordFreq *sortFrequency(wordFreq *wrdfreq)
{
  int x;
  char *y;
  wordFreq *aux;
  wordFreq *aux2 = wrdfreq;
  wordFreq *empty = NULL;

  for (; aux2; aux2 = aux2->next)
  {
    aux = wrdfreq;
    while (aux->next != empty)
    {
      if (aux->counter <= aux->next->counter)
      {
        /*Change Counter*/
        x = aux->counter;
        aux->counter = aux->next->counter; 
        aux->next->counter = x;
        /*Change Name*/
        y = strdup(aux->name);
        aux->name = strdup(aux->next->name);
        aux->next->name = strdup(y);
      }
      aux = aux->next;
    }
    empty = aux;
  }
  return empty;
}

/*Asks for a word and replies with the respective quartile*/
void list_wordFreq(wordFreq *wrdfreq)
{
  char c[600];
  float div;
  int valid, position = 0, total = 0, i;
  wordFreq *aux = wrdfreq;

  printf("Digite o nome da palavra que pretende procurar: ");
  getchar();
  gets(c);
  valid = wordFreqScanner(wrdfreq, c);
  if (valid == 0)
  {
    printf("Essa palavra nao existe!");
  }
  else
  {
    for (; aux; aux = aux->next)
    {
      total += aux->counter;
    }
    aux = wrdfreq;
    div = (float)total / 4;

    for (; aux; aux = aux->next)
    {
      if (stricmp(c, aux->name) == 0)
      {
        position++;
        break;
      }
      for (i = 0; i < aux->counter; i++)
        position++;
    }

    for (i = 1; i <= total; i++)
    {
      if (i == (int)div && position <= i)
      {
        printf("A palavra < %s > pertence ao Primeiro Quartil.", c);
        break;
      }
      if (i == (int)div * 2 && position <= i && position > div)
      {
        printf("A palavra < %s > pertence ao Segundo Quartil.", c);
        break;
      }
      if (i == (int)div * 3 && position <= i && position > div * 2)
      {
        printf("A palavra < %s > pertence ao Terceiro Quartil.", c);
        break;
      }
      if (i == total)
      {
        printf("A palavra < %s > pertence ao Quarto Quartil.", c);
      }
    }
  }
}
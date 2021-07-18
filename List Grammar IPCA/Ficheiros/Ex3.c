#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*First function of Word Lenght Counter*/
wordLen *wordLenCounter(wordLen *wrdlen, char *wordOri)
{
  int letterCounter, aux = 0;
  letterCounter = wordLetterCounter(wordOri);
  if (wrdlen)
  {
    aux = letterScanner(wrdlen, letterCounter);
  }

  wrdlen = wordLenghtInsert(wrdlen, aux, letterCounter);
  return wrdlen;
}

/*Function to count letters in each word*/
int wordLetterCounter(char *wordOri)
{
  int i;
  for (i = 0; wordOri[i]; i++)
    ;
  return i;
}

/*Scan Letter lenght of each word and verifies if it already exists*/
int letterScanner(wordLen *wrdlen, int letterCounter)
{
  if (wrdlen->wordSize == letterCounter)
  {
    return 1;
  }
  if (wrdlen->next == NULL)
  {
    return 0;
  }
  return letterScanner(wrdlen->next, letterCounter);
}

/*Insert the "wordLenght" neatly and count it*/
wordLen *wordLenghtInsert(wordLen *wrdlen, int aux, int letterCounter)
{
  wordLen *new = (wordLen *)malloc(sizeof(wordLen));
  if (aux == 0)
  {
    new->wordSize = letterCounter;
    new->counterLen = 1;
    new->next = NULL;
    new->next = wrdlen;
    return new;
  }
  if (aux == 1)
  {
    if (wrdlen != NULL)
    {
      new = wrdlen;
      for (; new; new = new->next)
      {
        if (new->wordSize == letterCounter)
        {
          new->counterLen++;
          break;
        }
      }
      return wrdlen;
    }
  }
  return wrdlen;
}

/*Sort by growing amount of letters in each word*/
wordLen *sortWordLen(wordLen *wrdlen)
{
  int x;
  wordLen *aux;
  wordLen *aux2 = wrdlen;
  wordLen *empty = NULL;

  for (; aux2; aux2 = aux2->next)
  {

    aux = wrdlen;
    while (aux->next != empty)
    {

      if ((aux->wordSize) >= (aux->next->wordSize))
      {

        /* Change counter*/
        x = aux->counterLen;
        aux->counterLen = aux->next->counterLen;
        aux->next->counterLen = x;

        /*Change wordsize*/
        x = aux->wordSize;
        aux->wordSize = aux->next->wordSize;
        aux->next->wordSize = x;
      }
      aux = aux->next;
    }
    empty = aux;
  }
  return empty;
}

/*List size of words and other details*/
void list_wordLen(wordLen *wrdlen)
{
  wordLen *aux = wrdlen;

  int total = 0, absoluteacc = 0, absolute;
  double relative = 0, relativeacc = 0;
  printf("|%-22s|%-22s|%-22s|%-22s|%-22s|\n", " Tamanho Palavra", " Frequencia Absoluta", " Frequencia Relativa", " Frequencia Absoluta", " Frequencia Relativa");
  printf("|%-22s|%-22s|%-22s|%-22s|%-22s|\n", "", "", "", "      Acumulada", "      Acumulada");

  while (wrdlen)
  {
    total = total + wrdlen->counterLen;
    wrdlen = wrdlen->next;
  }

  while (aux)
  {
    absolute = aux->counterLen;
    relative = absolute / (float)total;
    absoluteacc = absoluteacc + absolute;
    relativeacc = relativeacc + relative;
    printf("| %-21d| %-21d| %-21f| %-21d| %-21f|\n", aux->wordSize, absolute, relative, absoluteacc, relativeacc);
    aux = aux->next;
  }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../header.h"

/*Reads Grammatical Category Text's document*/
gramm *readTxtGramm(gramm *gra)
{
  FILE *file = fopen("FicheirosLeitura/slate-tagged", "r");
  int count = 0;
  char wO[600], wR[600], wM[600];
  double c = 0;
  if (file == NULL)
  {
    printf("\nERRO! Nenhum texto detetado.\n");
    return gra;
  }
  while (fscanf(file, "%s %s %s %lf", wO, wR, wM, &c) == 4)
  {
    count = scannerSymbols(wO);
    if (count == 1)
    {
      gra = grammaticalCategoryCounter(gra, wM, c);
    }
  }
  fclose(file);
  gra = sortGrammaticalOrder(gra);
  return gra;
}

/*Reads Word Lenght Text's document*/
wordLen *readTxtWordLen(wordLen *wrdlen)
{
  FILE *file = fopen("FicheirosLeitura/slate-tagged", "r");
  int count = 0;
  char wO[600], wR[600], wM[600];
  double c = 0;
  if (file == NULL)
  {
    printf("\nERRO! Nenhum texto detetado.\n");
    return wrdlen;
  }
  while (fscanf(file, "%s %s %s %lf", wO, wR, wM, &c) == 4)
  {
    count = scannerSymbols(wO);
    if (count == 1)
    {
      wrdlen = wordLenCounter(wrdlen, wO);
    }
  }
  fclose(file);
  wrdlen = sortWordLen(wrdlen);
  return wrdlen;
}

/*Reads Word Frequency Text's document*/
wordFreq *readTxtWordFreq(wordFreq *wrdfreq)
{
  FILE *file = fopen("FicheirosLeitura/Texto.txt", "r");
  int count = 0;
  char wO[600], wR[600], wM[600];
  double c = 0;
  if (file == NULL)
  {
    printf("\nERRO! Nenhum texto detetado.\n");
    return wrdfreq;
  }
  while (fscanf(file, "%s %s %s %lf", wO, wR, wM, &c) == 4)
  {
    count = scannerSymbols(wO);
    if (count == 1)
    {
      wrdfreq = wordFinder(wrdfreq, wO);
    }
  }
  fclose(file);
  wrdfreq = sortFrequency(wrdfreq);
  return wrdfreq;
}

/*Reads Certain Text's document*/
Histo readTxtHistogram(Histo his)
{
  FILE *file = fopen("FicheirosLeitura/slate-tagged", "r");
  int count = 0, i;
  char wO[600], wR[600], wM[600];
  double c = 0;
  if (file == NULL)
  {
    printf("\nERRO! Nenhum texto detetado.\n");
    return his;
  }
  his.total = 0;
  for (i = 0; i < 30; i++)
  {
    his.count[i]=0;
  }
  while (fscanf(file, "%s %s %s %lf", wO, wR, wM, &c) == 4)
  {
    count = scannerSymbols(wO);
    if (count == 1)
    {
      his.total++;
    }
  }
  fclose(file);

  his=calcHistogram(his);

  file = fopen("FicheirosLeitura/slate-tagged", "r");

  while (fscanf(file, "%s %s %s %lf", wO, wR, wM, &c) == 4)
  {
    count = scannerSymbols(wO);
    if (count == 1)
    {
      his = saveHistogram(his, c);
    }
  }

  return his;
}

/*Scan Symbols of text's lines*/
int scannerSymbols(char c[600])
{
  char *scan = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwyxz";
  int i, j;
  for (i = 0; c[i]; i++)
  {
    for (j = 0; scan[j]; j++)
    {
      if (c[i] == scan[j])
        return 1;
    }
  }
  return 0;
}
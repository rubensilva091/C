#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef HEADER_H_
#define HEADER_H_

typedef struct _gramm
{
    char *name;
    int counter;
    double sum;
    double sum2;
    struct _gramm *next;
} gramm;

typedef struct _wordLen
{

    int wordSize, counterLen;
    struct _wordLen *next;
} wordLen;

typedef struct _wordFreq
{
    char *name;
    int counter;
    struct _wordFreq *next;
} wordFreq;


typedef struct _Histo
{
    int count[30], total, classes;
} Histo;


/*Ex.1*/
gramm *readTxtGramm(gramm *gra);
wordLen *readTxtWordLen(wordLen *wrdlen);
wordFreq *readTxtWordFreq(wordFreq *wrdfreq);
Histo readTxtHistogram(Histo his);
int scannerSymbols(char c[600]);

/*Ex.2*/
gramm *grammaticalCategoryCounter(gramm *gra, char *wordMorf, double certain);
int grammScanner(gramm *gra, char *wordMorf);
gramm *gram_Insert(gramm *gra, char *wordMorf, double certain, int x);
gramm *sortGrammaticalOrder(gramm *gra);
void list_gram(gramm *gra);

/*Ex.3*/
wordLen *wordLenCounter(wordLen *wrdlen, char *wordOri);
int wordLetterCounter(char *wordOri);
int letterScanner(wordLen *wrdlen, int letterCounter);
wordLen *wordLenghtInsert(wordLen *wrdlen, int aux, int letterCounter);
wordLen *sortWordLen(wordLen *wrdlen);
void list_wordLen(wordLen *wrdlen);

/*Ex.4*/
void averageMorfo(gramm *gra);

/*EX.5*/
void localWords(wordLen *wrdlen);
float median(int x, int *y);

/*EX.6*/
wordFreq *wordFinder(wordFreq *wrdfreq, char *wordOri);
int wordFreqScanner(wordFreq *wrdfreq, char *wordOri);
wordFreq *wordFreq_Insert(wordFreq *wrdfreq, char *wordOri, int x);
wordFreq *sortFrequency(wordFreq *wrdfreq);
void list_wordFreq(wordFreq *wrdfreq);


/*EX.7*/
Histo saveHistogram(Histo his, double certain);
void printHistogram(Histo his);
Histo calcHistogram(Histo his);
double Log2n(int n);

#endif
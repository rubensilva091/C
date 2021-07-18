/**
 * @file Ficheiro que contem as funcoes da manipulacao da stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"
#include "array.h"
#include "string.h"
#include "token.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief Funcao que calcula o tamanho da stack
 *
 * Esta funcao recebe os dados e calcula o tamanho da stack
 *
 * @param dados receber a stack
 * @returns i tamanho da string 
 */
int lastPosition(stack *dados)
{
  int i;
  for (i = 0; dados[i].caracter; i++)
    ;
  return i;
}

/**
 * \brief Funcao que descobre se é float
 *
 * Esta funcao recebe os dados e calcula o tamanho da stack
 *
 * @param c recebe o numero
 * @returns 1 Se for float
 * @returns 0 Se não for float
 */
int isfloat(char *c)
{
  int i;
  for (i = 0; c[i]; i++)
  {
    if (isdigit(c[i]) != 0)
    {
      continue;
    }
    else
    {
      if (i > 0)
      {
        if (c[i] == '.')
        {
          return 1;
        }
        break;
      }
    }
  }
  return 0;
}

/**
 * \brief Funcao do Array "POP_Trash"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da stack
 * Esta funcao apaga o lixo todo
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void POP_Trash(stack *dados)
{
  int i;
  for (i = 0; dados[i].caracter; i++)
  {
    if (dados[i].tag == trash)
    {
      POP(dados, i);
      i--;
    }
  }
}
/**
 * \brief Funcao que calcula troca 2 posiçoes na STACK
 *
 * Esta funcao recebe os dados e troca 2 membros da stack
 *
 * @param dados receber a stack
 * @returns count numero de operadores
 */
void swap(stack *dados, int pos)
{
  stack aux = dados[pos];
  dados[pos] = dados[pos - 1];
  dados[pos - 1] = aux;
}

/**
 * \brief Funcao remove o index atual
 *
 * Esta funcao recebe os dados e remove o index atual puxando toda a estrutura para a posicao atual
 *
 * @param dados receber a stack
 * @param i posicao atual
 */
void removeIndex(stack *dados, int i)
{
  int y;
  int siz = lastPosition(dados);
  for (y = i; y < siz; y++)
  {
    dados[y] = dados[y + 1];
  }
}

/**
 * \brief Funcao cria o index atual
 *
 * Esta funcao recebe os dados e cria o index atual empurrando toda a estrutura para a posicao final
 *
 * @param dados receber a stack
 * @param i posicao atual
 */
void createIndex(stack *dados, int i)
{
  int y;
  int siz = lastPosition(dados);
  for (y = siz - 1; y >= i; y--)
  {
    dados[y + 1] = dados[y];
  }
}

/**
 * \brief Funcao pusha o valor do array
 *
 * Esta funcao recebe os dados e retorna o index atual
 *
 * @param dados receber a stack
 * @param pos posicao atual
 * @returns j valor em inteiro/float dentro da Stack ou o valor da Variavel
 * @returns t valor em float dentro da Stack (normalmente em Letras)
 */
double PUSH(stack *dados, int pos)
{
  double j = 0;
  int t;
  if (dados[pos].tag == variavel || dados[pos].tag == variavelFantasma)
  {
    j = atof(dados[pos].variavel);
    return j;
  }
  if (dados[pos].tag == nothing)
  {
    char *aux = malloc(SIZE);
    aux[0] = dados[pos].caracter[0];
    t = (int)(aux[0]);
    j = t;
    return j;
  }
  j = atof(dados[pos].caracter);
  return j;
}

/**
 * \brief Funcao usa o removeIndex
 *
 * Esta funcao recebe os dados e remove o index atual por meio da funcao do removeIndex
 *
 * @param dados receber a stack
 * @param pos posicao atual
 */
void POP(stack *dados, int pos)
{
  removeIndex(dados, pos);
}

/**
 * \brief Funcao strdup
 *
 * strdup é função que cria uma copia de uma string, esta função foi reescrita para evitar warnings
 * Os warnings aconteciam pois ela existia no sistema, mas não estava oficialmente declarada, isto acontece devido à
 * sua exclusão do "standard" da linguagem C
 *
 * @param dados receber a stack
 * @param pos posicao atual
 */
char *strdup(const char *str)
{
  int n = strlen(str) + 1;
  char *dup = malloc(n);
  if (dup)
  {
    strcpy(dup, str);
  }
  return dup;
}

/**
 * \brief Funcao que mostra a Variavel
 *
 * Esta funcao mostra o conteudo da variavel de formas ramificadas devido a strings e limites tem de ser mostrado de maneiras diferentes
 *
 * @param dados receber a stack
 * @param pos posicao atual
 */
void mostrarVariavel(stack *dados, int pos)
{
  if (dados[pos].variavel[0] == '[')
  {
    mostrarVariavelArray(dados, pos);
  }
  else
  {
    printf("%s", dados[pos].variavel);
  }
}

/**
 * \brief Funcao para mostrar a stack
 *
 * Esta funcao recebe os dados e mostra a stack por meio de um ciclo for e algumas verificacoes em relacao ao token
 *
 * @param dados receber a stack
 */
void DISPLAY(stack *dados)
{
  int i;
  int len = lastPosition(dados);
  for (i = 0; i < len; i++)
  {
    if (dados[i].caracter[0] == '[' || dados[i].caracter[0] == ']')
    {
      continue;
    }
    if (dados[i].tag == numInteiro || dados[i].tag == numInteiroFunc)
    {
      int j = atof(dados[i].caracter);
      printf("%d", j);
    }
    else if (dados[i].tag == numFloat || dados[i].tag == numFloatFunc)
    {
      double j = atof(dados[i].caracter);
      printf("%.6g", j);
    }
    else if (dados[i].tag == variavel)
    {
      lerVariaveilFanstasma(dados, i);
      mostrarVariavel(dados, i);
    }
    else if (dados[i].tag == variavelFantasma)
    {
      continue;
    }
    else
    {
      naoMostrarAspas(dados, i);
    }
  }
}

/**
 * \brief Funcao Para substituir da stack
 *
 * Funcao que substitui na stack por algo pretendido
 *
 * @param dados receber a stack
 * @param pos receber a stack
 * @param c recebr a string pretendida
 */
void substituirStack(stack *dados, int pos, char *c)
{
  char *aux = malloc(SIZE);
  strcpy(aux, c);
  dados[pos].caracter = aux;
}

/**
 * \brief Funcao igual à strlen
 *
 * Funcao exatamente igual a strlen, tem de sofrer alteracoes mais tarde
 *
 * @param dados receber a stack
 */
int sizeChar(char *c)
{
  int i;
  for (i = 0; c[i]; i++)
    ;
  return i;
}

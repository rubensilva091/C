/**
 * @file Ficheiro que contem as funcoes das Strings
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "interpretador.h"
#include "token.h"
#include "stack.h"
#include "array.h"
#include "string.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief Funcao da String "naoMostrarAspas"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Serve para mostrar a funcao a string sem aspas
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void naoMostrarAspas(stack *dados, int pos)
{

  int i;
  for (i = 0; dados[pos].caracter[i]; i++)
  {
    if (dados[pos].caracter[i] != '"')
    {
      printf("%c", dados[pos].caracter[i]);
    }
  }
}

/**
 * \brief Funcao da String "multString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Junta varias vezes a mesma string
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void multString(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == string)
  {
    int i, t, counter = 1;
    char *aux = malloc(SIZE);
    aux[0] = '"';
    for (i = valor; i > 0; i--)
    {
      for (t = 0; dados[pos - 2].caracter[t]; t++)
      {
        if (dados[pos - 2].caracter[t] != '"')
        {
          aux[counter] = dados[pos - 2].caracter[t];
          counter++;
        }
      }
    }
    aux[counter] = '"';
    POP(dados, pos - 1);
    POP(dados, pos - 2);
    dados[pos - 2].caracter = aux;
  }
}

/**
 * \brief Funcao da String "JuntaStrings"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai juntar 2 strings de duas maneiras:
 * 1 -> se for 2 strings, junta as duas strings
 * 2 -> se for 1 sgring e algo diferente de um array, junta ou à esquerda, ou à direita da string e da POP
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void juntarString(stack *dados, int pos)
{
  if ((dados[pos - 1].tag != limite && dados[pos - 1].tag != limite) && (dados[pos - 1].tag == string || dados[pos - 2].tag == string))
  {
    variavelString(dados, pos);
    POP(dados, pos);
    strcat(dados[pos - 2].caracter, dados[pos - 1].caracter);
    POP(dados, pos - 1);
    removeAspasInternas(dados, pos - 2);
    if (dados[pos - 2].caracter[strlen(dados[pos - 2].caracter)] != '"')
    {
      dados[pos - 2].caracter[strlen(dados[pos - 2].caracter)] = '"';
    }
  }
}

/**
 * \brief Funcao da String "variavelString"
 *
 * Esta funcao troca o careter pela variavel para uma melhor manipulação
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void variavelString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == variavel)
  {
    char *aux = malloc(SIZE);
    aux = dados[pos - 1].variavel;
    dados[pos - 1].caracter = aux;
  }
  if (dados[pos - 2].tag == variavel)
  {
    char *aux = malloc(SIZE);
    aux = dados[pos - 2].variavel;
    dados[pos - 2].caracter = aux;
  }
}

/**
 * \brief Funcao da String "removeAspasInternas"
 *
 * Esta funcao remove aspas no meio de uma string
 * Por exemplo : "ola" " mundo" +
 * "ola"" mundo" -> "ola mundo"
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void removeAspasInternas(stack *dados, int pos)
{
  int i, y;
  for (i = 1; dados[pos].caracter[i + 1] != '\0'; i++)
  {
    if (dados[pos].caracter[i] == '"')
    {
      for (y = i; dados[pos].caracter[y] != '\0'; y++)
      {
        dados[pos].caracter[y] = dados[pos].caracter[y + 1];
      }
      i--;
    }
  }
}

/**
 * \brief Funcao da String "rangeString"
 *
 * Esta funcao calcula o tamanho da string excluindo as aspas
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void rangeString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string || dados[pos - 1].tag == variavel)
  {
    int i, key = 0;
    char *aux = malloc(SIZE);
    variavelString(dados, pos);
    POP(dados, pos);
    if (dados[pos - 1].caracter[0] == '"')
    {
      for (i = 0; dados[pos - 1].caracter[i]; i++)
      {
        if (key == 0 && dados[pos - 1].caracter[i] == '\n')
        {
          key++;
        }
      }
      sprintf(aux, "%d", i - 2 + key);
      dados[pos - 1].caracter = aux;
    }
    else
    {
      int y = 0;
      for (i = 0; dados[pos - 1].caracter[i]; i++)
      {
        if (dados[pos - 1].caracter[i] != ' ')
        {
          y++;
        }
        if (key == 0 && dados[pos - 1].caracter[i] == '\n')
        {
          key++;
        }
      }
      sprintf(aux, "%d", y - 2 + key);
      dados[pos - 1].caracter = aux;
      POP(dados, pos - 2);
    }
  }
}

/**
 * \brief Funcao da String "buscarN_elementosMaiorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao vai buscar os valores por ordem decrescente na string baseado no input do utilizador
 * No final apaga a string
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void buscarN_elementosMaiorString(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == string)
  {
    char *aux = malloc(SIZE);
    int i, counter = -2, y = 1;
    POP(dados, pos);
    POP(dados, pos - 1);
    for (i = 0; dados[pos - 2].caracter[i]; i++)
    {
      counter++;
      aux[i] = '\0';
    }
    aux[0] = '"';
    for (i = valor; i > 0; i--)
    {
      aux[y] = dados[pos - 2].caracter[counter - i + 1];
      y++;
    }
    aux[y] = '"';
    dados[pos - 2].caracter = aux;
  }
}

/**
 * \brief Funcao da String "buscarN_elementosMenorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao vai buscar os valores por ordem crescente na string baseado no input do utilizador
 * No final apaga a string
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void buscarN_elementosMenorString(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == string)
  {
    char *aux = malloc(SIZE);
    int i, y = 0;
    POP(dados, pos);
    POP(dados, pos - 1);
    for (i = 0; dados[pos - 2].caracter[i]; i++)
    {
      aux[i] = '\0';
    }
    for (i = valor; i >= 0; i--)
    {
      aux[y] = dados[pos - 2].caracter[y];
      y++;
    }
    aux[y] = '"';
    dados[pos - 2].caracter = aux;
  }
}

/**
 * \brief Funcao da String "ultimoElementoString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao vai buscar o ultimo Elemento da string
 * Retira-a da stack e coloca-o à frente
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void ultimoElementoString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    int i;
    char *aux1 = malloc(SIZE);
    char *aux2 = malloc(SIZE);
    for (i = 0; dados[pos - 1].caracter[i]; i++)
    {
      aux1[i] = '\0';
      aux2[i] = '\0';
    }
    aux2[0] = dados[pos - 1].caracter[i - 1];
    aux1[0] = dados[pos - 1].caracter[i - 2];
    substituirStack(dados, pos, aux1);
    dados[pos].tag = nothing;
    dados[pos - 1].caracter[i - 1] = dados[pos - 1].caracter[i];
    dados[pos - 1].caracter[i - 2] = aux2[0];
  }
}

/**
 * \brief Funcao da String "primeiroElementoString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao vai buscar o primeiro Elemento da string
 * Retira-a da stack e coloca-o à frente
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void primeiroElementoString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    int i = 1;
    char *aux = malloc(SIZE);
    aux[0] = dados[pos - 1].caracter[i];
    for (i = 1; dados[pos - 1].caracter[i]; i++)
    {
      dados[pos - 1].caracter[i] = dados[pos - 1].caracter[i + 1];
    }
    removeAspasInternas(dados, pos - 1);
    substituirStack(dados, pos, aux);
    dados[pos].tag = nothing;
  }
}

/**
 * \brief Funcao da String "procurarString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao procura a existencia de uma substring na string pretendida
 * Se existir o output é o index
 * Se nao existir é -1
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void procurarSubstring(stack *dados, int pos, char *c)
{
  int size = 0, i;
  char *aux = malloc(SIZE);
  char *aux2 = malloc(SIZE);
  char *aux3 = malloc(SIZE);
  for (i = 0; c[i + 2]; i++)
  {
    aux2[i] = c[i + 1];
    aux2[i + 1] = '\0';
  }
  aux3 = strstr(dados[pos - 2].caracter, aux2);
  if (aux3 != NULL)
  {
    size = aux3 - dados[pos - 2].caracter;
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  sprintf(aux, "%d", size - 1);
  dados[pos - 2].caracter = aux;
}

/**
 * \brief Funcao da String "separarStringSubstring"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao corta a string principal pela substring e cria um array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void separarStringSubstring(stack *dados, int pos, char *c)
{
  int i, key = 0;
  char *aux1 = malloc(SIZE);
  char *aux2 = malloc(SIZE);
  char *aux3 = malloc(SIZE);
  stack *auxStack = malloc(SIZE);
  aux3 = strdup(dados[pos - 2].caracter);
  aux1 = strdup(dados[pos - 2].caracter);
  if (dados[pos - 2].tag == variavel)
  {
    aux1 = strdup(dados[pos - 2].variavel);
  }
  strcpy(aux2, c);
  if (dados[pos - 1].tag == string)
  {
    for (i = 0; c[i + 2]; i++)
    {
      key = 1;
      aux2[i] = c[i + 1];
    }
  }
  i = 0;
  if (key == 0 && aux2[0] != ' ' && aux2[0] != '\n')
  {
    i = separarStringLetra_Letra(dados, pos);
  }
  if (key == 1 || aux2[0] == ' ' || aux2[0] == '\n')
  {
    if (aux2[0] == ' ')
    {
      strcat(aux2, "\n");
    }
    for (auxStack[i].caracter = strtok(aux1, aux2); auxStack[i].caracter != NULL; auxStack[i].caracter = strtok(NULL, aux2))
    {
      createIndex(dados, pos + 1 + i);
      adicionarAspas(auxStack, i);
      dados[pos + 1 + i].tag = string;
      dados[pos + 1 + i].caracter = auxStack[i].caracter;
      i++;
    }
  }
  dados[pos - 2].caracter = aux3;
  substituirStack(dados, pos, "[");
  createIndex(dados, pos + i + 1);
  substituirStack(dados, pos + i + 1, "]");
  POP(dados, pos - 1);
  POP(dados, pos - 2);
}

/**
 * \brief Funcao da String "separarStringLetra_Letra"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao corta a string principal letra a letra e cria um array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int separarStringLetra_Letra(stack *dados, int pos)
{
  int i;
  for (i = 0; dados[pos - 2].caracter[i + 2]; i++)
  {
    char *aux = malloc(SIZE);
    aux[0] = dados[pos - 2].caracter[i + 1];
    createIndex(dados, pos + 1 + i);
    dados[pos + 1 + i].caracter = aux;
    adicionarAspas(dados, pos + 1 + i);
    dados[pos + 1 + i].tag = string;
  }
  return i;
}

/**
 * \brief Funcao da String "adiconarAspas"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao quando chamada, adiciona aspas na string pretendida
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void adicionarAspas(stack *dados, int pos)
{
  int i;
  char *aux = malloc(SIZE);
  aux[0] = '"';
  for (i = 0; dados[pos].caracter[i]; i++)
  {
    aux[i + 1] = dados[pos].caracter[i];
  }
  aux[i + 1] = '"';
  aux[i + 2] = '\0';
  dados[pos].caracter = aux;
  removeAspasInternas(dados, pos);
}

/**
 * \brief Funcao da String "comparar Strings"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao compara se 2 strings sao iguais ignorando as "
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void compararStrings(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    char *aux = malloc(SIZE);
    sprintf(aux, "%d", 0);
    if (strstr(dados[pos - 2].caracter, dados[pos - 1].caracter))
    {
      sprintf(aux, "%d", 1);
    }
    dados[pos].caracter = aux;
    POP(dados, pos - 1);
    POP(dados, pos - 2);
  }
}

/**
 * \brief Funcao da String "maiorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao compara qual das duas strings é maior ignorando as "
 * O output é 0 ou 1, falso ou verdade respetivamente 
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void maiorString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    char *aux = malloc(SIZE);
    sprintf(aux, "%d", 0);
    if (strcmp(dados[pos - 2].caracter, dados[pos - 1].caracter) > 0)
    {
      sprintf(aux, "%d", 1);
    }
    dados[pos].caracter = aux;
    POP(dados, pos - 1);
    POP(dados, pos - 2);
  }
}

/**
 * \brief Funcao da String "menorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao compara qual das duas strings é menor ignorando as "
 * O output é 0 ou 1, falso ou verdade respetivamente 
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void menorString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    char *aux = malloc(SIZE);
    sprintf(aux, "%d", 0);
    if (strcmp(dados[pos - 2].caracter, dados[pos - 1].caracter) < 0)
    {
      sprintf(aux, "%d", 1);
    }
    dados[pos].caracter = aux;
    POP(dados, pos - 1);
    POP(dados, pos - 2);
  }
}

/**
 * \brief Funcao da String "e_maiorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao compara qual das duas strings é menor ignorando as "
 * Dá Pop à maior string
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_maiorString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    POP(dados, pos);
    if (strcmp(dados[pos - 2].caracter, dados[pos - 1].caracter) > 0)
    {
      POP(dados, pos - 1);
    }
    else
    {
      POP(dados, pos - 2);
    }
  }
}

/**
 * \brief Funcao da String "e_menorString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao compara qual das duas strings é menor ignorando as "
 * Dá Pop à menor string
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_menorString(stack *dados, int pos)
{
  if (dados[pos - 1].tag == string)
  {
    POP(dados, pos);
    if (strcmp(dados[pos - 2].caracter, dados[pos - 1].caracter) < 0)
    {
      POP(dados, pos - 1);
    }
    else
    {
      POP(dados, pos - 2);
    }
  }
}

/**
 * \brief Funcao da String "pesquisarStringindex"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao pesquisa baseado no index dado pelo utilizador
 * Coloca na stack o char pretendido da string
 * Da POP à string
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void pesquisarStringIndex(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == string || dados[pos - 2].tag == variavel)
  {
    char *aux = malloc(SIZE);
    variavelString(dados, pos - 1);
    aux[0] = dados[pos - 2].caracter[valor + 1];
    aux[1] = '\0';
    dados[pos].caracter = aux;
    dados[pos].tag = nothing;
    POP(dados, pos - 1);
    POP(dados, pos - 2);
  }
}

/**
 * \brief Funcao da String "concatStringsAte"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual da string
 * Esta funcao concatena tudo o que tem tag nothing até encontrar uma string
 * Esta funcao foi desenvolvida para o guiao 5
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void concatStringsAte(stack *dados, int pos)
{
  int i;
  char *aux = malloc(SIZE);
  strcpy(aux, "");
  POP(dados, pos);
  for (i = 1; dados[pos - i].caracter; i++)
  {
    if (dados[pos - i].tag != string && dados[pos - i].tag != trash)
    {
      strcat(aux, dados[pos - i].caracter);
      POP(dados, pos - i);
    }
    else if (dados[pos - i].tag == trash)
    {
      POP(dados, pos - i);
      POP(dados, pos - i - 1);
      break;
    }
    else
    {
      if (aux != NULL)
      {
        createIndex(dados, pos - i);
        substituirStack(dados, pos - i + 1, aux);
        createIndex(dados, pos - i + 2);
        substituirStack(dados, pos - i + 2, "+");
        dados[pos - i + 2].tag = expressaoMat;
      }
      break;
    }
  }
}
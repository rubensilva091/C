/**
 * @file Ficheiro que contem as funcoes dos Arrays
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
 * \brief Funcao do Array "EncontraLimiteInferior"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Dado a posição do limite inferior, esta funcao vai descobrir o inferior para uma localização aritmetica do array
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 * @return (i+1) a posicao aritmetica + 1
 */
int encontrarLimiteInferior(stack *dados, int pos)
{
  int i;
  for (i = 1; dados[pos - 2].tag != limite && dados[pos - 2].caracter; i++)
  {
    pos--;
  }
  return (i + 1);
}

/**
 * \brief Funcao do Array "juntarArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai juntar 2 arrays de duas maneiras:
 * 1 -> se for 2 arrays, vai simplesmente dar POP dos limites internos dos dois, fazem assim um concat
 * 2 -> se for 1 array e algo diferente de um array, simplesmente vai dar swap na sua posição
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void juntarArray(stack *dados, int pos)
{
  if (dados[pos - 1].tag == limite || dados[pos - 2].tag == limite)
  {
    int x = encontrarLimiteInferior(dados, pos);
    POP(dados, pos);
    if (dados[pos - x - 1].tag != limite)
    {
      if (dados[pos - 1].tag == limite)
      {
        swap(dados, pos - x);
      }
      else
      {
        swap(dados, pos - x + 1);
      }
    }
    else
    {
      POP(dados, pos - x);
      POP(dados, pos - x - 1);
    }
  }
}

/**
 * \brief Funcao do Array "trocaArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Para trocar o array, visto este estar diretamente presente na Stack
 * Primeiro descubrirmos todos os limites
 * Existe uma reversão individual de cada Array e uma posterior reversão total, como exemplo abaixo:
 * [ 1 2 3 ] [ 7  8 9 ] \   -> ] 3 2 1 [ ] 9 8 7 [  ->  [ 7 8 9 ] [ 3 2 1 ]
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void trocarArray(stack *dados, int pos)
{
  int x = encontrarLimiteInferior(dados, pos - 1);
  if (dados[pos - 1].tag == limite && dados[pos - x - 2].tag == limite)
  {
    int i;
    int pos2 = pos - encontrarLimiteInferior(dados, pos);
    int pos3 = pos2 - encontrarLimiteInferior(dados, pos2);
    int end = pos - 1;
    POP(dados, pos);
    reverseArray(dados, pos);
    reverseArray(dados, pos2);
    for (i = pos3; i < end; i++)
    {
      stack aux = dados[i];
      dados[i] = dados[end];
      dados[end] = aux;
      end--;
    }
  }
}

/**
 * \brief Funcao do Array "reverseArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao utilizada na funcao, "trocaArray"
 * Esta funcao reverte 1 array dado o limite superior
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void reverseArray(stack *dados, int pos)
{
  int i;
  int end = encontrarLimiteInferior(dados, pos) - 1;
  int x = end + 1;
  for (i = 0; i < end; i++) /*Começa em 1 para ignorar os paranteses*/
  {
    stack aux = dados[pos - 1 - i];
    dados[pos - 1 - i] = dados[pos - x + i];
    dados[pos - x + i] = aux;
    end--;
  }
}

/**
 * \brief Funcao do Array "multArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao escreve varias vezes o array pretendido e dps junta-os
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void multArray(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == limite)
  {
    int i, t, x, counter = 0;
    x = encontrarLimiteInferior(dados, pos - 1);
    POP(dados, pos);
    POP(dados, pos - 1);
    for (i = valor - 1; i > 0; i--)
    {
      for (t = 0; t < x; t++)
      {
        char *aux = malloc(SIZE);
        strcpy(aux, dados[pos - x + t - 1].caracter);
        createIndex(dados, pos - 1 + counter);
        dados[pos - 1 + counter].caracter = aux;
        counter++;
      }
      createIndex(dados, pos - 1 + counter);
      substituirStack(dados, pos - 1 + counter, "+");
    }
  }
}

/**
 * \brief Funcao do Array "pesquisarArrayIndex"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao pesquisa no Array e se existir susbtitui fora do array
 * No fim apaga o array todo
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void pesquisarArrayIndex(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == limite)
  {
    char *aux = malloc(SIZE);
    int x = encontrarLimiteInferior(dados, pos - 2);
    strcpy(aux, dados[pos - x - 1 + valor].caracter);
    POP(dados, pos - 1);
    dados[pos - 1].caracter = aux;
    POP_ARRAY(dados, pos - 1);
  }
}

/**
 * \brief Funcao do Array "POP_ARRAY"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao apaga o array todo baseado no limite inferior
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void POP_ARRAY(stack *dados, int pos)
{
  int i = 1;
  int x = encontrarLimiteInferior(dados, pos);
  for (i = 1; i <= x; i++)
  {
    POP(dados, pos - x);
  }
}

/**
 * \brief Funcao do Array "negarArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao apaga os limites do array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void negarArray(stack *dados, int pos)
{
  int x = encontrarLimiteInferior(dados, pos);
  POP(dados, pos);
  POP(dados, pos - 1);
  POP(dados, pos - x);
}

/**
 * \brief Funcao do Array "rangeArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao calcula o tamanho do Array e coloca o valor na stack
 * No final apaga o array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void rangeArray(stack *dados, int pos)
{
  if (dados[pos - 1].tag == limite)
  {
    char *aux = malloc(SIZE);
    int x = encontrarLimiteInferior(dados, pos) - 2;
    POP(dados, pos - 1);
    sprintf(aux, "%d", x);
    dados[pos - 1].caracter = aux;
    POP_ARRAY(dados, pos - 1);
  }
}

/**
 * \brief Funcao do Array "buscarN_elementosMaior"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai buscar os valores por ordem decrescente no array baseado no input do utilizador
 * No final apaga o array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void buscarN_elementosMaior(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == limite)
  {
    int i, counter = 0;
    POP(dados, pos);
    POP(dados, pos - 1);
    POP(dados, pos - 2);
    for (i = valor; i > 0; i--)
    {
      char *aux = malloc(SIZE);
      strcpy(aux, dados[pos - i - 2].caracter);
      createIndex(dados, pos - 2 + counter);
      dados[pos - 2 + counter].caracter = aux;
      counter++;
    }
    POP_ARRAY(dados, pos - 2);
  }
}

/**
 * \brief Funcao do Array "buscarN_elementosMenor"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai buscar os valores por ordem crescente no array baseado no input do utilizador
 * No final apaga o array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void buscarN_elementosMenor(stack *dados, int pos, int valor)
{
  if (dados[pos - 2].tag == limite)
  {
    int i, counter = 0;
    int x = encontrarLimiteInferior(dados, pos - 1);
    POP(dados, pos);
    POP(dados, pos - 1);
    POP(dados, pos - 2);
    for (i = valor; i > 0; i--)
    {
      char *aux = malloc(SIZE);
      strcpy(aux, dados[pos - x + (valor - i)].caracter);
      createIndex(dados, pos - 2 + counter);
      dados[pos - 2 + counter].caracter = aux;
      counter++;
    }
    POP_ARRAY(dados, pos - 2);
  }
}

/**
 * \brief Funcao do Array "ultimoElemento"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai buscar o ultimo Elemento do array
 * Retira-o da stack e coloca-o à frente
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void ultimoElemento(stack *dados, int pos)
{
  if (dados[pos - 1].tag == limite)
  {
    POP(dados, pos);
    swap(dados, pos - 1);
  }
}

/**
 * \brief Funcao do Array "primeiroElemento"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao vai buscar o primeiro Elemento do array
 * Retira-o da stack e coloca-o à frente
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void primeiroElemento(stack *dados, int pos)
{
  if (dados[pos - 1].tag == limite)
  {
    int x = encontrarLimiteInferior(dados, pos - 1);
    char *aux = malloc(SIZE);
    aux = dados[pos - x].caracter;
    dados[pos].caracter = aux;
    POP(dados, pos - x);
  }
}

/**
 * \brief Funcao do Array "duplicarArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao duplica o Array usando a funcao multArray e depois adiciona os limites
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void duplicarArray(stack *dados, int pos)
{
  createIndex(dados, pos);
  multArray(dados, pos + 1, 2);
  POP(dados, pos);
  swap(dados, pos);
  createIndex(dados, pos - 1);
  substituirStack(dados, pos - 1, "]");
  substituirStack(dados, pos + 1, "[");
}

/**
 * \brief Funcao do Array "trocaArray_atomo"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta funcao existe para possibilitar a troca de um Array e de um membro da stack
 * É feita a verificacao da posicao de este membro, e depois é feita a troca
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void trocaArray_Atomo(stack *dados, int pos)
{
  int x = encontrarLimiteInferior(dados, pos - 1);
  if (dados[pos - 1].tag == limite && dados[pos - x - 2].tag != limite)
  {
    substituirStack(dados, pos, "+");
    createIndex(dados, pos + 1);
    substituirStack(dados, pos + 1, "(");
  }
  if (dados[pos - 1].tag != limite && dados[pos - 2].tag == limite)
  {
    char *aux = malloc(SIZE);
    int y = encontrarLimiteInferior(dados, pos - 2);
    aux = dados[pos - 1].caracter;
    createIndex(dados, pos - y - 1);
    substituirStack(dados, pos - y - 1, aux);
    swap(dados, pos - y - 1);
    POP(dados, pos + 1);
    POP(dados, pos);
  }
}

/**
 * \brief Funcao do Array "rodarStackArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Esta Funcao roda a stack usando um ciclo e adicionado o "\" para executar a troca de Array
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void rodarStackArray(stack *dados, int pos)
{
  int x = encontrarLimiteInferior(dados, pos);
  char *aux = malloc(SIZE);
  aux[0] = '\\';
  aux[1] = '\0';
  if (dados[pos - 1].tag != limite)
  {
    x = 1;
  }
  createIndex(dados, pos - x);
  substituirStack(dados, pos - x, aux);
  substituirStack(dados, pos + 1, aux);
}

/**
 * \brief Funcao do Array "preencherVariavelArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que Remove o Array da stack ao mesmo que tempo que o adiciona na Variavel
 * Caso seja array de array é usado outra funcao
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int preencherVariavelArray(stack *dados, int pos)
{
  int i;
  int x = encontrarLimiteInferior(dados, pos - 1);
  char *aux = malloc(SIZE);
  char *c1 = malloc(SIZE);
  strcpy(aux, "");
  if (dados[pos - 1].caracter[0] == ']' && dados[pos - 2].caracter[0] == ']')
  {
    preencherVariavelArrayArray(dados, pos - 1);
    return 0;
  }
  for (i = pos - x - 1; i < pos; i++)
  {
    strcat(aux, dados[pos - x - 1].caracter);
    strcat(aux, " ");
    POP(dados, pos - x - 1);
  }
  dados[pos - x - 1].variavel = aux;
  c1[0] = dados[pos - x - 1].caracter[1];
  dados[pos - x - 1].caracter = c1;
  return x;
}

/**
 * \brief Funcao do Array "preencherVariavelArrayArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que Remove os Arrays de um Array e coloca-os em variaveis para estes poderem ser processador mais facilmente
 * As novas variaveis vao para o array principal
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void preencherVariavelArrayArray(stack *dados, int pos)
{
  int i = 0;
  char *c = malloc(SIZE);
  *c = 'J';
  while (dados[pos - 1 - i].caracter[0] != '[' || dados[pos - i].caracter[0] != '[')
  {
    char *aux = malloc(SIZE);
    if ((dados[pos - 1 - i].caracter[0] == ']' && dados[pos - i].caracter[0] == ']') || (dados[pos - 1 - i].caracter[0] == ']' && dados[pos - i].caracter[0] == '['))
    {
      strcpy(aux, ":");
      strcat(aux, c);
      createIndex(dados, pos - i);
      substituirStack(dados, pos - i, aux);
      dados[pos - i].tag = variavel;
      *c = *c + 1;
    }
    i++;
  }
}

/**
 * \brief Funcao do Array "normalizarArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que normaliza o Array dentro da variavel colocando na stack
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int normalizarVariavelArray(stack *dados, int pos)
{
  int i = 0, y = 0;
  for (i = 0; dados[pos - 2].variavel[i]; i++)
  {
    char *c = malloc(SIZE);
    c[0] = dados[pos - 2].variavel[i];
    c[1] = '\0';
    if (c[0] != ' ')
    {
      createIndex(dados, pos + y);
      substituirStack(dados, pos + y, c);
      y++;
    }
  }
  return y;
}

/**
 * \brief Funcao do Array "mostraVariavelArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que usada para ocultar os limites e todo tipo de simbolo nao pretendido no final da stack quando mostrado ao utilizador
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void mostrarVariavelArray(stack *dados, int pos)
{
  int i, y = 0;
  char *c = malloc(SIZE);
  char *aux = malloc(SIZE);
  for (i = 0; i < 100; i++)
  {
    aux[i] = '\0';
    c[i] = '\0';
  }
  for (i = 0; dados[pos].variavel[i]; i++)
  {

    if (dados[pos].variavel[i] != ' ' && dados[pos].variavel[i] != '"' && dados[pos].variavel[i])
    {
      c[y] = dados[pos].variavel[i];
      c[y + 1] = '\0';
      y++;
    }
  }
  y = 0;
  for (i = 0; c[i]; i++)
  {
    if (c[i] == '[' || c[i] == ']' || c[i] == ' ')
    {
      continue;
    }
    else
    {
      aux[y] = c[i];
      y++;
    }
  }
  if (dados[pos + 1].tag != variavel && (dados[pos + 1].tag == numInteiro || dados[pos + 1].tag == numFloat))
  {
    printf("%s ", aux);
    return;
  }
  printf("%s", aux);
}

/**
 * \brief Funcao do Array "primeiroElementoVariavel"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que usa a normalizacao para colocar a informacao da variavel na stack e depois coloca o simbolo "(" para executar a funcao
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void primeiroElementoVariavel(stack *dados, int pos)
{
  createIndex(dados, pos + 1);
  substituirStack(dados, pos + 1, "(");
  normalizarVariavelArray(dados, pos + 1);
  POP(dados, pos);
  POP(dados, pos - 1);
}

/**
 * \brief Funcao do Array "primeiroElementoVariavel"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Array
 * Funcao que usa a normalizacao para colocar a informacao da variavel na stack e depois coloca o simbolo ")" para executar a funcao
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void ultimoElementoVariavel(stack *dados, int pos)
{
  createIndex(dados, pos + 1);
  substituirStack(dados, pos + 1, ")");
  normalizarVariavelArray(dados, pos + 1);
  POP(dados, pos);
  POP(dados, pos - 1);
}
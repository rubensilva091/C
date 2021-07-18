/**
 * @file Ficheiro que contem as funcoes dos Blocos
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
#include "bloco.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief Funcao do Array "normalizarBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do Bloco
 * Funcao que normaliza o Bloco dentro da variavel colocando na stack
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void normalizarBloco(stack *dados, int pos)
{
  int y = 0, i = 0;
  for (i = 0; dados[pos - 1].variavel[i]; i++)
  {
    char *c = malloc(SIZE);
    c[0] = dados[pos - 1].variavel[i];
    c[1] = '\0';
    if (c[0] != ' ')
    {
      createIndex(dados, pos + y);
      substituirStack(dados, pos + y, c);
      y++;
    }
  }
  dados[pos].tag = bloco;
  dados[pos + y - 1].tag = bloco;
  POP(dados, pos - 1);
}

/**
 * \brief Funcao do interpretador "POP_Bloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao dá POP no bloco todo
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void POP_Bloco(stack *dados, int pos)
{
  int i;
  int x = encontrarProximoBlocoSuperior(dados, pos);
  for (i = 0; i <= x; i++)
  {
    POP(dados, pos);
  }
}

/**
 * \brief Funcao do interpretador "PUSHBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta Funcao puxa toda a informacao do bloco
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void pushBloco(stack *dados, int pos, stack *auxStack)
{
  int i;
  for (i = 1; dados[pos - i].caracter; i++)
  {
    if (dados[pos - i].tag == bloco)
    {
      break;
    }
    auxStack[i - 1] = dados[pos - i];
  }
}

/**
 * \brief Funcao do interpretador "encontrarProximoBlocoSuperior"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta Funcao encontra o limite superior do bloco
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int encontrarProximoBlocoSuperior(stack *dados, int pos)
{
  int i;
  for (i = 1; dados[pos + i].caracter; i++)
  {
    if (dados[pos + i].tag == bloco)
    {
      break;
    }
  }
  return i;
}

/**
 * \brief Funcao do interpretador "encontrarProximoBlocoInferior"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta Funcao encontra o limite inferior do bloco
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int encontrarProximoBlocoInferior(stack *dados, int pos)
{
  int i = 1, y = 1;
  for (i = 1; dados[pos - i - 1].caracter; i++)
  {
    if (dados[pos - i - 1].tag == bloco)
    {
      break;
    }
    y++;
  }
  return y;
}

/**
 * \brief Funcao do interpretador "IgnorarBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta Funcao é usa no interpretador e ignora sempre que existe um bloco e este só ativa quando
 * tem alguma funcao antes
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int ignorarBloco(stack *dados, int pos)
{
  int i = 0;
  if (dados[pos].tag == bloco)
  {
    i = encontrarProximoBlocoSuperior(dados, pos);
  }
  return i;
}

/**
 * \brief Funcao do interpretador "ExecutarBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta Funcao remove os limites do bloco entregando-o à Stack
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void executarBloco(stack *dados, int pos)
{
  int x;
  if (dados[pos - 1].tag == variavel)
  {
    normalizarBloco(dados, pos);
    return;
  }
  x = encontrarProximoBlocoInferior(dados, pos);
  POP(dados, pos);
  POP(dados, pos - 1);
  POP(dados, pos - 1 - x);
}

/**
 * \brief Funcao do interpretador "mapBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao ramifica para array e string, dependedo da tag
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void mapBloco(stack *dados, int pos)
{
  int x;
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '{')
  {
    normalizarBloco(dados, pos);
    return;
  }
  x = encontrarProximoBlocoInferior(dados, pos);
  if (dados[pos - x - 2].tag == string)
  {
    mapBlocoString(dados, pos);
    return;
  }
  if (dados[pos - x - 2].tag == limite)
  {
    mapBlocoArray(dados, pos);
    return;
  }
}

/**
 * \brief Funcao do interpretador "mapBlocoArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro.
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * [ 1 2 3 ] { 5 + } % -> [ 1 5 + 2 5 + 3 5 + ] -> [ 6 7 8 ]
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void mapBlocoArray(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int pos2 = pos - tamanhoBloco - 2;
  int x = encontrarLimiteInferior(dados, pos2);
  int i, j, y = 1;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  for (i = 1; i < x - 1; i++)
  {
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 - x + i + y);
      substituirStack(dados, pos2 - x + i + y, auxStack[j - 1].caracter);
      dados[pos2 - x + i + y].tag = expressaoMat;
      dados[pos2 - x + i + y].variavel = auxStack[j - 1].variavel;
      y++;
    }
  }
  POP_Bloco(dados, pos2 + y - 1);
}

/**
 * \brief Funcao do interpretador "mapBlocoString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro.
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * "qnc" { ( ( } % -> [ "q" "n" "c"] -> { ( ( } % -> [ "q" ( ( ( ^ "n" ( ( ( ^ "c" ( ( ( ^ ] -> [ "ola" ]
 *
 * ( -> Retira da a letra da string 
 * ^ -> Funcao personalizada que concatena até encontrar a string inicial
 * 
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void mapBlocoString(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int i, j, y = 1, pos2, tamanhostring = 0, pos3;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  POP_Bloco(dados, pos - tamanhoBloco - 2);
  pos2 = pos - tamanhoBloco - 2 - 1;
  for (i = 1; dados[pos2].caracter[i + 1]; i++)
  {
    char *aux = malloc(SIZE);
    createIndex(dados, pos2 + i);
    aux[0] = dados[pos2].caracter[i];
    substituirStack(dados, pos2 + i, aux);
    adicionarAspas(dados, pos2 + i);
    dados[pos2 + i].tag = string;
    tamanhostring++;
  }
  for (i = 1; i <= tamanhostring; i++)
  {
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "(");
    dados[pos2 + i + y].tag = expressaoMat;
    y++;
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 + i + y);
      substituirStack(dados, pos2 + i + y, auxStack[j - 1].caracter);
      dados[pos2 + i + y].tag = expressaoMat;
      y++;
    }
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "^");
    dados[pos2 + i + y].tag = expressaoMat;
    y++;
  }
  pos3 = pos2 + i + y - 1;
  for (i = 0; i < tamanhostring - 1; i++)
  {
    createIndex(dados, pos3 + i);
    substituirStack(dados, pos3 + i, "+");
    dados[pos3 + i].tag = expressaoMat;
  }
  POP(dados, pos2);
}

/**
 * \brief Funcao do interpretador "foldBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao ramifica para array e string, dependedo da tag
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void foldBloco(stack *dados, int pos)
{
  int x;
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '{')
  {
    normalizarBloco(dados, pos);
    return;
  }
  x = encontrarProximoBlocoInferior(dados, pos);
  if (dados[pos - x - 2].tag == limite)
  {
    foldBlocoArray(dados, pos);
    return;
  }
}

/**
 * \brief Funcao do interpretador "foldBlocoArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro apartir do segundo.
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * [ 1 2 3 ] { * } * -> [ 1 2 * 3 * ] -> [ 6 ]
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void foldBlocoArray(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int pos2 = pos - tamanhoBloco - 2;
  int x = encontrarLimiteInferior(dados, pos2);
  int i, j, y = 1;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  for (i = 2; i < x - 1; i++)
  {
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 - x + i + y);
      substituirStack(dados, pos2 - x + i + y, auxStack[j - 1].caracter);
      y++;
    }
  }
  POP_Bloco(dados, pos2 + y - 1);
}

/**
 * \brief Funcao do interpretador "filterBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao ramifica para array e string, dependedo da tag
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void filterBloco(stack *dados, int pos)
{
  int x;
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '{')
  {
    normalizarBloco(dados, pos);
    return;
  }
  x = encontrarProximoBlocoInferior(dados, pos);
  if (dados[pos - x - 2].tag == limite)
  {
    filterBlocoArray(dados, pos);
    return;
  }
  if (dados[pos - x - 2].tag == string)
  {
    filterBlocoString(dados, pos);
    return;
  }
}

/**
 * \brief Funcao do interpretador "filterBlocoArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro apartir do segundo.
 * No fim é adicionado tambem a condicional, se for verdado, numero descartavel (trash), se for falso, numoro a guardar.
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * [ 1 2 3 ] { 2 % } , -> [ 1 2 % 10 1 ? 2 2 % 10 2 ? 3 2 % 10 3 ? ] -> [ 1 10 3 ] -> [ 1 3 ]
 * 
 * 10 -> tem a tag Trash, que servirá para ser apagado posteriormente
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void filterBlocoArray(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int pos2 = pos - tamanhoBloco - 2;
  int x = encontrarLimiteInferior(dados, pos2);
  int i, j, y = 1;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  for (i = 1; i < x - 1; i++)
  {
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 - x + i + y);
      substituirStack(dados, pos2 - x + i + y, auxStack[j - 1].caracter);
      y++;
    }
    createIndex(dados, pos2 - x + i + y);
    substituirStack(dados, pos2 - x + i + y, dados[pos2 - x + i + y - tamanhoBloco - 1].caracter);
    dados[pos2 - x + i + y].tag = numInteiro;
    y++;
    createIndex(dados, pos2 - x + i + y);
    substituirStack(dados, pos2 - x + i + y, "10");
    dados[pos2 - x + i + y].tag = trash;
    y++;
    createIndex(dados, pos2 - x + i + y);
    substituirStack(dados, pos2 - x + i + y, "?");
    dados[pos2 - x + i + y].tag = logica;
    y++;
  }
  POP_Bloco(dados, pos2 + y - 1);
}

/**
 * \brief Funcao do interpretador "filterBlocoString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro apartir do segundo.
 * No fim é adicionado tambem a condicional, se for verdado, numero descartavel (trash), se for falso, numoro a guardar.
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * 
 * "ABC," { 64 > } , -> "A" ( 64 > 10 "A" ? "B" ( 64 > 10 "B" ? "C" ( 64 > "C" 10 ?  "," ( 64 > "," 10 ? -> "ABC"
 * 
 * ( -> Retira da a letra da string 
 * ^ -> Funcao personalizada que concatena até encontrar a string inicial
 * 10 -> tem a tag Trash, que servirá para ser apagado posteriormente
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void filterBlocoString(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int i, j, y = 1, pos2, tamanhostring = 0, pos3;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  POP_Bloco(dados, pos - tamanhoBloco - 2);
  pos2 = pos - tamanhoBloco - 2 - 1;
  for (i = 1; dados[pos2].caracter[i + 1]; i++)
  {
    char *aux = malloc(SIZE);
    createIndex(dados, pos2 + i);
    aux[0] = dados[pos2].caracter[i];
    substituirStack(dados, pos2 + i, aux);
    adicionarAspas(dados, pos2 + i);
    dados[pos2 + i].tag = string;
    tamanhostring++;
  }
  for (i = 1; i <= tamanhostring; i++)
  {
    char *aux = malloc(SIZE);
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "(");
    dados[pos2 + i + y].tag = expressaoMat;
    y++;
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 + i + y);
      substituirStack(dados, pos2 + i + y, auxStack[j - 1].caracter);
      dados[pos2 + i + y].tag = expressaoMat;
      y++;
    }
    createIndex(dados, pos2 + i + y);
    aux[0] = dados[pos2 + i + y - tamanhoBloco - 2].caracter[1];
    substituirStack(dados, pos2 + i + y, aux);
    dados[pos2 + i + y].tag = nothing;
    y++;
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "10");
    dados[pos2 + i + y].tag = trash;
    y++;
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "?");
    dados[pos2 + i + y].tag = logica;
    y++;
    createIndex(dados, pos2 + i + y);
    substituirStack(dados, pos2 + i + y, "^");
    dados[pos2 + i + y].tag = expressaoMat;
    y++;
  }
  pos3 = pos2 + i + y - 1;
  for (i = 0; i < tamanhostring - 1; i++)
  {
    createIndex(dados, pos3 + i);
    substituirStack(dados, pos3 + i, "+");
    dados[pos3 + i].tag = expressaoMat;
  }
  POP(dados, pos2);
}

/**
 * \brief Funcao do interpretador "sortBloco"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao ramifica para array e string, dependedo da tag
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void sortBloco(stack *dados, int pos)
{
  int x;
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '{')
  {
    normalizarBloco(dados, pos);
    return;
  }
  x = encontrarProximoBlocoInferior(dados, pos);
  if (dados[pos - x - 2].tag == limite)
  {
    sortBlocoArray(dados, pos);
    return;
  }
  if (dados[pos - x - 2].tag == string)
  {
    /*NAO SEI O QUE POR_> ESPERAR STOR*/
    return;
  }
}

/**
 * \brief Funcao do interpretador "sortBlocoArray"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro apartir do segundo.
 * No fim é adicionado o simbolo "$" para passar realmente ao sort
 * O objetivo é alterar o array para chegar ao objetivo pretendido, por exemplo:
 * [ "ola" "mundo" "i" ] { , } $ -> [ "ola" "mundo" "i" ] [ "ola" , "mundo" , "i" , ] $ -> [ "ola" "mundo" "i" ] [ 3 5 1 ] $
 * 
 * Depois disto tudo, apartir do "$", vai para o sort noutra funcao
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void sortBlocoArray(stack *dados, int pos)
{
  stack *auxStack = malloc(SIZE);
  int tamanhoBloco = encontrarProximoBlocoInferior(dados, pos) - 1;
  int pos2 = pos - tamanhoBloco - 2;
  int x = encontrarLimiteInferior(dados, pos2);
  int pos3 = pos2 - x;
  int i, j, y = 1, tamanhoString;
  POP(dados, pos);
  pushBloco(dados, pos - 1, auxStack);
  for (i = 0; i < x; i++)
  {
    createIndex(dados, pos2 + i);
    substituirStack(dados, pos2 + i, dados[pos3 + i].caracter);
  }
  tamanhoString = i;
  for (i = 1; i < x - 1; i++)
  {
    for (j = tamanhoBloco; j != 0; j--)
    {
      createIndex(dados, pos2 - x + i + y + tamanhoString);
      substituirStack(dados, pos2 - x + i + y + tamanhoString, auxStack[j - 1].caracter);
      dados[pos2 - x + i + y + tamanhoString].tag = expressaoMat;
      y++;
    }
  }
  createIndex(dados, pos2 - x + i + y + tamanhoString);
  substituirStack(dados, pos2 - x + i + y + tamanhoString, "$");
  dados[pos2 - x + i + y + tamanhoString].tag = stacks;
  y++;
  POP_Bloco(dados, pos2 - x + i + y + tamanhoString);
}

/**
 * \brief Funcao do interpretador "sortBlocoArraySORT"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao aplica o bloco a cada membro apartir do segundo.
 * (CONTINUACAO DA OUTRA FUNCAO)
 * Esta funcao vai dar SORT usando o bubble sort no segundo ARRAY, sempre que alguma alteracao ocorrer,
 * os dois sao alterados simultaneamente
 * 
 * [ "ola" "mundo" "i" ] [ 3 5 1 ] $ -> [ "ola" "i" "mundo" ] [ 3 1 5 ] -> [ "i" "ola" "mundo" ] [ 1 3 5 ] -> [ "i" "ola" "mundo" ]
 * 
 * Depois disto tudo, o segundo Array sofre POP
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void sortBlocoArraySORT(stack *dados, int pos)
{
  int pos2 = pos - encontrarLimiteInferior(dados, pos);
  int pos3 = pos2 - encontrarLimiteInferior(dados, pos2);
  int nVariaveis = pos - pos2;
  int w, z, t = 0;
  POP(dados, pos);
  for (w = 0; w < nVariaveis; w++)
  {
    t = 0;
    for (z = pos2 + 1; z < pos - 2 && z > pos2; z++)
    {
      if (atof(dados[z].caracter) > atof(dados[z + 1].caracter))
      {
        stack *auxStack = malloc(SIZE);
        auxStack[0] = dados[z];
        dados[z] = dados[z + 1];
        dados[z + 1] = auxStack[0];
        auxStack[0] = dados[pos3 + 1 + t];
        dados[pos3 + 1 + t] = dados[pos3 + 2 + t];
        dados[pos3 + 2 + t] = auxStack[0];
      }
      t++;
    }
  }
  POP_ARRAY(dados, pos);
}


/**
 * \brief Funcao do interpretador "preencherBlocoVariavel"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao retira o bloco da stack e coloca-o na variavel
 * 
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
int preencherVariavelBloco(stack *dados, int pos)
{
  int i;
  int x = encontrarProximoBlocoInferior(dados, pos);
  char *aux = malloc(SIZE);
  char *c1 = malloc(SIZE);
  strcpy(aux, "");
  for (i = pos - x - 1; i < pos; i++)
  {
    strcat(aux, dados[pos - x - 1].caracter);
    if (i < pos - 1)
    {
      strcat(aux, " ");
    }
    POP(dados, pos - x - 1);
  }
  dados[pos - x - 1].variavel = aux;
  c1[0] = dados[pos - x - 1].caracter[1];
  dados[pos - x - 1].caracter = c1;
  return x;
}

/**
 * \brief Funcao do interpretador "trocaBloco_Atomo"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Esta funcao troca o bloco com algum membro da stack
 * 
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void trocaBloco_Atomo(stack *dados, int pos)
{
  int x = encontrarProximoBlocoInferior(dados, pos - 1);
  if (dados[pos - 1].tag == bloco && dados[pos - x - 1].tag != bloco)
  {
    substituirStack(dados, pos, dados[pos - x - 3].caracter);
    POP(dados, pos - x - 3);
  }
  else if (dados[pos - 1].tag != bloco && dados[pos - 2].tag == bloco)
  {
    char *aux = malloc(SIZE);
    int y = encontrarProximoBlocoInferior(dados, pos - 2);
    aux = dados[pos - 1].caracter;
    createIndex(dados, pos - y - 2);
    substituirStack(dados, pos - y - 2, aux);
    swap(dados, pos - y - 2);
    POP(dados, pos + 1);
    POP(dados, pos);
  }
}
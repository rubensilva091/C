/**
 * @file Ficheiro que contem as funcoes do interpretador
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
 * \brief Funcao do interpretador
 *
 * Esta funcao recebe os dados e faz uma verificacao ate encontrar algum operador
 * Depois de encontrado, entra na parte correspondente
 * Depois da operacao, da break, e volta ao main
 *
 * @param dados receber a stack
 */
int interpretador(stack *dados)
{
  int i, y = 0, key = 1;
  for (i = 0; dados[i].caracter; i++)
  {
    y = ignorarBloco(dados, i);
    i = i + y;
    if (dados[i].tag != numInteiro && dados[i].tag != numFloat && dados[i].tag != numFloatFunc && dados[i].tag != numInteiroFunc)
    {
      if (dados[i].tag == expressaoMat)
      {
        expressaoMatematicaFunc(dados, i);
        key = 0;
        break;
      }
      else if (dados[i].tag == stacks)
      {
        stacksFunc(dados, i);
        key = 0;
        break;
      }
      else if (dados[i].tag == inputOutput_Conversoes)
      {
        inputOutput_conversoesFunc(dados, i);
        key = 0;
        break;
      }
      else if (dados[i].tag == logica)
      {
        logicaFunc(dados, i);
        key = 0;
        break;
      }
    }
  }
  return key;
}

/**
 * \brief Funcao do interpretador (EXPRESSAO MATEMATICA)
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Depois de encontrado, entra na funcao respetiva
 * Depois de tudo, volta ao main
 *
 * @param dados receber a stack
 * @param pos recebe a posicao atual da stack
 */
void expressaoMatematicaFunc(stack *dados, int pos)
{
  switch (dados[pos].caracter[0])
  {
  case '+':
    soma(dados, pos);
    break;
  case '-':
    subtracao(dados, pos);
    break;
  case '*':
    multiplicacao(dados, pos);
    break;
  case '/':
    divisao(dados, pos);
    break;
  case ')':
    incrementacao(dados, pos);
    break;
  case '(':
    decrementacao(dados, pos);
    break;
  case '#':
    exponencializacao(dados, pos);
    break;
  case '%':
    modulo(dados, pos);
    break;
  case '&':
    bitwise_AND(dados, pos);
    break;
  case '|':
    bitwise_OR(dados, pos);
    break;
  case '^':
    bitwise_XOR(dados, pos);
    break;
  case '~':
    bitwise_NOT(dados, pos);
    break;
  }
}

/**
 * \brief Funcao do interpretador (STACKS)
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Depois de encontrado, entra na funcao respetiva
 * Depois de tudo, volta ao main
 *
 * @param dados receber a stack
 * @param pos recebe a posicao atual da stack
 */
void stacksFunc(stack *dados, int pos)
{
  switch (dados[pos].caracter[0])
  {
  case '_':
    duplicarStack(dados, pos);
    break;
  case ';':
    popStack(dados, pos);
    break;
  case '\\':
    trocaStack(dados, pos);
    break;
  case '@':
    rodaStack(dados, pos);
    break;
  case '$':
    duplicaN_esimoStack(dados, pos);
    break;
  case 'N':
    createIndex(dados, pos + 1);
    separarStringSubstring(dados, pos + 1, "\n");

    break;
  case 'S':
    createIndex(dados, pos + 1);
    separarStringSubstring(dados, pos + 1, " ");
    break;
  }
}

/**
 * \brief Funcao do interpretador "INPUT_OUTPUT_CONVERSOES"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Depois de encontrado, entra na funcao respetiva
 * Depois de tudo, volta ao main
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void inputOutput_conversoesFunc(stack *dados, int pos)
{
  switch (dados[pos].caracter[0])
  {
  case 'l':
    ler(dados, pos);
    break;
  case 't':
    lerT(dados, pos);
    break;
  case 'p':
    break;
  case 'i':
    interioFUNC(dados, pos);
    break;
  case 'f':
    floatFUNC(dados, pos);
    break;
  case 'c':
    converterNum_Letra(dados, pos);
    break;
  case 's':
    converterParaString(dados, pos);
    break;
  case ':':
    preencherVariavel(dados, pos);
    break;
  case ',':
    rangeFunc(dados, pos);
    break;
  }
}

/**
 * \brief Funcao do interpretador "LOGICA"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Depois de encontrado, entra na funcao respetiva
 * Depois de tudo, volta ao main
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void logicaFunc(stack *dados, int pos)
{
  switch (dados[pos].caracter[0])
  {
  case '=':
    igualdade(dados, pos);
    break;
  case '<':
    menor(dados, pos);
    break;
  case '>':
    maior(dados, pos);
    break;
  case '!':
    negacao(dados, pos);
    break;
  case 'e':
    switch (dados[pos].caracter[1])
    {
    case '&':
      e_And(dados, pos);
      break;
    case '|':
      e_Or(dados, pos);
      break;
    case '<':
      e_menor(dados, pos);
      break;
    case '>':
      e_maior(dados, pos);
      break;
    }
    break;
  case '?':
    condicional(dados, pos);
    break;
  }
}

/**
 * \brief Funcao do interpretador "SOMA"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a soma dos numeros baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack 
 */
void soma(stack *dados, int pos)
{

  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  if (!dados[pos - 1].caracter || !dados[pos - 2].caracter)
  {
    POP(dados, pos);
    return;
  }
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == limite || dados[pos - 2].tag == limite || dados[pos - 1].tag == string || dados[pos - 2].tag == string)
  {
    juntarString(dados, pos);
    juntarArray(dados, pos);
    return;
  }
  if ((isfloat(c1) == 0 && isfloat(c2) == 0))
  {
    sprintf(c, "%d", (int)y + (int)z);
  }
  else
  {
    sprintf(c, "%f", (y + z));
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "SUBTRACAO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a subtracao dos numeros baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void subtracao(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if ((isfloat(c1) == 0 && isfloat(c2) == 0))
  {
    sprintf(c, "%d", (int)y - (int)z);
  }
  else
  {
    sprintf(c, "%f", (y - z));
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "MULTIPLICAÇÃO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a multiplicação dos numeros baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void multiplicacao(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == bloco)
  {
    foldBloco(dados, pos);
    return;
  }
  if (dados[pos - 2].tag == string || dados[pos - 2].tag == limite)
  {
    multString(dados, pos, z);
    multArray(dados, pos, z);
    return;
  }
  else if ((isfloat(c1) == 0 && isfloat(c2) == 0))
  {
    sprintf(c, "%d", (int)y * (int)z);
  }
  else
  {
    sprintf(c, "%f", (y * z));
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "DIVISÃO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a divisão dos numeros baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void divisao(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string)
  {
    separarStringSubstring(dados, pos, dados[pos - 1].caracter);
    return;
  }

  if ((isfloat(c1) == 0 && isfloat(c2) == 0))
  {
    sprintf(c, "%d", (int)y / (int)z);
  }
  else
  {
    sprintf(c, "%f", (y / z));
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "INCREMENTAÇÃO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a incrementação do numero baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina o numero da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void incrementacao(stack *dados, int pos)
{
  double z;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '[')
  {
    ultimoElementoVariavel(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == string || dados[pos - 1].tag == limite)
  {
    ultimoElementoString(dados, pos);
    ultimoElemento(dados, pos);
    return;
  }
  else if (dados[pos - 1].tag != numFloat && dados[pos - 1].tag != numInteiro && dados[pos - 1].tag != numFloatFunc && dados[pos - 1].tag != numInteiroFunc)
  {
    *c = *c1 + 1;
    dados[pos].tag = nothing;
  }
  else if (isfloat(c1) == 0)
  {
    sprintf(c, "%d", ((int)z + 1));
  }
  else
  {
    sprintf(c, "%f", (z + 1));
  }
  POP(dados, pos - 1);
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "DECREMENTAÇÃO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a decrementação do numero baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina o numero da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void decrementacao(stack *dados, int pos)
{
  double z;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '[')
  {
    primeiroElementoVariavel(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == string || dados[pos - 1].tag == limite)
  {
    primeiroElementoString(dados, pos);
    primeiroElemento(dados, pos);
    return;
  }
  else if (dados[pos - 1].tag != numFloat && dados[pos - 1].tag != numInteiro && dados[pos - 1].tag != numFloatFunc && dados[pos - 1].tag != numInteiroFunc)
  {
    *c = *c1 - 1;
    dados[pos].tag = nothing;
  }
  else if (isfloat(c1) == 0)
  {
    sprintf(c, "%d", ((int)z - 1));
  }
  else
  {
    sprintf(c, "%f", (z - 1));
  }
  POP(dados, pos - 1);
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "EXPONENCIALIZAÇÃO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a exponencialização dos numeros baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se é inteiro ou float
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void exponencializacao(stack *dados, int pos)
{
  double z, y, x;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  x = pow(y, z);
  if (dados[pos - 2].tag == string || dados[pos - 1].tag == string)
  {
    procurarSubstring(dados, pos, dados[pos - 1].caracter);
    return;
  }
  if ((isfloat(c1) == 0 && isfloat(c2) == 0))
  {
    sprintf(c, "%d", (int)x);
  }
  else
  {
    sprintf(c, "%f", (x + 0.000004));
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "MODULO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz o modulo dos numeros baseada na posicao atual
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void modulo(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == bloco)
  {
    mapBloco(dados, pos);
    return;
  }
  sprintf(c, "%d", ((int)y % (int)z));
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "BITWISE_AND"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a funcao bitwise_AND dos numeros baseada na posicao atual
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack 
 */
void bitwise_AND(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  sprintf(c, "%d", ((int)y & (int)z));
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "BITWISE_OR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a funcao bitwise_OR dos numeros baseada na posicao atual
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void bitwise_OR(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  sprintf(c, "%d", ((int)y | (int)z));
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "BITWISE_XOR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a funcao bitwise_XOR dos numeros baseada na posicao atual
 * Elimina os numeros da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void bitwise_XOR(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == nothing || dados[pos - 1].tag == trash)
  {
    concatStringsAte(dados, pos);
    return;
  }
  sprintf(c, "%d", ((int)y ^ (int)z));
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "BITWISE_NOT"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a funcao bitwise_NOT do numero baseada na posicao atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Elimina o numero da stack
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void bitwise_NOT(stack *dados, int pos)
{
  double z;
  char *c = malloc(SIZE);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == limite)
  {
    negarArray(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == bloco || (dados[pos - 1].tag == variavel && dados[pos - 1].variavel[0] == '{'))
  {
    executarBloco(dados, pos);
    return;
  }
  sprintf(c, "%d", ~(int)z);
  POP(dados, pos - 1);
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "DUPLICASTACK"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz duplicação da ultima posição da stack baseada na posição atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void duplicarStack(stack *dados, int pos)
{
  stack aux1;
  if (dados[pos - 1].tag == limite)
  {
    duplicarArray(dados, pos);
    return;
  }
  aux1 = dados[pos - 1];
  dados[pos] = aux1;
}

/**
 * \brief Funcao do interpretador "POPSTACK"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Apaga a ultima posição da stack baseada na posição atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void popStack(stack *dados, int pos)
{
  POP(dados, pos);
  if (dados[pos - 1].tag == limite)
  {
    POP_ARRAY(dados, pos);
    return;
  }
  POP(dados, pos - 1);
}

/**
 * \brief Funcao do interpretador "TROCASTACK"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz troca das ultimas 2 posições da stack baseada na posição atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void trocaStack(stack *dados, int pos)
{
  stack aux1;
  stack aux2;
  if (dados[pos - 1].tag == bloco || dados[pos - 2].tag == bloco)
  {
    trocaBloco_Atomo(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == limite || dados[pos - 2].tag == limite)
  {
    trocaArray_Atomo(dados, pos);
    trocarArray(dados, pos);
    return;
  }
  aux1 = dados[pos - 2];
  aux2 = dados[pos - 1];
  dados[pos - 1] = aux1;
  dados[pos - 2] = aux2;
  POP(dados, pos);
}

/**
 * \brief Funcao do interpretador "RODASTACK"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz rotação das ultimas 3 posições da stack baseada na posição atual
 * Verifica a existencia de String ou Array para mudar de funcao
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void rodaStack(stack *dados, int pos)
{
  stack aux1;
  stack aux2;
  stack aux3;
  if (dados[pos - 1].tag == limite || dados[pos - 2].tag == limite || dados[pos - 3].tag == limite)
  {
    rodarStackArray(dados, pos);
    return;
  }
  aux1 = dados[pos - 3];
  aux2 = dados[pos - 1];
  aux3 = dados[pos - 2];
  dados[pos - 1] = aux1;
  dados[pos - 2] = aux2;
  dados[pos - 3] = aux3;
  POP(dados, pos);
}

/**
 * \brief Funcao do interpretador "DUPLICAN-ESIMOSTACK"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Duplica a posicao da stack que o utilizador quiser baseada na posição atual
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void duplicaN_esimoStack(stack *dados, int pos)
{
  int x = PUSH(dados, pos - 1);
  stack aux1;
  if (dados[pos - 1].tag == bloco)
  {
    sortBloco(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == limite)
  {
    sortBlocoArraySORT(dados, pos);
    return;
  }
  aux1 = dados[pos - (2 + x)];
  dados[pos - 1] = aux1;
  POP(dados, pos);
}

/**
 * \brief Funcao do interpretador "LER_L"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Substitui a posição atual por algum input do utilizador
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void ler(stack *dados, int pos)
{
  int auxInt = 0;
  char *c = malloc(SIZE);
  if (dados[pos + 1].tag == inputOutput_Conversoes)
  {
    assert(fgets(c, SIZE, stdin) != NULL);
    auxInt = strlen(c);
    c[auxInt - 1] = '\0';
    dados[pos].caracter = c;
  }
  else
  {
    char *aux = malloc(SIZE);
    aux[0] = '"';
    assert(fgets(c, SIZE, stdin) != NULL);
    auxInt = strlen(c);
    c[auxInt - 1] = '\0';
    strcat(aux, c);
    strcat(aux, " ");
    dados[pos].caracter = aux;
    dados[pos].tag = string;
  }
}

/**
 * \brief Funcao do interpretador "LER_T"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Substitui a posição atual por algum input do utilizador
 * Substitui o operador pelo valor final
 * Se for mais que 1, então cria uma posição uma nova e depois repete o até ao fim
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void lerT(stack *dados, int pos)
{
  int i, auxInt;
  char *aux = malloc(SIZE);
  aux[0] = '"';
  for (i = 0;; i++)
  {
    char *c = malloc(SIZE);
    if (fgets(c, SIZE, stdin) == NULL)
    {
      break;
    }
    else
    {
      auxInt = strlen(c);
      if (c[auxInt - 1] != '\n')
      {
        c[auxInt - 1] = ' ';
      }
      strcat(aux, c);
    }
  }
  aux[strlen(aux) - 1] = '"';
  dados[pos].caracter = aux;
  dados[pos].tag = string;
}

/**
 * \brief Funcao do interpretador "INTEROFUNC"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Troca a tag do numero anterior para inteiro e retira-lhe o resto se existir
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void interioFUNC(stack *dados, int pos)
{
  int auxInt = 0;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  int i;
  if (dados[pos - 1].tag == nothing)
  {
    auxInt = *c1 - 'a' + 97;
    sprintf(c, "%d", auxInt);
  }
  else if (dados[pos - 1].tag == string)
  {
    for (i = 0; c1[i + 2]; i++)
    {
      c[i] = c1[i + 1];
    }
    auxInt = atoi(c);
  }
  else
  {
    int aux = atof(dados[pos - 1].caracter);
    sprintf(c, "%d", aux);
  }
  POP(dados, pos);
  dados[pos - 1].tag = numInteiroFunc;
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "FLOATFUNC"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Troca a tag do numero anterior para float
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void floatFUNC(stack *dados, int pos)
{
  double auxFloat = 0;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  int i;
  if (dados[pos - 1].tag == nothing)
  {
    auxFloat = *c1 - 'a' + 97;
    sprintf(c, "%f", auxFloat);
  }
  else if (dados[pos - 1].tag == string)
  {
    for (i = 0; c1[i + 2]; i++)
    {
      c[i] = c1[i + 1];
    }
    auxFloat = atof(c);
  }
  else
  {
    sprintf(c, "%f", atof(dados[pos - 1].caracter));
  }
  POP(dados, pos);
  dados[pos - 1].tag = numFloatFunc;
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "CONVERTERNUM-LETRA"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Troca o numero pela respetia representação alfabética (letras)
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void converterNum_Letra(stack *dados, int pos)
{
  int auxInt = 0;
  char *c = malloc(SIZE);
  auxInt = PUSH(dados, pos - 1);
  POP(dados, pos);
  *c = auxInt;
  dados[pos - 1].caracter = c;
  dados[pos - 1].tag = nothing;
}

/**
 * \brief Funcao do interpretador "CONVERTERParaString"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Troca o membro da stack pela respetia string
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void converterParaString(stack *dados, int pos)
{
  adicionarAspas(dados, pos - 1);
  dados[pos - 1].tag = string;
  POP(dados, pos);
}
/**
 * \brief Funcao do interpretador "PREENCHEVARIAVEL"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Copia a posição anterior para a Variavel
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void preencherVariavel(stack *dados, int pos)
{
  char *c1 = malloc(SIZE);
  char *c2 = malloc(SIZE);
  if (dados[pos - 1].tag == bloco)
  {
    int x = preencherVariavelBloco(dados, pos);
    variavelFantasmaFunc(dados, pos - x - 1);
    reVariaveisInterpretador(dados, pos - x - 1);
    return;
  }
  if (dados[pos - 1].tag == limite)
  {
    int x = preencherVariavelArray(dados, pos);
    variavelFantasmaFunc(dados, pos - x - 1);
    reVariaveisInterpretador(dados, pos - x - 1);
    return;
  }
  c1[0] = dados[pos].caracter[1];
  c2 = dados[pos - 1].caracter;
  dados[pos].caracter = c1;
  dados[pos].variavel = c2;
  variavelFantasmaFunc(dados, pos);
  reVariaveisInterpretador(dados, pos);
  POP(dados, pos - 1);
}

/**
 * \brief Funcao do interpretador "IGUALDADE"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se os numeros sao iguais
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void igualdade(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string && dados[pos - 1].tag == string)
  {
    compararStrings(dados, pos);
    return;
  }
  if (dados[pos - 2].variavel[0] == '[')
  {
    y = normalizarVariavelArray(dados, pos);
    createIndex(dados, pos + 1 + y);
    substituirStack(dados, pos + 1 + y, dados[pos - 1].caracter);
    swap(dados, pos + 1 + y);
    POP(dados, pos - 1);
    POP(dados, pos - 2);
    return;
  }
  if (dados[pos - 2].tag == limite || dados[pos - 2].tag == string || dados[pos - 2].tag == variavel)
  {
    pesquisarStringIndex(dados, pos, z);
    pesquisarArrayIndex(dados, pos, z);
    return;
  }
  if (y == z)
  {
    sprintf(c, "%d", 1);
  }
  else
  {
    sprintf(c, "%d", 0);
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "MENOR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica qual o menor numero
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void menor(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string && dados[pos - 1].tag == string)
  {
    menorString(dados, pos);
    return;
  }
  if (dados[pos - 2].tag == limite || dados[pos - 2].tag == string)
  {
    buscarN_elementosMenorString(dados, pos, z);
    buscarN_elementosMenor(dados, pos, z);
    return;
  }
  if (y < z)
  {
    sprintf(c, "%d", 1);
  }
  else
  {
    sprintf(c, "%d", 0);
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "MAIOR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica qual o maior numero
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void maior(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string && dados[pos - 1].tag == string)
  {
    maiorString(dados, pos);
    return;
  }
  if (dados[pos - 2].tag == limite || dados[pos - 2].tag == string)
  {
    buscarN_elementosMaiorString(dados, pos, z);
    buscarN_elementosMaior(dados, pos, z);
    return;
  }
  if (y > z)
  {
    sprintf(c, "%d", 1);
  }
  else
  {
    sprintf(c, "%d", 0);
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "NEGACAO"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Nega a afirmacao anterior
 * Substitui o operador pelo valor final
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void negacao(stack *dados, int pos)
{
  double z;
  char *c = malloc(SIZE);
  z = PUSH(dados, pos - 1);
  if (z != 0 || (dados[pos - 1].tag == string && dados[pos - 1].caracter[0] == '0'))
  {
    sprintf(c, "%d", 0);
  }
  else
  {
    sprintf(c, "%d", 1);
  }
  POP(dados, pos - 1);
  dados[pos - 1].caracter = c;
}

/**
 * \brief Funcao do interpretador "e_MENOR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica qual o menor numero
 * Substitui o operador pelo valor correspondente ao menor
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_menor(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string && dados[pos - 1].tag == string)
  {
    e_menorString(dados, pos);
    return;
  }
  if (y < z)
  {
    sprintf(c, "%d", (int)y);
    if (isfloat(c2) != 0)
    {
      sprintf(c, "%f", y);
    }
  }
  else
  {
    sprintf(c, "%d", (int)z);
    if (isfloat(c1) != 0)
    {
      sprintf(c, "%f", z);
    }
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "e_MAIOR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica qual o maior numero
 * Substitui o operador pelo valor correspondente ao maior
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_maior(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  char *c2 = dados[pos - 2].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (dados[pos - 2].tag == string && dados[pos - 1].tag == string)
  {
    e_maiorString(dados, pos);
    return;
  }
  if (y > z)
  {
    sprintf(c, "%d", (int)y);
    if (isfloat(c2) != 0)
    {
      sprintf(c, "%f", y);
    }
  }
  else
  {
    sprintf(c, "%d", (int)z);
    if (isfloat(c1) != 0)
    {
      sprintf(c, "%f", z);
    }
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "e_AND"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a verificação lógica &.
 * Substitui o operador pelo valor pelo maior numero se verdade, ou 0 se falso
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_And(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (y == 0 || z == 0)
  {
    sprintf(c, "%d", 0);
  }
  else
  {
    if (y > z)
    {
      z = y;
    }
    sprintf(c, "%d", (int)z);
    if (isfloat(c1) != 0)
    {
      sprintf(c, "%f", z);
    }
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "e_OR"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Faz a verificação lógica |.
 * Substitui o operador pelo valor pelo menor numero se verdade, ou 0 se falso
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void e_Or(stack *dados, int pos)
{
  double z, y;
  char *c = malloc(SIZE);
  char *c1 = dados[pos - 1].caracter;
  y = PUSH(dados, pos - 2);
  z = PUSH(dados, pos - 1);
  if (y == 0 && z == 0)
  {
    sprintf(c, "%d", 0);
  }
  else if (z != 0 && y != 0)
  {
    if (y > z)
    {
      z = y;
    }
    sprintf(c, "%d", (int)z);
    if (isfloat(c1) != 0)
    {
      sprintf(c, "%f", z);
    }
  }
  else
  {
    if (z == 0)
    {
      z = y;
    }
    sprintf(c, "%d", (int)z);
    if (isfloat(c1) != 0)
    {
      sprintf(c, "%f", z);
    }
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  dados[pos - 2].caracter = c;
}

/**
 * \brief Funcao do interpretador "CONDICIONAL"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Verifica se a afirmacao anterior é falsa ou verdadeira
 * Se Verdadeiro, Substitui o operador pelo valor na posição atual do operador menos duas posições
 * Se Falso, Substitui o operador pelo valor na posição atual do operador menos uma posição
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void condicional(stack *dados, int pos)
{
  double x;
  int j = 0;
  stack *auxStack = malloc(SIZE);
  x = PUSH(dados, pos - 3);
  if (dados[pos - 3].tag == limite)
  {
    j = 1;
    x = PUSH(dados, pos - 4);
  }
  auxStack[0].caracter = dados[pos - 1].caracter;
  auxStack[0].tag = dados[pos - 1].tag;
  if (x != 0)
  {
    auxStack[0].caracter = dados[pos - 2].caracter;
    auxStack[0].tag = dados[pos - 2].tag;
  }
  POP(dados, pos - 1);
  POP(dados, pos - 2);
  POP(dados, pos - 3);
  dados[pos - 3].caracter = auxStack[0].caracter;
  dados[pos - 3].tag = auxStack[0].tag;
  if (j != 0)
  {
    if (x != 0)
    {
      POP_ARRAY(dados, pos - 3);
    }
    else
    {
      POP(dados, pos - 4);
    }
  }
}

/**
 * \brief Funcao do interpretador "rangeFunc"
 *
 * Esta funcao recebe os dados recebe os dados e a posicao atual do interpretador
 * Verifica a existencia de String ou Array para mudar de funcao
 * Calcula o tamanho do membro da stack anterior a esta posição
 *
 * @param dados receber a stack
 * @param pos receber a posicao atual da stack
 */
void rangeFunc(stack *dados, int pos)
{
  int t;
  int z = PUSH(dados, pos - 1);
  if (dados[pos - 1].tag == bloco)
  {
    filterBloco(dados, pos);
    return;
  }
  if (dados[pos - 1].tag == limite || dados[pos - 1].tag == string || dados[pos - 1].tag == variavel)
  {
    rangeString(dados, pos);
    rangeArray(dados, pos);
    return;
  }
  substituirStack(dados, pos, "]");
  for (t = 0; t < z; t++)
  {
    char *aux = malloc(100);
    sprintf(aux, "%d", z - t - 1);
    createIndex(dados, pos - 1);
    dados[pos].caracter = aux;
  }
  substituirStack(dados, pos - 1, "[");
}

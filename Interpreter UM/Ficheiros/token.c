/**
 * @file Ficheiro que contem as funcoes do tokenizador e algumas relativa as variaveis
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "token.h"
#include "parser.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief Funcao para dar token as parcelas da stack
 *
 * Esta funcao recebe os dados e tokeniza-la
 * A variavel key existe com o proposito de limitar as verificaçoes, como se fosse uma hierarquia
 *
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
void tokenFunc(char *c, stack *dados, int i)
{
  int key = 1;
  do
  {
    switch (key)
    {
    case 1:
      key = ignoreToken(dados, i);
      break;
    case 2:
      key = isLimite(c, dados, i);
      break;
    case 3:
      key = isBloco(c, dados, i);
      break;
    case 4:
      key = isExpressaoMat(c, dados, i);
      break;
    case 5:
      key = isStack(c, dados, i);
      break;
    case 6:
      key = isLogica(c, dados, i);
      break;
    case 7:
      key = isInputOutput_Conversoes(c, dados, i);
      break;
    case 8:
      key = isVariavel(c, dados, i);
      break;
    case 9:
      key = isString(c, dados, i);
      break;
    case 10:
      key = isIntFloatFunc(dados, i);
      break;
    case 11:
      key = isIntFloatNothing(c, dados, i);
      break;
    }
    key++;
  } while (key < 12);
}

/**
 * \brief Funcao para dar token "ignoreToken"
 *
 * Esta funcao recebe os dados
 * Faz as verificações nesta lista de exceçoes
 *
 * @param dados receber a stack
 * @param i posicao atual da stack
 */
int ignoreToken(stack *dados, int i)
{
  if (dados[i].tag == string)
  {
    dados[i].tag = string;
    return 20;
  }
  else if (dados[i].tag == nothing)
  {
    dados[i].tag = nothing;
    return 20;
  }
  else if (dados[i].tag == variavelFantasma)
  {
    dados[i].tag = variavelFantasma;
    return 20;
  }
  else if (dados[i].tag == variavelFantasma)
  {
    dados[i].tag = variavelFantasma;
    return 20;
  }
  else if (dados[i].tag == trash)
  {
    dados[i].tag = trash;
    return 20;
  }
  return 1;
}

/**
 * \brief Funcao para dar token "isLimite"
 *
 * Esta funcao recebe os dados
 * Verifica se é Limite
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isLimite(char *c, stack *dados, int i)
{
  if (c[0] == '[' || c[0] == ']')
  {
    dados[i].tag = limite;
    return 20;
  }
  return 2;
}

/**
 * \brief Funcao para dar token "isBloco"
 *
 * Esta funcao recebe os dados
 * Verifica se é Bloco
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isBloco(char *c, stack *dados, int i)
{
  if (c[0] == '{' || c[0] == '}')
  {
    dados[i].tag = bloco;
    return 20;
  }
  return 3;
}
/**
 * \brief Funcao para dar token "isExpressaoMat"
 *
 * Esta funcao recebe os dados
 * Verifica se é uma expressao de matematica
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isExpressaoMat(char *c, stack *dados, int i)
{
  if (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == '(' || c[0] == ')' || c[0] == '%' || c[0] == '#' || c[0] == '&' || c[0] == '|' || c[0] == '^' || c[0] == '~')
  {
    if (c[0] == '-' && isdigit(c[1]) != 0)
    {
      if (dados[i].tag == numFloat || isfloat(dados[i].caracter) != 0)
      {
        dados[i].tag = numFloat;
        return 20;
      }
      else
      {
        dados[i].tag = numInteiro;
        return 20;
      }
    }
    else
    {
      dados[i].tag = expressaoMat;
      return 20;
    }
  }
  return 4;
}

/**
 * \brief Funcao para dar token "isStack"
 *
 * Esta funcao recebe os dados
 * Verifica se é Stack
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isStack(char *c, stack *dados, int i)
{
  if (c[0] == '_' || c[0] == ';' || c[0] == '\\' || c[0] == '@' || c[0] == '$' || (c[0] == 'S' && c[1] == '/') || (c[0] == 'N' && c[1] == '/'))
  {
    dados[i].tag = stacks;
    return 20;
  }
  return 5;
}

/**
 * \brief Funcao para dar token "isLogica"
 *
 * Esta funcao recebe os dados
 * Verifica se é Logica
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isLogica(char *c, stack *dados, int i)
{
  if (c[0] == '=' || c[0] == '<' || c[0] == '>' || c[0] == '!' || (c[0] == 'e' && c[1] == '&') || (c[0] == 'e' && c[1] == '|') || (c[0] == 'e' && c[1] == '<') || (c[0] == 'e' && c[1] == '>') || c[0] == '?') /* está em falta o Falso e Verdadeiro */
  {                                                                                                                                                                                                            /*Manipular os char individualmente-------------------------------------------------------------------------------------------*/
    dados[i].tag = logica;
    return 20;
  }
  return 6;
}

/**
 * \brief Funcao para dar token "isInputOutput_Conversoes"
 *
 * Esta funcao recebe os dados
 * Verifica se é Input/Output ou Conversao
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isInputOutput_Conversoes(char *c, stack *dados, int i)
{
  if (((c[0] == 'l' || c[0] == 't' || c[0] == 'p' || c[0] == 'i' || c[0] == 'f' || c[0] == 'c' || c[0] == 's') && !c[1]) || (c[0] == ':' && (c[1] >= 'A' && c[1] <= 'Z') && !c[2]) || c[0] == ',')
  {
    dados[i].tag = inputOutput_Conversoes;
    return 20;
  }
  return 7;
}

/**
 * \brief Funcao para dar token "isVariavel"
 *
 * Esta funcao recebe os dados
 * Verifica se é uma Variavel
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isVariavel(char *c, stack *dados, int i)
{
  if (((isalpha(c[0]) != 0 && (c[0] >= 'A' && c[0] <= 'Z')) && !c[1]) || c[0] == ':')
  {
    dados[i].tag = variavel;
    return 20;
  }
  return 8;
}

/**
 * \brief Funcao para dar token "isString"
 *
 * Esta funcao recebe os dados
 * Verifica se é uma String
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isString(char *c, stack *dados, int i)
{
  if (c[0] == '"')
  {
    dados[i].tag = string;
    return 20;
  }
  return 9;
}

/**
 * \brief Funcao para dar token "isIntFloatFunc"
 *
 * Esta funcao recebe os dados
 * Faz as verificações nesta lista de exceçoes
 * 
 * @param dados receber a stack
 * @param i posicao atual da stack
 */
int isIntFloatFunc(stack *dados, int i)
{
  if (dados[i].tag == numFloatFunc || dados[i].tag == numInteiroFunc)
  {
    if (dados[i].tag == numFloatFunc)
    {
      dados[i].tag = numFloatFunc;
      return 20;
    }
    else
    {
      dados[i].tag = numInteiroFunc;
      return 20;
    }
  }
  return 10;
}

/**
 * \brief Funcao para dar token "isIntFloatNothing"
 *
 * Esta funcao recebe os dados
 * Verifica se é um Inteiro, Float ou se é não é nada em particular
 * 
 * @param dados receber a stack
 * @param c receber a string atual da estrutura de dados para uma facilidade na verificacao
 * @param i posicao atual da stack
 */
int isIntFloatNothing(char *c, stack *dados, int i)
{
  if (dados[i].tag == numFloat || isfloat(dados[i].caracter) != 0)
  {
    dados[i].tag = numFloat;
    return 20;
  }
  else if (isdigit(c[0]) != 0)
  {
    dados[i].tag = numInteiro;
    return 20;
  }
  else
  {
    dados[i].tag = nothing;
    return 20;
  }
  return 11;
}

/**
 * \brief Funcao para dar token as parcelas da stack
 *
 * Esta funcao recebe os dados e tokeniza-la sempre que a stack sofre alteracoes
 *
 * @param dados receber a stack
 */
void reToken(stack *dados)
{
  int i;
  for (i = 0; dados[i].caracter; i++)
  {
    if (dados[i].caracter)
    {
      tokenFunc(dados[i].caracter, dados, i);
    }
  }
}

/**
 * \brief Funcao para dar valores às variaveis por omissão
 *
 * Esta funcao recebe os dados, se for variavel, coloca o valor inicial
 *
 * @param dados receber a stack
 * @param i posicao atual da stack
 */
void variaveisOmissao(stack *dados, int i)
{
  char *c = malloc(SIZE);
  if (dados[i].tag == variavel)
  {
    switch (dados[i].caracter[0])
    {
    case 'A':
      sprintf(c, "%d", 10);
      break;
    case 'B':
      sprintf(c, "%d", 11);
      break;
    case 'C':
      sprintf(c, "%d", 12);
      break;
    case 'D':
      sprintf(c, "%d", 13);
      break;
    case 'E':
      sprintf(c, "%d", 14);
      break;
    case 'F':
      sprintf(c, "%d", 15);
      break;
    case 'N':
      c = "\n";
      break;
    case 'S':
      c[0] = ' ';
      break;
    case 'X':
      sprintf(c, "%d", 0);
      break;
    case 'Y':
      sprintf(c, "%d", 1);
      break;
    case 'Z':
      sprintf(c, "%d", 2);
      break;
    }
  }
  dados[i].variavel = c;
}

/**
 * \brief Funcao para dar token as parcelas da stack
 *
 * Esta funcao recebe os dados e modifica as variaveis todas iguais à que recebe sempre que alguma variavel é alterada
 *
 * @param dados receber a stack
 * @param pos receber a posição
 */
void reVariaveisInterpretador(stack *dados, int pos)
{
  int i;
  for (i = 0; dados[i].caracter; i++)
  {
    if ((dados[i].tag == variavel || dados[i].tag == variavelFantasma) && dados[i].caracter[0] == dados[pos].caracter[0])
    {
      if (dados[i].tag == variavel)
      {
        dados[i] = dados[pos];
      }
      else
      {
        dados[i] = dados[pos];
        dados[i].tag = variavelFantasma;
      }
    }
  }
}

/**
 * \brief Funcao para criar a "Variavel Fantasma"
 *
 * Cria uma "variavel Fantasma" sempre que alguma variavel é preenchida.
 * Esta "variavel" é residual e serve simplesmente para não se perder informação das variaveis.
 * Esta "variavel" não passa para o utilizador
 * 
 * @param dados receber a stack
 * @param pos receber a posição
 */
void variavelFantasmaFunc(stack *dados, int pos)
{
  int i;
  int x = lastPosition(dados);
  for (i = 0; dados[i].caracter; i++)
  {
    if (dados[i].tag == variavelFantasma && dados[i].caracter[0] == dados[pos].caracter[0])
    {
      return;
    }
  }
  createIndex(dados, x);
  dados[x] = dados[pos];
  dados[x].tag = variavelFantasma;
}

/**
 * \brief Funcao para ler as "variveis Fantasmas"
 *
 * Esta funcao procura as "variaveis fantasmas", e se as encontrar recolhe os dados
 *
 * @param dados receber a stack
 * @param pos receber a posição
 */
void lerVariaveilFanstasma(stack *dados, int pos)
{
  int i;
  for (i = 0; dados[i].caracter; i++)
  {
    if (dados[i].tag == variavelFantasma && dados[i].caracter[0] == dados[pos].caracter[0])
    {
      dados[pos] = dados[i];
      dados[pos].tag = variavel;
    }
  }
}
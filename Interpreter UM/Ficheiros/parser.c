/**
 * @file Ficheiro parser
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "stack.h"
#include "token.h"
#include "stack.h"
#include "string.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief Funcao responsavel por ler a String e colocar-la dentro da estrutura de dados já com o token
 *
 * Esta funcao recebe a string e corta a string em parcelas (sendo os limitadores " \t\n")
 * Cada vez que corta a string, e dado um token a funcao
 *
 * @param string String recebida do input do utilizador
 * @param dados receber a stack
 */
void parse(char *string, stack *dados)
{
  int i = 0;
  char *limite = " \t\n";
  for (dados[i].caracter = strtok(string, limite); dados[i].caracter != NULL; dados[i].caracter = strtok(NULL, limite))
  {
    tokenFunc(dados[i].caracter, dados, i);
    variaveisOmissao(dados, i);
    i++;
  }
}

/**
 * \brief Funcao responsavel juntar Strings
 *
 * Esta funcao existe pelo simples facto que o StrTok pode cortar uma string baseada no limite = " ".
 * Isto causaria enormes problemas pois "Ola Mundo" seria considerado 2 strings, então esta função:
 * Sempre que encontra uma string só com " no inicio, vai percorrer a stack até encontrar uma string com " no fim
 * Junta tudo e forma as strings pretendidas
 *
 * @param dados receber a stack
 */
void juntarStrings(stack *dados)
{
  int i, counter1;
  for (i = 0; dados[i].caracter; i++)
  {
    counter1 = sizeChar(dados[i].caracter) - 1;
    if (dados[i].caracter[0] == '"' && (dados[i].caracter[0] != dados[i].caracter[counter1] || !dados[i].caracter[1]))
    {
      char *c = malloc(SIZE);
      strcpy(c, dados[i + 1].caracter);
      strcat(dados[i].caracter, " ");
      strcat(dados[i].caracter, c);
      POP(dados, i + 1);
      i--;
    }
  }
}

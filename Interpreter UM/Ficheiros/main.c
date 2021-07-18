/**
 * @file main
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "parser.h"
#include "interpretador.h"
#include "stack.h"
#include "token.h"
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * \brief MAIN
 *
 * Funcao main:
 * Nesta funcao e inicializada toda a estrutura de dados e variaveis necessarias para a stack...
 * Recebe o input do utilizador
 * Calcula o numero de operadores para evitar fazer ciclos desnecessarios.
 * Sempre que algum ciclo acaba, a stack sofre a ReTokinizacao
 * No final, mostra a Stack
 *
 * @returns 0
 */
int main()
{
  stack dados[SIZE];
  char string[SIZE];
  int  key = 0;
  assert(fgets(string, SIZE, stdin) != NULL);
  assert(string[strlen(string) - 1] == '\n');
  parse(string, dados);
  juntarStrings(dados);
  while (key == 0)
  {
    key = interpretador(dados);
    reToken(dados);
  }
  POP_Trash(dados);
  DISPLAY(dados);
  printf("\n");
  return 0;
}

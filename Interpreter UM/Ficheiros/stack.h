/**
 * @file Ficheiro que contem as funcoes da stack que envia para o main
 */
#include <stdio.h>
#ifndef STACK_H_
#define STACK_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

/**
 * token para todo tipo de operação
 */
typedef enum token
{
  numInteiro,               /*!< enum Numero Inteiro */
  numFloat,                 /*!< enum Numero Float */
  numInteiroFunc,           /*!< enum Numero Interio Func */
  numFloatFunc,             /*!< enum Numero Float Func 1 */
  expressaoMat,             /*!< enum Expressao Matematica */
  stacks,                   /*!< enum Stacks */
  logica,                   /*!< enum Logica */
  inputOutput_Conversoes,   /*!< enum Input_Output e Conversoes */
  string,                   /*!< enum String */
  variavel,                 /*!< enum Variavel */
  variavelFantasma,         /*!< enum Variavel Fantasma */
  limite,                   /*!< enum Limite */
  bloco,                    /*!< enum Bloco */
  nothing,                  /*!< enum Nada */
  trash                     /*!< enum Lixo */ 
} token;

/**
 * Struct da stack com a definicao "stack"
 */
typedef struct Stack
{
  /**
  * Variavel que irá ter o objeto
  */
  char *caracter;
  /**
  * Token do objeto
  */
  token tag;
  /**
  * Caso que o objeto seja uma variavel, esta irá ter o valor dessa mesma
  */
  char *variavel;
} stack;

int lastPosition(stack *dados);
int isfloat(char *c);
void swap(stack *dados, int pos);
int sizeChar (char *c);
void substituirStack(stack *dados, int pos, char *c);
char *strdup(const char *str);

void POP_Trash(stack *dados);
double PUSH(stack *dados, int pos);
void POP(stack *dados, int pos);
void removeIndex(stack *dados, int i);
void createIndex(stack *dados, int i);
void DISPLAY(stack *dados);
void mostrarVariavel(stack *dados, int pos);

#endif
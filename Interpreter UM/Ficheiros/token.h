/**
 * @file Ficheiro que contem as funcoes do tokenizador para enviar para o main
 */
#include <stdio.h>
#include "stack.h"
#ifndef TOKEN_H_
#define TOKEN_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

void variaveisOmissao(stack *dados, int i);
void reVariaveisInterpretador(stack *dados, int pos);
void variavelFantasmaFunc(stack *dados, int pos);
void lerVariaveilFanstasma(stack *dados, int pos);

void tokenFunc(char *c, stack *dados, int i);
void reToken(stack *dados);
int ignoreToken(stack *dados, int i);
int isLimite(char *c, stack *dados, int i);
int isBloco(char *c, stack *dados, int i);
int isExpressaoMat(char *c, stack *dados, int i);
int isStack(char *c, stack *dados, int i);
int isLogica(char *c, stack *dados, int i);
int isInputOutput_Conversoes(char *c, stack *dados, int i);
int isVariavel(char *c, stack *dados, int i);
int isString(char *c, stack *dados, int i);
int isIntFloatFunc(stack *dados, int i);
int isIntFloatNothing(char *c, stack *dados, int i);

#endif
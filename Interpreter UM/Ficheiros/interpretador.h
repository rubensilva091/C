/**
 * @file Ficheiro que contem as funcoes do interpretador para enviar para o main
 */
#include <stdio.h>
#include "stack.h"
#ifndef INTERPRETADOR_H_
#define INTERPRETADOR_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

int interpretador(stack *dados);

void stacksFunc(stack *dados, int pos);
void duplicarStack(stack *dados, int pos);
void popStack(stack *dados, int pos);
void trocaStack(stack *dados, int pos);
void rodaStack(stack *dados, int pos);
void duplicaN_esimoStack(stack *dados, int pos);

void expressaoMatematicaFunc(stack *dados, int pos);
void soma(stack *dados, int pos);
void subtracao(stack *dados, int pos);
void multiplicacao(stack *dados, int pos);
void divisao(stack *dados, int pos);
void incrementacao(stack *dados, int pos);
void decrementacao(stack *dados, int pos);
void exponencializacao(stack *dados, int pos);
void modulo(stack *dados, int pos);
void bitwise_AND(stack *dados, int pos);
void bitwise_OR(stack *dados, int pos);
void bitwise_XOR(stack *dados, int pos);
void bitwise_NOT(stack *dados, int pos);

void inputOutput_conversoesFunc(stack *dados, int pos);
void ler(stack *dados, int pos);
void lerT(stack *dados, int pos);
void interioFUNC(stack *dados, int pos);
void floatFUNC(stack *dados, int pos);
void converterNum_Letra(stack *dados, int pos);
void converterParaString(stack *dados, int pos);
void preencherVariavel(stack *dados, int pos);

void logicaFunc(stack *dados, int pos);
void igualdade(stack *dados, int pos);
void maior(stack *dados, int pos);
void menor(stack *dados, int pos);
void negacao(stack *dados, int pos);
void e_maior(stack *dados, int pos);
void e_menor(stack *dados, int pos);
void e_And(stack *dados, int pos);
void e_Or(stack *dados, int pos);
void condicional(stack *dados, int pos);

void rangeFunc(stack *dados, int pos);

#endif
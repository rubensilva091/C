/**
 * @file Ficheiro que contem as funcoes das Strings para enviar para o main
 */
#include <stdio.h>
#include "stack.h"
#include "interpretador.h"
#ifndef STRING_H_
#define STRING_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

void multString(stack *dados, int pos, int valor);
void naoMostrarAspas(stack *dados, int pos);
void juntarString(stack *dados, int pos);
void removeAspasInternas(stack *dados, int pos);
void rangeString(stack *dados, int pos);
void buscarN_elementosMenorString(stack *dados, int pos, int valor);
void buscarN_elementosMaiorString(stack *dados, int pos, int valor);
void primeiroElementoString(stack *dados, int pos);
void ultimoElementoString(stack *dados, int pos);
void procurarSubstring(stack *dados, int pos, char *c);
void separarStringSubstring(stack *dados, int pos, char *c);
void adicionarAspas(stack *dados,int pos);
void compararStrings(stack *dados, int pos);
void maiorString(stack *dados, int pos);
void menorString(stack *dados, int pos);
void e_menorString(stack *dados, int pos);
void e_maiorString(stack *dados, int pos);
void variavelString(stack *dados, int pos);
void pesquisarStringIndex(stack *dados, int pos, int valor);
int separarStringLetra_Letra(stack *dados, int pos);
void concatStringsAte(stack *dados, int pos);

#endif
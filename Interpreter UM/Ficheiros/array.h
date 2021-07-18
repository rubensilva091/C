/**
 * @file Ficheiro que contem as funcoes do Array para enviar para o main
 */
#include <stdio.h>
#include "stack.h"
#include "interpretador.h"
#ifndef ARRAY_H_
#define ARRAY_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

int encontrarLimiteInferior(stack *dados, int pos);
void juntarArray(stack *dados, int pos);
void trocarArray(stack *dados, int pos);
void reverseArray(stack *dados, int pos);
void pesquisarArrayIndex(stack *dados, int pos, int valor);
void POP_ARRAY(stack *dados, int pos);
void negarArray(stack *dados, int pos);
void rangeArray(stack *dados, int pos);
void multArray(stack *dados, int pos, int valor);
void buscarN_elementosMaior(stack *dados, int pos, int valor);
void buscarN_elementosMenor(stack *dados, int pos, int valor);
void ultimoElemento(stack *dados, int pos);
void primeiroElemento(stack *dados, int pos);
void duplicarArray(stack *dados, int pos);
void trocaArray_Atomo(stack *dados, int pos);
void rodarStackArray(stack *dados, int pos);
int preencherVariavelArray (stack *dados, int pos);
int normalizarVariavelArray(stack *dados, int pos);
void mostrarVariavelArray(stack *dados, int pos);
void ultimoElementoVariavel(stack *dados, int pos);
void primeiroElementoVariavel(stack *dados, int pos);
void preencherVariavelArrayArray(stack *dados, int pos);

#endif
/**
 * @file Ficheiro que contem as funcoes do Array para enviar para o main
 */
#include <stdio.h>
#include "stack.h"
#include "interpretador.h"
#ifndef BLOCO_H_
#define BLOCO_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000

void POP_Bloco(stack *dados, int pos);
void pushBloco(stack *dados, int pos, stack *auxStack);
int ignorarBloco(stack *dados, int pos);
int encontrarProximoBlocoSuperior(stack *dados, int pos);
int encontrarProximoBlocoInferior(stack *dados, int pos);
void executarBloco(stack *dados, int pos);
void mapBloco(stack *dados, int pos);
void mapBlocoArray(stack *dados, int pos);
void mapBlocoString(stack *dados, int pos);
void foldBloco(stack *dados, int pos);
void foldBlocoArray(stack *dados, int pos);
void filterBloco(stack *dados, int pos);
void filterBlocoArray(stack *dados, int pos);
void filterBlocoString(stack *dados, int pos);
void sortBloco(stack *dados, int pos);
void sortBlocoArray(stack *dados, int pos);
void sortBlocoArraySORT(stack *dados, int pos);
int preencherVariavelBloco(stack *dados, int pos);
void normalizarBloco(stack *dados, int pos);
void trocaBloco_Atomo(stack *dados, int pos);

#endif
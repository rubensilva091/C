/**
 * @file Ficheiro que contem a funcao do parser para enviar para o main
 */

#include <stdio.h>
#include "stack.h"
#ifndef PARSER_H_
#define PARSER_H_
/**
 * Tamanho Padrão usado em todo o código
 */
#define SIZE 25000


void parse(char *string, stack *dados);
void juntarStrings(stack *dados);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/*Carregar o save*/

int carregaSave(Auditoria *auditoria)
{
    FILE *ficheiro;

    int quantidade = 0;

    ficheiro = fopen(FICHEIRO_SAVE, "rb");

    if (ficheiro == NULL)
    {
        return -1;
    }

    quantidade = fread(auditoria, sizeof(Auditoria), TAM, ficheiro);
    fclose(ficheiro);
    return quantidade;
}

/*Guardar as auditorias*/

void inserirSave(Auditoria *auditoria, int id)
{
    FILE *ficheiro;
    int i;

    ficheiro = fopen(FICHEIRO_SAVE, "wb");
    rewind(ficheiro);
    fwrite(auditoria, sizeof(Auditoria), id, ficheiro);
    fclose(ficheiro);
}
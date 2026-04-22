#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "../include/tipos.h"

void utils_inicializar_semente(void);

int utils_aleatorio_intervalo(int min, int max);

char *utils_ler_linha(char *buffer, size_t tamanho);

int utils_converter_int_seguro(const char *string, int *resultado);

int utils_ler_int_prompt(const char *mensagem, int min, int max);

void utils_limpar_stdin(void);

void utils_pausar(const char *mensagem);

void partida_inicializar(Partida *p, const char *nome);

void partida_imprimir(const Partida *p);

#endif
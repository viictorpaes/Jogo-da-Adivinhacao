#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* ENTRADA DE DADOS */

int ler_inteiro(int min, int max, const char *prompt);

void ler_string(char *buf, int n, const char *prompt);

/* TERMINAL E FLUXO VISUAL */

void limpar_tela(void);

void pausar(void);

/* ALEATORIEDADE */

void inicializar_rand(void);

int rand_intervalo(int min, int max);

/* DATA E TEMPO */

void formatar_data_atual(char *buf);

/* TRATAMENTO DE ERROS E AVISOS */

void erro_fatal(const char *msg);

void aviso(const char *msg);

#endif
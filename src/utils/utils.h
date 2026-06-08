#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int ler_inteiro(int min, int max, const char *prompt);

void ler_string(char *buf, int n, const char *prompt);

void limpar_tela(void);

void pausar(void);

void inicializar_rand(void);

void formatar_data_atual(char *buf);

void erro_fatal(const char *msg);

void aviso(const char *msg);

#endif
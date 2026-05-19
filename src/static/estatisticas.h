#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdbool.h>
#include "../include/tipos.h"

#define MAX_LINHAS_STATS 40
#define STATS_LINHA_LEN  160

int calcular_pontos(Dificuldade dif, int tentativas, bool venceu);
int calcular_pontos_memoria(int tentativas);
const char *heuristica_adivinhacao
(int tentativas, int max_tentativas, bool venceu,
                                    Dificuldade dif
);
const char *heuristica_memoria(int tentativas, int pontos);
void preparar_resumo_adivinhacao(char *buf, int len);
void preparar_resumo_memoria(char *buf, int len);
void exibir_estatisticas(void);
void exibir_historico_analitico(void);
void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas);

#endif

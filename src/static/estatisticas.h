#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdbool.h>
#include "../include/tipos.h"

#define MAX_LINHAS_STATS 35
#define STATS_LINHA_LEN  160

/* Pontuação - Adivinhação */
int calcular_pontos(Dificuldade dif, int tentativas, bool venceu);

/* Pontuação - Memória
 * Base 100, -5 por jogada além do mínimo de 8.
 * Ex: 8 jogadas = 100 pts | 16 jogadas = 60 pts | 28 jogadas = 0 pts */
int calcular_pontos_memoria(int tentativas);

/* Exibe estatísticas completas no terminal */
void exibir_estatisticas(void);

/* Preenche array de strings formatadas para o Raylib desenhar */
void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas);

#endif

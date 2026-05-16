#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "../include/tipos.h"

/* ── Adivinhação ─────────────────────────────── */
bool inicializar_historico(void);
bool salvar_partida(const RegistroPartida *r);
int  carregar_historico(RegistroPartida *buf, int max);
void exibir_historico(void);
void liberar_historico(void);

/* ── Memória ─────────────────────────────────── */
bool inicializar_historico_memoria(void);
bool salvar_partida_memoria(const RegistroMemoria *r);
int  carregar_historico_memoria(RegistroMemoria *buf, int max);
void exibir_historico_memoria(void);

#endif
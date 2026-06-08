#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "../include/tipos.h"

bool inicializar_historico(void);
bool salvar_partida(const RegistroPartida *r);
int  carregar_historico(RegistroPartida *buf, int max);
void exibir_historico(void);

bool inicializar_historico_memoria(void);
bool salvar_partida_memoria(const RegistroMemoria *r);
int  carregar_historico_memoria(RegistroMemoria *buf, int max);
void exibir_historico_memoria(void);

bool inicializar_historico_vs(void);
bool salvar_partida_vs(const RegistroVS *r);
int  carregar_historico_vs(RegistroVS *buf, int max);

bool inicializar_historico_memoria_vs(void);
bool salvar_partida_memoria_vs(const RegistroMemoria *r1, const RegistroMemoria *r2);
int  carregar_historico_memoria_vs(RegistroMemoriaVS *buf, int max);

bool inicializar_historico_logica(void);
bool salvar_puzzle(const RegistroPuzzle *r);
int  carregar_historico_puzzle(RegistroPuzzle *buf, int max, const char *modo);

bool inicializar_historico_precedencia(void);

#endif
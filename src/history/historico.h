#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "../include/tipos.h"

bool inicializar_historico(void);

bool salvar_partida(const RegistroPartida *r);

int carregar_historico(RegistroPartida *buf, int max);

void exibir_historico(void);

void liberar_historico(void);

#endif
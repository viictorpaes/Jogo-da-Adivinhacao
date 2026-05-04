#ifndef JOGO_H
#define JOGO_H

#include "../include/tipos.h"

Partida iniciar_partida(Dificuldade dif);

Resultado processar_palpite(Partida *p, int palpite);

bool partida_encerrada(const Partida *p);

void exibir_resultado_final(const Partida *p);

#endif
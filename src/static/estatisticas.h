#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdbool.h>
#include "../include/tipos.h"

int calcular_pontos(Dificuldade dif, int tentativas, bool venceu);

void exibir_estatisticas(void);

#endif

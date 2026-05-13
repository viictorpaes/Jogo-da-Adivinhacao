#ifndef MENU_H
#define MENU_H

#include "../include/tipos.h"

OpcaoMenu exibir_menu_principal(void);

Dificuldade exibir_menu_dificuldade(void);

void exibir_dica(Resultado r, int tentativas_restantes);

void exibir_erro_input(void);

void exibir_boas_vindas(void);

void exibir_despedida(void);

void pedir_nome_jogador(char *nome, int max);

#endif
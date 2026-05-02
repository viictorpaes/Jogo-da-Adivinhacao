#ifndef MENU_H
#define MENU_H

#include "../include/tipos.h"

/**
 * Exibe o menu principal e retorna a opção escolhida pelo jogador.
 * Loop interno até receber uma entrada válida.
 */
OpcaoMenu exibir_menu_principal(void);

/**
 * Exibe o submenu de seleção de dificuldade.
 * Retorna a dificuldade escolhida (FACIL, MEDIO ou DIFICIL).
 */
Dificuldade exibir_menu_dificuldade(void);

/**
 * Exibe uma dica durante o jogo (MAIOR ou MENOR).
 */
void exibir_dica(Resultado r, int tentativas_restantes);

/**
 * Exibe uma mensagem de erro de entrada inválida.
 */
void exibir_erro_input(void);

/**
 * Exibe a tela de boas-vindas / splash screen.
 */
void exibir_boas_vindas(void);

/**
 * Exibe a tela de encerramento do programa.
 */
void exibir_despedida(void);

#endif /* MENU_H */
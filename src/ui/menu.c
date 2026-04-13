#include <stdio.h>
#include "menu.h"
#include "../utils/utils.h"

int menu_exibir_principal(void) {
	printf("\n================ Jogo da Adivinhação 🎲 ================\n");
	printf("1) Jogar\n");
	printf("2) Ver historico\n");
	printf("3) Ver estatisticas\n");
	printf("4) Sair\n");
	return utils_ler_int_prompt("Escolha uma opcao: ", 1, 4);
}

int menu_selecionar_dificuldade(void) {
	printf("\nSelecione a dificuldade: \n");
	printf("0) Fácil (1-50)\n");
	printf("1) Médio (1-100)\n");
	printf("2) Difícil (1-500)\n");
	return utils_ler_int_prompt("Escolha: ", 0, 2);
}
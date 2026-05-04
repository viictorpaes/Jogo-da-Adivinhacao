#include "menu.h"
#include "../utils/utils.h"
#include <stdio.h>

#define BORDA_DUPLA   "##################################################"
#define LINHA_SIMPLES "--------------------------------------------------"


void exibir_boas_vindas(void) {
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|              JOGO DA ADIVINHACAO               |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  Descubra o numero secreto antes que suas tentativas acabem.\n");
    printf("  Boa sorte!\n\n");
    pausar();
}

OpcaoMenu exibir_menu_principal(void) {
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|                MENU PRINCIPAL                 |\n");
    printf("%s\n\n", BORDA_DUPLA);
    
    printf("  [1] Jogar Adivinhacao\n");
    printf("  [2] Jogar Memoria\n");
    printf("  [3] Ver Historico de Partidas\n");
    printf("  [4] Ver Estatisticas Globais\n");
    printf("  [5] Sair do Jogo\n\n");
    
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 5, "  Digite sua escolha: ");

    return (OpcaoMenu)escolha;
}

Dificuldade exibir_menu_dificuldade(void) {
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|             SELECIONE A DIFICULDADE            |\n");
    printf("%s\n\n", BORDA_DUPLA);
    
    printf("  [1] FACIL   (1 a %d, %d tentativas)\n", FACIL_MAX, FACIL_TENTATIVAS);
    printf("  [2] MEDIO   (1 a %d, %d tentativas)\n", MEDIO_MAX, MEDIO_TENTATIVAS);
    printf("  [3] DIFICIL (1 a %d, %d tentativas)\n\n", DIFICIL_MAX, DIFICIL_TENTATIVAS);
    
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 3, "  Escolha o nivel: ");

    if (escolha == 1) return FACIL;
    if (escolha == 2) return MEDIO;
    return DIFICIL;
}

void exibir_dica(Resultado r, int tentativas_restantes) {
    printf("\n%s\n", LINHA_SIMPLES);
    
    if (r == MAIOR) {
        printf("  DICA: O numero secreto e MAIOR que seu palpite.\n");
    } 
    else if (r == MENOR) {
        printf("  DICA: O numero secreto e MENOR que seu palpite.\n");
    } 
    else if (r == ACERTOU) {
        printf("  PARABÉNS! Voce encontrou o numero secreto.\n");
    }

    if (r != ACERTOU) {
        printf("  Tentativas restantes: %d\n", tentativas_restantes);
    }
    
    printf("%s\n\n", LINHA_SIMPLES);
}

void exibir_erro_input(void) {
    printf("\n  [!] Entrada invalida. Por favor, tente novamente.\n");
}

void exibir_despedida(void) {
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|               OBRIGADO POR JOGAR!              |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  Encerrando o sistema...\n\n");
}
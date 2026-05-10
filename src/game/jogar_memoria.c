#include <stdio.h>
#include <stdlib.h>
#include "memorygame.h"
#include "../utils/utils.h"

void jogar_memoria(void) {
    limpar_tela();
    printf("═══════════════════════════════════════\n");
    printf("   🎮 BEM-VINDO AO JOGO DA MEMÓRIA 🎮  \n");
    printf("═══════════════════════════════════════\n\n");
    
    printf("📋 REGRAS DO JOGO:\n");
    printf("  1. O tabuleiro tem 4x4 = 16 casas\n");
    printf("  2. Existem 8 pares de números (1-8)\n");
    printf("  3. Escolha 2 casas para revelar os números\n");
    printf("  4. Se os números forem iguais, você acerta!\n");
    printf("  5. Cada acerto = 10 pontos\n");
    printf("  6. Objetivo: encontrar todos os 8 pares\n\n");
    
    printf("Pressione ENTER para começar...\n");
    pausar();
    
    // Inicializar jogo
    JogoMemoria jogo = inicializar_jogo_memoria();
    
    // Loop principal do jogo
    while (!jogo_memoria_finalizado(&jogo)) {
        limpar_tela();
        exibir_tabuleiro(&jogo);
        
        printf("Escolha as duas casas (1-16):\n");
        int pos1 = ler_inteiro(1, TOTAL_CASAS, "Primeira casa: ");
        int pos2 = ler_inteiro(1, TOTAL_CASAS, "Segunda casa: ");
        
        fazer_jogada(&jogo, pos1, pos2);
    }
    
    // Mostrar resultado final
    limpar_tela();
    exibir_tabuleiro(&jogo);
    exibir_resultado_memoria(&jogo);
    
    printf("Pressione ENTER para voltar ao menu...\n");
    pausar();
}

#include "memorygame.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Embaralha os números do tabuleiro de forma aleatória
 */
static void embaralhar_tabuleiro(JogoMemoria *jogo) {
    // Preencher com pares de números (1-8)
    for (int i = 0; i < PARES; i++) {
        jogo->numeros[i * 2] = i + 1;
        jogo->numeros[i * 2 + 1] = i + 1;
    }

    // Embaralhar usando Fisher-Yates
    for (int i = TOTAL_CASAS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        
        // Trocar elementos
        int temp = jogo->numeros[i];
        jogo->numeros[i] = jogo->numeros[j];
        jogo->numeros[j] = temp;
    }
}

/**
 * Valida se uma posição está dentro do intervalo válido
 */
static bool posicao_valida(int posicao) {
    return posicao >= 1 && posicao <= TOTAL_CASAS;
}

/**
 * Revela as duas casas escolhidas
 */
static void revelar_casas(JogoMemoria *jogo, int pos1, int pos2) {
    jogo->reveladas[pos1 - 1] = true;
    jogo->reveladas[pos2 - 1] = true;
}

/**
 * Remove a revelação das casas após 1 segundo se não forem um par
 */
static void limpar_tabuleiro_temporario(JogoMemoria *jogo, int pos1, int pos2) {
    jogo->reveladas[pos1 - 1] = false;
    jogo->reveladas[pos2 - 1] = false;
}

/**
 * Inicializa um novo jogo de memória
 */
JogoMemoria inicializar_jogo_memoria(void) {
    JogoMemoria jogo;
    
    // Zerar estrutura
    memset(&jogo, 0, sizeof(JogoMemoria));
    
    // Inicializar arrays
    memset(jogo.reveladas, false, sizeof(jogo.reveladas));
    memset(jogo.acertadas, false, sizeof(jogo.acertadas));
    
    // Embaralhar tabuleiro
    embaralhar_tabuleiro(&jogo);
    
    jogo.pontuacao = 0;
    jogo.tentativas = 0;
    jogo.pares_encontrados = 0;
    
    return jogo;
}

/**
 * Exibe o tabuleiro atual com os números revelados ou ocultos
 */
void exibir_tabuleiro(const JogoMemoria *jogo) {
    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║     JOGO DA MEMÓRIA 4x4       ║\n");
    printf("║  Pontuação: %d | Pares: %d/8  ║\n", jogo->pontuacao, jogo->pares_encontrados);
    printf("╚════════════════════════════════╝\n\n");
    
    // Exibir números nas laterais para referência
    printf("    ");
    for (int col = 1; col <= TABULEIRO_SIZE; col++) {
        printf("  [%d] ", col);
    }
    printf("\n");
    
    for (int linha = 0; linha < TABULEIRO_SIZE; linha++) {
        printf("[%d] ", linha + 1);
        
        for (int col = 0; col < TABULEIRO_SIZE; col++) {
            int posicao = linha * TABULEIRO_SIZE + col;
            
            if (jogo->acertadas[posicao]) {
                printf("  ✓  ");
            } else if (jogo->reveladas[posicao]) {
                printf("  %d  ", jogo->numeros[posicao]);
            } else {
                printf("  ?  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Processa uma jogada (duas casas escolhidas)
 * Retorna true se é um par, false caso contrário
 */
bool fazer_jogada(JogoMemoria *jogo, int posicao1, int posicao2) {
    // Validar posições
    if (!posicao_valida(posicao1) || !posicao_valida(posicao2)) {
        printf("❌ Posição inválida! Digite números entre 1 e 16.\n");
        return false;
    }
    
    if (posicao1 == posicao2) {
        printf("❌ Escolha duas casas diferentes!\n");
        return false;
    }
    
    // Verificar se as casas já foram acertadas
    if (jogo->acertadas[posicao1 - 1] || jogo->acertadas[posicao2 - 1]) {
        printf("❌ Uma ou ambas as casas já foram acertadas!\n");
        return false;
    }
    
    // Incrementar tentativas
    jogo->tentativas++;
    
    // Revelar as casas
    revelar_casas(jogo, posicao1, posicao2);
    
    // Exibir tabuleiro com as casas reveladas
    exibir_tabuleiro(jogo);
    
    // Verificar se é um par
    if (jogo->numeros[posicao1 - 1] == jogo->numeros[posicao2 - 1]) {
        printf("✅ Acertou! Os números são iguais: %d = %d\n", 
               jogo->numeros[posicao1 - 1], jogo->numeros[posicao2 - 1]);
        
        // Marcar como acertadas
        jogo->acertadas[posicao1 - 1] = true;
        jogo->acertadas[posicao2 - 1] = true;
        
        // Adicionar pontos
        jogo->pontuacao += PONTOS_POR_ACERTO;
        jogo->pares_encontrados++;
        
        printf("🎉 +%d pontos! Total: %d\n\n", PONTOS_POR_ACERTO, jogo->pontuacao);
        return true;
    } else {
        printf("❌ Errou! Os números são diferentes: %d ≠ %d\n", 
               jogo->numeros[posicao1 - 1], jogo->numeros[posicao2 - 1]);
        printf("Voltando ao modo oculto...\n\n");
        
        // Aguardar 2 segundos e ocultar novamente
        pausar();
        
        // Limpar tabuleiro
        limpar_tabuleiro_temporario(jogo, posicao1, posicao2);
        
        return false;
    }
}

/**
 * Verifica se o jogo foi finalizado (todos os pares encontrados)
 */
bool jogo_memoria_finalizado(const JogoMemoria *jogo) {
    return jogo->pares_encontrados == PARES;
}

/**
 * Exibe o resultado final do jogo
 */
void exibir_resultado_memoria(const JogoMemoria *jogo) {
    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║   🎉 PARABÉNS! VOCÊ VENCEU!   ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    printf("📊 ESTATÍSTICAS FINAIS:\n");
    printf("   • Pontuação Total: %d pontos\n", jogo->pontuacao);
    printf("   • Pares Encontrados: %d/8\n", jogo->pares_encontrados);
    printf("   • Tentativas Realizadas: %d\n", jogo->tentativas);
    printf("   • Média de Acertos por Tentativa: %.2f%%\n", 
           (float)(jogo->pares_encontrados * 2) / (float)(jogo->tentativas * 2) * 100);
    printf("\n");
}

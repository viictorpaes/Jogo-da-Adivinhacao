#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <stdbool.h>

#define TABULEIRO_SIZE    4
#define TOTAL_CASAS      16
#define PARES            8
#define PONTOS_POR_ACERTO 10

typedef struct {
    int numeros[TOTAL_CASAS];      // Números do tabuleiro (1-8, duplicados)
    bool reveladas[TOTAL_CASAS];   // Estado de cada casa (revelada ou não)
    bool acertadas[TOTAL_CASAS];   // Pares já acertados
    int pontuacao;                 // Pontuação do jogador
    int tentativas;                // Número de tentativas
    int pares_encontrados;         // Total de pares encontrados
} JogoMemoria;

// Funções principais
JogoMemoria inicializar_jogo_memoria(void);
void exibir_tabuleiro(const JogoMemoria *jogo);
bool fazer_jogada(JogoMemoria *jogo, int posicao1, int posicao2);
bool jogo_memoria_finalizado(const JogoMemoria *jogo);
void exibir_resultado_memoria(const JogoMemoria *jogo);

#endif

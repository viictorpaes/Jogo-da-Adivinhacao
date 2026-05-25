#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <stdbool.h>

#define TABULEIRO_SIZE 4
#define TOTAL_CASAS 16
#define PARES 8
#define PONTOS_POR_ACERTO 10

typedef struct 
{
    int numeros[TOTAL_CASAS]; 
    bool reveladas[TOTAL_CASAS];  
    bool acertadas[TOTAL_CASAS];   
    int pontuacao;                 
    int tentativas;                
    int pares_encontrados;        
} JogoMemoria;


JogoMemoria inicializar_jogo_memoria(void);
void exibir_tabuleiro(const JogoMemoria *jogo);
bool fazer_jogada(JogoMemoria *jogo, int posicao1, int posicao2);
bool jogo_memoria_finalizado(const JogoMemoria *jogo);
void exibir_resultado_memoria(const JogoMemoria *jogo);

#endif
#include "memorygame.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void embaralhar_tabuleiro(JogoMemoria *jogo)
{
    for (int i = 0; i < PARES; i++)
    {
        jogo->numeros[i * 2] = i + 1;
        jogo->numeros[i * 2 + 1] = i + 1;
    }

    for (int i = TOTAL_CASAS - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = jogo->numeros[i];
        jogo->numeros[i] = jogo->numeros[j];
        jogo->numeros[j] = temp;
    }
}


static bool posicao_valida(int posicao) 
{
    return posicao >= 1 && posicao <= TOTAL_CASAS;
}


static void revelar_casas(JogoMemoria *jogo, int pos1, int pos2) 
{
    jogo->reveladas[pos1 - 1] = true;
    jogo->reveladas[pos2 - 1] = true;
}


JogoMemoria inicializar_jogo_memoria(void)
{
    JogoMemoria jogo;
    memset(&jogo, 0, sizeof(JogoMemoria));
    embaralhar_tabuleiro(&jogo);
    return jogo;
}

void exibir_tabuleiro(const JogoMemoria *jogo) 
{
    int coluna;
    int linha;

    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║     JOGO DA MEMÓRIA 4x4       ║\n");
    printf("║  Pontuação: %d | Pares: %d/8  ║\n", jogo->pontuacao, jogo->pares_encontrados);
    printf("╚════════════════════════════════╝\n\n");
    
    printf(" ");

    for (coluna = 1; coluna <= TABULEIRO_SIZE; coluna++) 
    {
        printf("  [%d]  ", coluna);
    }

    printf("\n");
    
    for (linha = 0; linha < TABULEIRO_SIZE; linha++) 
    {
        printf("[%d] ", linha + 1);
        
        for (coluna = 0; coluna < TABULEIRO_SIZE; coluna++) 
        {
            int posicao = linha * TABULEIRO_SIZE + coluna;
            
            if (jogo->acertadas[posicao]) 
            {
                printf("  ✅  ");
            } 

            else if (jogo->reveladas[posicao]) 
            {
                printf("  %d  ", jogo->numeros[posicao]);
            } 
            
            else 
            {
                printf("  ?  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


bool fazer_jogada(JogoMemoria *jogo, int posicao1, int posicao2) 
{
    if (!posicao_valida(posicao1) || !posicao_valida(posicao2)) 
    {
        printf("❌ Posição inválida! Digite números entre 1 e 16.\n");
        return false;
    }
    
    if (posicao1 == posicao2) 
    {
        printf("❌ Escolha duas casas diferentes!\n");
        return false;
    }
    
    if (jogo->acertadas[posicao1 - 1] || jogo->acertadas[posicao2 - 1]) 
    {
        printf("❌ Uma ou ambas as casas já foram acertadas!\n");
        return false;
    }
    
    jogo->tentativas++;

    revelar_casas(jogo, posicao1, posicao2);

    if (jogo->numeros[posicao1 - 1] == jogo->numeros[posicao2 - 1]) 
    {
        jogo->acertadas[posicao1 - 1] = true;
        jogo->acertadas[posicao2 - 1] = true;
        jogo->pontuacao += PONTOS_POR_ACERTO;
        jogo->pares_encontrados++;
        return true;
    }

    return false;
}

bool jogo_memoria_finalizado(const JogoMemoria *jogo) 
{
    return jogo->pares_encontrados == PARES;
}


void exibir_resultado_memoria(const JogoMemoria *jogo) 
{
    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║   🎉 PARABÉNS! VOCÊ VENCEU!    ║\n");
    printf("╚════════════════════════════════╝\n\n");
    
    printf("📊 ESTATÍSTICAS FINAIS:\n");
    printf("  • Pontuação Total: %d pontos\n", jogo->pontuacao);
    printf("  • Pares Encontrados: %d/8\n", jogo->pares_encontrados);
    printf("  • Tentativas Realizadas: %d\n", jogo->tentativas);
    printf("  • Média de Acertos por Tentativa: %.2f%%\n", 
           (float)(jogo->pares_encontrados * 2) / (float)(jogo->tentativas * 2) * 100);
    printf("\n");
}
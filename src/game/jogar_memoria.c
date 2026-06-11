#include "jogar_memoria.h"
#include "memorygame.h"
#include "../history/historico.h"
#include "../static/estatisticas.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void jogar_memoria(const char *nome)
{
    limpar_tela();
    printf("═══════════════════════════════════════\n");
    printf("   🎮 BEM-VINDO AO JOGO DA MEMÓRIA OTIMIZADO EM C 🎮  \n");
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

    JogoMemoria jogo = inicializar_jogo_memoria();

    while (!jogo_memoria_finalizado(&jogo))
    {
        limpar_tela();
        exibir_tabuleiro(&jogo);

        printf("\n\t Escolha duas casas (1-16): \n");
        int pos1 = ler_inteiro(1, TOTAL_CASAS, "Primeira casa: ");
        int pos2 = ler_inteiro(1, TOTAL_CASAS, "Segunda casa: ");

        bool acertou = fazer_jogada(&jogo, pos1, pos2);
        if (!acertou)
        {
            exibir_tabuleiro(&jogo);
            printf("\n ❌ Errou! Voltando ao modo oculto...\n\n");
            pausar();
            jogo.reveladas[pos1 - 1] = false;
            jogo.reveladas[pos2 - 1] = false;
        }
    }

    limpar_tela();
    exibir_tabuleiro(&jogo);
    exibir_resultado_memoria(&jogo);

    RegistroMemoria reg;
    formatar_data_atual(reg.data);
    snprintf(reg.nome, sizeof(reg.nome), "%s", nome);
    reg.pontuacao  = jogo.pontuacao;
    reg.tentativas = jogo.tentativas;
    reg.pontos = calcular_pontos_memoria(jogo.tentativas);

    salvar_partida_memoria(&reg);

    printf("\n  Pontos ganhos: %d pts 🏆\n", reg.pontos);
    printf("  Progresso salvo em: data/historico_memoria.csv\n\n");

    const char *dica = heuristica_memoria(jogo.tentativas, reg.pontos);
    printf(" \n💡 Dica: %s\n\n", dica);

    printf("Pressione ENTER para voltar ao menu...\n");
    pausar();

}
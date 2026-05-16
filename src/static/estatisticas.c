#include "estatisticas.h"
#include "../history/historico.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <string.h>

#define MAX_JOGADORES  50
#define TOP_RANKING    10
#define SEP "  ────────────────────────────────────────────────\n"

/* ════════════════════════════════════════════════════════
 *  CÁLCULO DE PONTOS
 * ════════════════════════════════════════════════════════ */

/* Adivinhação
 *   FÁCIL  : base 50,  -5  por tentativa após a 1ª (máx 10)
 *   MÉDIO  : base 70,  -10 por tentativa após a 1ª (máx  7)
 *   DIFÍCIL: base 100, -20 por tentativa após a 1ª (máx  5)
 *   DERROTA: 0 pontos */
int calcular_pontos(Dificuldade dif, int tentativas, bool venceu) {
    if (!venceu) return 0;
    int base, step;
    switch (dif) 
    {
        case FACIL:   base = 50;  step = 5;  break;
        case MEDIO:   base = 70;  step = 10; break;
        case DIFICIL: base = 100; step = 20; break;
        default: return 0;
    }

    int pts = base - (tentativas - 1) * step;
    return pts < 0 ? 0 : pts;
}

/* Memória
 *   Base 100, -5 por jogada além do mínimo teórico de 8 */
int calcular_pontos_memoria(int tentativas) 
{
    int pts = 100 - (tentativas - 8) * 5;
    return pts < 0 ? 0 : pts;
}

/* ════════════════════════════════════════════════════════
 *  RANKING COMPARTILHADO (adivinhação + memória por nome)
 * ════════════════════════════════════════════════════════ */

typedef struct 
{
    char nome[64];
    int  pontos_total;
    int  jogos;
} EntradaRanking;

static int encontrar_ou_inserir(EntradaRanking *r, int *n, const char *nome) 
{
    for (int i = 0; i < *n; i++) 
    {
        if (strcmp(r[i].nome, nome) == 0) 
        return i;
    }
    if (*n >= MAX_JOGADORES) return -1;
    int idx = *n;
    strncpy(r[idx].nome, nome, sizeof(r[idx].nome) - 1);
    r[idx].nome[sizeof(r[idx].nome) - 1] = '\0';
    r[idx].pontos_total = 0;
    r[idx].jogos = 0;
    (*n)++;
    return idx;
}

/* Constrói ranking combinado dos dois jogos */
static int construir_ranking(EntradaRanking *ranking, int *n_jogadores) {
    static RegistroPartida adv[MAX_HISTORICO];
    static RegistroMemoria mem[MAX_HISTORICO];

    int n_adv = carregar_historico(adv, MAX_HISTORICO);
    int n_mem = carregar_historico_memoria(mem, MAX_HISTORICO);

    *n_jogadores = 0;

    if (n_adv > 0) 
    {
        for (int i = 0; i < n_adv; i++) 
        {
            if (adv[i].pontos > 0 && adv[i].nome[0] != '\0') 
            {
                int idx = encontrar_ou_inserir(ranking, n_jogadores, adv[i].nome);
                if (idx >= 0) 
                {
                    ranking[idx].pontos_total += adv[i].pontos;
                    ranking[idx].jogos++;
                }
            }
        }
    }

    if (n_mem > 0) 
    {
        for (int i = 0; i < n_mem; i++) 
        {
            if (mem[i].pontos > 0 && mem[i].nome[0] != '\0') 
            {
                int idx = encontrar_ou_inserir(ranking, n_jogadores, mem[i].nome);
                if (idx >= 0) 
                {
                    ranking[idx].pontos_total += mem[i].pontos;
                    ranking[idx].jogos++;
                }
            }
        }
    }

    /* Bubble sort descendente por pontos */
    for (int i = 0; i < *n_jogadores - 1; i++) 
    {
        for (int j = 0; j < *n_jogadores - 1 - i; j++) 
        {
            if (ranking[j].pontos_total < ranking[j + 1].pontos_total) 
            {
                EntradaRanking tmp = ranking[j];
                ranking[j]     = ranking[j + 1];
                ranking[j + 1] = tmp;
            }
        }
    }

    return *n_jogadores;
}

/* ════════════════════════════════════════════════════════
 *  PREPARAR LINHAS (uso compartilhado: terminal + Raylib)
 * ════════════════════════════════════════════════════════ */

void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas) {
    *n_linhas = 0;

#define PUSH(fmt, ...) \
    if (*n_linhas < MAX_LINHAS_STATS) { \
        snprintf(linhas[*n_linhas], STATS_LINHA_LEN, fmt, ##__VA_ARGS__); \
        (*n_linhas)++; \
    }

    /* ── Adivinhação ── */
    static RegistroPartida adv[MAX_HISTORICO];
    int n_adv = carregar_historico(adv, MAX_HISTORICO);

    PUSH("=== ADIVINHACAO ===");
    if (n_adv <= 0) 
    {
        PUSH("  Nenhuma partida registrada.");
    } 
    else 
    {
        int vit = 0, soma_tent = 0;
        int p_total[3] = {0}, p_vit[3] = {0}, p_tent[3] = {0}, p_melhor[3] = {0};

        for (int i = 0; i < n_adv; i++) 
        {
            int d = (int)adv[i].dificuldade;
            p_total[d]++;
            p_tent[d] += adv[i].tentativas_usadas;
            if (adv[i].venceu) 
            {
                vit++;
                soma_tent += adv[i].tentativas_usadas;
                p_vit[d]++;
                if (adv[i].pontos > p_melhor[d]) p_melhor[d] = adv[i].pontos;
            }
        }

        int taxa = (vit * 100) / n_adv;
        PUSH("  Partidas: %d  |  Vitorias: %d  |  Derrotas: %d  (%d%%)",
             n_adv, vit, n_adv - vit, taxa);
        if (vit > 0)
            PUSH("  Media de tentativas (vitorias): %.1f",
                 (double)soma_tent / vit);

        const char *nd[] = {"FACIL  ", "MEDIO  ", "DIFICIL"};
        const int   pb[] = {50, 70, 100};
        for (int d = 0; d < 3; d++) {
            if (p_total[d] == 0) continue;
            int taxa_d = (p_vit[d] * 100) / p_total[d];
            double med = (double)p_tent[d] / p_total[d];
            if (p_melhor[d] > 0) {
                PUSH("  %s  %dV %dD  %d%%  med.%.1f tent.  melhor:%d/%dpts",
                     nd[d], p_vit[d], p_total[d]-p_vit[d], taxa_d, med,
                     p_melhor[d], pb[d]);
            } else {
                PUSH("  %s  %dV %dD  %d%%  med.%.1f tent.",
                     nd[d], p_vit[d], p_total[d]-p_vit[d], taxa_d, med);
            }
        }
    }

    PUSH(" ");

    /* ── Memória ── */
    static RegistroMemoria mem[MAX_HISTORICO];
    int n_mem = carregar_historico_memoria(mem, MAX_HISTORICO);

    PUSH("=== JOGO DA MEMORIA ===");
    if (n_mem <= 0) 
    {
        PUSH("  Nenhuma partida registrada.");
    } 
    else 
    {
        int soma_tent = 0, melhor = 0;
        for (int i = 0; i < n_mem; i++) 
        {
            soma_tent += mem[i].tentativas;
            if (mem[i].pontos > melhor) melhor = mem[i].pontos;
        }

        PUSH("  Partidas: %d  |  Media de jogadas: %.1f  |  Melhor pontuacao: %d",
             n_mem, (double)soma_tent / n_mem, melhor);
    }

    PUSH(" ");

    /* ── Ranking combinado ── */
    EntradaRanking ranking[MAX_JOGADORES];
    memset(ranking, 0, sizeof(ranking));
    int n_jog = 0;
    construir_ranking(ranking, &n_jog);

    PUSH("=== RANKING GERAL (Adivinhacao + Memoria) ===");
    if (n_jog == 0) 
    {
        PUSH("  Nenhum jogador com pontuacao ainda.");
    } 
    else 
    {
        int mostrar = n_jog < TOP_RANKING ? n_jog : TOP_RANKING;
        for (int i = 0; i < mostrar; i++) {
            PUSH("  #%-2d  %-15s  %d pts  (%d jogo%s)",
                 i + 1, ranking[i].nome, ranking[i].pontos_total,
                 ranking[i].jogos, ranking[i].jogos != 1 ? "s" : "");
        }
    }

#undef PUSH
}

/* ════════════════════════════════════════════════════════
 *  EXIBIÇÃO NO TERMINAL
 * ════════════════════════════════════════════════════════ */

void exibir_estatisticas(void) 
{
    char linhas[MAX_LINHAS_STATS][STATS_LINHA_LEN];
    int n = 0;

    preparar_linhas_estatisticas(linhas, &n);

    limpar_tela();
    printf("\n%s", SEP);
    printf("            CENTRAL DE ESTATISTICAS\n");
    printf("%s\n", SEP);

    for (int i = 0; i < n; i++) 
    {
        printf("  %s\n", linhas[i]);
    }

    printf("\n%s\n", SEP);
    pausar();
}

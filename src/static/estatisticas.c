#include "estatisticas.h"
#include "../history/historico.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <string.h>

#define MAX_JOGADORES  50
#define TOP_RANKING    10
#define SEP "  ────────────────────────────────────────────────\n"

/* Sistema de pontos por dificuldade                                   */
/*   FÁCIL  : base 50,  -5 pts por tentativa após a 1ª (10 tent. max) */
/*   MÉDIO  : base 70, -10 pts por tentativa após a 1ª ( 7 tent. max) */
/*   DIFÍCIL: base 100,-20 pts por tentativa após a 1ª ( 5 tent. max) */
/*   DERROTA: sempre 0 pontos                                          */

int calcular_pontos(Dificuldade dif, int tentativas, bool venceu) {
    if (!venceu) return 0;
    int base, step;
    switch (dif) {
        case FACIL:   base = 50;  step = 5;  break;
        case MEDIO:   base = 70;  step = 10; break;
        case DIFICIL: base = 100; step = 20; break;
        default: return 0;
    }
    int pts = base - (tentativas - 1) * step;
    return pts < 0 ? 0 : pts;
}

/* ------------------------------------------------------------------ */

typedef struct {
    char nome[64];
    int  pontos_total;
    int  vitorias;
    int  partidas;
} EntradaRanking;

static int encontrar_ou_inserir(EntradaRanking *r, int *n, const char *nome) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(r[i].nome, nome) == 0) return i;
    }
    if (*n >= MAX_JOGADORES) return -1;
    int idx = *n;
    strncpy(r[idx].nome, nome, sizeof(r[idx].nome) - 1);
    r[idx].nome[sizeof(r[idx].nome) - 1] = '\0';
    r[idx].pontos_total = 0;
    r[idx].vitorias = 0;
    r[idx].partidas = 0;
    (*n)++;
    return idx;
}

void exibir_estatisticas(void) {
    static RegistroPartida historico[MAX_HISTORICO];
    int total = carregar_historico(historico, MAX_HISTORICO);

    limpar_tela();
    printf("\n%s", SEP);
    printf("            CENTRAL DE ESTATÍSTICAS​📊​\n");
    printf("%s\n", SEP);

    if (total <= 0) {
        printf("\n  Nenhuma partida registrada ainda.​🤔​\n\n");
        pausar();
        return;
    }

    /* --- Contadores gerais --- */
    int vitorias = 0;
    int soma_tent_vit = 0;

    /* --- Contadores por dificuldade [FACIL=0, MEDIO=1, DIFICIL=2] --- */
    int p_total[3]  = {0};
    int p_vit[3]    = {0};
    int p_tent[3]   = {0};
    int p_melhor[3] = {0};

    /* --- Ranking de jogadores --- */
    EntradaRanking ranking[MAX_JOGADORES];
    memset(ranking, 0, sizeof(ranking));
    int n_jogadores = 0;

    for (int i = 0; i < total; i++) {
        RegistroPartida *rec = &historico[i];
        int d = (int)rec->dificuldade;

        p_total[d]++;
        p_tent[d] += rec->tentativas_usadas;

        if (rec->venceu) {
            vitorias++;
            soma_tent_vit += rec->tentativas_usadas;
            p_vit[d]++;
            if (rec->pontos > p_melhor[d]) p_melhor[d] = rec->pontos;
        }

        if (rec->pontos > 0 && rec->nome[0] != '\0') {
            int idx = encontrar_ou_inserir(ranking, &n_jogadores, rec->nome);
            if (idx >= 0) {
                ranking[idx].pontos_total += rec->pontos;
                ranking[idx].partidas++;
                if (rec->venceu) ranking[idx].vitorias++;
            }
        }
    }

    int derrotas = total - vitorias;
    int taxa_geral = (vitorias * 100) / total;

    /* --- Exibição geral --- */
    printf("  Partidas registradas : %d\n", total);
    printf("  Vitórias / Derrotas  : %d / %d  (%d%%)\n", vitorias, derrotas, taxa_geral);
    if (vitorias > 0) {
        printf("  Média de tentativas  : %.1f  (só vitórias)\n",
               (double)soma_tent_vit / vitorias);
    }

    /* --- Por dificuldade --- */
    printf("\n%s", SEP);
    printf("  Por Dificuldade:\n\n");

    const char *nomes_dif[] = {"FÁCIL  ", "MÉDIO  ", "DIFÍCIL"};
    const int   pontos_base[] = {50, 70, 100};

    for (int d = 0; d < 3; d++) {
        if (p_total[d] == 0) continue;
        int taxa_d = (p_vit[d] * 100) / p_total[d];
        double media_d = (double)p_tent[d] / p_total[d];

        printf("  %s  %2d partidas  %dV %dD  %3d%%  med. %.1f tent.",
               nomes_dif[d], p_total[d],
               p_vit[d], p_total[d] - p_vit[d],
               taxa_d, media_d);
        if (p_melhor[d] > 0)
            printf("  melhor: %d/%d pts", p_melhor[d], pontos_base[d]);
        printf("\n");
    }

    /* --- Ranking --- */
    if (n_jogadores > 0) {
        /* Bubble sort descendente por pontos */
        for (int i = 0; i < n_jogadores - 1; i++) {
            for (int j = 0; j < n_jogadores - 1 - i; j++) {
                if (ranking[j].pontos_total < ranking[j + 1].pontos_total) {
                    EntradaRanking tmp = ranking[j];
                    ranking[j]     = ranking[j + 1];
                    ranking[j + 1] = tmp;
                }
            }
        }

        printf("\n%s", SEP);
        printf("  Ranking de Jogadores:\n\n");
        printf("  %-4s  %-15s  %-10s  %s\n", "Pos", "Nome", "Pontos", "Vitórias");

        int mostrar = n_jogadores < TOP_RANKING ? n_jogadores : TOP_RANKING;
        for (int i = 0; i < mostrar; i++) {
            printf("  #%-3d  %-15s  %-10d  %d vitória%s\n",
                   i + 1,
                   ranking[i].nome,
                   ranking[i].pontos_total,
                   ranking[i].vitorias,
                   ranking[i].vitorias != 1 ? "s" : "");
        }
    }

    printf("\n%s\n", SEP);
    pausar();
}

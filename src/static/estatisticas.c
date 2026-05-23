#include "estatisticas.h"
#include "../history/historico.h"
#include "../utils/utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_JOGADORES 50
#define TOP_RANKING   10
#define SEP           "  ────────────────────────────────────────────────\n"


static int soma_recursiva(const int *arr, int n)
{
    if (n <= 0) return 0;
    return arr[n - 1] + soma_recursiva(arr, n - 1);
}

static int minimo_recursivo(const int *arr, int n)
{
    if (n == 1) return arr[0];
    int sub = minimo_recursivo(arr, n - 1);
    return arr[n - 1] < sub ? arr[n - 1] : sub;
}

static int maximo_recursivo(const int *arr, int n)
{
    if (n == 1) return arr[0];
    int sub = maximo_recursivo(arr, n - 1);
    return arr[n - 1] > sub ? arr[n - 1] : sub;
}

static double soma_quadrados_recursiva(const int *arr, double media, int n)
{
    if (n <= 0) return 0.0;
    double d = arr[n - 1] - media;
    return d * d + soma_quadrados_recursiva(arr, media, n - 1);
}


const char *heuristica_adivinhacao(int tentativas, int max_tentativas, bool venceu,
                                    Dificuldade dif)
{
    (void)dif;
    if (!venceu)
    {
        if (tentativas >= max_tentativas)
            return "Nao desanime! Use busca binaria: sempre chute o ponto medio do intervalo.";
        return "Quase la! Divida o intervalo ao meio a cada palpite para chegar mais rapido.";
    }
    if (tentativas == 1)
        return "Incrivel! Na primeira tentativa! Prove que e elite tentando o nivel Dificil!";
    if (tentativas * 2 <= max_tentativas)
        return "Estrategia impecavel! Busca binaria aplicada com perfeicao — parabens!";
    if ((tentativas * 4) <= (max_tentativas * 3))
        return "Boa missao! Para melhorar, sempre chute o ponto medio do intervalo restante.";
    return "Missao cumprida! Com busca binaria voce pode chegar ao resultado em menos tentativas.";
}

const char *heuristica_memoria(int tentativas, int pontos)
{
    if (pontos >= 80 && tentativas <= 8)
        return "Memoria fotografica! Desempenho perfeito — parabens, astronauta de elite!";
    if (pontos >= 60)
        return "Otimo trabalho! Foque nos cantos do tabuleiro para memorizar posicoes mais rapido.";
    if (tentativas <= 16)
        return "Bom inicio! Tente memorizar pares simetricos para reduzir o numero de jogadas.";
    return "Pratique! Observe bem as posicoes antes de agir — a memoria melhora a cada sessao!";
}


int calcular_pontos(Dificuldade dif, int tentativas, bool venceu)
{
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

int calcular_pontos_memoria(int tentativas)
{
    int pts = 100 - (tentativas - 8) * 5;
    return pts < 0 ? 0 : pts;
}


void preparar_resumo_adivinhacao(char *buf, int len)
{
    static RegistroPartida adv[MAX_HISTORICO];
    int n = carregar_historico(adv, MAX_HISTORICO);
    if (n <= 0)
    {
        snprintf(buf, len, "Nenhuma partida registrada.");
        return;
    }

    static int vit_tent[MAX_HISTORICO];
    int n_vit = 0;
    for (int i = 0; i < n; i++)
    {
        if (adv[i].venceu)
            vit_tent[n_vit++] = adv[i].tentativas_usadas;
    }

    if (n_vit == 0)
    {
        snprintf(buf, len, "%d partida%s | 0 vitorias", n, n != 1 ? "s" : "");
        return;
    }

    double media  = (double)soma_recursiva(vit_tent, n_vit) / n_vit;
    int    min_t  = minimo_recursivo(vit_tent, n_vit);
    int    max_t  = maximo_recursivo(vit_tent, n_vit);
    double sq     = soma_quadrados_recursiva(vit_tent, media, n_vit);
    double dp     = (n_vit > 1) ? sqrt(sq / (n_vit - 1)) : 0.0;

    snprintf(buf, len,
             "%d partidas | %d vit. | Med %.1ft | Min %d | Max %d | DP +/-%.1f",
             n, n_vit, media, min_t, max_t, dp);
}

void preparar_resumo_memoria(char *buf, int len)
{
    static RegistroMemoria mem[MAX_HISTORICO];
    int n = carregar_historico_memoria(mem, MAX_HISTORICO);
    if (n <= 0)
    {
        snprintf(buf, len, "Nenhuma partida registrada.");
        return;
    }

    static int tent_arr[MAX_HISTORICO];
    for (int i = 0; i < n; i++) tent_arr[i] = mem[i].tentativas;

    double media = (double)soma_recursiva(tent_arr, n) / n;
    int    min_t = minimo_recursivo(tent_arr, n);
    int    max_t = maximo_recursivo(tent_arr, n);
    double sq    = soma_quadrados_recursiva(tent_arr, media, n);
    double dp    = (n > 1) ? sqrt(sq / (n - 1)) : 0.0;

    snprintf(buf, len,
             "%d partidas | Med %.1f jog. | Min %d | Max %d | DP +/-%.1f",
             n, media, min_t, max_t, dp);
}

typedef struct
{
    char nome[64];
    int  pontos_total;
    int  jogos;
} EntradaRanking;

static int encontrar_ou_inserir(EntradaRanking *r, int *n, const char *nome)
{
    for (int i = 0; i < *n; i++)
        if (strcmp(r[i].nome, nome) == 0) return i;

    if (*n >= MAX_JOGADORES) return -1;
    int idx = *n;
    strncpy(r[idx].nome, nome, sizeof(r[idx].nome) - 1);
    r[idx].nome[sizeof(r[idx].nome) - 1] = '\0';
    r[idx].pontos_total = 0;
    r[idx].jogos        = 0;
    (*n)++;
    return idx;
}

static int construir_ranking(EntradaRanking *ranking, int *n_jogadores)
{
    static RegistroPartida  adv[MAX_HISTORICO];
    static RegistroMemoria  mem[MAX_HISTORICO];
    static RegistroVS       vs[MAX_HISTORICO];
    static RegistroPuzzle   log_a[MAX_HISTORICO];
    static RegistroPuzzle   prec[MAX_HISTORICO];

    int n_adv  = carregar_historico(adv, MAX_HISTORICO);
    int n_mem  = carregar_historico_memoria(mem, MAX_HISTORICO);
    int n_vs   = carregar_historico_vs(vs, MAX_HISTORICO);
    int n_log  = carregar_historico_puzzle(log_a, MAX_HISTORICO, "logica");
    int n_prec = carregar_historico_puzzle(prec,  MAX_HISTORICO, "precedencia");

    *n_jogadores = 0;

#define ACUM(nome_, pts_)                                              \
    do {                                                               \
        if ((pts_) > 0 && (nome_)[0]) {                               \
            int _i = encontrar_ou_inserir(ranking, n_jogadores, nome_);\
            if (_i >= 0) { ranking[_i].pontos_total += (pts_); ranking[_i].jogos++; } \
        }                                                              \
    } while (0)

    for (int i = 0; i < n_adv;  i++) ACUM(adv[i].nome,  adv[i].pontos);
    for (int i = 0; i < n_mem;  i++) ACUM(mem[i].nome,  mem[i].pontos);
    for (int i = 0; i < n_vs;   i++) { ACUM(vs[i].nome1, vs[i].pontos1); ACUM(vs[i].nome2, vs[i].pontos2); }
    for (int i = 0; i < n_log;  i++) ACUM(log_a[i].nome, log_a[i].pontos);
    for (int i = 0; i < n_prec; i++) ACUM(prec[i].nome,  prec[i].pontos);

    /* VS Memória: lê CSV diretamente (formato distinto) */
    FILE *fmvs = fopen(HISTORICO_MEM_VS_CSV, "r");
    if (fmvs)
    {
        char linha[256];
        fgets(linha, sizeof(linha), fmvs);
        while (fgets(linha, sizeof(linha), fmvs))
        {
            char d[11], n1[64], n2[64];
            int p1, pt1, p2, pt2;
            if (sscanf(linha, "%10[^,],%63[^,],%d,%d,%63[^,],%d,%d",
                       d, n1, &p1, &pt1, n2, &p2, &pt2) == 7)
            {
                ACUM(n1, pt1);
                ACUM(n2, pt2);
            }
        }
        fclose(fmvs);
    }

#undef ACUM

    for (int i = 0; i < *n_jogadores - 1; i++)
    {
        for (int j = 0; j < *n_jogadores - 1 - i; j++)
        {
            if (ranking[j].pontos_total < ranking[j + 1].pontos_total)
            {
                EntradaRanking tmp = ranking[j];
                ranking[j]         = ranking[j + 1];
                ranking[j + 1]     = tmp;
            }
        }
    }

    return *n_jogadores;
}


void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas)
{
    *n_linhas = 0;

#define PUSH(fmt, ...)                                                             \
    if (*n_linhas < MAX_LINHAS_STATS)                                              \
    {                                                                              \
        snprintf(linhas[*n_linhas], STATS_LINHA_LEN, fmt, ##__VA_ARGS__);         \
        (*n_linhas)++;                                                             \
    }

    static RegistroPartida adv[MAX_HISTORICO];
    int n_adv = carregar_historico(adv, MAX_HISTORICO);

    PUSH("=== ADIVINHAÇÃO ===");
    if (n_adv <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        static int vit_tent[MAX_HISTORICO];
        static int p_tent_arr[3][MAX_HISTORICO];
        int        p_tent_n[3] = {0};
        int        n_vit       = 0;
        int        p_total[3]  = {0}, p_vit[3] = {0}, p_melhor[3] = {0};

        for (int i = 0; i < n_adv; i++)
        {
            int d = (int)adv[i].dificuldade;
            p_total[d]++;
            p_tent_arr[d][p_tent_n[d]++] = adv[i].tentativas_usadas;
            if (adv[i].venceu)
            {
                vit_tent[n_vit++] = adv[i].tentativas_usadas;
                p_vit[d]++;
                if (adv[i].pontos > p_melhor[d]) p_melhor[d] = adv[i].pontos;
            }
        }

        int taxa = (n_vit * 100) / n_adv;
        PUSH("  Partidas: %d  |  Vitorias: %d  |  Derrotas: %d  (%d%%)",
             n_adv, n_vit, n_adv - n_vit, taxa);

        if (n_vit > 0)
        {
            double media = (double)soma_recursiva(vit_tent, n_vit) / n_vit;
            int    min_t = minimo_recursivo(vit_tent, n_vit);
            int    max_t = maximo_recursivo(vit_tent, n_vit);
            double sq    = soma_quadrados_recursiva(vit_tent, media, n_vit);
            double dp    = (n_vit > 1) ? sqrt(sq / (n_vit - 1)) : 0.0;
            PUSH("  Media: %.1f tent.  |  Min: %d  |  Max: %d  |  DP: +/-%.1f  (vitorias)",
                 media, min_t, max_t, dp);
        }

        const char *nd[] = {"FÁCIL  ", "MÉDIO  ", "DIFÍCIL"};
        const int pb[] = {50, 70, 100};
        for (int d = 0; d < 3; d++)
        {
            if (p_total[d] == 0) continue;
            int    taxa_d = (p_vit[d] * 100) / p_total[d];
            double med    = (double)soma_recursiva(p_tent_arr[d], p_tent_n[d]) / p_tent_n[d];
            if (p_melhor[d] > 0)
            {
                int pmin = minimo_recursivo(p_tent_arr[d], p_tent_n[d]);
                int pmax = maximo_recursivo(p_tent_arr[d], p_tent_n[d]);
                PUSH("  %s  %dV %dD  %d%%  med.%.1f  min:%d max:%d  melhor:%d/%dpts",
                     nd[d], p_vit[d], p_total[d] - p_vit[d], taxa_d, med,
                     pmin, pmax, p_melhor[d], pb[d]);
            }
            else
            {
                PUSH("  %s  %dV %dD  %d%%  med.%.1f tent.",
                     nd[d], p_vit[d], p_total[d] - p_vit[d], taxa_d, med);
            }
        }
    }

    PUSH(" ");

    static RegistroMemoria mem[MAX_HISTORICO];
    int n_mem = carregar_historico_memoria(mem, MAX_HISTORICO);

    PUSH("=== JOGO DA MEMÓRIA ===");
    if (n_mem <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        static int tent_arr[MAX_HISTORICO];
        static int pts_arr[MAX_HISTORICO];
        for (int i = 0; i < n_mem; i++)
        {
            tent_arr[i] = mem[i].tentativas;
            pts_arr[i]  = mem[i].pontos;
        }

        double media = (double)soma_recursiva(tent_arr, n_mem) / n_mem;
        int    min_t = minimo_recursivo(tent_arr, n_mem);
        int    max_t = maximo_recursivo(tent_arr, n_mem);
        double sq    = soma_quadrados_recursiva(tent_arr, media, n_mem);
        double dp    = (n_mem > 1) ? sqrt(sq / (n_mem - 1)) : 0.0;
        int    melhor = maximo_recursivo(pts_arr, n_mem);
        int    pior   = minimo_recursivo(pts_arr, n_mem);

        PUSH("  Partidas: %d  |  Media: %.1f jog.  |  Min: %d  |  Max: %d  |  DP: +/-%.1f",
             n_mem, media, min_t, max_t, dp);
        PUSH("  Melhor pontuacao: %d pts  |  Pior: %d pts", melhor, pior);
    }

    PUSH(" ");

    /* VS Adivinhação */
    static RegistroVS vs_arr[MAX_HISTORICO];
    int n_vs = carregar_historico_vs(vs_arr, MAX_HISTORICO);

    PUSH("=== BATALHA DE SINAIS (VS) ===");
    if (n_vs <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int v1 = 0, v2 = 0, emp = 0;
        for (int i = 0; i < n_vs; i++)
        {
            if      (vs_arr[i].vencedor == 1) v1++;
            else if (vs_arr[i].vencedor == 2) v2++;
            else                              emp++;
        }
        PUSH("  Partidas: %d  |  Vit. J1: %d  |  Vit. J2: %d  |  Empates: %d",
             n_vs, v1, v2, emp);
    }

    PUSH(" ");

    /* VS Memória */
    PUSH("=== 1v1 MAPAS ESTELARES ===");
    {
        FILE *fmvs = fopen(HISTORICO_MEM_VS_CSV, "r");
        if (!fmvs)
        {
            PUSH("  Nenhuma partida registrada.");
        }
        else
        {
            char ln[256];
            int  n_mvs = 0, tot_pares = 0;
            fgets(ln, sizeof(ln), fmvs);
            while (fgets(ln, sizeof(ln), fmvs))
            {
                char d[11], n1[64], n2[64];
                int p1, pt1, p2, pt2;
                if (sscanf(ln, "%10[^,],%63[^,],%d,%d,%63[^,],%d,%d",
                           d, n1, &p1, &pt1, n2, &p2, &pt2) == 7)
                { n_mvs++; tot_pares += p1 + p2; }
            }
            fclose(fmvs);
            if (n_mvs <= 0)
            {
                PUSH("  Nenhuma partida registrada.");
            }
            else
            {
                PUSH("  Partidas: %d  |  Média de pares/lado: %.1f",
                     n_mvs, (double)tot_pares / n_mvs / 2.0);
            }
        }
    }

    PUSH(" ");

    /* Protocolo Lógico */
    static RegistroPuzzle log_arr[MAX_HISTORICO];
    int n_log = carregar_historico_puzzle(log_arr, MAX_HISTORICO, "logica");

    PUSH("=== PROTOCOLO LÓGICO ===");
    if (n_log <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int tot_ac = 0, tot_tot = 0, melhor = 0;
        for (int i = 0; i < n_log; i++)
        {
            tot_ac  += log_arr[i].acertos;
            tot_tot += log_arr[i].total;
            if (log_arr[i].pontos > melhor) melhor = log_arr[i].pontos;
        }
        int pct = tot_tot > 0 ? (tot_ac * 100 / tot_tot) : 0;
        PUSH("  Partidas: %d  |  Acertos: %d/%d (%d%%)  |  Melhor: %d pts",
             n_log, tot_ac, tot_tot, pct, melhor);
    }

    PUSH(" ");

    /* Hierarquia de Comandos */
    static RegistroPuzzle prec_arr[MAX_HISTORICO];
    int n_prec = carregar_historico_puzzle(prec_arr, MAX_HISTORICO, "precedencia");

    PUSH("=== HIERARQUIA DE COMANDOS ===");
    if (n_prec <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int tot_ac = 0, tot_tot = 0, melhor = 0;
        for (int i = 0; i < n_prec; i++)
        {
            tot_ac  += prec_arr[i].acertos;
            tot_tot += prec_arr[i].total;
            if (prec_arr[i].pontos > melhor) melhor = prec_arr[i].pontos;
        }
        int pct = tot_tot > 0 ? (tot_ac * 100 / tot_tot) : 0;
        PUSH("  Partidas: %d  |  Acertos: %d/%d (%d%%)  |  Melhor: %d pts",
             n_prec, tot_ac, tot_tot, pct, melhor);
    }

    PUSH(" ");

    EntradaRanking ranking[MAX_JOGADORES];
    memset(ranking, 0, sizeof(ranking));
    int n_jog = 0;
    construir_ranking(ranking, &n_jog);

    PUSH("=== RANKING GERAL (Todos os Jogos) ===");
    if (n_jog == 0)
    {
        PUSH("  Nenhum jogador com pontuacao ainda.");
    }

    else
    {
        int mostrar = n_jog < TOP_RANKING ? n_jog : TOP_RANKING;
        for (int i = 0; i < mostrar; i++)
        {
            PUSH("  #%-2d  %-15s  %d pts  (%d jogo%s)",
                 i + 1, ranking[i].nome, ranking[i].pontos_total,
                 ranking[i].jogos, ranking[i].jogos != 1 ? "s" : "");
        }
    }

#undef PUSH
}


void exibir_estatisticas(void)
{
    char linhas[MAX_LINHAS_STATS][STATS_LINHA_LEN];
    int  n = 0;

    preparar_linhas_estatisticas(linhas, &n);

    limpar_tela();
    printf("\n%s", SEP);
    printf("            CENTRAL DE ESTÁTISTICAS\n");
    printf("%s\n", SEP);

    for (int i = 0; i < n; i++)
        printf("  %s\n", linhas[i]);

    printf("\n%s\n", SEP);
    pausar();
}

void exibir_historico_analitico(void)
{
    exibir_historico();
    exibir_historico_memoria();

    char buf_adiv[200];
    char buf_mem[200];
    preparar_resumo_adivinhacao(buf_adiv, sizeof(buf_adiv));
    preparar_resumo_memoria(buf_mem, sizeof(buf_mem));

    limpar_tela();
    printf("\n%s", SEP);
    printf("            RESUMO ESTATÍSTICO\n");
    printf("%s\n", SEP);
    printf("  Adivinhação : %s\n", buf_adiv);
    printf("  Memória     : %s\n", buf_mem);
    printf("\n%s\n", SEP);
    pausar();
}

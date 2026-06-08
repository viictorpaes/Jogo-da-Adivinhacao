#include "estatisticas.h"
#include "../history/historico.h"
#include "../utils/utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_JOGADORES 50
#define TOP_RANKING   10
#define SEPARADOR           "  ────────────────────────────────────────────────\n"


static int soma_recursiva(const int *valores, int qtd)
{
    if (qtd <= 0)
    {
        return 0;
    }
    return valores[qtd - 1] + soma_recursiva(valores, qtd - 1);
}

static int minimo_recursivo(const int *valores, int qtd)
{
    if (qtd == 1)
    {
        return valores[0];
    }
    int resto = minimo_recursivo(valores, qtd - 1);
    return valores[qtd - 1] < resto ? valores[qtd - 1] : resto;
}

static int maximo_recursivo(const int *valores, int qtd)
{
    if (qtd == 1)
    {
        return valores[0];
    }
    int resto = maximo_recursivo(valores, qtd - 1);
    return valores[qtd - 1] > resto ? valores[qtd - 1] : resto;
}

static double soma_quadrados_recursiva(const int *valores, double media, int qtd)
{
    if (qtd <= 0)
    {
        return 0.0;
    }
    double delta = valores[qtd - 1] - media;
    return delta * delta + soma_quadrados_recursiva(valores, media, qtd - 1);
}


const char *heuristica_adivinhacao(int tentativas, int max_tentativas, bool venceu,
                                    Dificuldade dif)
{
    (void) dif;

    if (!venceu)
    {
        if (tentativas >= max_tentativas)
        {
            return "Não desanime! Use busca binária: sempre chute o ponto médio do intervalo.";
        }

        return "Quase lá! Divida o intervalo ao meio a cada palpite para chegar mais rápido.";
    }

    if (tentativas == 1)
    {
        return "Incrível! Na primeira tentativa! Prove que é elite tentando o nível Difícil!";
    }
    
    if (tentativas * 2 <= max_tentativas)
    {
        return "Estratégia impecável! Busca binária aplicada com perfeição — parabéns!";
    }

    if ((tentativas * 4) <= (max_tentativas * 3))
    {
        return "Boa missão! Para melhorar, sempre chute o ponto médio do intervalo restante.";
    }

    return "Missão cumprida! Com busca binária você pode chegar ao resultado em menos tentativas.";
}

const char *heuristica_memoria(int tentativas, int pontos)
{
    if (pontos >= 80 && tentativas <= 8)
    {
        return "Memória fotográfica! Desempenho perfeito — parabéns, astronauta de elite!";
    }
    if (pontos >= 60)
    {
        return "Ótimo trabalho! Foque nos cantos do tabuleiro para memorizar posições mais rápido.";
    }
    if (tentativas <= 16)
    {
        return "Bom início! Tente memorizar pares simétricos para reduzir o número de jogadas.";
    }
    return "Pratique! Observe bem as posições antes de agir — a memória melhora a cada sessão!";
}


int calcular_pontos(Dificuldade dif, int tentativas, bool venceu)
{
    if (!venceu)
    {
        return 0;
    }

    int base, step;

    switch (dif)
    {
        case FACIL: base = 50; step = 5;  
        break;

        case MEDIO: base = 70; step = 10; 
        break;

        case DIFICIL: base = 100; step = 20; 
        break;

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
    int num_partidas = carregar_historico(adv, MAX_HISTORICO);
    if (num_partidas <= 0)
    {
        snprintf(buf, len, "\nNenhuma partida registrada.");
        return;
    }

    static int tent_vit[MAX_HISTORICO];
    int num_vit = 0;

    for (int i = 0; i < num_partidas; i++)
    {
        if (adv[i].venceu)
        {
            tent_vit[num_vit++] = adv[i].tentativas_usadas;
        }
    }

    if (num_vit == 0)
    {
        snprintf(buf, len, "%d partida%s | 0 vitórias", num_partidas, num_partidas != 1 ? "s" : "");
        return;
    }

    double media = (double)soma_recursiva(tent_vit, num_vit) / num_vit;
    int min_t = minimo_recursivo(tent_vit, num_vit);
    int max_t = maximo_recursivo(tent_vit, num_vit);
    double sq = soma_quadrados_recursiva(tent_vit, media, num_vit);
    double dp = (num_vit > 1) ? sqrt(sq / (num_vit - 1)) : 0.0;

    snprintf(buf, len,
             "%d partidas | %d vit. | Média %.1ft | Mín %d | Máx %d | DP +/-%.1f",
             num_partidas, num_vit, media, min_t, max_t, dp);
}

void preparar_resumo_memoria(char *buf, int len)
{
    static RegistroMemoria mem[MAX_HISTORICO];
    int num_partidas = carregar_historico_memoria(mem, MAX_HISTORICO);
    if (num_partidas <= 0)
    {
        snprintf(buf, len, "\nNenhuma partida registrada.");
        return;
    }

    static int tentativas_mem[MAX_HISTORICO];
    for (int i = 0; i < num_partidas; i++)
    {
        tentativas_mem[i] = mem[i].tentativas;
    }

    double media = (double)soma_recursiva(tentativas_mem, num_partidas) / num_partidas;
    int min_t = minimo_recursivo(tentativas_mem, num_partidas);
    int max_t = maximo_recursivo(tentativas_mem, num_partidas);
    double sq  = soma_quadrados_recursiva(tentativas_mem, media, num_partidas);
    double dp  = (num_partidas > 1) ? sqrt(sq / (num_partidas - 1)) : 0.0;

    snprintf(buf, len,
             "%d partidas | Média %.1f jog. | Mín %d | Máx %d | DP +/-%.1f",
             num_partidas, media, min_t, max_t, dp);
}

typedef struct
{
    char nome[64];
    int  pontos_total;
    int  jogos;
} EntradaRanking;

static int encontrar_ou_inserir(EntradaRanking *rank, int *n_rank, const char *nome)
{
    for (int i = 0; i < *n_rank; i++)
    {
        if (strcmp(rank[i].nome, nome) == 0)
        {
            return i;
        }
    }

    if (*n_rank >= MAX_JOGADORES)
    {
        return -1;
    }

    int novo_idx = *n_rank;
    strncpy(rank[novo_idx].nome, nome, sizeof(rank[novo_idx].nome) - 1);
    rank[novo_idx].nome[sizeof(rank[novo_idx].nome) - 1] = '\0';
    rank[novo_idx].pontos_total = 0;
    rank[novo_idx].jogos        = 0;
    (*n_rank)++;

    return novo_idx;
}

static int construir_ranking(EntradaRanking *ranking, int *num_jogadores)
{
    static RegistroPartida adv[MAX_HISTORICO];
    static RegistroMemoria mem[MAX_HISTORICO];
    static RegistroVS vs[MAX_HISTORICO];
    static RegistroPuzzle log_a[MAX_HISTORICO];
    static RegistroPuzzle prec[MAX_HISTORICO];

    int num_adv  = carregar_historico(adv, MAX_HISTORICO);
    int num_mem  = carregar_historico_memoria(mem, MAX_HISTORICO);
    int num_vs   = carregar_historico_vs(vs, MAX_HISTORICO);
    int num_log  = carregar_historico_puzzle(log_a, MAX_HISTORICO, "logica");
    int num_prec = carregar_historico_puzzle(prec,  MAX_HISTORICO, "precedencia");

    *num_jogadores = 0;

#define ACUM(nome_, pts_)                                                    \
    do {                                                                     \
        if ((pts_) > 0 && (nome_)[0])                                        \
        {                                                                    \
            int _idx = encontrar_ou_inserir(ranking, num_jogadores, nome_);  \
            if (_idx >= 0)                                                   \
            {                                                                \
                ranking[_idx].pontos_total += (pts_);                        \
                ranking[_idx].jogos++;                                       \
            }                                                                \
        }                                                                    \
    } while (0)

    for (int i = 0; i < num_adv;  i++)
    {
        ACUM(adv[i].nome, adv[i].pontos);
    }

    for (int i = 0; i < num_mem;  i++)
    {
        ACUM(mem[i].nome, mem[i].pontos);
    }

    for (int i = 0; i < num_vs; i++)
    {
        ACUM(vs[i].nome1, vs[i].pontos1);
        ACUM(vs[i].nome2, vs[i].pontos2);
    }

    for (int i = 0; i < num_log;  i++)
    {
        ACUM(log_a[i].nome, log_a[i].pontos);
    }

    for (int i = 0; i < num_prec; i++)
    {
        ACUM(prec[i].nome, prec[i].pontos);
    }

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

    for (int i = 0; i < *num_jogadores - 1; i++)
    {
        for (int j = 0; j < *num_jogadores - 1 - i; j++)
        {
            if (ranking[j].pontos_total < ranking[j + 1].pontos_total)
            {
                EntradaRanking tmp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = tmp;
            }
        }
    }

    return *num_jogadores;
}


void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas)
{
    *n_linhas = 0;

#define PUSH(fmt, ...)                                                    \
    if (*n_linhas < MAX_LINHAS_STATS)                                     \
    {                                                                     \
        snprintf(linhas[*n_linhas], STATS_LINHA_LEN, fmt, ##__VA_ARGS__); \
        (*n_linhas)++;                                                    \
    }

    static RegistroPartida adv[MAX_HISTORICO];
    int num_adv = carregar_historico(adv, MAX_HISTORICO);

    PUSH("=== ADIVINHAÇÃO ===");
    if (num_adv <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        static int tent_vit[MAX_HISTORICO];
        static int tent_por_dif[3][MAX_HISTORICO];
        int        cnt_por_dif[3]   = {0};
        int        num_vit          = 0;
        int        total_por_dif[3] = {0}, vit_por_dif[3] = {0}, melhor_por_dif[3] = {0};

        for (int i = 0; i < num_adv; i++)
        {
            int dif = (int)adv[i].dificuldade;
            total_por_dif[dif]++;
            tent_por_dif[dif][cnt_por_dif[dif]++] = adv[i].tentativas_usadas;
            if (adv[i].venceu)
            {
                tent_vit[num_vit++] = adv[i].tentativas_usadas;
                vit_por_dif[dif]++;
                if (adv[i].pontos > melhor_por_dif[dif])
                {
                    melhor_por_dif[dif] = adv[i].pontos;
                }
            }
        }

        int taxa_vit = (num_vit * 100) / num_adv;
        PUSH("  Partidas: %d  |  Vitórias: %d  |  Derrotas: %d  (%d%%)",
             num_adv, num_vit, num_adv - num_vit, taxa_vit);

        if (num_vit > 0)
        {
            double media = (double)soma_recursiva(tent_vit, num_vit) / num_vit;
            int min_t = minimo_recursivo(tent_vit, num_vit);
            int max_t = maximo_recursivo(tent_vit, num_vit);
            double sq = soma_quadrados_recursiva(tent_vit, media, num_vit);
            double dp = (num_vit > 1) ? sqrt(sq / (num_vit - 1)) : 0.0;

            PUSH("\n Média: %.1f tent.  |  Mín: %d  |  Máx: %d  |  DP: +/-%.1f  (vitórias)",
                 media, min_t, max_t, dp);
        }

        const char *label_dif[]  = {"FÁCIL  ", "MÉDIO  ", "DIFÍCIL"};
        const int   base_por_dif[] = {50, 70, 100};
        for (int dif = 0; dif < 3; dif++)
        {
            if (total_por_dif[dif] == 0)
            {
                continue;
            }

            int    taxa_vit_d = (vit_por_dif[dif] * 100) / total_por_dif[dif];
            double media_d    = (double)soma_recursiva(tent_por_dif[dif], cnt_por_dif[dif]) / cnt_por_dif[dif];

            if (melhor_por_dif[dif] > 0)
            {
                int pmin = minimo_recursivo(tent_por_dif[dif], cnt_por_dif[dif]);
                int pmax = maximo_recursivo(tent_por_dif[dif], cnt_por_dif[dif]);
                PUSH("  %s  %dV %dD  %d%%  méd.%.1f  mín:%d máx:%d  melhor:%d/%dpts",
                     label_dif[dif], vit_por_dif[dif], total_por_dif[dif] - vit_por_dif[dif],
                     taxa_vit_d, media_d, pmin, pmax, melhor_por_dif[dif], base_por_dif[dif]);
            }
            else
            {
                PUSH("  %s  %dV %dD  %d%%  méd.%.1f tent.",
                     label_dif[dif], vit_por_dif[dif], total_por_dif[dif] - vit_por_dif[dif],
                     taxa_vit_d, media_d);
            }
        }
    }

    PUSH(" ");

    static RegistroMemoria mem[MAX_HISTORICO];
    int num_mem = carregar_historico_memoria(mem, MAX_HISTORICO);

    PUSH("=== JOGO DA MEMÓRIA ===");
    if (num_mem <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        static int tentativas_mem[MAX_HISTORICO];
        static int pontos_mem[MAX_HISTORICO];
        for (int i = 0; i < num_mem; i++)
        {
            tentativas_mem[i] = mem[i].tentativas;
            pontos_mem[i]     = mem[i].pontos;
        }

        double media = (double)soma_recursiva(tentativas_mem, num_mem) / num_mem;
        int    min_tent = minimo_recursivo(tentativas_mem, num_mem);
        int    max_tent = maximo_recursivo(tentativas_mem, num_mem);
        double sq = soma_quadrados_recursiva(tentativas_mem, media, num_mem);
        double dp = (num_mem > 1) ? sqrt(sq / (num_mem - 1)) : 0.0;
        int    melhor_pontos = maximo_recursivo(pontos_mem, num_mem);
        int    pior_pontos = minimo_recursivo(pontos_mem, num_mem);

        PUSH("  Partidas: %d  |  Média: %.1f jog.  |  Mín: %d  |  Máx: %d  |  DP: +/-%.1f",
             num_mem, media, min_tent, max_tent, dp);
        PUSH("  Melhor pontuação: %d pts  |  Pior: %d pts", melhor_pontos, pior_pontos);
    }

    PUSH(" ");

    static RegistroVS vs_arr[MAX_HISTORICO];
    int num_vs = carregar_historico_vs(vs_arr, MAX_HISTORICO);

    PUSH("=== BATALHA DE SINAIS (VS) ===");
    if (num_vs <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int vit_j1 = 0, vit_j2 = 0, empates = 0;
        for (int i = 0; i < num_vs; i++)
        {
            if (vs_arr[i].vencedor == 1)
            {
                vit_j1++;
            }
            else if (vs_arr[i].vencedor == 2)
            {
                vit_j2++;
            }
            else
            {
                empates++;
            }
        }
        PUSH("  Partidas: %d  |  Vit. J1: %d  |  Vit. J2: %d  |  Empates: %d",
             num_vs, vit_j1, vit_j2, empates);
    }

    PUSH(" ");

    PUSH("=== 1v1 MAPAS ESTELARES ===");
    {
        FILE *fmvs = fopen(HISTORICO_MEM_VS_CSV, "r");
        if (!fmvs)
        {
            PUSH("  Nenhuma partida registrada.");
        }
        else
        {
            char linha[256];
            int  num_mvs = 0, total_pares = 0;
            fgets(linha, sizeof(linha), fmvs);
            while (fgets(linha, sizeof(linha), fmvs))
            {
                char data[11], nome1[64], nome2[64];
                int  pares1, pontos1, pares2, pontos2;
                if (sscanf(linha, "%10[^,],%63[^,],%d,%d,%63[^,],%d,%d",
                           data, nome1, &pares1, &pontos1, nome2, &pares2, &pontos2) == 7)
                {
                    num_mvs++;
                    total_pares += pares1 + pares2;
                }
            }

            fclose(fmvs);
            
            if (num_mvs <= 0)
            {
                PUSH("  Nenhuma partida registrada.");
            }
            else
            {
                PUSH("  Partidas: %d  |  Média de pares/lado: %.1f",
                     num_mvs, (double)total_pares / num_mvs / 2.0);
            }
        }
    }

    PUSH(" ");

    static RegistroPuzzle log_arr[MAX_HISTORICO];
    int num_log = carregar_historico_puzzle(log_arr, MAX_HISTORICO, "logica");

    PUSH("=== PROTOCOLO LÓGICO ===");
    if (num_log <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int total_acertos_log = 0, total_questoes_log = 0, melhor_pontos_log = 0;
        for (int i = 0; i < num_log; i++)
        {
            total_acertos_log  += log_arr[i].acertos;
            total_questoes_log += log_arr[i].total;
            if (log_arr[i].pontos > melhor_pontos_log)
            {
                melhor_pontos_log = log_arr[i].pontos;
            }
        }

        int pct_acertos_log = total_questoes_log > 0 ? (total_acertos_log * 100 / total_questoes_log) : 0;

        PUSH("  Partidas: %d  |  Acertos: %d/%d (%d%%)  |  Melhor: %d pts",
             num_log, total_acertos_log, total_questoes_log, pct_acertos_log, melhor_pontos_log);
    }

    PUSH(" ");

    static RegistroPuzzle prec_arr[MAX_HISTORICO];
    int num_prec = carregar_historico_puzzle(prec_arr, MAX_HISTORICO, "precedencia");

    PUSH("=== HIERARQUIA DE COMANDOS ===");
    if (num_prec <= 0)
    {
        PUSH("  Nenhuma partida registrada.");
    }
    else
    {
        int total_acertos_prec = 0, total_questoes_prec = 0, melhor_pontos_prec = 0;
        for (int i = 0; i < num_prec; i++)
        {
            total_acertos_prec  += prec_arr[i].acertos;
            total_questoes_prec += prec_arr[i].total;
            if (prec_arr[i].pontos > melhor_pontos_prec)
            {
                melhor_pontos_prec = prec_arr[i].pontos;
            }
        }
        int pct_acertos_prec = total_questoes_prec > 0 ? (total_acertos_prec * 100 / total_questoes_prec) : 0;
        PUSH("  Partidas: %d  |  Acertos: %d/%d (%d%%)  |  Melhor: %d pts",
             num_prec, total_acertos_prec, total_questoes_prec, pct_acertos_prec, melhor_pontos_prec);
    }

    PUSH(" ");

    EntradaRanking ranking[MAX_JOGADORES];
    memset(ranking, 0, sizeof(ranking));
    int num_jog = 0;
    construir_ranking(ranking, &num_jog);

    PUSH("=== RANKING GERAL (Todos os Jogos) ===");
    if (num_jog == 0)
    {
        PUSH("  Nenhum jogador com pontuação ainda.");
    }
    else
    {
        int mostrar = num_jog < TOP_RANKING ? num_jog : TOP_RANKING;
        for (int i = 0; i < mostrar; i++)
        {
            PUSH(" #%-2d  %-15s  %d pts  (%d jogo%s)",
                 i + 1, ranking[i].nome, ranking[i].pontos_total,
                 ranking[i].jogos, ranking[i].jogos != 1 ? "s" : "");
        }
    }

#undef PUSH
}


void exibir_estatisticas(void)
{
    char linhas[MAX_LINHAS_STATS][STATS_LINHA_LEN];
    int  num_linhas = 0;

    preparar_linhas_estatisticas(linhas, &num_linhas);

    limpar_tela();
    printf("\n%s", SEPARADOR);
    printf("            CENTRAL DE ESTATÍSTICAS\n");
    printf("%s\n", SEPARADOR);

    for (int i = 0; i < num_linhas; i++)
        printf("  %s\n", linhas[i]);

    printf("\n%s\n", SEPARADOR);
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
    printf("\n%s", SEPARADOR);
    printf("  RESUMO ESTATÍSTICO    \n");
    printf("%s\n", SEPARADOR);
    printf("  Adivinhação : %s\n", buf_adiv);
    printf("  Memória     : %s\n", buf_mem);
    printf("\n%s\n", SEPARADOR);
    pausar();
}
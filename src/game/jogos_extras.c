#include "jogos_extras.h"
#include "jogo.h"
#include "memorygame.h"
#include "logica.h"
#include "precedencia.h"
#include "../history/historico.h"
#include "../static/estatisticas.h"
#include "../utils/utils.h"
#include "../ui/menu.h"
#include <stdio.h>
#include <string.h>

#define SEP "══════════════════════════════════════════════════\n"

void jogar_adivinhacao_vs(void)
{
    char nome1[64], nome2[64];

    limpar_tela();
    printf("\n" SEP);
    printf("        ⚔️  BATALHA DE SINAIS — 1v1  ⚔️\n");
    printf(SEP "\n");
    printf("  Dois astronautas, um número secreto, %d rodadas!\n\n", VS_MAX_RODADAS);

    pedir_nome_jogador(nome1, sizeof(nome1));
    pedir_nome_jogador(nome2, sizeof(nome2));

    Dificuldade dif = exibir_menu_dificuldade();

    int vitorias[2]     = {0, 0};
    int pontos_total[2] = {0, 0};

    for (int rodada = 0; rodada < VS_MAX_RODADAS; rodada++)
    {
        limpar_tela();
        printf("\n" SEP);
        printf("  RODADA %d/%d  |  %s: %d vit.  |  %s: %d vit.\n",
               rodada + 1, VS_MAX_RODADAS,
               nome1, vitorias[0], nome2, vitorias[1]);
        printf(SEP "\n");

        Partida partida  = iniciar_partida(dif);
        int numero_secreto = partida.numero_secreto;
        int tentativas[2] = {0, 0};
        int jogador = 0;

        printf("  Número gerado! Range: %d a %d | %d tentativas por jogador.\n\n",
               partida.min_range, partida.max_range, VS_MAX_TENTATIVAS);

        while (1)
        {
            if (tentativas[0] >= VS_MAX_TENTATIVAS && tentativas[1] >= VS_MAX_TENTATIVAS)
            {
                printf("\n Nenhum acertou! Empate na rodada.\n");
                printf(" O número secreto era: %d\n", numero_secreto);
                break;
            }

            if (tentativas[jogador] >= VS_MAX_TENTATIVAS)
                jogador = 1 - jogador;

            const char *nome_turno = jogador == 0 ? nome1 : nome2;
            printf("  [%s] Tentativa %d/%d\n",
                   nome_turno, tentativas[jogador] + 1, VS_MAX_TENTATIVAS);

            char prompt[128];
            snprintf(prompt, sizeof(prompt), "  Palpite (%d a %d): ",
                     partida.min_range, partida.max_range);
            int palpite = ler_inteiro(partida.min_range, partida.max_range, prompt);
            tentativas[jogador]++;

            if (palpite == numero_secreto)
            {
                printf("\n 🎉 %s ACERTOU o número %d!\n", nome_turno, numero_secreto);
                vitorias[jogador]++;
                pontos_total[jogador] += calcular_pontos(dif, tentativas[jogador], 1);
                break;
            }
            else if (palpite < numero_secreto)
            {
                printf(" 🚀 O número secreto é MAIOR! ^\n\n");
            }
            else
            {
                printf(" 🚀 O número secreto é MENOR! v\n\n");
            }

            int prox = 1 - jogador;
            if (tentativas[prox] >= VS_MAX_TENTATIVAS) prox = jogador;
            jogador = prox;
        }

        pausar();
    }

    limpar_tela();
    printf("\n" SEP);
    printf("        🏆  FIM DA BATALHA DE SINAIS  🏆\n");
    printf(SEP "\n");
    printf("  %s: %d vitória(s) | %d pontos\n", nome1, vitorias[0], pontos_total[0]);
    printf("  %s: %d vitória(s) | %d pontos\n", nome2, vitorias[1], pontos_total[1]);
    printf("\n");

    if (vitorias[0] > vitorias[1])
        printf(" 🥇 VENCEDOR: %s!\n\n", nome1);
    else if (vitorias[1] > vitorias[0])
        printf(" 🥇 VENCEDOR: %s!\n\n", nome2);
    else
        printf(" 🤝 EMPATE!\n\n");

    RegistroVS reg;
    formatar_data_atual(reg.data);
    strncpy(reg.nome1, nome1, sizeof(reg.nome1) - 1);
    reg.nome1[sizeof(reg.nome1) - 1] = '\0';
    strncpy(reg.nome2, nome2, sizeof(reg.nome2) - 1);
    reg.nome2[sizeof(reg.nome2) - 1] = '\0';
    reg.dificuldade = dif;
    reg.vitorias1   = vitorias[0];
    reg.vitorias2   = vitorias[1];
    reg.pontos1     = pontos_total[0];
    reg.pontos2     = pontos_total[1];
    reg.vencedor    = vitorias[0] > vitorias[1] ? 1 : vitorias[1] > vitorias[0] ? 2 : 0;
    salvar_partida_vs(&reg);

    printf("  Resultado salvo! ✅\n\n");
    pausar();
}

void jogar_memoria_vs(void)
{
    char nome1[64], nome2[64];

    limpar_tela();
    printf("\n" SEP);
    printf("  🃏 1v1 MAPAS ESTELARES — MEMÓRIA VS 🃏\n");
    printf(SEP "\n");

    pedir_nome_jogador(nome1, sizeof(nome1));
    pedir_nome_jogador(nome2, sizeof(nome2));

    JogoMemoria jogo = inicializar_jogo_memoria();
    int pares[2] = {0, 0};
    int jogador = 0;

    while (!jogo_memoria_finalizado(&jogo))
    {
        limpar_tela();
        printf("  1v1 MAPAS ESTELARES 🌕\n");
        printf("  %s: %d pares  |  %s: %d pares\n\n",
               nome1, pares[0], nome2, pares[1]);
        printf("  TURNO: %s\n\n", jogador == 0 ? nome1 : nome2);

        exibir_tabuleiro(&jogo);

        int pos1 = ler_inteiro(1, TOTAL_CASAS, " Primeira casa: ");
        int pos2 = ler_inteiro(1, TOTAL_CASAS, " Segunda casa: ");

        int acertou_par = fazer_jogada(&jogo, pos1, pos2);
        if (acertou_par)
        {
            pares[jogador]++;
            printf("\n ✅ Par encontrado! %s continua jogando.\n\n",
                   jogador == 0 ? nome1 : nome2);
            pausar();
        }
        else
        {
            exibir_tabuleiro(&jogo);
            printf("\n ❌ Errou! Voltando ao modo oculto...\n");
            pausar();
            jogo.reveladas[pos1 - 1] = 0;
            jogo.reveladas[pos2 - 1] = 0;
            jogador = 1 - jogador;
        }
    }

    limpar_tela();
    exibir_tabuleiro(&jogo);
    printf("\n" SEP);
    printf(" 🏆  1v1 MAPAS ESTELARES — RESULTADO  🏆\n");
    printf(SEP "\n");
    printf(" %s: %d pares\n", nome1, pares[0]);
    printf(" %s: %d pares\n", nome2, pares[1]);
    printf("\n");

    if (pares[0] > pares[1])
        printf(" 🥇 VENCEDOR: %s!\n\n", nome1);
    else if (pares[1] > pares[0])
        printf(" 🥇 VENCEDOR: %s!\n\n", nome2);
    else
        printf(" 🤝 EMPATE!\n\n");

    RegistroMemoria registro1, registro2;
    formatar_data_atual(registro1.data);
    strncpy(registro1.nome, nome1, sizeof(registro1.nome) - 1);
    registro1.nome[sizeof(registro1.nome) - 1] = '\0';
    registro1.pontuacao  = pares[0];
    registro1.tentativas = jogo.tentativas;
    registro1.pontos     = pares[0] * PONTOS_POR_ACERTO;

    formatar_data_atual(registro2.data);
    strncpy(registro2.nome, nome2, sizeof(registro2.nome) - 1);
    registro2.nome[sizeof(registro2.nome) - 1] = '\0';
    registro2.pontuacao = pares[1];
    registro2.tentativas = jogo.tentativas;
    registro2.pontos = pares[1] * PONTOS_POR_ACERTO;

    salvar_partida_memoria_vs(&registro1, &registro2);

    printf("  Resultado salvo! ✅\n\n");
    pausar();
}


static void exibir_formula_logica(const JogoLogica *jogo)
{
    printf("  Fórmula : %s\n", jogo->formula_str);
    printf("  Legenda : ~ = NÃO  ^ = E  V = OU  -> = IMPLICA  <-> = BICOND.\n");
    printf("  Valores : ");
    for (int v = 0; v < jogo->qtd_vars; v++)
        printf("%c = %s   ", "PQR"[v], jogo->vars[v] ? "V" : "F");
    printf("\n\n");
}

void jogar_logica_terminal(void)
{
    char nome[64];
    pedir_nome_jogador(nome, sizeof(nome));
    Dificuldade dif = exibir_menu_dificuldade();

    JogoLogica jogo = inicializar_jogo_logica(dif);

    while (!jogo.finalizado)
    {
        limpar_tela();
        printf("\n" SEP);
        printf("  PROTOCOLO LÓGICO | Questão %d/%d\n",
               jogo.questoes_respondidas + 1, jogo.questoes_total);
        printf(SEP "\n");

        exibir_formula_logica(&jogo);

        printf(" Esta fórmula é VERDADEIRA ou FALSA para esses valores?\n");
        printf(" 1 = Verdadeira   2 = Falsa\n");
        int resposta_vf = ler_inteiro(1, 2, "  Resposta (1/2): ");
        int escolheu_v = (resposta_vf == 1);
        responder_vf_logica(&jogo, escolheu_v);

        const char *resp_str  = escolheu_v ? "Verdadeira" : "Falsa";
        const char *certa_str = jogo.resp_correta_vf ? "Verdadeira" : "Falsa";
        if (jogo.acertou_vf)
            printf(" ✅ Correto! (%s)\n\n", resp_str);
        else
            printf("  ❌ Errado! Você respondeu: %s | Correto: %s\n\n", resp_str, certa_str);

        printf(" Classifique a fórmula: \n");
        printf(" 1 = Tautologia   2 = Contradição   3 = Contingência\n");
        printf(" (TAUTOLOGIA = sempre V | CONTRADIÇÃO = sempre F | CONTINGÊNCIA = V ou F)\n");
        int resposta_classif = ler_inteiro(1, 3, "  Classificação (1/2/3): ");
        ClassFormula classificacao = (ClassFormula)(resposta_classif - 1);
        responder_classif_logica(&jogo, classificacao);

        const char *classes[] = {"Tautologia", "Contradição", "Contingência"};
        if (jogo.acertou_class)
            printf(" ✅ Correto! (%s)\n", classes[classificacao]);
        else
            printf(" ❌ Errado! Você respondeu: %s | Correto: %s\n",
                   classes[classificacao], classes[jogo.classificacao]);

        printf("\n");
        pausar();

        if (!jogo.finalizado)
            gerar_proxima_questao_logica(&jogo);
    }

    limpar_tela();
    int pontos = calcular_pontos_logica(&jogo);
    printf("\n" SEP);
    printf(" PROTOCOLO LÓGICO — FIM\n");
    printf(SEP "\n");
    printf(" Astronauta    : %s\n", nome);
    printf(" Acertos V/F   : %d/%d\n", jogo.acertos_vf,    jogo.questoes_total);
    printf(" Classificação : %d/%d\n", jogo.acertos_class, jogo.questoes_total);
    printf(" Pontos        : %d\n\n", pontos);

    RegistroPuzzle registro;
    formatar_data_atual(registro.data);
    strncpy(registro.nome, nome, sizeof(registro.nome) - 1);
    registro.nome[sizeof(registro.nome) - 1] = '\0';
    registro.acertos = jogo.acertos_vf + jogo.acertos_class;
    registro.total   = jogo.questoes_total * 2;
    registro.pontos  = pontos;
    strncpy(registro.modo, "logica", sizeof(registro.modo) - 1);
    salvar_puzzle(&registro);

    printf(" Resultado salvo! ✅\n\n");
    pausar();
}


void jogar_precedencia_terminal(void)
{
    char nome[64];
    pedir_nome_jogador(nome, sizeof(nome));
    Dificuldade dif = exibir_menu_dificuldade();

    JogoPrecedencia jogo = inicializar_jogo_precedencia(dif);

    while (!jogo.finalizado)
    {
        limpar_tela();
        printf("\n" SEP);
        printf(" HIERARQUIA DE COMANDOS | Questão %d/%d\n",
               jogo.questoes_respondidas + 1, jogo.questoes_total);
        printf(SEP "\n");
        printf(" Precedência: ~ > ^ > V > -> > <->\n\n");
        printf(" Fórmula: %s\n\n", jogo.questao.formula);
        printf(" Adicione parênteses para indicar a precedência correta:\n\n");

        for (int k = 0; k < 4; k++)
            printf("  [%d] %s\n", k + 1, jogo.questao.opcoes[k]);

        printf("\n");
        int resposta = ler_inteiro(1, 4, " Resposta (1-4): ");
        responder_precedencia(&jogo, resposta - 1);

        if (jogo.acertou)
            printf("\n ✅ Correto! +10 pts\n");
        else
            printf("\n ❌ Errado! Correto: [%d] %s\n",
                   jogo.questao.correta + 1, jogo.questao.opcoes[jogo.questao.correta]);

        printf("\n");
        pausar();

        if (!jogo.finalizado)
            gerar_proxima_questao_prec(&jogo);
    }

    limpar_tela();
    int pontos = calcular_pontos_prec(&jogo);
    printf("\n" SEP);
    printf(" HIERARQUIA DE COMANDOS — FIM\n");
    printf(SEP "\n");
    printf(" Astronauta : %s\n", nome);
    printf(" Acertos    : %d/%d\n", jogo.acertos, jogo.questoes_total);
    printf(" Pontos     : %d\n\n", pontos);

    RegistroPuzzle registro;
    formatar_data_atual(registro.data);
    strncpy(registro.nome, nome, sizeof(registro.nome) - 1);
    registro.nome[sizeof(registro.nome) - 1] = '\0';
    registro.acertos = jogo.acertos;
    registro.total   = jogo.questoes_total;
    registro.pontos  = pontos;
    strncpy(registro.modo, "precedencia", sizeof(registro.modo) - 1);
    salvar_puzzle(&registro);

    printf(" Resultado salvo! ✅\n\n");
    pausar();
}
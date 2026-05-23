#include "precedencia.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const QuestaoPreced banco_facil[] = 
{
    { "P ^ Q V R",
      { "(P ^ Q) V R", "P ^ (Q V R)", "(P V Q) ^ R", "P ^ (Q V R) V P" }, 0 },

    { "P V Q ^ R",
      { "P V (Q ^ R)", "(P V Q) ^ R", "(P ^ Q) V R", "P V Q ^ P" }, 0 },

    { "~P ^ Q V R",
      { "(~P ^ Q) V R", "~P ^ (Q V R)", "~(P ^ Q) V R", "(~P V Q) ^ R" }, 0 },

    { "P ^ ~Q V R",
      { "(P ^ ~Q) V R", "P ^ (~Q V R)", "(P V ~Q) ^ R", "~(P ^ Q) V R" }, 0 },

    { "~P V Q ^ R",
      { "~P V (Q ^ R)", "(~P V Q) ^ R", "~(P V Q) ^ R", "~P V Q ^ ~R" }, 0 },

    { "P ^ Q V ~R",
      { "(P ^ Q) V ~R", "P ^ (Q V ~R)", "(P V Q) ^ ~R", "P ^ Q V R" }, 0 },

    { "~P ^ ~Q V R",
      { "(~P ^ ~Q) V R", "~P ^ (~Q V R)", "~(P ^ Q) V R", "(~P V ~Q) ^ R" }, 0 },

    { "P V ~Q ^ R",
      { "P V (~Q ^ R)", "(P V ~Q) ^ R", "(P ^ ~Q) V R", "~P V (Q ^ R)" }, 0 },

    { "~P ^ Q V ~R",
      { "(~P ^ Q) V ~R", "~P ^ (Q V ~R)", "(~P V Q) ^ ~R", "~(P ^ Q) V ~R" }, 0 },

    { "P ^ Q V Q ^ R",
      { "(P ^ Q) V (Q ^ R)", "P ^ (Q V Q) ^ R", "(P V Q) ^ (Q V R)", "P ^ Q V Q V R" }, 0 },
};

static const QuestaoPreced banco_medio[] = 
{
    { "P -> Q ^ R",
      { "P -> (Q ^ R)", "(P -> Q) ^ R", "(P ^ Q) -> R", "P -> Q V R" }, 0 },

    { "P ^ Q -> R",
      { "(P ^ Q) -> R", "P ^ (Q -> R)", "(P -> Q) ^ R", "P V Q -> R" }, 0 },

    { "P V Q -> R",
      { "(P V Q) -> R", "P V (Q -> R)", "(P -> Q) V R", "P V Q ^ R" }, 0 },

    { "P -> Q V R",
      { "P -> (Q V R)", "(P -> Q) V R", "(P V Q) -> R", "P -> Q ^ R" }, 0 },

    { "~P -> Q ^ R",
      { "~P -> (Q ^ R)", "(~P -> Q) ^ R", "~(P -> Q) ^ R", "~P -> Q V R" }, 0 },

    { "P ^ Q -> P V R",
      { "(P ^ Q) -> (P V R)", "P ^ (Q -> P) V R", "(P ^ Q) -> P ^ R", "P ^ Q V P -> R" }, 0 },

    { "P -> ~Q ^ R",
      { "P -> (~Q ^ R)", "(P -> ~Q) ^ R", "~(P -> Q) ^ R", "P -> ~Q V R" }, 0 },

    { "P ^ Q V R -> S",
      { "((P ^ Q) V R) -> S", "(P ^ Q) V (R -> S)", "P ^ Q V (R -> S)", "(P ^ Q) -> (R V S)" }, 0 },

    { "~P -> ~Q V R",
      { "~P -> (~Q V R)", "(~P -> ~Q) V R", "~P -> ~Q ^ R", "(~P V ~Q) -> R" }, 0 },

    { "P -> Q -> R",
      { "P -> (Q -> R)", "(P -> Q) -> R", "(P ^ Q) -> R", "P V Q -> R" }, 0 },
};

static const QuestaoPreced banco_dificil[] = 
{
    { "P <-> Q -> R",
      { "P <-> (Q -> R)", "(P <-> Q) -> R", "(P -> Q) <-> R", "P <-> Q ^ R" }, 0 },

    { "P -> Q <-> R",
      { "(P -> Q) <-> R", "P -> (Q <-> R)", "P <-> (Q -> R)", "(P <-> Q) -> R" }, 0 },

    { "P ^ Q <-> R V S",
      { "(P ^ Q) <-> (R V S)", "P ^ (Q <-> R) V S", "(P ^ Q <-> R) V S", "P ^ Q V (R <-> S)" }, 0 },

    { "P -> Q <-> Q -> P",
      { "(P -> Q) <-> (Q -> P)", "P -> (Q <-> Q) -> P", "P -> Q -> (Q <-> P)", "(P <-> Q) -> (Q -> P)" }, 0 },

    { "~P <-> Q V R",
      { "~P <-> (Q V R)", "(~P <-> Q) V R", "~(P <-> Q) V R", "~P <-> Q ^ R" }, 0 },

    { "P ^ Q V R -> S <-> T",
      { "(((P ^ Q) V R) -> S) <-> T", "((P ^ Q) V R) -> (S <-> T)", "((P ^ Q) V (R -> S)) <-> T", "(P ^ Q) V (R -> (S <-> T))" }, 0 },

    { "~P ^ ~Q -> R <-> S",
      { "((~P ^ ~Q) -> R) <-> S", "(~P ^ ~Q) -> (R <-> S)", "~P ^ (~Q -> R) <-> S", "(~P ^ ~Q <-> R) -> S" }, 0 },

    { "P -> Q ^ R <-> S V T",
      { "(P -> (Q ^ R)) <-> (S V T)", "P -> ((Q ^ R) <-> (S V T))", "((P -> Q) ^ R) <-> (S V T)", "P -> (Q ^ (R <-> S)) V T" }, 0 },

    { "~(P ^ Q) -> R <-> S",
      { "(~(P ^ Q) -> R) <-> S", "~(P ^ Q) -> (R <-> S)", "~((P ^ Q) -> R) <-> S", "~(P ^ Q <-> R) -> S" }, 0 },

    { "P <-> ~Q -> R ^ S",
      { "P <-> (~Q -> (R ^ S))", "(P <-> ~Q) -> (R ^ S)", "P <-> (~Q -> R) ^ S", "(P <-> ~Q -> R) ^ S" }, 0 },

    { "P V Q -> R ^ S <-> T",
      { "((P V Q) -> (R ^ S)) <-> T", "(P V Q) -> ((R ^ S) <-> T)", "((P V Q) -> R) ^ (S <-> T)", "(P V Q) -> (R ^ (S <-> T))" }, 0 },

    { "~P V ~Q -> R <-> ~S",
      { "((~P V ~Q) -> R) <-> ~S", "(~P V ~Q) -> (R <-> ~S)", "~P V (~Q -> R) <-> ~S", "((~P V ~Q) -> (R <-> ~S))" }, 0 },
};

#define BANCO_FACIL_N (int)(sizeof(banco_facil) / sizeof(banco_facil[0]))
#define BANCO_MEDIO_N (int)(sizeof(banco_medio) / sizeof(banco_medio[0]))
#define BANCO_DIFICIL_N (int)(sizeof(banco_dificil) / sizeof(banco_dificil[0]))

static void embaralhar_opcoes(QuestaoPreced *q)
{
    for (int i = 3; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        const char *tmp = q->opcoes[i];
        q->opcoes[i] = q->opcoes[j];
        q->opcoes[j] = tmp;
        if (q->correta == i) q->correta = j;
        else if (q->correta == j) q->correta = i;
    }
}


JogoPrecedencia inicializar_jogo_precedencia(Dificuldade dif)
{
    JogoPrecedencia j;
    memset(&j, 0, sizeof(JogoPrecedencia));

    switch (dif)
    {
        case FACIL:
            j.questoes_total    = PREC_Q_FACIL;
            j.tempo_por_questao = PREC_T_FACIL;
            j.nivel             = 0;
            break;
        case MEDIO:
            j.questoes_total    = PREC_Q_MEDIO;
            j.tempo_por_questao = PREC_T_MEDIO;
            j.nivel             = 1;
            break;
        case DIFICIL:
            j.questoes_total    = PREC_Q_DIFICIL;
            j.tempo_por_questao = PREC_T_DIFICIL;
            j.nivel             = 2;
            break;
    }

    j.resp_selecionada = -1;
    gerar_proxima_questao_prec(&j);
    return j;
}

void gerar_proxima_questao_prec(JogoPrecedencia *j)
{
    const QuestaoPreced *banco;
    int banco_n;

    switch (j->nivel)
    {
        case 0:  banco = banco_facil;   banco_n = BANCO_FACIL_N;   break;
        case 1:  banco = banco_medio;   banco_n = BANCO_MEDIO_N;   break;
        default: banco = banco_dificil; banco_n = BANCO_DIFICIL_N; break;
    }

    int tentativas = 0;
    int idx;

    do 
    {
        idx = rand() % banco_n;
        bool usado = false;
        for (int i = 0; i < j->n_usados; i++)
        {
            if (j->indices_usados[i] == idx) { usado = true; break; }
        }
        if (!usado)
        {
            break;
        }
        tentativas++;
    } while (tentativas < banco_n * 3);

    if (j->n_usados < 24) j->indices_usados[j->n_usados++] = idx;

    j->questao = banco[idx];
    embaralhar_opcoes(&j->questao);

    j->resp_selecionada = -1;
    j->acertou = false;
    j->mostrando_feedback = false;
    j->timer = j->tempo_por_questao;
    j->timer_feedback = 0.0;
}

void responder_precedencia(JogoPrecedencia *j, int opcao)
{
    if (j->mostrando_feedback || j->finalizado) return;
    if (opcao < 0 || opcao > 3) return;

    j->resp_selecionada = opcao;
    j->acertou = (opcao == j->questao.correta);
    if (j->acertou) j->acertos++;
    j->questoes_respondidas++;
    j->mostrando_feedback = true;
    j->timer_feedback = 2.0;

    if (j->questoes_respondidas >= j->questoes_total)
        j->finalizado = true;
}

void atualizar_timer_prec(JogoPrecedencia *j, double dt)
{
    if (j->finalizado) return;

    if (j->mostrando_feedback) 
    {
        j->timer_feedback -= dt;
        if (j->timer_feedback <= 0.0 && !j->finalizado)
            gerar_proxima_questao_prec(j);
        return;
    }

    j->timer -= dt;
    if (j->timer <= 0.0) 
    {
        j->resp_selecionada   = -1;
        j->acertou            = false;
        j->questoes_respondidas++;
        j->mostrando_feedback = true;
        j->timer_feedback     = 2.0;
        if (j->questoes_respondidas >= j->questoes_total)
            j->finalizado = true;
    }
}

int calcular_pontos_prec(const JogoPrecedencia *j)
{
    return j->acertos * 10;
}

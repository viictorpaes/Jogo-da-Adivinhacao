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
        int pos = rand() % (i + 1);
        const char *tmp = q->opcoes[i];
        q->opcoes[i] = q->opcoes[pos];
        q->opcoes[pos] = tmp;

        if (q->correta == i) 
        { 
          q->correta = pos;
        }

        else if (q->correta == pos) 
        { 
          q->correta = i;
        }
    }
}


JogoPrecedencia inicializar_jogo_precedencia(Dificuldade dif)
{
    JogoPrecedencia j;
    memset(&j, 0, sizeof(JogoPrecedencia));

    switch (dif)
    {
        case FACIL:
            j.questoes_total = PREC_Q_FACIL;
            j.tempo_por_questao = PREC_T_FACIL;
            j.nivel = 0;
            break;

        case MEDIO:
            j.questoes_total = PREC_Q_MEDIO;
            j.tempo_por_questao = PREC_T_MEDIO;
            j.nivel = 1;
            break;

        case DIFICIL:
            j.questoes_total = PREC_Q_DIFICIL;
            j.tempo_por_questao = PREC_T_DIFICIL;
            j.nivel = 2;
            break;
    }

    j.resp_selecionada = -1;
    gerar_proxima_questao_prec(&j);
    return j;
}

void gerar_proxima_questao_prec(JogoPrecedencia *jogo)
{
    const QuestaoPreced *banco;
    int tamanho_banco;

    switch (jogo->nivel)
    {
        case 0:
            banco = banco_facil;
            tamanho_banco = BANCO_FACIL_N;
            break;

        case 1:
            banco = banco_medio;
            tamanho_banco = BANCO_MEDIO_N;
            break;

        default:
            banco = banco_dificil;
            tamanho_banco = BANCO_DIFICIL_N;
            break;
    }

    int tentativas = 0;
    int indice;

    do
    {
        indice = rand() % tamanho_banco;
        bool ja_usado = false;

        for (int i = 0; i < jogo->n_usados; i++)
        {
            if (jogo->indices_usados[i] == indice)
            {
                ja_usado = true;
                break;
            }
        }
        if (!ja_usado)
        {
            break;
        }
        tentativas++;
    } 
    while (tentativas < tamanho_banco * 3);

    if (jogo->n_usados < 24)
    {
        jogo->indices_usados[jogo->n_usados++] = indice;
    }

    jogo->questao = banco[indice];
    embaralhar_opcoes(&jogo->questao);

    jogo->resp_selecionada  = -1;
    jogo->acertou           = false;
    jogo->mostrando_feedback = false;
    jogo->timer             = jogo->tempo_por_questao;
    jogo->timer_feedback    = 0.0;
}

void responder_precedencia(JogoPrecedencia *jogo, int opcao)
{
    if (jogo->mostrando_feedback || jogo->finalizado)
    {
        return;
    }

    if (opcao < 0 || opcao > 3)
    {
        return;
    }

    jogo->resp_selecionada = opcao;
    jogo->acertou = (opcao == jogo->questao.correta);

    if (jogo->acertou)
    {
        jogo->acertos++;
        jogo->timer += 15.0;
    }

    else
    {
        jogo->timer -= 5.0;

        if (jogo->timer < 0.0)
        {
            jogo->timer = 0.0;
        }
    }

    jogo->questoes_respondidas++;
    jogo->mostrando_feedback = true;
    jogo->timer_feedback     = 2.0;

    if (jogo->questoes_respondidas >= jogo->questoes_total)
    {
        jogo->finalizado = true;
    }
}

void atualizar_timer_prec(JogoPrecedencia *jogo, double delta_t)
{
    if (jogo->finalizado)
    {
        return;
    }

    if (jogo->mostrando_feedback)
    {
        jogo->timer_feedback -= delta_t;

        if (jogo->timer_feedback <= 0.0 && !jogo->finalizado)
        {
            gerar_proxima_questao_prec(jogo);
        }
        return;
    }

    jogo->timer -= delta_t;

    if (jogo->timer <= 0.0)
    {
        jogo->resp_selecionada   = -1;
        jogo->acertou            = false;
        jogo->questoes_respondidas++;
        jogo->mostrando_feedback = true;
        jogo->timer_feedback     = 2.0;
        
        if (jogo->questoes_respondidas >= jogo->questoes_total)
        {
            jogo->finalizado = true;
        }
    }
}

int calcular_pontos_prec(const JogoPrecedencia *jogo)
{
    return jogo->acertos * 10;
}
#include "logica.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static int alocar_no(JogoLogica *j)
{
    if (j->formula.n_nos >= MAX_NOS_FORMULA)
    {
        return -1;
    }
    int idx = j->formula.n_nos++;
    j->formula.nos[idx].esq = -1;
    j->formula.nos[idx].dir = -1;
    return idx;
}

static int gerar_no(JogoLogica *j, int profundidade)
{
    if (j->formula.n_nos >= MAX_NOS_FORMULA - 4 || profundidade == 0 || rand() % 3 == 0)
    {
        int idx = alocar_no(j);
        if (idx < 0) return 0;
        j->formula.nos[idx].tipo = OP_VAR;
        j->formula.nos[idx].var  = rand() % j->n_vars;
        return idx;
    }

    int max_op = (profundidade >= 2) ? 5 : 4;
    int tipo = rand() % max_op + 1;

    int idx = alocar_no(j);
    if (idx < 0) return 0;
    j->formula.nos[idx].tipo = tipo;
    j->formula.nos[idx].esq  = gerar_no(j, profundidade - 1);
    if (tipo != OP_NOT)
    {
        j->formula.nos[idx].dir = gerar_no(j, profundidade - 1);
    }
    return idx;
}

static bool avaliar(const JogoLogica *j, int idx, const bool vars[])
{
    if (idx < 0)
    {
        return false;
    }
    const NoFormula *n = &j->formula.nos[idx];
    bool esq_val, dir_val;
    switch (n->tipo)
    {
        case OP_VAR:  return vars[n->var];
        case OP_NOT:  return !avaliar(j, n->esq, vars);
        case OP_AND:  return  avaliar(j, n->esq, vars) && avaliar(j, n->dir, vars);
        case OP_OR:   return  avaliar(j, n->esq, vars) || avaliar(j, n->dir, vars);
        case OP_IMPL: esq_val = avaliar(j, n->esq, vars); dir_val = avaliar(j, n->dir, vars);
                      return !esq_val || dir_val;
        case OP_BIMP: esq_val = avaliar(j, n->esq, vars); dir_val = avaliar(j, n->dir, vars);
                      return esq_val == dir_val;
    }
    return false;
}


static void formula_str(const JogoLogica *j, int idx, char *buf, int sz)
{
    if (idx < 0 || sz <= 0)
    {
        buf[0] = '\0';
        return;
    }

    const NoFormula *n = &j->formula.nos[idx];
    char e[128] = {0}, d[128] = {0};

    switch (n->tipo) 
    {
        case OP_VAR:
            snprintf(buf, sz, "%c", "PQR"[n->var]);
            break;
        case OP_NOT:
            formula_str(j, n->esq, e, sizeof(e));
            snprintf(buf, sz, "~%s", e);
            break;
        case OP_AND:
            formula_str(j, n->esq, e, sizeof(e));
            formula_str(j, n->dir, d, sizeof(d));
            snprintf(buf, sz, "(%s ^ %s)", e, d);
            break;
        case OP_OR:
            formula_str(j, n->esq, e, sizeof(e));
            formula_str(j, n->dir, d, sizeof(d));
            snprintf(buf, sz, "(%s V %s)", e, d);
            break;
        case OP_IMPL:
            formula_str(j, n->esq, e, sizeof(e));
            formula_str(j, n->dir, d, sizeof(d));
            snprintf(buf, sz, "(%s -> %s)", e, d);
            break;
        case OP_BIMP:
            formula_str(j, n->esq, e, sizeof(e));
            formula_str(j, n->dir, d, sizeof(d));
            snprintf(buf, sz, "(%s <-> %s)", e, d);
            break;
    }
}


static ClassFormula classificar(JogoLogica *j)
{
    int total = 1 << j->n_vars;
    bool teve_v = false, teve_f = false;
    for (int i = 0; i < total; i++) 
    {
        bool vars[3] = {false, false, false};
        for (int v = 0; v < j->n_vars; v++)
            vars[v] = (i >> v) & 1;
        if (avaliar(j, j->formula.raiz, vars)) teve_v = true;
        else                                   teve_f = true;
    }
    if (teve_v && !teve_f)
    {
        return CLASS_TAUTOLOGIA;
    }
    if (!teve_v && teve_f)
    {
        return CLASS_CONTRADICAO;
    }

    return CLASS_CONTINGENCIA;
}


JogoLogica inicializar_jogo_logica(Dificuldade dif)
{
    JogoLogica j;
    memset(&j, 0, sizeof(JogoLogica));

    switch (dif) 
    {
        case FACIL:   j.questoes_total = LOGICA_Q_FACIL;   j.n_vars = 2; j.tempo_por_questao = LOGICA_T_FACIL;   break;
        case MEDIO:   j.questoes_total = LOGICA_Q_MEDIO;   j.n_vars = 3; j.tempo_por_questao = LOGICA_T_MEDIO;   break;
        case DIFICIL: j.questoes_total = LOGICA_Q_DIFICIL; j.n_vars = 3; j.tempo_por_questao = LOGICA_T_DIFICIL; break;
    }

    j.resp_vf = -1;
    j.resp_class = -1;
    j.fase  = FASE_RESP_VF;

    gerar_proxima_questao_logica(&j);
    return j;
}

void gerar_proxima_questao_logica(JogoLogica *j)
{
    j->formula.n_nos = 0;
    j->formula.n_vars = j->n_vars;
    int prof = (j->n_vars == 2) ? 2 : 3;
    j->formula.raiz = gerar_no(j, prof);

    formula_str(j, j->formula.raiz, j->formula_str, sizeof(j->formula_str));
    j->classificacao = classificar(j);

    for (int v = 0; v < j->n_vars; v++)
        j->vars[v] = rand() & 1;
    j->resp_correta_vf = avaliar(j, j->formula.raiz, j->vars);

    j->resp_vf         = -1;
    j->resp_class      = -1;
    j->acertou_vf      = false;
    j->acertou_class   = false;
    j->fase            = FASE_RESP_VF;
    j->timer           = j->tempo_por_questao;
    j->timer_feedback  = 0.0;
}

void responder_vf_logica(JogoLogica *j, bool resposta)
{
    if (j->fase != FASE_RESP_VF) return;
    j->resp_vf    = resposta ? 1 : 0;
    j->acertou_vf = (resposta == j->resp_correta_vf);
    if (j->acertou_vf) j->acertos_vf++;
    j->fase  = FASE_CLASSIF;
    j->timer = j->tempo_por_questao;
}

void responder_classif_logica(JogoLogica *j, ClassFormula resp)
{
    if (j->fase != FASE_CLASSIF) return;
    j->resp_class    = (int)resp;
    j->acertou_class = (resp == j->classificacao);
    if (j->acertou_class) j->acertos_class++;
    j->questoes_respondidas++;
    j->fase           = FASE_FEEDBACK;
    j->timer_feedback = 2.5;
    if (j->questoes_respondidas >= j->questoes_total)
        j->finalizado = true;
}

void atualizar_timer_logica(JogoLogica *j, double dt)
{
    if (j->finalizado) return;

    if (j->fase == FASE_FEEDBACK) 
    {
        j->timer_feedback -= dt;
        if (j->timer_feedback <= 0.0 && !j->finalizado)
            gerar_proxima_questao_logica(j);
        return;
    }

    j->timer -= dt;
    if (j->timer > 0.0) return;

    j->timer = 0.0;
    if (j->fase == FASE_RESP_VF) 
    {
        j->resp_vf    = 0;
        j->acertou_vf = false;
        j->fase       = FASE_CLASSIF;
        j->timer      = j->tempo_por_questao;
    } 
    else if (j->fase == FASE_CLASSIF) 
    {
        j->resp_class    = 0;
        j->acertou_class = false;
        j->questoes_respondidas++;
        j->fase           = FASE_FEEDBACK;
        j->timer_feedback = 2.0;
        if (j->questoes_respondidas >= j->questoes_total)
            j->finalizado = true;
    }
}

int calcular_pontos_logica(const JogoLogica *j)
{
    return j->acertos_vf * 5 + j->acertos_class * 10;
}
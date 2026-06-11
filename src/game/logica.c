#include "logica.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static int alocar_no(JogoLogica *jogo)
{
    if (jogo->formula.total_nos >= MAX_NOS_FORMULA)
    {
        return -1;
    }

    else
    {
        int indice = jogo->formula.total_nos++;
        jogo->formula.nos[indice].esq = -1;
        jogo->formula.nos[indice].dir = -1;
        return indice;
    }
}

static int gerar_no(JogoLogica *jogo, int profundidade)
{
    if (jogo->formula.total_nos >= MAX_NOS_FORMULA - 4 || profundidade == 0 || rand() % 3 == 0)
    {
        int indice = alocar_no(jogo);
        if (indice < 0) return 0;
        jogo->formula.nos[indice].tipo = OP_VARIAVEL;
        jogo->formula.nos[indice].var  = rand() % jogo->qtd_vars;
        return indice;
    }

    int max_op = (profundidade >= 2) ? 5 : 4;
    int tipo = rand() % max_op + 1;

    int indice = alocar_no(jogo);

    if (indice < 0) 
    {
        return 0;
    }

    jogo->formula.nos[indice].tipo = tipo;
    jogo->formula.nos[indice].esq  = gerar_no(jogo, profundidade - 1);

    if (tipo != OP_NEGACAO)
    {
        jogo->formula.nos[indice].dir = gerar_no(jogo, profundidade - 1);
    }

    return indice;
}

static bool avaliar(const JogoLogica *jogo, int indice, const bool vars[])
{
    if (indice < 0)
    {
        return false;
    }

    const NoFormula *no = &jogo->formula.nos[indice];
    bool val_esq, val_dir;

    switch (no->tipo)
    {
        case OP_VARIAVEL:
        return vars[no->var];

        case OP_NEGACAO:
        return !avaliar(jogo, no->esq, vars);

        case OP_CONJUNCAO:
        return avaliar(jogo, no->esq, vars) && avaliar(jogo, no->dir, vars);

        case OP_DISJUNCAO:
        return avaliar(jogo, no->esq, vars) || avaliar(jogo, no->dir, vars);

        case OP_IMPLICACAO:
            val_esq = avaliar(jogo, no->esq, vars);
            val_dir = avaliar(jogo, no->dir, vars);
            return !val_esq || val_dir;

        case OP_BIIMPLICACAO:
            val_esq = avaliar(jogo, no->esq, vars);
            val_dir = avaliar(jogo, no->dir, vars);
            return val_esq == val_dir;
    }

    return false;
}


static void formula_str(const JogoLogica *jogo, int indice, char *buf, int tamanho)
{
    if (indice < 0 || tamanho <= 0)
    {
        buf[0] = '\0';
        return;
    }

    const NoFormula *no = &jogo->formula.nos[indice];
    char str_esq[128] = {0}, str_dir[128] = {0};

    switch (no->tipo)
    {
        case OP_VARIAVEL:
            snprintf(buf, tamanho, "%c", "PQR"[no->var]);
            break;

        case OP_NEGACAO:
            formula_str(jogo, no->esq, str_esq, sizeof(str_esq));
            snprintf(buf, tamanho, "~%s", str_esq);
            break;

        case OP_CONJUNCAO:
            formula_str(jogo, no->esq, str_esq, sizeof(str_esq));
            formula_str(jogo, no->dir, str_dir, sizeof(str_dir));
            snprintf(buf, tamanho, "(%s ^ %s)", str_esq, str_dir);
            break;

        case OP_DISJUNCAO:
            formula_str(jogo, no->esq, str_esq, sizeof(str_esq));
            formula_str(jogo, no->dir, str_dir, sizeof(str_dir));
            snprintf(buf, tamanho, "(%s V %s)", str_esq, str_dir);
            break;

        case OP_IMPLICACAO:
            formula_str(jogo, no->esq, str_esq, sizeof(str_esq));
            formula_str(jogo, no->dir, str_dir, sizeof(str_dir));
            snprintf(buf, tamanho, "(%s -> %s)", str_esq, str_dir);
            break;

        case OP_BIIMPLICACAO:
            formula_str(jogo, no->esq, str_esq, sizeof(str_esq));
            formula_str(jogo, no->dir, str_dir, sizeof(str_dir));
            snprintf(buf, tamanho, "(%s <-> %s)", str_esq, str_dir);
            break;
    }
}


static ClassFormula classificar(JogoLogica *jogo)
{
    int total_combinacoes = 1 << jogo->qtd_vars;
    bool achou_verdadeiro = false, achou_falso = false;

    for (int i = 0; i < total_combinacoes; i++)
    {
        bool vars[3] = {false, false, false};

        for (int var = 0; var < jogo->qtd_vars; var++)
        {
            vars[var] = (i >> var) & 1;
        }

        if (avaliar(jogo, jogo->formula.raiz, vars)) 
        {
            achou_verdadeiro = true;
        }

        else
        {
            achou_falso = true;
        }
    }

    if (achou_verdadeiro && !achou_falso)
    {
        return CLASS_TAUTOLOGIA;
    }
    
    if (!achou_verdadeiro && achou_falso)
    {
        return CLASS_CONTRADICAO;
    }

    return CLASS_CONTINGENCIA;
}


JogoLogica inicializar_jogo_logica(Dificuldade dif)
{
    JogoLogica jogo;
    memset(&jogo, 0, sizeof(JogoLogica));

    switch (dif)
    {
        case FACIL:
            jogo.questoes_total    = LOGICA_Q_FACIL;
            jogo.qtd_vars          = 2;
            jogo.tempo_por_questao = LOGICA_T_FACIL;
            break;

        case MEDIO:
            jogo.questoes_total    = LOGICA_Q_MEDIO;
            jogo.qtd_vars          = 3;
            jogo.tempo_por_questao = LOGICA_T_MEDIO;
            break;

        case DIFICIL:
            jogo.questoes_total    = LOGICA_Q_DIFICIL;
            jogo.qtd_vars          = 3;
            jogo.tempo_por_questao = LOGICA_T_DIFICIL;
            break;
    }

    jogo.resp_vf = -1;
    jogo.resp_class = -1;
    jogo.fase  = FASE_RESP_VF;

    gerar_proxima_questao_logica(&jogo);
    return jogo;
}

void gerar_proxima_questao_logica(JogoLogica *jogo)
{
    jogo->formula.total_nos = 0;
    jogo->formula.qtd_vars = jogo->qtd_vars;
    int profundidade = (jogo->qtd_vars == 2) ? 2 : 3;
    jogo->formula.raiz = gerar_no(jogo, profundidade);

    formula_str(jogo, jogo->formula.raiz, jogo->formula_str, sizeof(jogo->formula_str));
    jogo->classificacao = classificar(jogo);

    for (int v = 0; v < jogo->qtd_vars; v++)
    {
        jogo->vars[v] = rand() & 1;
    }

    jogo->resp_correta_vf = avaliar(jogo, jogo->formula.raiz, jogo->vars);

    jogo->resp_vf         = -1;
    jogo->resp_class      = -1;
    jogo->acertou_vf      = false;
    jogo->acertou_class   = false;
    jogo->fase            = FASE_RESP_VF;
    jogo->timer           = jogo->tempo_por_questao;
    jogo->timer_feedback  = 0.0;
}

void responder_vf_logica(JogoLogica *jogo, bool resposta)
{
    if (jogo->fase != FASE_RESP_VF) 
    {
        return;
    }

    jogo->resp_vf    = resposta ? 1 : 0;
    jogo->acertou_vf = (resposta == jogo->resp_correta_vf);

    if (jogo->acertou_vf)
    {
        jogo->acertos_vf++;
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

    jogo->fase = FASE_CLASSIF;
}

void responder_classif_logica(JogoLogica *jogo, ClassFormula resp)
{
    if (jogo->fase != FASE_CLASSIF) 
    {
        return;
    }

    jogo->resp_class = (int)resp;
    jogo->acertou_class = (resp == jogo->classificacao);

    if (jogo->acertou_class)
    {
        jogo->acertos_class++;
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
    jogo->fase = FASE_FEEDBACK;
    jogo->timer_feedback = 2.5;

    if (jogo->questoes_respondidas >= jogo->questoes_total) 
    {
        jogo->finalizado = true;
    }
}

void atualizar_timer_logica(JogoLogica *jogo, double delta_t)
{
    if (jogo->finalizado) 
    { 
        return;
    }


    if (jogo->fase == FASE_FEEDBACK)
    {
        jogo->timer_feedback -= delta_t;

        if (jogo->timer_feedback <= 0.0 && !jogo->finalizado) 
        {
            gerar_proxima_questao_logica(jogo);
        }

        return;
    }

    jogo->timer -= delta_t;

    if (jogo->timer > 0.0) 
    {
        return;
    }

    jogo->timer = 0.0;

    if (jogo->fase == FASE_RESP_VF)
    {
        jogo->resp_vf    = 0;
        jogo->acertou_vf = false;
        jogo->fase       = FASE_CLASSIF;
        jogo->timer      = jogo->tempo_por_questao;
    }

    else if (jogo->fase == FASE_CLASSIF)
    {
        jogo->resp_class = 0;
        jogo->acertou_class = false;
        jogo->questoes_respondidas++;
        jogo->fase = FASE_FEEDBACK;
        jogo->timer_feedback = 2.0;
        
        if (jogo->questoes_respondidas >= jogo->questoes_total) 
        {

            jogo->finalizado = true;
        }
    }
}

int calcular_pontos_logica(const JogoLogica *jogo)
{
    return jogo->acertos_vf * 5 + jogo->acertos_class * 10;
}
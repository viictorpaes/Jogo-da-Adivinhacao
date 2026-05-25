#ifndef LOGICA_H
#define LOGICA_H

#include <stdbool.h>
#include "../include/tipos.h"

#define OP_VARIAVEL     0
#define OP_NEGACAO      1
#define OP_CONJUNCAO    2
#define OP_DISJUNCAO    3
#define OP_IMPLICACAO   4
#define OP_BIIMPLICACAO 5

#define MAX_NOS_FORMULA 32
#define LOGICA_MAX_VARS  3 

typedef struct 
{
    int tipo;
    int var; 
    int esq;   
    int dir;   
} NoFormula;

typedef struct
{
    NoFormula nos[MAX_NOS_FORMULA];
    int raiz;
    int total_nos;
    int qtd_vars;
} Formula;

typedef enum 
{
    CLASS_TAUTOLOGIA = 0,
    CLASS_CONTRADICAO = 1,
    CLASS_CONTINGENCIA = 2
} ClassFormula;

typedef enum 
{
    FASE_RESP_VF    = 0,
    FASE_CLASSIF    = 1,  
    FASE_FEEDBACK   = 2, 
} FaseLogica;

typedef struct 
{
    int questoes_total;
    double tempo_por_questao;
    int qtd_vars;

    int questoes_respondidas;
    int acertos_vf;
    int acertos_class;
    bool finalizado;

    Formula formula;
    char formula_str[256];
    ClassFormula classificacao;
    bool vars[LOGICA_MAX_VARS]; 
    bool resp_correta_vf;

    int  resp_vf;      
    int  resp_class;
    bool acertou_vf;
    bool acertou_class;

    double timer;
    double timer_feedback;
    FaseLogica fase;
} JogoLogica;

JogoLogica inicializar_jogo_logica(Dificuldade dif);
void gerar_proxima_questao_logica(JogoLogica *jogo);
void responder_vf_logica(JogoLogica *jogo, bool resposta);
void responder_classif_logica(JogoLogica *jogo, ClassFormula resp);
void atualizar_timer_logica(JogoLogica *jogo, double delta_t);
int calcular_pontos_logica(const JogoLogica *jogo);

#endif
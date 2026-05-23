#ifndef LOGICA_H
#define LOGICA_H

#include <stdbool.h>
#include "../include/tipos.h"

#define OP_VAR  0
#define OP_NOT  1
#define OP_AND  2  
#define OP_OR   3  
#define OP_IMPL 4  
#define OP_BIMP 5   

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
    int n_nos;
    int n_vars;
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
    int n_vars;

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
void gerar_proxima_questao_logica(JogoLogica *j);
void responder_vf_logica(JogoLogica *j, bool resposta);
void responder_classif_logica(JogoLogica *j, ClassFormula resp);
void atualizar_timer_logica(JogoLogica *j, double dt);
int calcular_pontos_logica(const JogoLogica *j);

#endif
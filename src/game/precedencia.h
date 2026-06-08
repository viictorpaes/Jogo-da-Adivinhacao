#ifndef PRECEDENCIA_H
#define PRECEDENCIA_H

#include <stdbool.h>
#include "../include/tipos.h"

typedef struct 
{
    const char *formula;       
    const char *opcoes[4];     
    int         correta;      
} QuestaoPreced;

typedef struct 
{
    int questoes_total;
    double tempo_por_questao;
    int questoes_respondidas;
    int acertos;
    bool finalizado;

    QuestaoPreced questao;
    int resp_selecionada; 
    bool acertou;

    double timer;
    bool mostrando_feedback;
    double timer_feedback;

    int indices_usados[24];
    int n_usados;
    int nivel;   
} JogoPrecedencia;

JogoPrecedencia inicializar_jogo_precedencia(Dificuldade dif);
void gerar_proxima_questao_prec(JogoPrecedencia *jogo);
void responder_precedencia(JogoPrecedencia *jogo, int opcao);
void atualizar_timer_prec(JogoPrecedencia *jogo, double dt);
int calcular_pontos_prec(const JogoPrecedencia *jogo);

#endif
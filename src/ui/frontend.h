#ifndef FRONTEND_H
#define FRONTEND_H

#include "../include/tipos.h"
#include "../game/memorygame.h"

typedef enum 
{
    ESTADO_MENU_PRINCIPAL,
    ESTADO_MENU_JOGO,
    ESTADO_DIFICULDADE,
    ESTADO_JOGANDO_ADIVINHACAO,
    ESTADO_JOGANDO_MEMORIA,
    ESTADO_RESULTADO_ADIVINHACAO,
    ESTADO_RESULTADO_MEMORIA,
    ESTADO_SAIR
} EstadoAplicacao;


typedef struct 
{
    EstadoAplicacao estado_atual;
    Partida partida_atual;
    JogoMemoria jogo_memoria;
    Dificuldade dificuldade_selecionada;
    int entrada_numero;
    char entrada_texto[10];
    int indice_entrada;
    int clique_casa1;
    int clique_casa2;  
} EstadoUI;

#define LARGURA_JANELA   1200
#define ALTURA_JANELA    800

void executar_frontend(void);
void atualizar_ui(EstadoUI *ui);
void desenhar_ui(const EstadoUI *ui);

void desenhar_menu_principal(void);
void desenhar_menu_jogo(void);
void desenhar_menu_dificuldade(void);
void desenhar_jogo_adivinhacao(const EstadoUI *ui);
void desenhar_jogo_memoria(const EstadoUI *ui);
void desenhar_resultado_adivinhacao(const EstadoUI *ui);
void desenhar_resultado_memoria(const EstadoUI *ui);

void processar_entrada(EstadoUI *ui);
void processar_clique_mouse_memoria(EstadoUI *ui);

#endif
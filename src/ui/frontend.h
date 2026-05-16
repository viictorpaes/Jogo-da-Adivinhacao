#ifndef FRONTEND_H
#define FRONTEND_H

#include "../include/tipos.h"
#include "../game/memorygame.h"

typedef enum
{
    ESTADO_MENU_PRINCIPAL,
    ESTADO_MENU_JOGO,
    ESTADO_INSERIR_NOME,
    ESTADO_DIFICULDADE,
    ESTADO_JOGANDO_ADIVINHACAO,
    ESTADO_JOGANDO_MEMORIA,
    ESTADO_RESULTADO_ADIVINHACAO,
    ESTADO_RESULTADO_MEMORIA,
    ESTADO_ESTATISTICAS,
    ESTADO_SAIR
} EstadoAplicacao;


typedef struct
{
    EstadoAplicacao estado_atual;
    Partida         partida_atual;
    JogoMemoria     jogo_memoria;
    Dificuldade     dificuldade_selecionada;

    /* Entrada de palpite */
    int  entrada_numero;
    char entrada_texto[10];
    int  indice_entrada;

    /* Jogo da memória */
    int  clique_casa1;
    int  clique_casa2;
    bool aguardando_ocultar;
    int  timer_ocultar;

    /* Mensagem de erro */
    char mensagem_erro[128];

    /* Nome do jogador e controle de gravação */
    char nome_jogador[64];
    int  nome_indice;
    bool partida_salva;
    bool memoria_salva;

    /* Roteamento após inserção de nome */
    bool nome_para_memoria;   /* true → vai p/ memória; false → vai p/ dificuldade */

    /* Cache de estatísticas (carregado uma vez ao entrar na tela) */
    bool stats_carregadas;
    char stats_linhas[35][160];
    int  stats_n_linhas;
} EstadoUI;

#define LARGURA_JANELA   1200
#define ALTURA_JANELA    800

void executar_frontend(void);
void atualizar_ui(EstadoUI *ui);
void desenhar_ui(EstadoUI *ui);

void desenhar_menu_principal(void);
void desenhar_menu_jogo(void);
void desenhar_inserir_nome(const EstadoUI *ui);
void desenhar_menu_dificuldade(void);
void desenhar_jogo_adivinhacao(const EstadoUI *ui);
void desenhar_jogo_memoria(const EstadoUI *ui);
void desenhar_resultado_adivinhacao(const EstadoUI *ui);
void desenhar_resultado_memoria(const EstadoUI *ui);
void desenhar_estatisticas(EstadoUI *ui);

void processar_entrada(EstadoUI *ui);
void processar_clique_mouse_memoria(EstadoUI *ui);

#endif
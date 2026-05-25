#ifndef FRONTEND_H
#define FRONTEND_H

#include "../include/tipos.h"
#include "../game/memorygame.h"
#include "../game/logica.h"
#include "../game/precedencia.h"

typedef enum
{
    ESTADO_MENU_PRINCIPAL,
    ESTADO_MENU_JOGO,
    ESTADO_INSERIR_NOME,
    ESTADO_INSERIR_NOME_P2, 
    ESTADO_DIFICULDADE,

    ESTADO_JOGANDO_ADIVINHACAO,
    ESTADO_RESULTADO_ADIVINHACAO,

    ESTADO_JOGANDO_VS,
    ESTADO_RESULTADO_VS,

    ESTADO_JOGANDO_MEMORIA,
    ESTADO_RESULTADO_MEMORIA,

    ESTADO_JOGANDO_MEMORIA_VS,
    ESTADO_RESULTADO_MEMORIA_VS,

    ESTADO_JOGANDO_LOGICA,
    ESTADO_RESULTADO_LOGICA,

    ESTADO_JOGANDO_PRECEDENCIA,
    ESTADO_RESULTADO_PRECEDENCIA,

    ESTADO_ESTATISTICAS,
    ESTADO_HISTORICO,
    ESTADO_SAIR
} EstadoAplicacao;

typedef enum 
{
    MODO_SOLO_ADIV = 0,
    MODO_VS_ADIV = 1,
    MODO_SOLO_MEM = 2,
    MODO_VS_MEM = 3,
    MODO_LOGICA = 4,
    MODO_PRECEDENCIA = 5,
} ModoJogo;

typedef struct
{
    EstadoAplicacao estado_atual;
    ModoJogo modo_pendente;
    Partida partida_atual;
    Dificuldade dificuldade_selecionada;
    double timer_adiv;     
    bool timer_adiv_ativo;

    Partida vs_partida;
    int vs_jogador_atual;      
    int vs_rodada;               
    int vs_tentativas[2]; 
    int vs_pontos[2];
    int vs_rodadas_vencidas[2];
    int vs_vencedor_rodada;  
    bool vs_rodada_acabou;
    bool vs_jogo_acabou;
    bool vs_salvo;
    double vs_timer;            

    JogoMemoria jogo_memoria;
    double timer_memoria;    
    bool timer_memoria_ativo;
    bool memoria_salva;

    JogoMemoria mem_vs_jogo;
    int mem_vs_jogador;
    int mem_vs_pares[2];
    int mem_vs_pontos[2];
    double mem_vs_timer[2]; 
    int mem_vs_clique1;
    int mem_vs_clique2;
    bool mem_vs_aguardando;
    int mem_vs_timer_ocultar;
    bool mem_vs_salvo;

    JogoLogica logica;
    bool logica_salva;

    JogoPrecedencia precedencia;
    bool precedencia_salva;

    int  entrada_numero;
    char entrada_texto[10];
    int  indice_entrada;

    int  clique_casa1;
    int  clique_casa2;
    bool aguardando_ocultar;
    int  timer_ocultar;

    char mensagem_erro[128];

    char nome_jogador[64];
    int  nome_indice;
    char nome_jogador2[64];
    int  nome_indice2;

    bool partida_salva;

    bool pode_avancar_fase;
    double timer_carry;

    char hist_filtro_nome[64];
    bool hist_com_filtro;

    bool stats_carregadas;
    char stats_linhas[64][160];
    int  stats_n_linhas;
    bool hist_carregado;
    RegistroPartida  hist_adiv[10];
    int              hist_adiv_n;
    RegistroMemoria  hist_mem[10];
    int              hist_mem_n;
    RegistroVS       hist_vs[10];
    int              hist_vs_n;
    RegistroMemoriaVS hist_mem_vs[10];
    int              hist_mem_vs_n;
    RegistroPuzzle   hist_logica[10];
    int              hist_logica_n;
    RegistroPuzzle   hist_prec[10];
    int              hist_prec_n;
    char hist_resumo_adiv[200];
    char hist_resumo_mem[200];

    char nomes_hist[100][64];
    int  nomes_hist_n;
    bool nomes_hist_carregados;
} EstadoUI;

#define LARGURA_JANELA 1200
#define ALTURA_JANELA 800

void executar_frontend(void);
void atualizar_ui(EstadoUI *ui);
void desenhar_ui(EstadoUI *ui);
void desenhar_menu_principal(void);
void desenhar_menu_jogo(void);
void desenhar_inserir_nome(const EstadoUI *ui);
void desenhar_inserir_nome_p2(const EstadoUI *ui);
void desenhar_menu_dificuldade(EstadoUI *ui);
void desenhar_jogo_adivinhacao(const EstadoUI *ui);
void desenhar_jogo_vs(const EstadoUI *ui);
void desenhar_jogo_memoria(const EstadoUI *ui);
void desenhar_jogo_memoria_vs(const EstadoUI *ui);
void desenhar_jogo_logica(const EstadoUI *ui);
void desenhar_jogo_precedencia(const EstadoUI *ui);
void desenhar_resultado_adivinhacao(const EstadoUI *ui);
void desenhar_resultado_vs(const EstadoUI *ui);
void desenhar_resultado_memoria(const EstadoUI *ui);
void desenhar_resultado_memoria_vs(const EstadoUI *ui);
void desenhar_resultado_logica(const EstadoUI *ui);
void desenhar_resultado_precedencia(const EstadoUI *ui);
void desenhar_estatisticas(EstadoUI *ui);
void desenhar_historico(EstadoUI *ui);
void processar_entrada(EstadoUI *ui);
void processar_clique_mouse_memoria(EstadoUI *ui);
void processar_clique_mouse_memoria_vs(EstadoUI *ui);

#endif
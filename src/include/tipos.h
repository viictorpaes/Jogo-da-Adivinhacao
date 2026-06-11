#ifndef TIPOS_H
#define TIPOS_H
#include <stdbool.h>

#define FACIL_MIN            1
#define FACIL_MAX           10
#define FACIL_TENTATIVAS     5

#define MEDIO_MIN            1
#define MEDIO_MAX           50
#define MEDIO_TENTATIVAS     8

#define DIFICIL_MIN          1
#define DIFICIL_MAX        100
#define DIFICIL_TENTATIVAS  10

#define TIMER_ADIV_FACIL     60.0
#define TIMER_ADIV_MEDIO     40.0
#define TIMER_ADIV_DIFICIL   35.0
#define TIMER_MEM_BASE_SEG        60.0
#define TIMER_MEM_BONUS_SEG       15.0
#define TIMER_MEM_PENALIDADE_SEG   5.0

#define VS_MAX_RODADAS      3
#define VS_MAX_TENTATIVAS  12 

#define LOGICA_Q_FACIL      8
#define LOGICA_Q_MEDIO     10
#define LOGICA_Q_DIFICIL   12
#define LOGICA_T_FACIL     60.0
#define LOGICA_T_MEDIO     40.0
#define LOGICA_T_DIFICIL   35.0

#define PREC_Q_FACIL        8
#define PREC_Q_MEDIO       10
#define PREC_Q_DIFICIL     12
#define PREC_T_FACIL       60.0
#define PREC_T_MEDIO       40.0
#define PREC_T_DIFICIL     35.0

#define MAX_HISTORICO         500
#define HISTORICO_CSV         "data/historico.csv"
#define HISTORICO_TXT         "data/historico.txt"
#define HISTORICO_MEM_CSV     "data/historico_memoria.csv"
#define HISTORICO_MEM_TXT     "data/historico_memoria.txt"
#define HISTORICO_VS_CSV      "data/historico_vs.csv"
#define HISTORICO_VS_TXT      "data/historico_vs.txt"
#define HISTORICO_MEM_VS_CSV  "data/historico_memoria_vs.csv"
#define HISTORICO_MEM_VS_TXT  "data/historico_memoria_vs.txt"
#define HISTORICO_LOG_CSV     "data/historico_logica.csv"
#define HISTORICO_LOG_TXT     "data/historico_logica.txt"
#define HISTORICO_PRE_CSV     "data/historico_precedencia.csv"
#define HISTORICO_PRE_TXT     "data/historico_precedencia.txt"

#define LARGURA_TERMINAL   50

typedef enum 
{
    FACIL   = 0,
    MEDIO   = 1,
    DIFICIL = 2
} Dificuldade;

typedef enum 
{
    MAIOR   = 0,
    MENOR   = 1,
    ACERTOU = 2
} Resultado;

typedef enum
{
    MENU_JOGAR         = 1,
    MENU_VS_ADIV       = 2,
    MENU_MEMORIA       = 3,
    MENU_VS_MEM        = 4,
    MENU_LOGICA        = 5,
    MENU_PRECEDENCIA   = 6,
    MENU_HISTORICO     = 7,
    MENU_ESTATISTICAS  = 8,
    MENU_SAIR          = 9
} OpcaoMenu;

typedef struct 
{
    int numero_secreto;
    int tentativas_usadas;
    int max_tentativas;
    int min_range;
    int max_range;
    bool venceu;
} Partida;

typedef struct 
{
    char data[11];
    char nome[64];
    Dificuldade dificuldade;
    int tentativas_usadas;
    int max_tentativas;
    int numero_secreto;
    bool venceu;
    int pontos;
} RegistroPartida;

typedef struct 
{
    char data[11];
    char nome[64];
    int pontuacao;
    int tentativas;
    int pontos;
} RegistroMemoria;

typedef struct 
{
    char data[11];
    char nome1[64];
    char nome2[64];
    Dificuldade dificuldade;
    int vitorias1;
    int vitorias2;
    int pontos1;
    int pontos2;
    int vencedor;
} RegistroVS;

typedef struct
{
    char data[11];
    char nome1[64];
    int  pares1, pontos1;
    char nome2[64];
    int  pares2, pontos2;
} RegistroMemoriaVS;

typedef struct 
{
    char data[11];
    char nome[64];
    int  acertos;
    int  total;
    int  pontos;
    char modo[32];  
} RegistroPuzzle;

#endif
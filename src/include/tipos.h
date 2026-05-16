#ifndef TIPOS_H
#define TIPOS_H

#include <stdbool.h>

#define FACIL_MIN           1
#define FACIL_MAX          50
#define FACIL_TENTATIVAS   10

#define MEDIO_MIN           1
#define MEDIO_MAX         100
#define MEDIO_TENTATIVAS    7

#define DIFICIL_MIN         1
#define DIFICIL_MAX       200
#define DIFICIL_TENTATIVAS  5

#define MAX_HISTORICO        500
#define HISTORICO_CSV        "data/historico.csv"
#define HISTORICO_TXT        "data/historico.txt"
#define HISTORICO_MEM_CSV    "data/historico_memoria.csv"
#define HISTORICO_MEM_TXT    "data/historico_memoria.txt"

#define LARGURA_TERMINAL   50


typedef enum {
    FACIL   = 0,
    MEDIO   = 1,
    DIFICIL = 2
} Dificuldade;

typedef enum {
    MAIOR   = 0,
    MENOR   = 1,
    ACERTOU = 2
} Resultado;

typedef enum {
    MENU_JOGAR         = 1,
    MENU_MEMORIA       = 2,
    MENU_HISTORICO     = 3,
    MENU_ESTATISTICAS  = 4,
    MENU_SAIR          = 5
} OpcaoMenu;

typedef struct {
    int    numero_secreto;
    int    tentativas_usadas;
    int    max_tentativas;
    int    min_range;
    int    max_range;
    bool   venceu;
} Partida;

typedef struct {
    char        data[11];
    char        nome[64];
    Dificuldade dificuldade;
    int         tentativas_usadas;
    int         max_tentativas;
    int         numero_secreto;
    bool        venceu;
    int         pontos;
} RegistroPartida;

/* Registro de uma partida do Jogo da Memória */
typedef struct {
    char data[11];
    char nome[64];
    int  pontuacao;   /* 10 pts por par acertado (máx 80) */
    int  tentativas;  /* número de jogadas feitas         */
    int  pontos;      /* score por eficiência             */
} RegistroMemoria;

#endif
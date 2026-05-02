#ifndef TIPOS_H
#define TIPOS_H

#include <stdbool.h>

/* Intervalos e limites por dificuldade */
#define FACIL_MIN           1
#define FACIL_MAX          50
#define FACIL_TENTATIVAS   10

#define MEDIO_MIN           1
#define MEDIO_MAX         100
#define MEDIO_TENTATIVAS    7

#define DIFICIL_MIN         1
#define DIFICIL_MAX       200
#define DIFICIL_TENTATIVAS  5

/* Histórico e Persistência */
#define MAX_HISTORICO     500
#define HISTORICO_CSV     "data/historico.csv"
#define HISTORICO_TXT     "data/historico.txt"

/* Interface de Usuário (UI) */
#define LARGURA_TERMINAL   50


/* ==========================================================================
 * ENUMERAÇÕES
 * ========================================================================== */

typedef enum {
    FACIL   = 0,
    MEDIO   = 1,
    DIFICIL = 2
} Dificuldade;

typedef enum {
    MAIOR   = 0,   /* O palpite foi menor que o número secreto */
    MENOR   = 1,   /* O palpite foi maior que o número secreto */
    ACERTOU = 2
} Resultado;

typedef enum {
    MENU_JOGAR        = 1,
    MENU_HISTORICO    = 2,
    MENU_ESTATISTICAS = 3,
    MENU_SAIR         = 4
} OpcaoMenu;


/* ==========================================================================
 * ESTRUTURAS (STRUCTS)
 * ========================================================================== */

/* Representa o estado da partida atual */
typedef struct {
    int    numero_secreto;
    int    tentativas_usadas;
    int    max_tentativas;
    int    min_range;
    int    max_range;
    bool   venceu;
} Partida;

/* Representa uma partida finalizada para salvar no histórico */
typedef struct {
    char        data[11];
    Dificuldade dificuldade;
    int         tentativas_usadas;
    int         max_tentativas;
    int         numero_secreto;
    bool        venceu;
} RegistroPartida;

#endif /* TIPOS_H */
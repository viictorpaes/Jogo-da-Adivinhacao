#ifndef TIPOS_H

#define TIPOS_H

#define MAX_NOME 100

typedef enum 
{   JOGANDO,
    GANHOU,
    PERDEU,
    DESISTIU
} StatusPartida;

typedef struct 
{   char nomeJogador[MAX_NOME];
    StatusPartida statusAtual;
    int idJogador, numeroTentativas, acumuladorErros, numeroSecreto, pontuacaoFinal;
    float mediaTentativas;
} Partida;

#endif
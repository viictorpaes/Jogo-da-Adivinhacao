#include "jogo.h"
#include "../utils/utils.h"
#include "../ui/menu.h"
#include <stdio.h>
#include <stdlib.h>

Partida iniciar_partida(Dificuldade dif) {
    Partida nova_partida;
    
    nova_partida.tentativas_usadas = 0;
    nova_partida.venceu = false;

    if (dif == FACIL) {
        nova_partida.min_range = FACIL_MIN;
        nova_partida.max_range = FACIL_MAX;
        nova_partida.max_tentativas = FACIL_TENTATIVAS;
    } 
    else if (dif == MEDIO) {
        nova_partida.min_range = MEDIO_MIN;
        nova_partida.max_range = MEDIO_MAX;
        nova_partida.max_tentativas = MEDIO_TENTATIVAS;
    } 
    else {
        nova_partida.min_range = DIFICIL_MIN;
        nova_partida.max_range = DIFICIL_MAX;
        nova_partida.max_tentativas = DIFICIL_TENTATIVAS;
    }

    nova_partida.numero_secreto = (rand() % (nova_partida.max_range - nova_partida.min_range + 1)) + nova_partida.min_range;

    return nova_partida;
}

Resultado processar_palpite(Partida *p, int palpite) {
    p->tentativas_usadas++;

    if (palpite < p->numero_secreto) {
        return MAIOR;
    } 
    else if (palpite > p->numero_secreto) {
        return MENOR;
    } 
    else {
        p->venceu = true;
        return ACERTOU;
    }
}

bool partida_encerrada(const Partida *p) {
    if (p->venceu == true) {
        return true;
    }
    
    if (p->tentativas_usadas >= p->max_tentativas) {
        return true;
    }
    
    return false;
}

void exibir_resultado_final(const Partida *p) {
    printf("\n");
    for (int i = 0; i < LARGURA_TERMINAL; i++) printf("=");
    printf("\n");

    if (p->venceu) {
        printf("VITORIA!\n");
        printf("Voce acertou o numero secreto: %d\n", p->numero_secreto);
        printf("Tentativas utilizadas: %d de %d\n", p->tentativas_usadas, p->max_tentativas);
    } 
    else {
        printf("DERROTA!\n");
        printf("Voce esgotou todas as %d tentativas.\n", p->max_tentativas);
        printf("O numero secreto era: %d\n", p->numero_secreto);
    }

    for (int i = 0; i < LARGURA_TERMINAL; i++) printf("=");
    printf("\n\n");
}
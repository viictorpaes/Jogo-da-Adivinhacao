#include "jogo.h"
#include "../utils/utils.h" /* Para possíveis utilitários auxiliares futuramente */
#include "../ui/menu.h"     /* Para feedbacks visuais, se necessário */
#include <stdio.h>
#include <stdlib.h>

Partida iniciar_partida(Dificuldade dif) {
    Partida nova_partida;
    
    /* Inicializa o estado zerado */
    nova_partida.tentativas_usadas = 0;
    nova_partida.venceu = false;

    /* Configura os limites com base na dificuldade recebida usando as constantes de tipos.h */
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
    else { /* DIFICIL */
        nova_partida.min_range = DIFICIL_MIN;
        nova_partida.max_range = DIFICIL_MAX;
        nova_partida.max_tentativas = DIFICIL_TENTATIVAS;
    }

    /* 
     * Gera o número secreto.
     * A função rand() gera um número enorme, usamos o módulo (%) para mantê-lo 
     * dentro do nosso range de dificuldade.
     * Nota: A semente (srand) não deve ser chamada aqui, conforme especificado na issue.
     */
    nova_partida.numero_secreto = (rand() % (nova_partida.max_range - nova_partida.min_range + 1)) + nova_partida.min_range;

    return nova_partida;
}

Resultado processar_palpite(Partida *p, int palpite) {
    /* Toda vez que processamos um palpite, o jogador gasta uma tentativa */
    p->tentativas_usadas++;

    /* Lógica legível e direta para avaliar o número */
    if (palpite < p->numero_secreto) {
        return MAIOR; /* O palpite foi menor, então o número secreto é MAIOR */
    } 
    else if (palpite > p->numero_secreto) {
        return MENOR; /* O palpite foi maior, então o número secreto é MENOR */
    } 
    else {
        p->venceu = true;
        return ACERTOU;
    }
}

bool partida_encerrada(const Partida *p) {
    /* O jogo acaba imediatamente se o jogador vencer */
    if (p->venceu == true) {
        return true;
    }
    
    /* O jogo também acaba se as tentativas chegarem ao limite */
    if (p->tentativas_usadas >= p->max_tentativas) {
        return true;
    }
    
    /* Caso contrário, a partida continua */
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
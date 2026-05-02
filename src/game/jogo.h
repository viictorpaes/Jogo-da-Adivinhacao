#ifndef JOGO_H
#define JOGO_H

#include "../include/tipos.h"

/**
 * Inicializa uma nova partida com base na dificuldade escolhida.
 * Gera o número secreto aleatoriamente dentro do intervalo definido.
 */
Partida iniciar_partida(Dificuldade dif);

/**
 * Processa um palpite do jogador.
 * Retorna MAIOR, MENOR ou ACERTOU e atualiza o estado da partida.
 */
Resultado processar_palpite(Partida *p, int palpite);

/**
 * Retorna verdadeiro se a partida chegou ao fim
 * (vitória ou esgotamento de tentativas).
 */
bool partida_encerrada(const Partida *p);

/**
 * Exibe o resumo final da partida (resultado, número secreto, tentativas).
 */
void exibir_resultado_final(const Partida *p);

#endif /* JOGO_H */
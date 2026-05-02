#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "../include/tipos.h"

/**
 * Inicializa o sistema de histórico.
 * Cria os arquivos em data/ se não existirem (com cabeçalhos apropriados).
 * Retorna true em sucesso, false em erro de I/O.
 */
bool inicializar_historico(void);

/**
 * Salva o registro de uma partida finalizada.
 * Grava tanto no .csv (para leitura das estatísticas) quanto no .txt (para exibição na UI).
 */
bool salvar_partida(const RegistroPartida *r);

/**
 * Carrega todos os registros do CSV para um array fornecido.
 * Retorna o número de registros lidos, ou -1 em caso de erro na abertura.
 */
int carregar_historico(RegistroPartida *buf, int max);

/**
 * Exibe o histórico formatado no terminal, lendo diretamente do .txt.
 * Aplica paginação se houver muitos registros.
 */
void exibir_historico(void);

/**
 * Libera recursos internos do módulo.
 * (Nesta implementação em lote, arquivos não ficam abertos, mas a função 
 * é mantida para cumprir o contrato da API caso a arquitetura mude).
 */
void liberar_historico(void);

#endif /* HISTORICO_H */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* ==========================================================================
 * ENTRADA DE DADOS
 * ========================================================================== */

/**
 * Lê um inteiro do stdin com validação robusta.
 * Rejeita entradas não-numéricas e fora do intervalo [min, max].
 * Mantém o usuário em loop até que um valor válido seja fornecedo.
 */
int ler_inteiro(int min, int max, const char *prompt);

/**
 * Lê uma linha de texto do stdin de forma segura, evitando buffer overflow.
 * Remove o caractere de nova linha ('\n') final automaticamente.
 */
void ler_string(char *buf, int n, const char *prompt);


/* ==========================================================================
 * TERMINAL E FLUXO VISUAL
 * ========================================================================== */

/**
 * Limpa a tela do terminal de forma independente de sistema operacional.
 */
void limpar_tela(void);

/**
 * Pausa a execução do programa até o usuário pressionar a tecla Enter.
 */
void pausar(void);


/* ==========================================================================
 * ALEATORIEDADE
 * ========================================================================== */

/**
 * Inicializa a semente do gerador de números aleatórios.
 * Deve ser chamada EXATAMENTE UMA VEZ no início da execução do programa.
 */
void inicializar_rand(void);

/**
 * Gera e retorna um número inteiro aleatório dentro de um intervalo específico.
 */
int rand_intervalo(int min, int max);


/* ==========================================================================
 * DATA E TEMPO
 * ========================================================================== */

/**
 * Preenche o buffer fornecido com a data atual no formato "AAAA-MM-DD".
 * O buffer deve ter capacidade mínima de 11 caracteres.
 */
void formatar_data_atual(char *buf);


/* ==========================================================================
 * TRATAMENTO DE ERROS E AVISOS
 * ========================================================================== */

/**
 * Imprime uma mensagem de erro fatal no fluxo padrão de erro (stderr)
 * e encerra a execução do programa imediatamente.
 */
void erro_fatal(const char *msg);

/**
 * Imprime uma mensagem de aviso no fluxo padrão de erro (stderr),
 * mas permite que a execução do programa continue.
 */
void aviso(const char *msg);

#endif /* UTILS_H */
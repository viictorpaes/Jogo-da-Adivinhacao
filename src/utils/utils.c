#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int ler_inteiro(int min, int max, const char *prompt) {
    int valor;
    int quantidade_lida;
    int caractere_temp;

    while (true) {
        if (prompt != NULL) {
            printf("%s", prompt);
        }

        quantidade_lida = scanf("%d", &valor);

        /* 
         * Limpeza do buffer de entrada (stdin).
         * Lê e descarta todos os caracteres residuais até encontrar uma quebra 
         * de linha ou o fim do arquivo. Isso previne leituras fantasmas.
         */
        while ((caractere_temp = getchar()) != '\n' && caractere_temp != EOF) {
            /* Apenas consumindo os caracteres */
        }

        /* Verifica se scanf conseguiu ler um número e se ele está no limite */
        if (quantidade_lida == 1 && valor >= min && valor <= max) {
            return valor;
        }

        printf("Entrada invalida. Por favor, digite um numero entre %d e %d.\n", min, max);
    }
}

void ler_string(char *buf, int n, const char *prompt) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buf, n, stdin) != NULL) {
        /* Localiza a posição da quebra de linha (\n) e a substitui por um terminador nulo (\0) */
        size_t posicao_nova_linha = strcspn(buf, "\n");
        buf[posicao_nova_linha] = '\0';
    }
}

void limpar_tela(void) {
    /* Diretivas de pré-processamento para compatibilidade entre sistemas operacionais */
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    /* Consome o caractere gerado ao pressionar Enter */
    getchar(); 
}

void inicializar_rand(void) {
    /* Utiliza o tempo atual do sistema como semente para garantir resultados diferentes a cada execução */
    srand((unsigned int)time(NULL));
}

int rand_intervalo(int min, int max) {
    if (min > max) {
        /* Proteção básica caso os parâmetros sejam passados invertidos */
        int temp = min;
        min = max;
        max = temp;
    }
    return (rand() % (max - min + 1)) + min;
}

void formatar_data_atual(char *buf) {
    time_t tempo_atual = time(NULL);
    struct tm *tempo_local = localtime(&tempo_atual);

    if (tempo_local != NULL) {
        /* Formata a estrutura de tempo para a string no formato AAAA-MM-DD */
        strftime(buf, 11, "%Y-%m-%d", tempo_local);
    } else {
        /* Fallback seguro caso localtime falhe */
        strcpy(buf, "0000-00-00");
    }
}

void erro_fatal(const char *msg) {
    fprintf(stderr, "\n[ERRO FATAL] %s\n", msg);
    fprintf(stderr, "O programa sera encerrado.\n");
    exit(EXIT_FAILURE);
}

void aviso(const char *msg) {
    fprintf(stderr, "\n[AVISO] %s\n", msg);
}
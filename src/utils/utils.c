#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int ler_inteiro(int min, int max, const char *prompt) 
{
    int valor;
    int quantidade_lida;
    int caractere_temp;

    while (true) 
    {
        if (prompt != NULL) 
        {
            printf("%s", prompt);
        }

        quantidade_lida = scanf("%d", &valor);

        while ((caractere_temp = getchar()) != '\n' && caractere_temp != EOF)
        {
           NULL;
        }

        if (quantidade_lida == 1 && valor >= min && valor <= max) 
        {
            return valor;
        }

        printf("Entrada inválida. ❌ Por favor, digite um número entre %d e %d.\n", min, max);
    }
}

void ler_string(char *buf, int n, const char *prompt) 
{
    if (prompt != NULL) 
    {
        printf("%s", prompt);
    }

    if (fgets(buf, n, stdin) != NULL) 
    {
        size_t posicao_nova_linha = strcspn(buf, "\n");
        buf[posicao_nova_linha] = '\0';
    }
}

void limpar_tela(void) 
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar(void) 
{
    printf("\n Pressione ENTER para continuar... ");
    getchar(); 
}

void inicializar_rand(void) 
{
    srand((unsigned int)time(NULL));
}

void formatar_data_atual(char *buf) 
{
    time_t tempo_atual = time(NULL);
    struct tm *tempo_local = localtime(&tempo_atual);

    if (tempo_local != NULL) 
    {
        strftime(buf, 11, "%Y-%m-%d", tempo_local);
    }
    
    else 
    {
        strcpy(buf, "0000-00-00");
    }
}

void erro_fatal(const char *msg) 
{
    fprintf(stderr, "\n[ERRO FATAL] %s\n", msg);
    fprintf(stderr, "O programa será encerrado. 🚨\n");
    exit(EXIT_FAILURE);
}

void aviso(const char *msg) 
{
    fprintf(stderr, "\n[AVISO] %s\n", msg);
}
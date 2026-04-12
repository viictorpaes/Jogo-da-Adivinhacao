#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

void utils_inicializar_semente(void) 
{
    srand((unsigned)time(NULL));
}

int utils_aleatorio_intervalo(int min, int max) 
{
    if (min > max) 
    {
        int temporario = min; min = max; max = temporario;
    }
    if (min == max)
    { 
        return min;
    }
    int intervalo = max - min + 1;
    return min + (rand() % intervalo);
}

char *utils_ler_linha(char *buffer, size_t tamanho) 
{
    if (!buffer || tamanho == 0)
    {
        return NULL;
    }
    if (fgets(buffer, (int)tamanho, stdin) == NULL)
    { 
        return NULL;
    }
    
    size_t comprimento = strlen(buffer);

    if (comprimento > 0 && buffer[comprimento - 1] == '\n') 
    {
        buffer[comprimento - 1] = '\0';
    }

    return buffer;

}

int utils_converter_int_seguro(const char *string, int *resultado) 
{
    if (!string || !resultado)
    { 
        return 0;
    }

    char *ponteiro_final = NULL;
    errno = 0;
    long valor = strtol(string, &ponteiro_final, 10);

    if (ponteiro_final == string)
    { 
        return 0;
    }    
    if (errno != 0)
    { 
        return 0;
    }    
    while (*ponteiro_final != '\0') 
    {
        if (*ponteiro_final != ' ' && *ponteiro_final != '\t' && *ponteiro_final != '\r')
        {
            return 0;
        }
        
        ponteiro_final++;
    }

    if (valor < INT_MIN || valor > INT_MAX)
    { 
        return 0;
    }

    *resultado = (int)valor;
    return 1;
}


int utils_ler_int_prompt(const char *mensagem, int min, int max) 
{
    char buffer[128];
    int valor;
    while (1) 
    {
        if (mensagem) 
        {
            printf("%s", mensagem);
            fflush(stdout);
        }

        if (utils_ler_linha(buffer, sizeof(buffer)) == NULL) 
        {
            clearerr(stdin);
            continue;
        }

        if (!utils_converter_int_seguro(buffer, &valor)) 
        {
            printf("\nEntrada inválida. Digite um número inteiro.\n");
            continue;
        }

        if (valor < min || valor > max) 
        {
            printf("\nValor fora do intervalo [%d - %d]. Tente novamente.\n", min, max);
            continue;
        }

        return valor;
    }
}

void utils_limpar_stdin(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    { 

    }
}

void utils_pausar(const char *mensagem) {
    if (mensagem && mensagem[0] != '\0')
    {
        printf("%s", mensagem);
    }
    else
    { 
        printf("\nPressione ENTER para continuar...");
    }

    fflush(stdout);
    char temporario[4];
    utils_ler_linha(temporario, sizeof(temporario));
}


void partida_inicializar(Partida *p, const char *nome) 
{
    if (!p)
    {
        return;
    }

    if (nome) 
    {
        strncpy(p->nomeJogador, nome, MAX_NOME - 1);
        p->nomeJogador[MAX_NOME - 1] = '\0';
    } 
    else 
    {
        p->nomeJogador[0] = '\0';
    }

    p->statusAtual = JOGANDO;
    p->idJogador = 0;
    p->numeroTentativas = 0;
    p->acumuladorErros = 0;
    p->numeroSecreto = 0;
    p->pontuacaoFinal = 0;
    p->mediaTentativas = 0.0f;
}

void partida_imprimir(const Partida *p) 
{
    if (!p)
    { 
        return;
    }
    printf("--- Partida ---\n");
    printf("Jogador: %s\n", p->nomeJogador);
    printf("Status: %d\n", (int)p->statusAtual);
    printf("Tentativas: %d\n", p->numeroTentativas);
    printf("Erros acumulados: %d\n", p->acumuladorErros);
    printf("Numero secreto: %d\n", p->numeroSecreto);
    printf("Pontuação final: %d\n", p->pontuacaoFinal);
    printf("Media tentativas: %.2f\n", p->mediaTentativas);
}
#include "historico.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 15

bool inicializar_historico(void) 
{
    FILE *f_csv = fopen(HISTORICO_CSV, "r");
    if (f_csv == NULL) 
    {
        f_csv = fopen(HISTORICO_CSV, "w");
        if (f_csv != NULL) 
        {
            fprintf(f_csv, "data,nome,dificuldade,tentativas_usadas,max_tentativas,numero_secreto,resultado,pontos\n");
            fclose(f_csv);
        }
         else 
         {
            aviso("​⚠️​​​Falha ao criar o arquivo CSV do histórico.​⚠️​");
            return false;
        }

    }

    else 
    {
        fclose(f_csv);
    }

    FILE *f_txt = fopen(HISTORICO_TXT, "r");
    if (f_txt == NULL) 
    {
        f_txt = fopen(HISTORICO_TXT, "w");
        if (f_txt != NULL) 
        {
            fprintf(f_txt, "​➖​➖​➖​➖​➖​​➖​➖​ HISTÓRICO DE PARTIDAS ​➖​➖​➖​➖​➖​​➖​➖​\n\n");
            fclose(f_txt);
        } 
        else 
        {
            aviso("​⚠️​Falha ao criar o arquivo TXT do histórico.​⚠️​");
            return false;
        }
    }

    else 
    {
        fclose(f_txt);
    }

    return true;
}

bool salvar_partida(const RegistroPartida *r) 
{
    FILE *f_csv = fopen(HISTORICO_CSV, "a");
    FILE *f_txt = fopen(HISTORICO_TXT, "a");

    if (f_csv == NULL || f_txt == NULL) 
    {
        aviso("​⚠️​Erro ao abrir os arquivos de histórico para gravação.​⚠️​");
        if (f_csv != NULL) fclose(f_csv);
        if (f_txt != NULL) fclose(f_txt);
        return false;
    }

    const char *str_dif = "DIFÍCIL";
    if (r->dificuldade == FACIL) str_dif = "FÁCIL";
    else if (r->dificuldade == MEDIO) str_dif = "MÉDIO";

    const char *str_res = r->venceu ? "VITÓRIA" : "DERROTA";

    fprintf(f_csv, "%s,%s,%s,%d,%d,%d,%s,%d\n",
            r->data, r->nome, str_dif, r->tentativas_usadas,
            r->max_tentativas, r->numero_secreto, str_res, r->pontos);

    fprintf(f_txt, "  [%s] %-15s | %-7s | %02d/%02d | Secreto: %03d | %-7s | %d pts\n",
            r->data, r->nome, str_dif, r->tentativas_usadas,
            r->max_tentativas, r->numero_secreto, str_res, r->pontos);

    fclose(f_csv);
    fclose(f_txt);
    return true;
}

int carregar_historico(RegistroPartida *buf, int max) 
{
    FILE *f_csv = fopen(HISTORICO_CSV, "r");
    if (f_csv == NULL) 
    {
        return -1; 
    }

    char linha[256];
    int count = 0;

    fgets(linha, sizeof(linha), f_csv);

    while (count < max && fgets(linha, sizeof(linha), f_csv) != NULL) 
    {
        char str_dif[20];
        char str_res[20];

        int n_virgulas = 0;
        for (int k = 0; linha[k]; k++) 
        {
            if (linha[k] == ',') n_virgulas++;
        }

        int extraidos;
        if (n_virgulas >= 7) 
        {
            extraidos = sscanf(linha, "%10[^,],%63[^,],%19[^,],%d,%d,%d,%19[^,],%d",
                               buf[count].data, buf[count].nome, str_dif,
                               &buf[count].tentativas_usadas, &buf[count].max_tentativas,
                               &buf[count].numero_secreto, str_res, &buf[count].pontos);
            extraidos = (extraidos == 8) ? 6 : 0;
        } 
        else 
        {
            extraidos = sscanf(linha, "%10[^,],%19[^,],%d,%d,%d,%19[^\n]",
                               buf[count].data, str_dif, &buf[count].tentativas_usadas,
                               &buf[count].max_tentativas, &buf[count].numero_secreto, str_res);
            if (extraidos == 6) 
            {
                buf[count].nome[0] = '\0';
                buf[count].pontos = 0;
            }
        }

        if (extraidos == 6) 
        {
            if (strcmp(str_dif, "FÁCIL") == 0) 
            {
                buf[count].dificuldade = FACIL;
            } 

            else if (strcmp(str_dif, "MÉDIO") == 0) 
            {
                buf[count].dificuldade = MEDIO;
            } 

            else 
            {
                buf[count].dificuldade = DIFICIL;
            }

            buf[count].venceu = (strcmp(str_res, "VITÓRIA") == 0);

            count++;
        }
    }

    fclose(f_csv);
    return count;
}

void exibir_historico(void) 
{
    FILE *f_txt = fopen(HISTORICO_TXT, "r");
    if (f_txt == NULL) 
    {
        printf("\n Nenhum histórico de partidas encontrado.​🤔​\n");
        pausar();
        return;
    }

    char linha[256];
    int linhas_impressas = 0;

    limpar_tela();
    
    while (fgets(linha, sizeof(linha), f_txt) != NULL) {
        printf("%s", linha);
        linhas_impressas++;

        if (linhas_impressas % PAGE_SIZE == 0) {
            pausar();
            limpar_tela();
        }
    }

    fclose(f_txt);
    pausar();
}

void liberar_historico(void) 
{}


bool inicializar_historico_memoria(void) 
{
    FILE *f_csv = fopen(HISTORICO_MEM_CSV, "r");
    if (f_csv == NULL) 
    {
        f_csv = fopen(HISTORICO_MEM_CSV, "w");
        if (f_csv != NULL) 
        {
            fprintf(f_csv, "data,nome,pontuacao,tentativas,pontos\n");
            fclose(f_csv);
        } 
        
        else 
        {
            aviso("⚠️ Falha ao criar o arquivo CSV do histórico de memória.⚠️");
            return false;
        }
    } 
    
    else 
    {
        fclose(f_csv);
    }

    FILE *f_txt = fopen(HISTORICO_MEM_TXT, "r");
    if (f_txt == NULL) {
        f_txt = fopen(HISTORICO_MEM_TXT, "w");
        if (f_txt != NULL) 
        {
            fprintf(f_txt, "➖➖➖➖➖➖➖ HISTÓRICO - JOGO DA MEMÓRIA ➖➖➖➖➖➖➖\n\n");
            fclose(f_txt);
        }

        else 
        {
            aviso("⚠️ Falha ao criar o arquivo TXT do histórico de memória.⚠️");
            return false;
        }
    }

    else 
    {
        fclose(f_txt);
    }

    return true;
}

bool salvar_partida_memoria(const RegistroMemoria *r) 
{
    FILE *f_csv = fopen(HISTORICO_MEM_CSV, "a");
    FILE *f_txt = fopen(HISTORICO_MEM_TXT, "a");

    if (f_csv == NULL || f_txt == NULL) 
    {
        aviso("⚠️ Erro ao abrir arquivos de memória para gravação.⚠️");
        if (f_csv != NULL) fclose(f_csv);
        if (f_txt != NULL) fclose(f_txt);
        return false;
    }

    fprintf(f_csv, "%s,%s,%d,%d,%d\n",
            r->data, r->nome, r->pontuacao, r->tentativas, r->pontos);

    fprintf(f_txt, "  [%s] %-15s | Pontuacao: %2d | Tentativas: %2d | Pontos: %d\n",
            r->data, r->nome, r->pontuacao, r->tentativas, r->pontos);

    fclose(f_csv);
    fclose(f_txt);
    return true;
}

int carregar_historico_memoria(RegistroMemoria *buf, int max) 
{
    FILE *f_csv = fopen(HISTORICO_MEM_CSV, "r");
    if (f_csv == NULL) return -1;

    char linha[256];
    int count = 0;

    fgets(linha, sizeof(linha), f_csv); /* pula cabeçalho */

    while (count < max && fgets(linha, sizeof(linha), f_csv) != NULL) 
    {
        int n = sscanf(linha, "%10[^,],%63[^,],%d,%d,%d",
                       buf[count].data, buf[count].nome,
                       &buf[count].pontuacao, &buf[count].tentativas,
                       &buf[count].pontos);
        if (n == 5) count++;
    }

    fclose(f_csv);
    return count;
}

void exibir_historico_memoria(void) 
{
    FILE *f_txt = fopen(HISTORICO_MEM_TXT, "r");
    if (f_txt == NULL) 
    {
        printf("\n  Nenhum histórico de memória encontrado.🤔\n");
        pausar();
        return;
    }

    char linha[256];
    int linhas_impressas = 0;

    limpar_tela();

    while (fgets(linha, sizeof(linha), f_txt) != NULL) 
    {
        printf("%s", linha);
        linhas_impressas++;
        if (linhas_impressas % PAGE_SIZE == 0) 
        {
            pausar();
            limpar_tela();
        }
    }

    fclose(f_txt);
    pausar();
}
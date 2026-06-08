#include "historico.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 15

bool inicializar_historico(void) 
{
    FILE *file_csv = fopen(HISTORICO_CSV, "r");
    if (file_csv == NULL)
    {
        file_csv = fopen(HISTORICO_CSV, "w");
        if (file_csv != NULL)
        {
            fprintf(file_csv, "data,nome,dificuldade,tentativas_usadas,max_tentativas,numero_secreto,resultado,pontos\n");
            fclose(file_csv);
        }
        else
        {
            aviso("⚠️ Falha ao criar o arquivo CSV do histórico. ⚠️");
            return false;
        }
    }
    else
    {
        fclose(file_csv);
    }

    FILE *file_txt = fopen(HISTORICO_TXT, "r");
    if (file_txt == NULL)
    {
        file_txt = fopen(HISTORICO_TXT, "w");
        if (file_txt != NULL)
        {
            fprintf(file_txt, "------- HISTÓRICO DE PARTIDAS -------\n\n");
            fclose(file_txt);
        }
        else
        {
            aviso("⚠️ Falha ao criar o arquivo TXT do histórico. ⚠️");
            return false;
        }
    }
    else
    {
        fclose(file_txt);
    }

    return true;
}

bool salvar_partida(const RegistroPartida *r) 
{
    FILE *file_csv = fopen(HISTORICO_CSV, "a");
    FILE *file_txt = fopen(HISTORICO_TXT, "a");

    if (file_csv == NULL || file_txt == NULL) 
    {
        aviso("⚠️ Erro ao abrir os arquivos de histórico para gravação. ⚠️");
        if (file_csv != NULL) fclose(file_csv);
        if (file_txt != NULL) fclose(file_txt);
        return false;
    }

    const char *str_dif = "DIFÍCIL";
    if (r->dificuldade == FACIL) str_dif = "FÁCIL";
    else if (r->dificuldade == MEDIO) str_dif = "MÉDIO";

    const char *str_res = r->venceu ? "VITÓRIA" : "DERROTA";

    fprintf(file_csv, "%s,%s,%s,%d,%d,%d,%s,%d\n",
            r->data, r->nome, str_dif, r->tentativas_usadas,
            r->max_tentativas, r->numero_secreto, str_res, r->pontos);

    fprintf(file_txt, "  [%s] %-15s | %-7s | %02d/%02d | Secreto: %03d | %-7s | %d pts\n",
            r->data, r->nome, str_dif, r->tentativas_usadas,
            r->max_tentativas, r->numero_secreto, str_res, r->pontos);

    fclose(file_csv);
    fclose(file_txt);
    return true;
}

int carregar_historico(RegistroPartida *buf, int max) 
{
    FILE *file_csv = fopen(HISTORICO_CSV, "r");
    if (file_csv == NULL) 
    {
        return -1; 
    }

    char linha[256];
    int count = 0;

    fgets(linha, sizeof(linha), file_csv);

    while (count < max && fgets(linha, sizeof(linha), file_csv) != NULL) 
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

    fclose(file_csv);
    return count;
}

void exibir_historico(void) 
{
    FILE *file_txt = fopen(HISTORICO_TXT, "r");
    if (file_txt == NULL) 
    {
        printf("\n Nenhum histórico de partidas encontrado. 🤔\n");
        pausar();
        return;
    }

    char linha[256];
    int linhas_impressas = 0;

    limpar_tela();
    
    while (fgets(linha, sizeof(linha), file_txt) != NULL) 
    {
        printf("%s", linha);
        linhas_impressas++;

        if (linhas_impressas % PAGE_SIZE == 0) 
        {
            pausar();
            limpar_tela();
        }
    }

    fclose(file_txt);
    pausar();
}

bool inicializar_historico_memoria(void) 
{
    FILE *file_csv = fopen(HISTORICO_MEM_CSV, "r");
    if (file_csv == NULL)
    {
        file_csv = fopen(HISTORICO_MEM_CSV, "w");
        if (file_csv != NULL)
        {
            fprintf(file_csv, "data,nome,pontuacao,tentativas,pontos\n");
            fclose(file_csv);
        }
        else
        {
            aviso("⚠️ Falha ao criar o arquivo CSV do histórico de memória.⚠️");
            return false;
        }
    }
    else
    {
        fclose(file_csv);
    }

    FILE *file_txt = fopen(HISTORICO_MEM_TXT, "r");
    if (file_txt == NULL)
    {
        file_txt = fopen(HISTORICO_MEM_TXT, "w");
        if (file_txt != NULL)
        {
            fprintf(file_txt, "------- HISTÓRICO - JOGO DA MEMÓRIA -------\n\n");
            fclose(file_txt);
        }
        else
        {
            aviso("⚠️ Falha ao criar o arquivo TXT do histórico de memória.⚠️");
            return false;
        }
    }
    else
    {
        fclose(file_txt);
    }

    return true;
}

bool salvar_partida_memoria(const RegistroMemoria *r) 
{
    FILE *file_csv = fopen(HISTORICO_MEM_CSV, "a");
    FILE *file_txt = fopen(HISTORICO_MEM_TXT, "a");

    if (file_csv == NULL || file_txt == NULL) 
    {
        aviso("⚠️ Erro ao abrir arquivos de memória para gravação.⚠️");
        if (file_csv != NULL) fclose(file_csv);
        if (file_txt != NULL) fclose(file_txt);
        return false;
    }

    fprintf(file_csv, "%s,%s,%d,%d,%d\n",
            r->data, r->nome, r->pontuacao, r->tentativas, r->pontos);

    fprintf(file_txt, " [%s] %-15s | Pontuacao: %2d | Tentativas: %2d | Pontos: %d\n",
            r->data, r->nome, r->pontuacao, r->tentativas, r->pontos);

    fclose(file_csv);
    fclose(file_txt);
    return true;
}

int carregar_historico_memoria(RegistroMemoria *buf, int max) 
{
    FILE *file_csv = fopen(HISTORICO_MEM_CSV, "r");
    if (file_csv == NULL) return -1;

    char linha[256];
    int count = 0;

    fgets(linha, sizeof(linha), file_csv);

    while (count < max && fgets(linha, sizeof(linha), file_csv) != NULL) 
    {
        int n = sscanf(linha, "%10[^,],%63[^,],%d,%d,%d",
                       buf[count].data, buf[count].nome,
                       &buf[count].pontuacao, &buf[count].tentativas,
                       &buf[count].pontos);
        if (n == 5) count++;
    }

    fclose(file_csv);
    return count;
}

void exibir_historico_memoria(void)
{
    FILE *file_txt = fopen(HISTORICO_MEM_TXT, "r");
    if (file_txt == NULL)
    {
        printf("\n  Nenhum histórico de memória encontrado.🤔\n");
        pausar();
        return;
    }

    char linha[256];
    int linhas_impressas = 0;

    limpar_tela();

    while (fgets(linha, sizeof(linha), file_txt) != NULL)
    {
        printf("%s", linha);
        linhas_impressas++;
        if (linhas_impressas % PAGE_SIZE == 0)
        {
            pausar();
            limpar_tela();
        }
    }

    fclose(file_txt);
    pausar();
}

static bool inicializar_par_arquivos(const char *csv_path, const char *txt_path,
                                     const char *csv_header, const char *txt_header)
{
    FILE *file_csv = fopen(csv_path, "r");
    if (!file_csv)
    {
        file_csv = fopen(csv_path, "w");

        if (!file_csv) 
        {
            return false;
        }

        fprintf(file_csv, "%s\n", csv_header);
        fclose(file_csv);
    }
    else
    {
        fclose(file_csv);
    }

    FILE *file_txt = fopen(txt_path, "r");
    if (!file_txt)
    {
        file_txt = fopen(txt_path, "w");
        if (!file_txt)
        {
            return false;
        }
        fprintf(file_txt, "%s\n\n", txt_header);
        fclose(file_txt);
    }
    else
    {
        fclose(file_txt);
    }

    return true;
}


bool inicializar_historico_vs(void)
{
    return inicializar_par_arquivos
    (
        HISTORICO_VS_CSV, HISTORICO_VS_TXT,
        "data,nome1,nome2,dificuldade,vitorias1,vitorias2,pontos1,pontos2,vencedor",
        "------- HISTORICO - BATALHA DE SINAIS (VS) -------"
    );
}

bool salvar_partida_vs(const RegistroVS *r)
{
    FILE *file_csv = fopen(HISTORICO_VS_CSV, "a");
    FILE *file_txt = fopen(HISTORICO_VS_TXT, "a");
    if (!file_csv || !file_txt)
    {
        if (file_csv) 
        {
            fclose(file_csv);
        }

        if (file_txt) 
        { 
            fclose(file_txt); 
        }

        return false;
    }

    const char *difs[] = {"CADETE", "PILOTO", "COMANDANTE"};
    const char *dif = difs[(int)r->dificuldade];
    const char *venc = r->vencedor == 1 ? r->nome1
                     : r->vencedor == 2 ? r->nome2 : "EMPATE";

    fprintf(file_csv, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
            r->data, r->nome1, r->nome2, dif,
            r->vitorias1, r->vitorias2, r->pontos1, r->pontos2, r->vencedor);

    fprintf(file_txt, "  [%s] %-12s vs %-12s | %s | %d-%d | pts %d-%d | Vencedor: %s\n",
            r->data, r->nome1, r->nome2, dif,
            r->vitorias1, r->vitorias2, r->pontos1, r->pontos2, venc);

    fclose(file_csv); fclose(file_txt);
    return true;
}

int carregar_historico_vs(RegistroVS *buf, int max)
{
    FILE *file_csv = fopen(HISTORICO_VS_CSV, "r");
    if (!file_csv) return -1;

    char linha[256];
    int  count = 0;
    fgets(linha, sizeof(linha), file_csv);

    while (count < max && fgets(linha, sizeof(linha), file_csv)) 
    {
        char dif[20];
        int n = sscanf(linha, "%10[^,],%63[^,],%63[^,],%19[^,],%d,%d,%d,%d,%d",
                       buf[count].data, buf[count].nome1, buf[count].nome2, dif,
                       &buf[count].vitorias1, &buf[count].vitorias2,
                       &buf[count].pontos1, &buf[count].pontos2, &buf[count].vencedor);
        if (n == 9) 
        {
            buf[count].dificuldade = strcmp(dif, "CADETE") == 0    ? FACIL
                                   : strcmp(dif, "PILOTO") == 0    ? MEDIO : DIFICIL;
            count++;
        }
    }
    fclose(file_csv);
    return count;
}


bool inicializar_historico_memoria_vs(void)
{
    return inicializar_par_arquivos(
        HISTORICO_MEM_VS_CSV, HISTORICO_MEM_VS_TXT,
        "data,nome1,pares1,pontos1,nome2,pares2,pontos2",
        "------- HISTORICO - 1v1 MAPAS ESTELARES -------");
}

bool salvar_partida_memoria_vs(const RegistroMemoria *r1, const RegistroMemoria *r2)
{
    FILE *file_csv = fopen(HISTORICO_MEM_VS_CSV, "a");
    FILE *file_txt = fopen(HISTORICO_MEM_VS_TXT, "a");
    if (!file_csv || !file_txt)
    {
        if (file_csv) 
        { 
            fclose(file_csv); 
        }

        if (file_txt) 
        { 
            fclose(file_txt); 
        }

        return false;
    }

    fprintf(file_csv, "%s,%s,%d,%d,%s,%d,%d\n",
            r1->data, r1->nome, r1->pontuacao, r1->pontos,
            r2->nome, r2->pontuacao, r2->pontos);

    const char *venc = r1->pontos > r2->pontos ? r1->nome
                     : r2->pontos > r1->pontos ? r2->nome : "EMPATE";

    fprintf(file_txt, "  [%s] %-12s %2d pares (%dpts) vs %-12s %2d pares (%dpts) | %s\n",
            r1->data, r1->nome, r1->pontuacao, r1->pontos,
            r2->nome, r2->pontuacao, r2->pontos, venc);

    fclose(file_csv); fclose(file_txt);
    return true;
}


int carregar_historico_memoria_vs(RegistroMemoriaVS *buf, int max)
{
    FILE *file_csv = fopen(HISTORICO_MEM_VS_CSV, "r");
    if (!file_csv) 
    { 
        return -1; 
    }

    char linha[256];
    int  count = 0;
    fgets(linha, sizeof(linha), file_csv);

    while (count < max && fgets(linha, sizeof(linha), file_csv))
    {
        int n = sscanf(linha, "%10[^,],%63[^,],%d,%d,%63[^,],%d,%d",
                       buf[count].data,
                       buf[count].nome1, &buf[count].pares1, &buf[count].pontos1,
                       buf[count].nome2, &buf[count].pares2, &buf[count].pontos2);
        if (n == 7) count++;
    }
    fclose(file_csv);
    return count;
}


bool inicializar_historico_logica(void)
{
    return inicializar_par_arquivos(
        HISTORICO_LOG_CSV, HISTORICO_LOG_TXT,
        "data,nome,acertos,total,pontos,modo",
        "------- HISTORICO - PROTOCOLO LOGICO -------");
}

bool salvar_puzzle(const RegistroPuzzle *r)
{
    const char *csv = strcmp(r->modo, "logica") == 0 ? HISTORICO_LOG_CSV : HISTORICO_PRE_CSV;
    const char *txt = strcmp(r->modo, "logica") == 0 ? HISTORICO_LOG_TXT : HISTORICO_PRE_TXT;

    FILE *file_csv = fopen(csv, "a");
    FILE *file_txt = fopen(txt, "a");
    
    if (!file_csv || !file_txt)
    {
        if (file_csv) 
        {
            fclose(file_csv);
        } 

        if (file_txt) 
        {
            fclose(file_txt);
        }

        return false;
    }

    fprintf(file_csv, "%s,%s,%d,%d,%d,%s\n",
            r->data, r->nome, r->acertos, r->total, r->pontos, r->modo);
    fprintf(file_txt, "  [%s] %-15s | %d/%d acertos | %d pts\n",
            r->data, r->nome, r->acertos, r->total, r->pontos);

    fclose(file_csv); fclose(file_txt);
    return true;
}

int carregar_historico_puzzle(RegistroPuzzle *buf, int max, const char *modo)
{
    const char *csv = strcmp(modo, "logica") == 0 ? HISTORICO_LOG_CSV : HISTORICO_PRE_CSV;
    FILE *file_csv = fopen(csv, "r");
    if (!file_csv)
    {
        return -1;
    }

    char linha[256];
    int  count = 0;
    fgets(linha, sizeof(linha), file_csv);

    while (count < max && fgets(linha, sizeof(linha), file_csv)) 
    {
        int n = sscanf(linha, "%10[^,],%63[^,],%d,%d,%d,%31[^\n]",
                       buf[count].data, buf[count].nome,
                       &buf[count].acertos, &buf[count].total,
                       &buf[count].pontos, buf[count].modo);
        if (n == 6) count++;
    }
    fclose(file_csv);
    return count;
}

bool inicializar_historico_precedencia(void)
{
    return inicializar_par_arquivos(
        HISTORICO_PRE_CSV, HISTORICO_PRE_TXT,
        "data,nome,acertos,total,pontos,modo",
        "------- HISTORICO - HIERARQUIA DE COMANDOS -------");
}
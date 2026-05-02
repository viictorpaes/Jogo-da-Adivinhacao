#include "historico.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constante para o controle de paginação na visualização do histórico */
#define PAGE_SIZE 15

bool inicializar_historico(void) {
    FILE *f_csv = fopen(HISTORICO_CSV, "r");
    if (f_csv == NULL) {
        /* Arquivo não existe, vamos criar e adicionar o cabeçalho CSV */
        f_csv = fopen(HISTORICO_CSV, "w");
        if (f_csv != NULL) {
            fprintf(f_csv, "data,dificuldade,tentativas_usadas,max_tentativas,numero_secreto,resultado\n");
            fclose(f_csv);
        } else {
            aviso("Falha ao criar o arquivo CSV do historico.");
            return false;
        }
    } else {
        fclose(f_csv);
    }

    FILE *f_txt = fopen(HISTORICO_TXT, "r");
    if (f_txt == NULL) {
        /* Cria o arquivo TXT com um título base */
        f_txt = fopen(HISTORICO_TXT, "w");
        if (f_txt != NULL) {
            fprintf(f_txt, "=================== HISTORICO DE PARTIDAS ===================\n\n");
            fclose(f_txt);
        } else {
            aviso("Falha ao criar o arquivo TXT do historico.");
            return false;
        }
    } else {
        fclose(f_txt);
    }

    return true;
}

bool salvar_partida(const RegistroPartida *r) {
    /* Modos de abertura 'a' (append) anexam conteúdo ao final do arquivo sem sobrescrever */
    FILE *f_csv = fopen(HISTORICO_CSV, "a");
    FILE *f_txt = fopen(HISTORICO_TXT, "a");

    if (f_csv == NULL || f_txt == NULL) {
        aviso("Erro ao abrir os arquivos de historico para gravacao.");
        if (f_csv != NULL) fclose(f_csv);
        if (f_txt != NULL) fclose(f_txt);
        return false;
    }

    /* Conversões auxiliares para string visando legibilidade no arquivo */
    const char *str_dif = "DIFICIL";
    if (r->dificuldade == FACIL) str_dif = "FACIL";
    else if (r->dificuldade == MEDIO) str_dif = "MEDIO";

    const char *str_res = r->venceu ? "VITORIA" : "DERROTA";

    /* Gravação no CSV (dados brutos estruturados) */
    fprintf(f_csv, "%s,%s,%d,%d,%d,%s\n", 
            r->data, str_dif, r->tentativas_usadas, 
            r->max_tentativas, r->numero_secreto, str_res);

    /* Gravação no TXT (dados formatados humanizados) */
    fprintf(f_txt, "  [%s] Dificuldade: %-7s | Tentativas: %02d/%02d | Secreto: %03d | Resultado: %s\n",
            r->data, str_dif, r->tentativas_usadas, 
            r->max_tentativas, r->numero_secreto, str_res);

    fclose(f_csv);
    fclose(f_txt);
    return true;
}

int carregar_historico(RegistroPartida *buf, int max) {
    FILE *f_csv = fopen(HISTORICO_CSV, "r");
    if (f_csv == NULL) {
        return -1; 
    }

    char linha[256];
    int count = 0;

    /* A primeira leitura descarta a linha de cabeçalho do CSV */
    fgets(linha, sizeof(linha), f_csv);

    /* O laço percorre o arquivo linha por linha até o final ou atingir o limite max */
    while (count < max && fgets(linha, sizeof(linha), f_csv) != NULL) {
        char str_dif[20];
        char str_res[20];

        /* sscanf mapeia a string lida nos tipos correspondentes através das vírgulas */
        int extraidos = sscanf(linha, "%10[^,],%19[^,],%d,%d,%d,%19[^\n]",
                               buf[count].data, str_dif, &buf[count].tentativas_usadas,
                               &buf[count].max_tentativas, &buf[count].numero_secreto, str_res);

        if (extraidos == 6) {
            /* Restaura o Enum Dificuldade */
            if (strcmp(str_dif, "FACIL") == 0) {
                buf[count].dificuldade = FACIL;
            } else if (strcmp(str_dif, "MEDIO") == 0) {
                buf[count].dificuldade = MEDIO;
            } else {
                buf[count].dificuldade = DIFICIL;
            }

            /* Restaura o Booleano de Vitória */
            buf[count].venceu = (strcmp(str_res, "VITORIA") == 0);

            count++;
        }
    }

    fclose(f_csv);
    return count;
}

void exibir_historico(void) {
    FILE *f_txt = fopen(HISTORICO_TXT, "r");
    if (f_txt == NULL) {
        printf("\n  [!] Nenhum historico de partidas encontrado.\n");
        pausar();
        return;
    }

    char linha[256];
    int linhas_impressas = 0;

    limpar_tela();
    
    /* Lê e exibe o arquivo texto diretamente no terminal */
    while (fgets(linha, sizeof(linha), f_txt) != NULL) {
        printf("%s", linha);
        linhas_impressas++;

        /* Paginação: interrompe e limpa a tela se exceder o PAGE_SIZE */
        if (linhas_impressas % PAGE_SIZE == 0) {
            pausar();
            limpar_tela();
        }
    }

    fclose(f_txt);
    pausar();
}

void liberar_historico(void) {
    /* 
     * Como não mantemos buffers alocados dinamicamente ou conexões de 
     * banco de dados persistentes neste módulo, a função pode permanecer vazia. 
     */
}
#include <raylib.h>
#include "frontend.h"
#include "../game/jogo.h"
#include "../game/memorygame.h"
#include "../history/historico.h"
#include "../static/estatisticas.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COR_FUNDO        (Color){10, 5, 25, 255}
#define COR_PRIMARIA     (Color){180, 100, 255, 255}
#define COR_SECUNDARIA   (Color){255, 200, 80, 255}
#define COR_SUCESSO      (Color){100, 255, 180, 255}
#define COR_ERRO         (Color){255, 80, 120, 255}
#define COR_TEXTO        (Color){230, 220, 255, 255}
#define COR_BOTAO        (Color){60, 30, 100, 255}
#define COR_BOTAO_HOVER  (Color){110, 60, 170, 255}


typedef struct 
{
    Rectangle rect;
    const char *texto;
    bool hover;
} Botao;


void inicializar_raylib(void) 
{
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "🚀 Missão Espacial: Adivinhação & Memória");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));
}


Botao desenhar_botao(float x, float y, float width, float height, const char *texto) 
{
    Botao botao;
    botao.rect = (Rectangle){x, y, width, height};
    botao.texto = texto;
    botao.hover = CheckCollisionPointRec(GetMousePosition(), botao.rect);
    
    Color cor = botao.hover ? COR_BOTAO_HOVER : COR_BOTAO;
    DrawRectangleRec(botao.rect, cor);
    DrawRectangleLines((int)botao.rect.x, (int)botao.rect.y,
                       (int)botao.rect.width, (int)botao.rect.height, COR_PRIMARIA);
    
    int text_width = MeasureText(texto, 20);
    DrawText(texto, (int)(x + width/2 - text_width/2),
             (int)(y + height/2 - 10), 20, COR_TEXTO);
    
    return botao;
}

void desenhar_menu_principal(void) 
{
    DrawText("* MISSAO ESPACIAL *", 270, 50, 30, COR_PRIMARIA);
    DrawText("ADIVINHACAO & MEMORIA", 220, 90, 40, COR_PRIMARIA);
    DrawText("Bem-vindo, Astronauta! Escolha sua missao:", 270, 220, 25, COR_TEXTO);

    desenhar_botao(400, 320, 400, 80, "1. Missao: Adivinhacao");
    desenhar_botao(400, 450, 400, 80, "2. Missao: Jogo da Memoria");
    desenhar_botao(400, 580, 400, 80, "3. Abortar Missao (Sair)");
}

void desenhar_menu_dificuldade(void)
{
    DrawText("SELECIONE NIVEL DO ASTRONAUTA", 200, 80, 38, COR_PRIMARIA);
    DrawText("Qual e a sua patente espacial?", 310, 145, 22, COR_TEXTO);

    desenhar_botao(250, 230, 700, 100, "[1] Cientista     (1-50,  10 tentativas)");
    desenhar_botao(250, 380, 700, 100, "[2] Piloto        (1-100,  7 tentativas)");
    desenhar_botao(250, 530, 700, 100, "[3] Buzz Lightyear (1-200,  5 tentativas)");
    DrawText("Clique ou pressione 1 / 2 / 3 para selecionar", 280, 670, 20, COR_TEXTO);
    DrawText("Pressione ESC para voltar ao menu", 310, 700, 20, COR_TEXTO);
}

void desenhar_inserir_nome(const EstadoUI *ui)
{
    DrawText("IDENTIFICACAO DO ASTRONAUTA", 240, 100, 40, COR_PRIMARIA);
    DrawText("Qual e o nome do seu astronauta?", 320, 220, 25, COR_TEXTO);

    Rectangle input_box = {250, 280, 700, 70};
    DrawRectangleRec(input_box, (Color){20, 10, 40, 255});
    DrawRectangleLines(250, 280, 700, 70, COR_PRIMARIA);

    DrawText(ui->nome_jogador,
             (int)(input_box.x + 20),
             (int)(input_box.y + 15),
             40, COR_PRIMARIA);

    /* cursor piscante */
    if ((GetTime() * 2) - (int)(GetTime() * 2) < 1.0)
    {
        int cursor_x = (int)(input_box.x + 20) + MeasureText(ui->nome_jogador, 40);
        DrawText("|", cursor_x, (int)(input_box.y + 15), 40, COR_PRIMARIA);
    }

    desenhar_botao(400, 420, 400, 70, "CONFIRMAR (Enter)");
    DrawText("Deixe em branco para usar 'Astronauta'", 305, 520, 20, COR_TEXTO);
    DrawText("Pressione ESC para voltar ao menu", 330, 550, 20, COR_TEXTO);
}

void desenhar_jogo_adivinhacao(const EstadoUI *ui)
{
    DrawText("MISSAO: ADIVINHACAO", 350, 30, 40, COR_PRIMARIA);
    
    const char *patente = "Cientista";
    if      (ui->dificuldade_selecionada == MEDIO)  patente = "Piloto";
    else if (ui->dificuldade_selecionada == DIFICIL) patente = "Buzz Lightyear";

    char info_buffer[256];
    snprintf(info_buffer, sizeof(info_buffer),
             "Patente: %s | Range: %d a %d | Tentativas: %d/%d",
             patente,
             ui->partida_atual.min_range,
             ui->partida_atual.max_range,
             ui->partida_atual.tentativas_usadas,
             ui->partida_atual.max_tentativas);
    DrawText(info_buffer, 150, 100, 20, COR_TEXTO);
    
    if (ui->partida_atual.tentativas_usadas > 0) 
    {
        DrawText("Seu ultimo palpite foi:", 200, 180, 25, COR_SECUNDARIA);
        
        if (ui->entrada_numero < ui->partida_atual.numero_secreto) 
        {
            DrawText("O numero secreto e MAIOR! Aponte para cima! ^", 200, 220, 25, COR_ERRO);
        } 
        else if (ui->entrada_numero > ui->partida_atual.numero_secreto) 
        {
            DrawText("O numero secreto e MENOR! Volte a orbita! v", 200, 220, 25, COR_ERRO);
        }
    }
    
    DrawText("Digite seu palpite:", 200, 320, 25, COR_TEXTO);
    
    Rectangle input_box = {200, 370, 400, 60};
    DrawRectangleRec(input_box, (Color){20, 10, 40, 255});
    DrawRectangleLines(200, 370, 400, 60, COR_PRIMARIA);
    
    DrawText(ui->entrada_texto,
             (int)(input_box.x + 20),
             (int)(input_box.y + 10),
             40, COR_PRIMARIA);
    
    desenhar_botao(200, 480, 400, 60, "CONFIRMAR PALPITE (Enter)");

    if (ui->mensagem_erro[0] != '\0')
    {
        DrawText(ui->mensagem_erro, 200, 560, 22, COR_ERRO);
    }

    DrawText("Pressione ESC para voltar a selecao de dificuldade", 200, 600, 20, COR_TEXTO);
}

void desenhar_jogo_memoria(const EstadoUI *ui) 
{
    DrawText("MISSAO: JOGO DA MEMORIA 4x4", 300, 30, 40, COR_PRIMARIA);
    
    char stats[256];
    snprintf(stats, sizeof(stats), "Pontuacao: %d | Pares: %d/8 | Tentativas: %d",
             ui->jogo_memoria.pontuacao,
             ui->jogo_memoria.pares_encontrados,
             ui->jogo_memoria.tentativas);
    DrawText(stats, 200, 100, 25, COR_TEXTO);
    
    int tamanho_casa = 80;
    int espaco = 10;
    int inicio_x = 200;
    int inicio_y = 200;
    
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            int posicao = i * 4 + j;
            int x = inicio_x + (tamanho_casa + espaco) * j;
            int y = inicio_y + (tamanho_casa + espaco) * i;
            
            Rectangle casa = {(float)x, (float)y, (float)tamanho_casa, (float)tamanho_casa};
            
            Color cor_casa;
            if (ui->jogo_memoria.acertadas[posicao]) 
            {
                cor_casa = COR_SUCESSO;
            } 
            else if (ui->aguardando_ocultar &&
                     (posicao + 1 == ui->clique_casa1 || posicao + 1 == ui->clique_casa2)) 
            {
                cor_casa = COR_ERRO;
            } 
            else if (ui->jogo_memoria.reveladas[posicao]) 
            {
                cor_casa = COR_PRIMARIA;
            }
            else 
            {
                cor_casa = COR_BOTAO;
            }
            
            DrawRectangleRec(casa, cor_casa);
            DrawRectangleLines(x, y, tamanho_casa, tamanho_casa, COR_TEXTO);
            
            if (ui->jogo_memoria.acertadas[posicao] || ui->jogo_memoria.reveladas[posicao])
            {
                char num_str[8];
                snprintf(num_str, sizeof(num_str), "%d", ui->jogo_memoria.numeros[posicao]);
                int text_width = MeasureText(num_str, 40);
                DrawText(num_str, x + tamanho_casa/2 - text_width/2, y + 20, 40, COR_TEXTO);
            }
            else
            {
                DrawText("?", x + 30, y + 20, 40, COR_TEXTO);
            }
        }
    }
    
    DrawText("Clique em duas casas para revelar os pares!", 200, 700, 20, COR_TEXTO);
    DrawText("Pressione ESC para voltar ao menu", 200, 740, 20, COR_TEXTO);
}

void desenhar_resultado_adivinhacao(const EstadoUI *ui)
{
    DrawText("FIM DA MISSAO", 380, 80, 50, COR_PRIMARIA);

    if (ui->partida_atual.venceu)
    {
        DrawText("MISSAO CUMPRIDA!", 380, 180, 40, COR_SUCESSO);
        DrawText("Voce acertou o numero secreto, astronauta!", 220, 260, 28, COR_TEXTO);
    }
    else
    {
        DrawText("MISSAO FRACASSADA!", 340, 180, 40, COR_ERRO);
        DrawText("Voce esgotou todas as tentativas. De volta a Terra!", 200, 260, 28, COR_TEXTO);
    }

    const char *patente = "Cientista";
    if      (ui->dificuldade_selecionada == MEDIO)   patente = "Piloto";
    else if (ui->dificuldade_selecionada == DIFICIL)  patente = "Buzz Lightyear";

    char linha1[128], linha2[128], linha3[128], linha4[128], linha5[128];
    snprintf(linha1, sizeof(linha1), "Astronauta : %s", ui->nome_jogador);
    snprintf(linha2, sizeof(linha2), "Patente    : %s", patente);
    snprintf(linha3, sizeof(linha3), "Numero Secreto: %d", ui->partida_atual.numero_secreto);
    snprintf(linha4, sizeof(linha4), "Tentativas : %d de %d",
             ui->partida_atual.tentativas_usadas, ui->partida_atual.max_tentativas);

    int pts = calcular_pontos(ui->dificuldade_selecionada,
                              ui->partida_atual.tentativas_usadas,
                              ui->partida_atual.venceu);
    snprintf(linha5, sizeof(linha5), "Pontos ganhos: %d", pts);

    DrawText(linha1, 300, 330, 25, COR_TEXTO);
    DrawText(linha2, 300, 362, 25, COR_TEXTO);
    DrawText(linha3, 300, 394, 25, COR_TEXTO);
    DrawText(linha4, 300, 426, 25, COR_TEXTO);
    DrawText(linha5, 300, 458, 25, pts > 0 ? COR_SUCESSO : COR_ERRO);

    desenhar_botao(400, 540, 400, 80, "Voltar ao Menu (ESC)");
}

void desenhar_resultado_memoria(const EstadoUI *ui) 
{
    DrawText("MISSAO CONCLUIDA! PARABENS!", 210, 80, 45, COR_SUCESSO);
    DrawText("Voce encontrou todos os pares, astronauta!", 220, 150, 26, COR_TEXTO);

    char linha1[128], linha2[64], linha3[64], linha4[64];
    snprintf(linha1, sizeof(linha1), "Pontuacao Total : %d", ui->jogo_memoria.pontuacao);
    snprintf(linha2, sizeof(linha2), "Pares Encontrados: %d/8", ui->jogo_memoria.pares_encontrados);
    snprintf(linha3, sizeof(linha3), "Tentativas       : %d", ui->jogo_memoria.tentativas);
    snprintf(linha4, sizeof(linha4), "Eficiencia       : %.1f%%",
             (ui->jogo_memoria.pares_encontrados * 2.0f / ui->jogo_memoria.tentativas) * 100.0f);

    DrawText(linha1, 300, 270, 30, COR_TEXTO);
    DrawText(linha2, 300, 310, 30, COR_TEXTO);
    DrawText(linha3, 300, 350, 30, COR_TEXTO);
    DrawText(linha4, 300, 390, 30, COR_TEXTO);

    desenhar_botao(400, 580, 400, 80, "Voltar ao Menu (ESC)");
}
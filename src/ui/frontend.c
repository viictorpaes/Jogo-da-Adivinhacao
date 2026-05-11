#include <raylib.h>
#include "frontend.h"
#include "../game/jogo.h"
#include "../game/memorygame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COR_FUNDO (Color){20, 20, 30, 255}
#define COR_PRIMARIA (Color){100, 200, 255, 255}
#define COR_SECUNDARIA (Color){255, 150, 50, 255}
#define COR_SUCESSO (Color){100, 255, 100, 255}
#define COR_ERRO (Color){255, 100, 100, 255}
#define COR_TEXTO (Color){255, 255, 255, 255}
#define COR_BOTAO (Color){70, 130, 180, 255}
#define COR_BOTAO_HOVER (Color){100, 150, 200, 255}


typedef struct 
{
    Rectangle rect;
    const char *texto;
    bool hover;
} Botao;


void inicializar_raylib(void) 
{
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Jogo da Adivinhação & Memória - RayLib");
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
    DrawRectangleLines ((int)botao.rect.x, (int)botao.rect.y, 
    (int)botao.rect.width, (int)botao.rect.height, COR_PRIMARIA);
    
    int text_width = MeasureText(texto, 20);
    DrawText (texto, (int)(x + width/2 - text_width/2), 
             (int)(y + height/2 - 10), 20, COR_TEXTO);
    
    return botao;
}

void desenhar_menu_principal(void) 
{
    DrawText("JOGO DA ADIVINHAÇÃO & MEMÓRIA", 200, 100, 40, COR_PRIMARIA);

    DrawText("\n Escolha uma opção: ", 400, 250, 30, COR_TEXTO);

    desenhar_botao(400, 350, 400, 80, "1. Jogo da Adivinhação");
    desenhar_botao(400, 480, 400, 80, "2. Jogo da Memória");
    desenhar_botao(400, 610, 400, 80, "3. Sair");
}

void desenhar_menu_dificuldade(void)
{
    DrawText("SELECIONE A DIFICULDADE", 250, 100, 40, COR_PRIMARIA);

    desenhar_botao(250, 250, 700, 100, "[1] FÁCIL  (1-50, 10 tentativas)");
    desenhar_botao(250, 400, 700, 100, "[2] MÉDIO  (1-100, 7 tentativas)");
    desenhar_botao(250, 550, 700, 100, "[3] DIFÍCIL (1-200, 5 tentativas)");
    DrawText("Clique ou pressione 1 / 2 / 3 para selecionar", 280, 690, 20, COR_TEXTO);
    DrawText("Pressione ESC para voltar ao menu", 310, 720, 20, COR_TEXTO);
}

void desenhar_jogo_adivinhacao(const EstadoUI *ui) 
{
    DrawText("JOGO DA ADIVINHAÇÃO", 400, 30, 40, COR_PRIMARIA);
    
    char info_buffer[256];
    snprintf(info_buffer, sizeof(info_buffer), 
             "Range: %d a %d | Tentativas: %d/%d",
             ui->partida_atual.min_range,
             ui->partida_atual.max_range,
             ui->partida_atual.tentativas_usadas,
             ui->partida_atual.max_tentativas);
    DrawText(info_buffer, 200, 100, 20, COR_TEXTO);
    
    if (ui->partida_atual.tentativas_usadas > 0) 
    {
        DrawText("Seu último palpite foi:", 200, 180, 25, COR_SECUNDARIA);
        
        if (ui->entrada_numero < ui->partida_atual.numero_secreto) 
        {
            DrawText("O número secreto é MAIOR! ↑", 200, 220, 25, COR_ERRO);
        } 
        else if (ui->entrada_numero > ui->partida_atual.numero_secreto) 
        {
            DrawText("O número secreto é MENOR! ↓", 200, 220, 25, COR_ERRO);
        }
    }
    
    DrawText("Digite seu palpite:", 200, 320, 25, COR_TEXTO);
    
    Rectangle input_box = {200, 370, 400, 60};
    DrawRectangleRec(input_box, (Color){40, 40, 50, 255});
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

    DrawText("Pressione: ESC para voltar a seleção de dificuldade", 200, 600, 20, COR_TEXTO);
}

void desenhar_jogo_memoria(const EstadoUI *ui) 
{
    DrawText("JOGO DA MEMÓRIA 4x4", 400, 30, 40, COR_PRIMARIA);
    
    char stats[256];
    snprintf(stats, sizeof(stats), "Pontuação: %d | Pares: %d/8 | Tentativas: %d",
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
                cor_casa = GREEN;
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
            
            if (ui->jogo_memoria.acertadas[posicao])
            {
                char num_str[8];
                snprintf(num_str, sizeof(num_str), "%d", ui->jogo_memoria.numeros[posicao]);
                int text_width = MeasureText(num_str, 40);
                DrawText(num_str, x + tamanho_casa/2 - text_width/2, y + 20, 40, COR_TEXTO);
            }
            else if (ui->jogo_memoria.reveladas[posicao])
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
    
    DrawText("Clique em duas casas diferentes para revelá-las", 200, 700, 20, COR_TEXTO);
    DrawText("Pressione ESC para voltar ao menu", 200, 740, 20, COR_TEXTO);
}

void desenhar_resultado_adivinhacao(const EstadoUI *ui) 
{
    DrawText("FIM DO JOGO", 400, 100, 50, COR_PRIMARIA);
    
    if (ui->partida_atual.venceu) 
    {
        DrawText("VITÓRIA!", 450, 200, 40, COR_SUCESSO);
        DrawText("Você acertou o número secreto!", 250, 280, 30, COR_TEXTO);
    }
    else 
    {
        DrawText("DERROTA!", 450, 200, 40, COR_ERRO);
        DrawText("Você esgotou todas as tentativas.", 250, 280, 30, COR_TEXTO);
    }
    
    char linha1[128], linha2[128];
    snprintf(linha1, sizeof(linha1), "Número Secreto: %d", ui->partida_atual.numero_secreto);
    snprintf(linha2, sizeof(linha2), "Tentativas Usadas: %d de %d",
             ui->partida_atual.tentativas_usadas, ui->partida_atual.max_tentativas);
    DrawText(linha1, 300, 380, 25, COR_TEXTO);
    DrawText(linha2, 300, 415, 25, COR_TEXTO);

    desenhar_botao(400, 550, 400, 80, "Voltar ao Menu (ESC)");
}

void desenhar_resultado_memoria(const EstadoUI *ui) 
{
    DrawText("PARABÉNS! VOCÊ VENCEU!", 250, 100, 50, COR_SUCESSO);

    char linha1[128], linha2[64], linha3[64], linha4[64];
    snprintf(linha1, sizeof(linha1), "Pontuação Total: %d", ui->jogo_memoria.pontuacao);
    snprintf(linha2, sizeof(linha2), "Pares Encontrados: %d/8", ui->jogo_memoria.pares_encontrados);
    snprintf(linha3, sizeof(linha3), "Tentativas: %d", ui->jogo_memoria.tentativas);
    snprintf(linha4, sizeof(linha4), "Eficiência: %.1f%%",
             (ui->jogo_memoria.pares_encontrados * 2.0f / ui->jogo_memoria.tentativas) * 100.0f);
    DrawText(linha1, 300, 280, 30, COR_TEXTO);
    DrawText(linha2, 300, 320, 30, COR_TEXTO);
    DrawText(linha3, 300, 360, 30, COR_TEXTO);
    DrawText(linha4, 300, 400, 30, COR_TEXTO);

    desenhar_botao(400, 600, 400, 80, "Voltar ao Menu (ESC)");
}

void processar_entrada(EstadoUI *ui)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (ui->estado_atual == ESTADO_JOGANDO_ADIVINHACAO)
            ui->estado_atual = ESTADO_DIFICULDADE;
        else
            ui->estado_atual = ESTADO_MENU_PRINCIPAL;

        memset(ui->entrada_texto, 0, sizeof(ui->entrada_texto));
        ui->indice_entrada = 0;
        ui->entrada_numero = 0;
        return;
    }

    if (ui->estado_atual == ESTADO_DIFICULDADE)
    {
        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
        {
            ui->partida_atual = iniciar_partida(FACIL);
            ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;
        }
        else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
        {
            ui->partida_atual = iniciar_partida(MEDIO);
            ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;
        }
        else if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3))
        {
            ui->partida_atual = iniciar_partida(DIFICIL);
            ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;
        }
        return;
    }

    if (ui->estado_atual == ESTADO_JOGANDO_ADIVINHACAO)
    {
        int key = GetCharPressed();
        
        while (key > 0) 
        {
            if ((key >= '0' && key <= '9') && ui->indice_entrada < 9) {
                ui->entrada_texto[ui->indice_entrada] = (char)key;
                ui->indice_entrada++;
                ui->entrada_texto[ui->indice_entrada] = '\0';
            }
            key = GetCharPressed();
        }
        
        if (IsKeyPressed(KEY_BACKSPACE) && ui->indice_entrada > 0) 
        {
            ui->indice_entrada--;
            ui->entrada_texto[ui->indice_entrada] = '\0';
        }
        
        if (IsKeyPressed(KEY_ENTER) && ui->indice_entrada > 0) 
        {
            ui->entrada_numero = atoi(ui->entrada_texto);
            
            if (ui->entrada_numero >= ui->partida_atual.min_range && 
                ui->entrada_numero <= ui->partida_atual.max_range) 
            {
                
                ui->mensagem_erro[0] = '\0';
                processar_palpite(&ui->partida_atual, ui->entrada_numero);

                if (partida_encerrada(&ui->partida_atual))
                {
                    ui->estado_atual = ESTADO_RESULTADO_ADIVINHACAO;
                }
            }
            else
            {
                snprintf(ui->mensagem_erro, sizeof(ui->mensagem_erro),
                         "O número %d está fora do escopo do jogo. Por favor, tente novamente!",
                         ui->entrada_numero);
            }
            
            memset(ui->entrada_texto, 0, sizeof(ui->entrada_texto));
            ui->indice_entrada = 0;
        }
    }
}

void processar_clique_mouse_memoria(EstadoUI *ui)
{
    if (ui->aguardando_ocultar)
    {
        ui->timer_ocultar--;
        if (ui->timer_ocultar <= 0)
        {
            ui->jogo_memoria.reveladas[ui->clique_casa1 - 1] = false;
            ui->jogo_memoria.reveladas[ui->clique_casa2 - 1] = false;
            ui->clique_casa1 = -1;
            ui->clique_casa2 = -1;
            ui->aguardando_ocultar = false;
        }
        return;
    }

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    Vector2 mouse_pos = GetMousePosition();

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

            if (CheckCollisionPointRec(mouse_pos, casa))
            {
                if (!ui->jogo_memoria.acertadas[posicao] && !ui->jogo_memoria.reveladas[posicao])
                {
                    if (ui->clique_casa1 == -1)
                    {
                        ui->clique_casa1 = posicao + 1;
                        ui->jogo_memoria.reveladas[posicao] = true;
                    }
                    else if (ui->clique_casa2 == -1 && posicao + 1 != ui->clique_casa1)
                    {
                        ui->clique_casa2 = posicao + 1;

                        bool acertou = fazer_jogada(&ui->jogo_memoria, ui->clique_casa1, ui->clique_casa2);

                        if (jogo_memoria_finalizado(&ui->jogo_memoria))
                        {
                            ui->estado_atual = ESTADO_RESULTADO_MEMORIA;
                        }
                        else if (acertou)
                        {
                            ui->clique_casa1 = -1;
                            ui->clique_casa2 = -1;
                        }
                        else
                        {
                            ui->aguardando_ocultar = true;
                            ui->timer_ocultar = 90;
                        }
                    }
                }
            }
        }
    }
}

void atualizar_ui(EstadoUI *ui) 
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        Vector2 mouse_pos = GetMousePosition();
        
        switch (ui->estado_atual) 
        {
        case (ESTADO_MENU_PRINCIPAL): 
        {
            Botao btn_adiv = (Botao){{400, 350, 400, 80}, "", 
                                      CheckCollisionPointRec(mouse_pos, (Rectangle){400, 350, 400, 80})};
            Botao btn_mem = (Botao){{400, 480, 400, 80}, "", 
                                     CheckCollisionPointRec(mouse_pos, (Rectangle){400, 480, 400, 80})};
            Botao btn_sair_menu = (Botao){{400, 610, 400, 80}, "", 
                                          CheckCollisionPointRec(mouse_pos, (Rectangle){400, 610, 400, 80})};
            
            if (btn_adiv.hover) 
            {
                ui->estado_atual = ESTADO_DIFICULDADE;
            } 
            else if (btn_mem.hover) 
            {
                ui->jogo_memoria = inicializar_jogo_memoria();
                ui->clique_casa1 = -1;
                ui->clique_casa2 = -1;
                ui->estado_atual = ESTADO_JOGANDO_MEMORIA;
            } 
            else if (btn_sair_menu.hover) 
            {
                ui->estado_atual = ESTADO_SAIR;
            }
            break;
        }
        case ESTADO_DIFICULDADE: 
        {
            Botao btn_facil = (Botao){{250, 250, 700, 100}, "", 
                                       CheckCollisionPointRec(mouse_pos, (Rectangle){250, 250, 700, 100})};
            Botao btn_medio = (Botao){{250, 400, 700, 100}, "", 
                                       CheckCollisionPointRec(mouse_pos, (Rectangle){250, 400, 700, 100})};
            Botao btn_dif = (Botao){{250, 550, 700, 100}, "", 
                                     CheckCollisionPointRec(mouse_pos, (Rectangle){250, 550, 700, 100})};
            
            if (btn_facil.hover) 
            {
                ui->partida_atual = iniciar_partida(FACIL);
                ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;

            } 
            else if (btn_medio.hover) 
            {
                ui->partida_atual = iniciar_partida(MEDIO);
                ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;

            } 
            else if (btn_dif.hover) 
            {
                ui->partida_atual = iniciar_partida(DIFICIL);
                ui->estado_atual = ESTADO_JOGANDO_ADIVINHACAO;
            }
            break;
        }
        case ESTADO_RESULTADO_ADIVINHACAO: 
        {
            Botao btn_voltar_adiv = (Botao){{400, 550, 400, 80}, "",
                CheckCollisionPointRec(mouse_pos, (Rectangle){400, 550, 400, 80})};
            if (btn_voltar_adiv.hover) {
                ui->estado_atual = ESTADO_MENU_PRINCIPAL;
            }
            break;
        }
        case ESTADO_RESULTADO_MEMORIA: 
        {
            Botao btn_voltar_mem = (Botao){{400, 600, 400, 80}, "",
                CheckCollisionPointRec(mouse_pos, (Rectangle){400, 600, 400, 80})};
            if (btn_voltar_mem.hover) {
                ui->estado_atual = ESTADO_MENU_PRINCIPAL;
            }
            break;
        }
        default:
            break;
        }
    }

    if (ui->estado_atual == ESTADO_JOGANDO_MEMORIA) 
    {
        processar_clique_mouse_memoria(ui);
    }

    processar_entrada(ui);
}

void desenhar_ui(const EstadoUI *ui) 
{
    BeginDrawing();
    ClearBackground(COR_FUNDO);
    
    switch (ui->estado_atual) 
    {
    case ESTADO_MENU_PRINCIPAL:
        desenhar_menu_principal();
        break;
    case ESTADO_DIFICULDADE:
        desenhar_menu_dificuldade();
        break;
    case ESTADO_JOGANDO_ADIVINHACAO:
        desenhar_jogo_adivinhacao(ui);
        break;
    case ESTADO_JOGANDO_MEMORIA:
        desenhar_jogo_memoria(ui);
        break;
    case ESTADO_RESULTADO_ADIVINHACAO:
        desenhar_resultado_adivinhacao(ui);
        break;
    case ESTADO_RESULTADO_MEMORIA:
        desenhar_resultado_memoria(ui);
        break;
    case ESTADO_SAIR:
        break;
    default:
        break;
    }
    
    EndDrawing();
}

void executar_frontend(void) 
{
    inicializar_raylib();
    
    EstadoUI ui = {0};
    ui.estado_atual = ESTADO_MENU_PRINCIPAL;
    ui.clique_casa1 = -1;
    ui.clique_casa2 = -1;
    
    while (!WindowShouldClose() && ui.estado_atual != ESTADO_SAIR) 
    {
        atualizar_ui(&ui);
        desenhar_ui(&ui);
    }
    
    CloseWindow();
}

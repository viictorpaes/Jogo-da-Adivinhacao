#include <raylib.h>
#include "frontend.h"
#include "../game/jogo.h"
#include "../game/memorygame.h"
#include "../history/historico.h"
#include "../static/estatisticas.h"
#include "../utils/utils.h"
#include "../music/musica.h"
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
    DrawText("* MISSÃO ESPACIAL *", 270, 40, 30, COR_PRIMARIA);
    DrawText("ADIVINHAÇÃO & MEMÓRIA", 220, 78, 40, COR_PRIMARIA);
    DrawText("Bem-vindo, Astronauta! Escolha sua missão:", 265, 163, 25, COR_TEXTO);

    desenhar_botao(400, 210, 400, 65, "1. Missão: Adivinhação");
    desenhar_botao(400, 295, 400, 65, "2. Missão: Jogo da Memória");
    desenhar_botao(400, 380, 400, 65, "3. Estatisticas");
    desenhar_botao(400, 465, 400, 65, "4. Histórico");
    desenhar_botao(400, 550, 400, 65, "5. Abortar Missão (Sair)");
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
    DrawText("IDENTIFICACÇÃO DO ASTRONAUTA", 240, 100, 40, COR_PRIMARIA);
    DrawText("Qual é o nome do seu astronauta?", 320, 220, 25, COR_TEXTO);

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
        DrawText("Seu ultimo palpite:", 200, 175, 22, COR_SECUNDARIA);

        const char *dir_msg = NULL;
        if (ui->entrada_numero < ui->partida_atual.numero_secreto)
            dir_msg = "TRANSMISSAO: O numero secreto é MAIOR! Aponte para cima! ^";

        else if (ui->entrada_numero > ui->partida_atual.numero_secreto)
            dir_msg = "TRANSMISSÃO: O número secreto é MENOR! Volte a orbita! v";

        if (dir_msg)
            DrawText(dir_msg, 200, 205, 22, COR_ERRO);

        int dist = ui->entrada_numero - ui->partida_atual.numero_secreto;
        if (dist < 0) dist = -dist;
        int range = ui->partida_atual.max_range - ui->partida_atual.min_range;
        int pct   = (range > 0) ? (dist * 100 / range) : 100;

        const char *prox_msg;
        Color        prox_cor;
        if  (pct < 5)  
        { prox_msg = "Sinal estabelecido! Frequência muito proxima!"; prox_cor = COR_SUCESSO;    }

        else if (pct < 15) 
        { prox_msg = "Sinal detectado! Continue ajustando..."; prox_cor = COR_SECUNDARIA; }

        else if (pct < 40) { prox_msg = "Interferencia estatica... Sinal fraco.";          prox_cor = COR_SECUNDARIA; }
        
        else { prox_msg = "Sem sinal no espaco... Muito longe!";  prox_cor = COR_ERRO;       }

        DrawText(prox_msg, 200, 235, 22, prox_cor);
    }

    DrawText("Digite seu palpite:", 200, 310, 25, COR_TEXTO);
    
    Rectangle input_box = {200, 360, 400, 60};
    DrawRectangleRec(input_box, (Color){20, 10, 40, 255});
    DrawRectangleLines(200, 360, 400, 60, COR_PRIMARIA);

    DrawText(ui->entrada_texto,
             (int)(input_box.x + 20),
             (int)(input_box.y + 10),
             40, COR_PRIMARIA);

    desenhar_botao(200, 470, 400, 60, "CONFIRMAR PALPITE (Enter)");

    if (ui->mensagem_erro[0] != '\0')
    {
        DrawText(ui->mensagem_erro, 200, 550, 22, COR_ERRO);
    }

    DrawText("Pressione ESC para voltar a seleção de dificuldade", 200, 590, 20, COR_TEXTO);
}

void desenhar_jogo_memoria(const EstadoUI *ui) 
{
    DrawText("MISSÃO: JOGO DA MEMÓRIA 4x4", 300, 30, 40, COR_PRIMARIA);
    
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
    DrawText("Pressione ESC para voltar ao menu principal", 200, 740, 20, COR_TEXTO);
}

void desenhar_resultado_adivinhacao(const EstadoUI *ui)
{
    DrawText("FIM DA MISSÃO", 380, 80, 50, COR_PRIMARIA);

    if (ui->partida_atual.venceu)
    {
        DrawText("MISSÃO CUMPRIDA!", 380, 180, 40, COR_SUCESSO);
        DrawText("Você acertou o número secreto, astronauta!", 220, 260, 28, COR_TEXTO);
    }
    else
    {
        DrawText("MISSÃO FRACASSADA!", 340, 180, 40, COR_ERRO);
        DrawText("Voce esgotou todas as tentativas. De volta a Terra!", 200, 260, 28, COR_TEXTO);
    }

    const char *patente = "Cientista";
    if      (ui->dificuldade_selecionada == MEDIO)   patente = "Piloto";
    else if (ui->dificuldade_selecionada == DIFICIL)  patente = "Buzz Lightyear";

    char linha1[128], linha2[128], linha3[128], linha4[128], linha5[128];
    snprintf(linha1, sizeof(linha1), "Astronauta : %s", ui->nome_jogador);
    snprintf(linha2, sizeof(linha2), "Patente    : %s", patente);
    snprintf(linha3, sizeof(linha3), "NÚmero Secreto: %d", ui->partida_atual.numero_secreto);
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

    const char *dica_adv = heuristica_adivinhacao(
        ui->partida_atual.tentativas_usadas,
        ui->partida_atual.max_tentativas,
        ui->partida_atual.venceu,
        ui->dificuldade_selecionada);
    DrawText(dica_adv, 120, 500, 18, COR_SECUNDARIA);

    desenhar_botao(400, 540, 400, 80, "Voltar ao Menu (ESC)");
}

void desenhar_resultado_memoria(const EstadoUI *ui)
{
    DrawText("MISSÃO CONCLUIDA! PARÁBENS!", 210, 80, 45, COR_SUCESSO);

    char saudacao[128];
    snprintf(saudacao, sizeof(saudacao), "Parabens, %s! Todos os pares foram encontrados!", ui->nome_jogador);
    DrawText(saudacao, 100, 150, 24, COR_TEXTO);

    int pts = calcular_pontos_memoria(ui->jogo_memoria.tentativas);

    char linha1[128], linha2[64], linha3[64], linha4[64], linha5[64];
    snprintf(linha1, sizeof(linha1), "Astronauta       : %s", ui->nome_jogador);
    snprintf(linha2, sizeof(linha2), "Pontuacao Total  : %d / 80", ui->jogo_memoria.pontuacao);
    snprintf(linha3, sizeof(linha3), "Pares Encontrados: %d/8", ui->jogo_memoria.pares_encontrados);
    snprintf(linha4, sizeof(linha4), "Tentativas       : %d", ui->jogo_memoria.tentativas);
    snprintf(linha5, sizeof(linha5), "Pontos de Missao : %d pts", pts);

    DrawText(linha1, 300, 230, 28, COR_TEXTO);
    DrawText(linha2, 300, 270, 28, COR_TEXTO);
    DrawText(linha3, 300, 310, 28, COR_TEXTO);
    DrawText(linha4, 300, 350, 28, COR_TEXTO);
    DrawText(linha5, 300, 390, 28, pts > 60 ? COR_SUCESSO : COR_SECUNDARIA);

    const char *dica_mem = heuristica_memoria(ui->jogo_memoria.tentativas, pts);
    DrawText(dica_mem, 120, 432, 18, COR_SECUNDARIA);

    DrawText("Resultado salvo no historico!", 380, 460, 22, COR_TEXTO);

    desenhar_botao(400, 500, 400, 75, "Voltar ao Menu (ESC)");
}

void desenhar_menu_jogo(void)
{
}

static bool clique_em_rect(Rectangle r)
{
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), r);
}

static void salvar_resultado_memoria(const EstadoUI *ui)
{
    RegistroMemoria reg;
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(reg.data, sizeof(reg.data), "%Y-%m-%d", t);
    strncpy(reg.nome, ui->nome_jogador, sizeof(reg.nome) - 1);
    reg.nome[sizeof(reg.nome) - 1] = '\0';
    reg.pontuacao  = ui->jogo_memoria.pontuacao;
    reg.tentativas = ui->jogo_memoria.tentativas;
    reg.pontos     = calcular_pontos_memoria(ui->jogo_memoria.tentativas);
    salvar_partida_memoria(&reg);
}

static void salvar_partida_adivinhacao(const EstadoUI *ui)
{
    RegistroPartida reg;
    time_t agora = time(NULL);
    struct tm *t  = localtime(&agora);
    strftime(reg.data, sizeof(reg.data), "%Y-%m-%d", t);
    strncpy(reg.nome, ui->nome_jogador, sizeof(reg.nome) - 1);
    reg.nome[sizeof(reg.nome) - 1] = '\0';
    reg.dificuldade      = ui->dificuldade_selecionada;
    reg.tentativas_usadas = ui->partida_atual.tentativas_usadas;
    reg.max_tentativas   = ui->partida_atual.max_tentativas;
    reg.numero_secreto   = ui->partida_atual.numero_secreto;
    reg.venceu           = ui->partida_atual.venceu;
    reg.pontos           = calcular_pontos(ui->dificuldade_selecionada,
                                           ui->partida_atual.tentativas_usadas,
                                           ui->partida_atual.venceu);
    salvar_partida(&reg);
}

void desenhar_estatisticas(EstadoUI *ui)
{
    if (!ui->stats_carregadas)
    {
        preparar_linhas_estatisticas(ui->stats_linhas, &ui->stats_n_linhas);
        ui->stats_carregadas = true;
    }

    DrawText("ESTÁTISTICAS DE MISSÕES", 270, 30, 38, COR_PRIMARIA);
    DrawLine(50, 80, 1150, 80, COR_PRIMARIA);

    int y = 100;
    for (int i = 0; i < ui->stats_n_linhas && y < 720; i++, y += 22)
        DrawText(ui->stats_linhas[i], 60, y, 18, COR_TEXTO);

    desenhar_botao(400, 730, 400, 55, "Voltar ao Menu (ESC)");
}

void desenhar_historico(EstadoUI *ui)
{
    if (!ui->hist_carregado)
    {
        ui->hist_adiv_n = carregar_historico(ui->hist_adiv, 20);
        ui->hist_mem_n  = carregar_historico_memoria(ui->hist_mem, 20);
        preparar_resumo_adivinhacao(ui->hist_resumo_adiv, sizeof(ui->hist_resumo_adiv));
        preparar_resumo_memoria(ui->hist_resumo_mem, sizeof(ui->hist_resumo_mem));
        ui->hist_carregado = true;
    }

    DrawText("HISTÓRICO DE MISSÕES", 310, 20, 38, COR_PRIMARIA);
    DrawLine(50, 68, 1150, 68, COR_PRIMARIA);

    DrawText("Adivinhação", 60, 78, 20, COR_SECUNDARIA);
    DrawText(ui->hist_resumo_adiv, 60, 100, 13, COR_TEXTO);
    DrawLine(60, 118, 560, 118, COR_SECUNDARIA);

    if (ui->hist_adiv_n == 0)
    {
        DrawText("Nenhuma partida registrada.", 60, 130, 18, COR_TEXTO);
    }
    else
    {
        int y = 128;
        const char *difs[] = {"Fácil", "Médio", "Difícil"};
        for (int i = ui->hist_adiv_n - 1; i >= 0 && y < 725; i--, y += 27)
        {
            RegistroPartida *r = &ui->hist_adiv[i];
            char linha[120];
            snprintf(linha, sizeof(linha), "%s  %-12s  %s  %d/%d tent  %d pts",
                     r->data, r->nome,
                     difs[r->dificuldade],
                     r->tentativas_usadas, r->max_tentativas,
                     r->pontos);
            Color cor = r->venceu ? COR_SUCESSO : COR_ERRO;
            DrawText(linha, 60, y, 15, cor);
        }
    }

    DrawText("Memória", 640, 78, 20, COR_SECUNDARIA);
    DrawText(ui->hist_resumo_mem, 640, 100, 13, COR_TEXTO);
    DrawLine(640, 118, 1140, 118, COR_SECUNDARIA);

    if (ui->hist_mem_n == 0)
    {
        DrawText("Nenhuma partida registrada.", 640, 130, 18, COR_TEXTO);
    }
    else
    {
        int y = 128;
        for (int i = ui->hist_mem_n - 1; i >= 0 && y < 725; i--, y += 27)
        {
            RegistroMemoria *r = &ui->hist_mem[i];
            char linha[120];
            snprintf(linha, sizeof(linha), "%s  %-12s  %d jogadas  %d pts",
                     r->data, r->nome, r->tentativas, r->pontos);
            DrawText(linha, 640, y, 15, COR_TEXTO);
        }
    }

    desenhar_botao(400, 730, 400, 55, "Voltar ao Menu (ESC)");
}

void processar_clique_mouse_memoria(EstadoUI *ui)
{
    if (ui->aguardando_ocultar) return;
    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

    Vector2 mouse       = GetMousePosition();
    int tamanho_casa    = 80;
    int espaco          = 10;
    int inicio_x        = 200;
    int inicio_y        = 200;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int posicao = i * 4 + j;
            float x = (float)(inicio_x + (tamanho_casa + espaco) * j);
            float y = (float)(inicio_y + (tamanho_casa + espaco) * i);
            Rectangle casa = {x, y, (float)tamanho_casa, (float)tamanho_casa};

            if (!CheckCollisionPointRec(mouse, casa)) continue;
            if (ui->jogo_memoria.acertadas[posicao])  return;

            int pos = posicao + 1;

            if (ui->clique_casa1 == 0)
            {
                if (!ui->jogo_memoria.reveladas[posicao])
                {
                    ui->jogo_memoria.reveladas[posicao] = true;
                    ui->clique_casa1 = pos;
                }
            }
            else if (pos != ui->clique_casa1 && !ui->jogo_memoria.reveladas[posicao])
            {
                ui->clique_casa2 = pos;
                bool acertou = fazer_jogada(&ui->jogo_memoria, ui->clique_casa1, ui->clique_casa2);
                if (acertou)
                {
                    ui->clique_casa1 = 0;
                    ui->clique_casa2 = 0;
                    if (jogo_memoria_finalizado(&ui->jogo_memoria))
                        ui->estado_atual = ESTADO_RESULTADO_MEMORIA;
                }
                else
                {
                    ui->aguardando_ocultar = true;
                    ui->timer_ocultar      = 90;
                }
            }
            return;
        }
    }
}

void processar_entrada(EstadoUI *ui)
{
    switch (ui->estado_atual)
    {
    case ESTADO_MENU_PRINCIPAL:
    case ESTADO_MENU_JOGO:
        if (IsKeyReleased(KEY_ONE) || clique_em_rect((Rectangle){400, 210, 400, 65}))
        {
            memset(ui->nome_jogador, 0, sizeof(ui->nome_jogador));
            ui->nome_indice  = 0;
            ui->estado_atual = ESTADO_INSERIR_NOME;
        }
        else if (IsKeyReleased(KEY_TWO) || clique_em_rect((Rectangle){400, 295, 400, 65}))
        {
            memset(ui->nome_jogador, 0, sizeof(ui->nome_jogador));
            ui->nome_indice       = 0;
            ui->nome_para_memoria = true;
            ui->memoria_salva     = false;
            ui->estado_atual      = ESTADO_INSERIR_NOME;
        }
        else if (IsKeyReleased(KEY_THREE) || clique_em_rect((Rectangle){400, 380, 400, 65}))
        {
            ui->stats_carregadas = false;
            ui->estado_atual     = ESTADO_ESTATISTICAS;
        }
        else if (IsKeyReleased(KEY_FOUR) || clique_em_rect((Rectangle){400, 465, 400, 65}))
        {
            ui->hist_carregado = false;
            ui->estado_atual   = ESTADO_HISTORICO;
        }
        else if (IsKeyReleased(KEY_FIVE) || clique_em_rect((Rectangle){400, 550, 400, 65}))
        {
            ui->estado_atual = ESTADO_SAIR;
        }
        break;

    case ESTADO_INSERIR_NOME:
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if (key >= 32 && key < 127 && ui->nome_indice < (int)sizeof(ui->nome_jogador) - 1)
            {
                ui->nome_jogador[ui->nome_indice++] = (char)key;
                ui->nome_jogador[ui->nome_indice]   = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyReleased(KEY_BACKSPACE) && ui->nome_indice > 0)
            ui->nome_jogador[--ui->nome_indice] = '\0';

        if (IsKeyReleased(KEY_ENTER) || clique_em_rect((Rectangle){400, 420, 400, 70}))
        {
            if (ui->nome_indice == 0)
            {
                strcpy(ui->nome_jogador, "Astronauta");
                ui->nome_indice = (int)strlen("Astronauta");
            }
            if (ui->nome_para_memoria)
            {
                ui->nome_para_memoria  = false;
                ui->jogo_memoria       = inicializar_jogo_memoria();
                ui->clique_casa1       = 0;
                ui->clique_casa2       = 0;
                ui->aguardando_ocultar = false;
                ui->timer_ocultar      = 0;
                ui->memoria_salva      = false;
                ui->estado_atual       = ESTADO_JOGANDO_MEMORIA;
            }
            else
            {
                ui->estado_atual = ESTADO_DIFICULDADE;
            }
        }
        if (IsKeyReleased(KEY_ESCAPE))
        {
            ui->nome_para_memoria = false;
            ui->estado_atual      = ESTADO_MENU_PRINCIPAL;
        }
        break;
    }

    case ESTADO_DIFICULDADE:
    {
        Dificuldade dif = FACIL;
        bool escolheu   = false;

        if (IsKeyReleased(KEY_ONE) || clique_em_rect((Rectangle){250, 230, 700, 100}))
            { dif = FACIL;   escolheu = true; }
        else if (IsKeyReleased(KEY_TWO) || clique_em_rect((Rectangle){250, 380, 700, 100}))
            { dif = MEDIO;   escolheu = true; }
        else if (IsKeyReleased(KEY_THREE) || clique_em_rect((Rectangle){250, 530, 700, 100}))
            { dif = DIFICIL; escolheu = true; }

        if (escolheu)
        {
            ui->dificuldade_selecionada = dif;
            ui->partida_atual           = iniciar_partida(dif);
            memset(ui->entrada_texto,  0, sizeof(ui->entrada_texto));
            memset(ui->mensagem_erro,  0, sizeof(ui->mensagem_erro));
            ui->entrada_numero = 0;
            ui->indice_entrada = 0;
            ui->partida_salva  = false;
            ui->estado_atual   = ESTADO_JOGANDO_ADIVINHACAO;
        }
        if (IsKeyReleased(KEY_ESCAPE))
            ui->estado_atual = ESTADO_INSERIR_NOME;
        break;
    }

    case ESTADO_JOGANDO_ADIVINHACAO:
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if (key >= '0' && key <= '9' && ui->indice_entrada < 9)
            {
                ui->entrada_texto[ui->indice_entrada++] = (char)key;
                ui->entrada_texto[ui->indice_entrada]   = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyReleased(KEY_BACKSPACE) && ui->indice_entrada > 0)
            ui->entrada_texto[--ui->indice_entrada] = '\0';

        if (IsKeyReleased(KEY_ENTER) || clique_em_rect((Rectangle){200, 470, 400, 60}))
        {
            if (ui->indice_entrada == 0)
            {
                snprintf(ui->mensagem_erro, sizeof(ui->mensagem_erro),
                         "Digite um numero para palpitar!");
            }
            else
            {
                int palpite = atoi(ui->entrada_texto);
                if (palpite < ui->partida_atual.min_range || palpite > ui->partida_atual.max_range)
                {
                    snprintf(ui->mensagem_erro, sizeof(ui->mensagem_erro),
                             "Palpite fora do range! Digite entre %d e %d.",
                             ui->partida_atual.min_range, ui->partida_atual.max_range);
                }
                else
                {
                    ui->entrada_numero = palpite;
                    memset(ui->mensagem_erro, 0, sizeof(ui->mensagem_erro));
                    processar_palpite(&ui->partida_atual, palpite);
                    memset(ui->entrada_texto, 0, sizeof(ui->entrada_texto));
                    ui->indice_entrada = 0;
                    if (partida_encerrada(&ui->partida_atual))
                    {
                        if (!ui->partida_salva)
                        {
                            salvar_partida_adivinhacao(ui);
                            ui->partida_salva = true;
                        }
                        ui->estado_atual = ESTADO_RESULTADO_ADIVINHACAO;
                    }
                }
            }
        }
        if (IsKeyReleased(KEY_ESCAPE))
            ui->estado_atual = ESTADO_DIFICULDADE;
        break;
    }

    case ESTADO_JOGANDO_MEMORIA:
        processar_clique_mouse_memoria(ui);
        if (IsKeyReleased(KEY_ESCAPE))
            ui->estado_atual = ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_ADIVINHACAO:
        if (IsKeyReleased(KEY_ESCAPE) || IsKeyReleased(KEY_ENTER) ||
            clique_em_rect((Rectangle){400, 540, 400, 80}))
            ui->estado_atual = ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_MEMORIA:
        if (!ui->memoria_salva)
        {
            salvar_resultado_memoria(ui);
            ui->memoria_salva = true;
        }
        if (IsKeyReleased(KEY_ESCAPE) || IsKeyReleased(KEY_ENTER) ||
            clique_em_rect((Rectangle){400, 500, 400, 75}))
            ui->estado_atual = ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_ESTATISTICAS:
        if (IsKeyReleased(KEY_ESCAPE) || clique_em_rect((Rectangle){400, 730, 400, 55}))
        {
            ui->stats_carregadas = false;
            ui->estado_atual     = ESTADO_MENU_PRINCIPAL;
        }
        break;

    case ESTADO_HISTORICO:
        if (IsKeyReleased(KEY_ESCAPE) || clique_em_rect((Rectangle){400, 730, 400, 55}))
        {
            ui->hist_carregado = false;
            ui->estado_atual   = ESTADO_MENU_PRINCIPAL;
        }
        break;

    default:
        break;
    }
}

void atualizar_ui(EstadoUI *ui)
{
    if (ui->estado_atual != ESTADO_JOGANDO_MEMORIA || !ui->aguardando_ocultar) return;

    ui->timer_ocultar--;
    if (ui->timer_ocultar <= 0)
    {
        if (ui->clique_casa1 > 0) ui->jogo_memoria.reveladas[ui->clique_casa1 - 1] = false;
        if (ui->clique_casa2 > 0) ui->jogo_memoria.reveladas[ui->clique_casa2 - 1] = false;
        ui->aguardando_ocultar = false;
        ui->clique_casa1       = 0;
        ui->clique_casa2       = 0;
    }
}

void desenhar_ui(EstadoUI *ui)
{
    switch (ui->estado_atual)
    {
    case ESTADO_MENU_PRINCIPAL:
    case ESTADO_MENU_JOGO:      desenhar_menu_principal();          break;
    case ESTADO_INSERIR_NOME:   desenhar_inserir_nome(ui);          break;
    case ESTADO_DIFICULDADE:    desenhar_menu_dificuldade();        break;
    case ESTADO_JOGANDO_ADIVINHACAO: desenhar_jogo_adivinhacao(ui); break;
    case ESTADO_JOGANDO_MEMORIA:     desenhar_jogo_memoria(ui);     break;
    case ESTADO_RESULTADO_ADIVINHACAO: desenhar_resultado_adivinhacao(ui); break;
    case ESTADO_RESULTADO_MEMORIA:     desenhar_resultado_memoria(ui);     break;
    case ESTADO_ESTATISTICAS:          desenhar_estatisticas(ui);          break;
    case ESTADO_HISTORICO:             desenhar_historico(ui);             break;
    default: break;
    }
}

void executar_frontend(void)
{
    inicializar_raylib();
    InitMusica();

    EstadoUI ui;
    memset(&ui, 0, sizeof(EstadoUI));
    ui.estado_atual = ESTADO_MENU_PRINCIPAL;

    while (!WindowShouldClose() && ui.estado_atual != ESTADO_SAIR)
    {
        UpdateMusica();
        processar_entrada(&ui);
        atualizar_ui(&ui);

        BeginDrawing();
        ClearBackground((Color){10, 5, 25, 255});
        desenhar_ui(&ui);
        EndDrawing();
    }

    UnloadMusica();
    CloseWindow();
}
#include <raylib.h>
#include "frontend.h"
#include "../game/jogo.h"
#include "../game/memorygame.h"
#include "../game/logica.h"
#include "../game/precedencia.h"
#include "../history/historico.h"
#include "../static/estatisticas.h"
#include "../utils/utils.h"
#include "../music/musica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COR_FUNDO        (Color){10,  5,  25, 255}
#define COR_PRIMARIA     (Color){180,100, 255, 255}
#define COR_SECUNDARIA   (Color){255,200,  80, 255}
#define COR_SUCESSO      (Color){100,255, 180, 255}
#define COR_ERRO         (Color){255, 80, 120, 255}
#define COR_TEXTO        (Color){230,220, 255, 255}
#define COR_BOTAO        (Color){ 60, 30, 100, 255}
#define COR_BOTAO_HOVER  (Color){110, 60, 170, 255}
#define COR_AVISO        (Color){255,160,  40, 255}
#define COR_TIMER_OK     (Color){100,220, 255, 255}
#define COR_TIMER_PERIGO (Color){255, 80,  80, 255}

typedef struct 
{
    Rectangle  rect;
    const char *texto;
    bool        hover;
} Botao;


static void inicializar_raylib(void)
{
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Missao Espacial: Adivinhacao & Memoria");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));
}

static Botao desenhar_botao(float x, float y, float w, float h, const char *texto)
{
    Botao b;
    b.rect  = (Rectangle){x, y, w, h};
    b.texto = texto;
    b.hover = CheckCollisionPointRec(GetMousePosition(), b.rect);
    Color cor = b.hover ? COR_BOTAO_HOVER : COR_BOTAO;
    DrawRectangleRec(b.rect, cor);
    DrawRectangleLines((int)x, (int)y, (int)w, (int)h, COR_PRIMARIA);
    int largura_texto = MeasureText(texto, 20);
    DrawText(texto, (int)(x + w/2 - largura_texto/2), (int)(y + h/2 - 10), 20, COR_TEXTO);
    return b;
}

static bool clique_em_rect(Rectangle r)
{
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), r);
}

static void desenhar_timer(double secs, float x, float y, float largura)
{
    Color cor = secs > 5.0 ? COR_TIMER_OK : COR_TIMER_PERIGO;
    char buf[32];
    snprintf(buf, sizeof(buf), "Tempo: %.0fs", secs < 0 ? 0.0 : secs);
    DrawText(buf, (int)x, (int)y, 24, cor);

    float maxw = largura;
    float filled = (float)(secs / TIMER_ADIV_SEG) * maxw;
    if (filled < 0) filled = 0;
    if (filled > maxw) filled = maxw;
    DrawRectangle((int)x, (int)(y+30), (int)maxw, 8, COR_BOTAO);
    DrawRectangle((int)x, (int)(y+30), (int)filled, 8, cor);
}

static void desenhar_timer_generico(double secs, double max_secs,
                                    float x, float y, float largura)
{
    Color cor = secs > max_secs * 0.3 ? COR_TIMER_OK : COR_TIMER_PERIGO;
    char buf[32];
    snprintf(buf, sizeof(buf), "%.0fs", secs < 0 ? 0.0 : secs);
    DrawText(buf, (int)x, (int)y, 22, cor);

    float filled = (float)(secs / max_secs) * largura;
    if (filled < 0) filled = 0;
    if (filled > largura) filled = largura;
    DrawRectangle((int)x, (int)(y+26), (int)largura, 6, COR_BOTAO);
    DrawRectangle((int)x, (int)(y+26), (int)filled, 6, cor);
}


static void salvar_partida_adivinhacao(const EstadoUI *ui)
{
    RegistroPartida reg;
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(reg.data, sizeof(reg.data), "%Y-%m-%d", t);
    strncpy(reg.nome, ui->nome_jogador, sizeof(reg.nome)-1);
    reg.nome[sizeof(reg.nome)-1] = '\0';
    reg.dificuldade = ui->dificuldade_selecionada;
    reg.tentativas_usadas = ui->partida_atual.tentativas_usadas;
    reg.max_tentativas = ui->partida_atual.max_tentativas;
    reg.numero_secreto = ui->partida_atual.numero_secreto;
    reg.venceu  = ui->partida_atual.venceu;
    reg.pontos  = calcular_pontos(ui->dificuldade_selecionada,
                                           ui->partida_atual.tentativas_usadas,
                                           ui->partida_atual.venceu);
    salvar_partida(&reg);
}

static void salvar_resultado_memoria(const EstadoUI *ui)
{
    RegistroMemoria reg;
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(reg.data, sizeof(reg.data), "%Y-%m-%d", t);
    strncpy(reg.nome, ui->nome_jogador, sizeof(reg.nome)-1);
    reg.nome[sizeof(reg.nome)-1] = '\0';
    reg.pontuacao  = ui->jogo_memoria.pontuacao;
    reg.tentativas = ui->jogo_memoria.tentativas;
    reg.pontos     = calcular_pontos_memoria(ui->jogo_memoria.tentativas);
    salvar_partida_memoria(&reg);
}

static void data_hoje(char *buf, int len)
{
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(buf, len, "%Y-%m-%d", t);
}

typedef struct { float x, y, w, h; const char *texto; } ItemMenu;

static const ItemMenu ITENS_MENU[9] = 
{
    {  60, 115, 530, 62, "1. Operação Resgate    (Adivinhação solo)"  }, 
    { 610, 115, 530, 62, "2. Batalha de Sinais   (Adivinhação VS)"    },
    {  60, 187, 530, 62, "3. Mapas Estelares     (Memória solo)"      }, 
    { 610, 187, 530, 62, "4. 1v1 Mapas Estelares (Memória VS)"        }, 
    {  60, 259, 530, 62, "5. Protocolo Lógico    (Fórmulas V/F)"      },
    {  60, 331, 530, 62, "6. Hierarquia de Cmds  (Precedência)"       },
    {  60, 422, 340, 58, "7. Estatísticas"                            },
    { 430, 422, 340, 58, "8. Histórico"                               }, 
    { 800, 422, 340, 58, "9. Abortar Missao (Sair)"                   }, 
};
#define N_ITENS_MENU 9

void desenhar_menu_principal(void)
{
    DrawText("MISSÃO ESPACIAL", 380, 18, 36, COR_PRIMARIA);
    DrawText("Escolha sua missão, astronauta:", 370, 60, 20, COR_TEXTO);

    DrawText("SOLO / LOGICA", 70,  95, 16, COR_SECUNDARIA);
    DrawText("VERSUS",       720,  95, 16, COR_SECUNDARIA);

    for (int i = 0; i < N_ITENS_MENU; i++)
    {
        desenhar_botao(ITENS_MENU[i].x, ITENS_MENU[i].y,
                       ITENS_MENU[i].w, ITENS_MENU[i].h,
                       ITENS_MENU[i].texto);
    }

    DrawLine(60, 412, 1140, 412, COR_BOTAO);
    DrawText("Clique ou pressione 1-9", 430, 498, 18, COR_TEXTO);
}


void desenhar_inserir_nome(const EstadoUI *ui)
{
    bool is_p2 = (ui->estado_atual == ESTADO_INSERIR_NOME_P2);
    const char *titulo = is_p2 ? "ASTRONAUTA 2 - IDENTIFICAÇÃO" : "IDENTIFICAÇÃO DO ASTRONAUTA";
    DrawText(titulo, 220, 100, 40, COR_PRIMARIA);

    const char *nome_atual = is_p2 ? ui->nome_jogador2 : ui->nome_jogador;
    DrawText("Qual o nome do astronauta?", 330, 220, 25, COR_TEXTO);

    Rectangle box = {250,280,700,70};
    DrawRectangleRec(box, (Color){20,10,40,255});
    DrawRectangleLines(250,280,700,70, COR_PRIMARIA);
    DrawText(nome_atual,(int)(box.x+20),(int)(box.y+15),40,COR_PRIMARIA);

    if ((GetTime()*2)-(int)(GetTime()*2) < 1.0) {
        int cx = (int)(box.x+20)+MeasureText(nome_atual,40);
        DrawText("|",cx,(int)(box.y+15),40,COR_PRIMARIA);
    }

    desenhar_botao(400,420,400,70,"CONFIRMAR (Enter)");
    DrawText("Deixe em branco para usar 'Astronauta'", 305,520,20,COR_TEXTO);
    DrawText("ESC para voltar", 490,550,20,COR_TEXTO);
}

void desenhar_inserir_nome_p2(const EstadoUI *ui)
{
    desenhar_inserir_nome(ui);
}

void desenhar_menu_dificuldade(EstadoUI *ui)
{
    const char *titulo = "SELECIONE A PATENTE";
    if (ui->modo_pendente == MODO_LOGICA)      titulo = "PROTOCOLO LOGICO - PATENTE";
    if (ui->modo_pendente == MODO_PRECEDENCIA) titulo = "HIERARQUIA DE CMDS - PATENTE";

    DrawText(titulo, 300,80,38,COR_PRIMARIA);
    DrawText("Qual a sua patente espacial?", 350,148,22,COR_TEXTO);

    desenhar_botao(200,230,800,95,"[1] Cadete      (1-10,  5 tent. | 30s/questao)");
    desenhar_botao(200,380,800,95,"[2] Piloto      (1-50,  8 tent. | 20s/questao)");
    desenhar_botao(200,530,800,95,"[3] Comandante  (1-100,10 tent. | 15s/questao)");

    DrawText("Clique ou pressione 1/2/3", 410,665,20,COR_TEXTO);
    DrawText("ESC para voltar", 490,692,20,COR_TEXTO);
}

void desenhar_jogo_adivinhacao(const EstadoUI *ui)
{
    DrawText("MISSÃO: OPERAÇÃO RESGATE", 320,30,38,COR_PRIMARIA);

    const char *pat = "Cadete";
    if (ui->dificuldade_selecionada == MEDIO)  pat = "Piloto";
    if (ui->dificuldade_selecionada == DIFICIL) pat = "Comandante";

    char info[256];
    snprintf(info,sizeof(info),"Patente: %s | Range: %d a %d | Tentativas: %d/%d",
             pat,ui->partida_atual.min_range,ui->partida_atual.max_range,
             ui->partida_atual.tentativas_usadas,ui->partida_atual.max_tentativas);
    DrawText(info,90,95,20,COR_TEXTO);

    desenhar_timer(ui->timer_adiv, 850, 90, 290);

    if (ui->partida_atual.tentativas_usadas > 0) 
    {
        int dist = ui->entrada_numero - ui->partida_atual.numero_secreto;
        if (dist < 0) dist = -dist;
        int range = ui->partida_atual.max_range - ui->partida_atual.min_range;
        int pct   = range > 0 ? dist*100/range : 100;
        const char *msg; Color cor;
        if      (pct < 5)  { msg = "Sinal estabelecido! Frequência muito próxima!"; cor = COR_SUCESSO;   }
        else if (pct < 15) { msg = "Sinal detectado! Continue ajustando...";         cor = COR_SECUNDARIA;}
        else if (pct < 40) { msg = "Interferência estática... Sinal fraco.";         cor = COR_SECUNDARIA;}
        else               { msg = "Sem sinal no espaço... Muito longe!";            cor = COR_ERRO;      }
        DrawText("Último palpite:", 140,175,22,COR_SECUNDARIA);
        DrawText(msg,140,205,22,cor);
    }

    DrawText("Digite seu palpite:", 140,310,25,COR_TEXTO);
    Rectangle box = {140,360,420,60};
    DrawRectangleRec(box,(Color){20,10,40,255});
    DrawRectangleLines(140,360,420,60,COR_PRIMARIA);
    DrawText(ui->entrada_texto,(int)(box.x+20),(int)(box.y+10),40,COR_PRIMARIA);

    desenhar_botao(140,470,420,60,"CONFIRMAR PALPITE (Enter)");

    if (ui->mensagem_erro[0])
        DrawText(ui->mensagem_erro,140,550,20,COR_ERRO);
    DrawText("ESC = voltar à dificuldade",140,590,18,COR_TEXTO);
}

void desenhar_jogo_vs(const EstadoUI *ui)
{
    DrawText("BATALHA DE SINAIS - 1v1", 340,22,36,COR_PRIMARIA);

    char placar[128];
    snprintf(placar,sizeof(placar),"Rodada %d/%d | %s: %d rodada(s) | %s: %d rodada(s)",
             ui->vs_rodada+1, VS_MAX_RODADAS,
             ui->nome_jogador,  ui->vs_rodadas_vencidas[0],
             ui->nome_jogador2, ui->vs_rodadas_vencidas[1]);
    DrawText(placar,60,68,18,COR_TEXTO);

    const char *nome_turno = ui->vs_jogador_atual == 0 ? ui->nome_jogador : ui->nome_jogador2;
    char turno_buf[128];
    snprintf(turno_buf,sizeof(turno_buf),"TURNO DE: %s   Tent.: %d/%d",
             nome_turno,
             ui->vs_tentativas[ui->vs_jogador_atual],
             VS_MAX_TENTATIVAS);
    DrawText(turno_buf,60,100,24, ui->vs_jogador_atual == 0 ? COR_SUCESSO : COR_AVISO);

    desenhar_timer(ui->vs_timer, 850, 90, 290);

    const char *pat = "Cadete";
    if (ui->dificuldade_selecionada == MEDIO)  pat = "Piloto";
    if (ui->dificuldade_selecionada == DIFICIL) pat = "Comandante";
    char info_range[64];
    snprintf(info_range, sizeof(info_range), "Range %s: %d a %d", pat,
             ui->vs_partida.min_range, ui->vs_partida.max_range);
    DrawText(info_range, 60, 138, 20, COR_TEXTO);

    if (ui->vs_partida.tentativas_usadas > 0) {
        int dist = ui->entrada_numero - ui->vs_partida.numero_secreto;
        if (dist < 0) dist = -dist;
        int range = ui->vs_partida.max_range - ui->vs_partida.min_range;
        int pct   = range > 0 ? dist*100/range : 100;
        const char *msg; Color cor;
        if      (pct < 5)  { msg = "Sinal estabelecido! Frequência muito próxima!"; cor = COR_SUCESSO;   }
        else if (pct < 15) { msg = "Sinal detectado! Continue ajustando...";         cor = COR_SECUNDARIA;}
        else if (pct < 40) { msg = "Interferência estática... Sinal fraco.";         cor = COR_SECUNDARIA;}
        else               { msg = "Sem sinal no espaço... Muito longe!";            cor = COR_ERRO;      }
        DrawText(msg,60,175,20,cor);
    }

    char tent_j1[64], tent_j2[64];
    snprintf(tent_j1, sizeof(tent_j1), "%s: %d tent.", ui->nome_jogador,  ui->vs_tentativas[0]);
    snprintf(tent_j2, sizeof(tent_j2), "%s: %d tent.", ui->nome_jogador2, ui->vs_tentativas[1]);
    DrawText(tent_j1, 60,  210, 18, COR_SUCESSO);
    DrawText(tent_j2, 400, 210, 18, COR_AVISO);

    DrawText("Digite seu palpite:",60,300,25,COR_TEXTO);
    Rectangle box = {60,350,420,60};
    DrawRectangleRec(box,(Color){20,10,40,255});
    DrawRectangleLines(60,350,420,60,COR_PRIMARIA);
    DrawText(ui->entrada_texto,(int)(box.x+20),(int)(box.y+10),40,COR_PRIMARIA);
    desenhar_botao(60,460,420,60,"CONFIRMAR PALPITE (Enter)");

    if (ui->mensagem_erro[0])
        DrawText(ui->mensagem_erro,60,540,20,COR_ERRO);

    /* Indicador visual de jogador atual */
    Color col_j1 = ui->vs_jogador_atual==0 ? COR_SUCESSO : (Color){80,80,80,255};
    Color col_j2 = ui->vs_jogador_atual==1 ? COR_AVISO   : (Color){80,80,80,255};
    DrawRectangle(560,300,580,240,COR_BOTAO);
    DrawRectangleLines(560,300,580,240,COR_PRIMARIA);
    DrawText("ASTRONAUTAS", 720,315,20,COR_PRIMARIA);
    DrawText(ui->nome_jogador,  590,360,22,col_j1);
    DrawText(ui->nome_jogador2, 590,400,22,col_j2);
    if (ui->vs_jogador_atual==0) DrawText("<-- SUA VEZ",820,360,18,COR_SUCESSO);
    else                         DrawText("<-- SUA VEZ",820,400,18,COR_AVISO);
}

/* ── Telas: Memória solo ─────────────────────────────────────────── */

static void _desenhar_grade_memoria(const JogoMemoria *jogo,
                                    int inicio_x, int inicio_y,
                                    int tamanho_casa, int espacamento,
                                    int linhas, int colunas,
                                    int clique1, int clique2)
{
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int pos = i * colunas + j;
            int x   = inicio_x + (tamanho_casa + espacamento) * j;
            int y   = inicio_y + (tamanho_casa + espacamento) * i;
            Rectangle casa = {(float)x, (float)y, (float)tamanho_casa, (float)tamanho_casa};
            Color cor;
            if      (jogo->acertadas[pos])                               cor = COR_SUCESSO;
            else if (clique1 > 0 && (pos+1 == clique1 || pos+1 == clique2)) cor = COR_ERRO;
            else if (jogo->reveladas[pos])                               cor = COR_PRIMARIA;
            else                                                         cor = COR_BOTAO;
            DrawRectangleRec(casa, cor);
            DrawRectangleLines(x, y, tamanho_casa, tamanho_casa, COR_TEXTO);
            if (jogo->acertadas[pos] || jogo->reveladas[pos]) {
                char num_str[8];
                snprintf(num_str, sizeof(num_str), "%d", jogo->numeros[pos]);
                int largura_texto = MeasureText(num_str, 36);
                DrawText(num_str, x + tamanho_casa/2 - largura_texto/2, y + tamanho_casa/2 - 18, 36, COR_TEXTO);
            } else {
                DrawText("?", x + tamanho_casa/2 - 10, y + tamanho_casa/2 - 18, 36, COR_TEXTO);
            }
        }
    }
}

void desenhar_jogo_memoria(const EstadoUI *ui)
{
    DrawText("MISSÃO: MAPAS ESTELARES", 350,22,36,COR_PRIMARIA);

    char stats[256];
    snprintf(stats,sizeof(stats),"Pontuação: %d | Pares: %d/8 | Jogadas: %d",
             ui->jogo_memoria.pontuacao,
             ui->jogo_memoria.pares_encontrados,
             ui->jogo_memoria.tentativas);
    DrawText(stats,180,72,22,COR_TEXTO);

    /* Timer de memória */
    Color tc = ui->timer_memoria > 10.0 ? COR_TIMER_OK : COR_TIMER_PERIGO;
    char tbuf[32]; snprintf(tbuf,sizeof(tbuf),"Timer: %.0fs",ui->timer_memoria<0?0.0:ui->timer_memoria);
    DrawText(tbuf,840,72,22,tc);
    float bw = 300;
    float bf = (float)(ui->timer_memoria / TIMER_MEM_BASE_SEG)*bw;
    if(bf<0)bf=0; if(bf>bw)bf=bw;
    DrawRectangle(840,98,(int)bw,8,COR_BOTAO);
    DrawRectangle(840,98,(int)bf,8,tc);

    _desenhar_grade_memoria(&ui->jogo_memoria, 200, 145, 80, 8, 4, 4,
                            ui->clique_casa1, ui->clique_casa2);

    DrawText("Clique em duas casas para revelar pares!",200,550,20,COR_TEXTO);
    DrawText("ESC = voltar ao menu",200,578,18,COR_TEXTO);
}

/* ── Telas: 1v1 Memória ──────────────────────────────────────────── */

void desenhar_jogo_memoria_vs(const EstadoUI *ui)
{
    DrawText("1v1 MAPAS ESTELARES", 390,22,36,COR_PRIMARIA);

    /* Timer dos dois jogadores */
    Color cor_j1 = ui->mem_vs_timer[0] > 10 ? COR_SUCESSO : COR_ERRO;
    Color cor_j2 = ui->mem_vs_timer[1] > 10 ? COR_AVISO   : COR_ERRO;
    char buf_j1[64], buf_j2[64];
    snprintf(buf_j1, sizeof(buf_j1), "%s: %.0fs | %d pares",
             ui->nome_jogador, ui->mem_vs_timer[0] < 0 ? 0.0 : ui->mem_vs_timer[0], ui->mem_vs_pares[0]);
    snprintf(buf_j2, sizeof(buf_j2), "%s: %.0fs | %d pares",
             ui->nome_jogador2, ui->mem_vs_timer[1] < 0 ? 0.0 : ui->mem_vs_timer[1], ui->mem_vs_pares[1]);
    DrawText(buf_j1, 60,  68, 20, cor_j1);
    DrawText(buf_j2, 630, 68, 20, cor_j2);

    /* Indicador de turno */
    const char *nome_t = ui->mem_vs_jogador==0?ui->nome_jogador:ui->nome_jogador2;
    Color cor_t = ui->mem_vs_jogador==0?COR_SUCESSO:COR_AVISO;
    char turno[64]; snprintf(turno,sizeof(turno),"TURNO: %s",nome_t);
    DrawText(turno,450,98,26,cor_t);

    _desenhar_grade_memoria(&ui->mem_vs_jogo, 280, 145, 80, 8, 4, 4,
                            ui->mem_vs_clique1, ui->mem_vs_clique2);

    DrawText("Clique em duas casas para revelar pares!",280,550,20,COR_TEXTO);
    DrawText("ESC = voltar ao menu",280,578,18,COR_TEXTO);
}

/* ── Telas: Lógica ───────────────────────────────────────────────── */

void desenhar_jogo_logica(const EstadoUI *ui)
{
    const JogoLogica *j = &ui->logica;
    DrawText("PROTOCOLO LÓGICO", 410,22,36,COR_PRIMARIA);

    char hdr[128];
    snprintf(hdr,sizeof(hdr),"Questão %d/%d | Acertos VF:%d | Acertos Class:%d | Pts:%d",
             j->questoes_respondidas+1, j->questoes_total,
             j->acertos_vf, j->acertos_class,
             calcular_pontos_logica(j));
    DrawText(hdr,60,72,18,COR_TEXTO);

    /* Timer */
    double max_t = j->fase==FASE_FEEDBACK ? 2.5 : j->tempo_por_questao;
    double t_val = j->fase==FASE_FEEDBACK ? j->timer_feedback : j->timer;
    desenhar_timer_generico(t_val,max_t,860,72,270);

    /* Legenda de operadores */
    DrawText("Legenda: ~ = NÃO  ^ = E  V = OU  -> = IMPLICA  <-> = BICONDICIONAL",
             60,108,14,COR_SECUNDARIA);

    DrawLine(60,130,1140,130,COR_BOTAO);

    /* Formula */
    DrawText("Fórmula:",60,152,22,COR_SECUNDARIA);
    DrawText(j->formula_str,200,152,28,COR_PRIMARIA);

    /* Valores de P, Q, R */
    char vals[128] = "Valores: ";
    for (int v = 0; v < j->n_vars; v++) {
        char tmp[16];
        snprintf(tmp,sizeof(tmp),"%c = %s  ","PQR"[v],j->vars[v]?"V":"F");
        strcat(vals,tmp);
    }
    DrawText(vals,60,200,22,COR_TEXTO);

    DrawLine(60,240,1140,240,COR_BOTAO);

    if (j->fase == FASE_RESP_VF) {
        DrawText("Esta fórmula é VERDADEIRA ou FALSA para esses valores?",
                 60,265,22,COR_TEXTO);
        desenhar_botao(180,320,280,80,"V - VERDADEIRO");
        desenhar_botao(540,320,280,80,"F - FALSO");
        DrawText("Pressione V ou F",480,425,20,COR_TEXTO);

    } else if (j->fase == FASE_CLASSIF) {
        char res_vf[64];
        snprintf(res_vf,sizeof(res_vf),"Você respondeu: %s  |  Correto: %s",
                 j->resp_vf==1?"V":"F",j->resp_correta_vf?"V":"F");
        Color c = j->acertou_vf ? COR_SUCESSO : COR_ERRO;
        DrawText(res_vf,60,265,20,c);

        DrawText("Classifique esta fórmula:",60,310,22,COR_TEXTO);
        desenhar_botao(60, 360,340,75,"[1] TAUTOLOGIA");
        desenhar_botao(430,360,340,75,"[2] CONTRADIÇÃO");
        desenhar_botao(800,360,340,75,"[3] CONTINGÊNCIA");
        DrawText("Pressione 1, 2 ou 3",470,455,20,COR_TEXTO);

    } else { /* FASE_FEEDBACK */
        char fb_vf[64];
        snprintf(fb_vf,sizeof(fb_vf),"V/F: %s  (correto: %s)",
                 j->resp_vf==1?"V":"F",j->resp_correta_vf?"V":"F");
        DrawText(fb_vf,60,268,22,j->acertou_vf?COR_SUCESSO:COR_ERRO);

        const char *classes[]={"TAUTOLOGIA","CONTRADIÇÃO","CONTINGÊNCIA"};
        char fb_cl[128];
        snprintf(fb_cl,sizeof(fb_cl),"Classificação: %s  (correto: %s)",
                 j->resp_class>=0?classes[j->resp_class]:"---",classes[j->classificacao]);
        DrawText(fb_cl,60,308,22,j->acertou_class?COR_SUCESSO:COR_ERRO);

        DrawText("Próxima questão...",480,380,24,COR_TEXTO);
    }

    /* Legenda de tabela da verdade */
    DrawLine(60,480,1140,480,COR_BOTAO);
    DrawText("Lembretes de lógica:",60,496,16,COR_SECUNDARIA);
    DrawText("TAUTOLOGIA = sempre V  |  CONTRADIÇÃO = sempre F  |  CONTINGÊNCIA = V ou F dependendo dos valores",
             60,516,14,COR_TEXTO);
}

/* ── Telas: Precedência ──────────────────────────────────────────── */

void desenhar_jogo_precedencia(const EstadoUI *ui)
{
    const JogoPrecedencia *j = &ui->precedencia;
    DrawText("HIERARQUIA DE COMANDOS", 330,22,36,COR_PRIMARIA);

    char hdr[128];
    snprintf(hdr,sizeof(hdr),"Questão %d/%d | Acertos: %d | Pts: %d",
             j->questoes_respondidas+1, j->questoes_total,
             j->acertos, calcular_pontos_prec(j));
    DrawText(hdr,60,72,18,COR_TEXTO);

    double t_val = j->mostrando_feedback ? j->timer_feedback : j->timer;
    double max_t = j->mostrando_feedback ? 2.0 : j->tempo_por_questao;
    desenhar_timer_generico(t_val,max_t,860,72,270);

    DrawText("Precedência: ~ > ^ > V > -> > <->", 60,108,16,COR_SECUNDARIA);
    DrawLine(60,132,1140,132,COR_BOTAO);

    DrawText("Adicione parênteses para indicar a precedência correta:",60,155,22,COR_TEXTO);
    DrawText(j->questao.formula, 60, 195, 36, COR_PRIMARIA);

    DrawLine(60,250,1140,250,COR_BOTAO);
    DrawText("Escolha a opção correta:",60,268,22,COR_TEXTO);

    float oy = 310;
    for (int k = 0; k < 4; k++) {
        char label[280];
        snprintf(label,sizeof(label),"[%d] %s",k+1,j->questao.opcoes[k]);
        Color cor_btn = COR_BOTAO;
        if (j->mostrando_feedback) {
            if (k == j->questao.correta)  cor_btn = (Color){0,120,60,255};
            else if (k == j->resp_selecionada && !j->acertou) cor_btn = (Color){120,0,40,255};
        }
        Rectangle r = {60,(float)(oy+k*75),1080,65};
        bool hover  = CheckCollisionPointRec(GetMousePosition(),r);
        DrawRectangleRec(r, hover && !j->mostrando_feedback ? COR_BOTAO_HOVER : cor_btn);
        DrawRectangleLines(60,(int)(oy+k*75),1080,65,COR_PRIMARIA);
        DrawText(label,80,(int)(oy+k*75+20),20,COR_TEXTO);
    }

    if (j->mostrando_feedback) {
        const char *msg = j->resp_selecionada < 0 ? "Tempo esgotado!"
                        : j->acertou ? "Correto! +10 pts" : "Errado!";
        Color mc = j->acertou ? COR_SUCESSO : COR_ERRO;
        DrawText(msg, 470, 624, 26, mc);
    } else {
        DrawText("Pressione 1, 2, 3 ou 4 para responder",380,624,20,COR_TEXTO);
    }
}

/* ── Telas: Resultados ───────────────────────────────────────────── */

void desenhar_resultado_adivinhacao(const EstadoUI *ui)
{
    DrawText("FIM DA MISSÃO", 400,80,48,COR_PRIMARIA);
    if (ui->partida_atual.venceu) {
        DrawText("MISSÃO CUMPRIDA!", 380,175,40,COR_SUCESSO);
        DrawText("Você acertou a frequência, astronauta!",230,258,26,COR_TEXTO);
    } else {
        DrawText("MISSÃO FRACASSADA!", 350,175,40,COR_ERRO);
        DrawText("Todas as tentativas foram esgotadas. De volta a Terra!",155,258,26,COR_TEXTO);
    }

    const char *pat = "Cadete";
    if (ui->dificuldade_selecionada==MEDIO)  pat="Piloto";
    if (ui->dificuldade_selecionada==DIFICIL) pat="Comandante";

    char linha_astronauta[128], linha_patente[128], linha_secreto[128];
    char linha_tentativas[128], linha_pontos[128];
    snprintf(linha_astronauta, sizeof(linha_astronauta), "Astronauta : %s", ui->nome_jogador);
    snprintf(linha_patente,    sizeof(linha_patente),    "Patente    : %s", pat);
    snprintf(linha_secreto,    sizeof(linha_secreto),    "Número Secreto: %d", ui->partida_atual.numero_secreto);
    snprintf(linha_tentativas, sizeof(linha_tentativas), "Tentativas : %d de %d",
             ui->partida_atual.tentativas_usadas, ui->partida_atual.max_tentativas);
    int pts = calcular_pontos(ui->dificuldade_selecionada,
                              ui->partida_atual.tentativas_usadas, ui->partida_atual.venceu);
    snprintf(linha_pontos, sizeof(linha_pontos), "Pontos ganhos: %d", pts);

    DrawText(linha_astronauta, 300, 328, 25, COR_TEXTO);
    DrawText(linha_patente,    300, 360, 25, COR_TEXTO);
    DrawText(linha_secreto,    300, 392, 25, COR_TEXTO);
    DrawText(linha_tentativas, 300, 424, 25, COR_TEXTO);
    DrawText(linha_pontos,     300, 456, 25, pts > 0 ? COR_SUCESSO : COR_ERRO);

    const char *dica=heuristica_adivinhacao(ui->partida_atual.tentativas_usadas,
                                             ui->partida_atual.max_tentativas,
                                             ui->partida_atual.venceu,
                                             ui->dificuldade_selecionada);
    DrawText(dica,120,500,17,COR_SECUNDARIA);
    desenhar_botao(400,540,400,80,"Voltar ao Menu (ESC)");
}

void desenhar_resultado_vs(const EstadoUI *ui)
{
    DrawText("FIM DA BATALHA DE SINAIS", 310,60,40,COR_PRIMARIA);

    /* Placar final */
    int vit_j1 = ui->vs_rodadas_vencidas[0];
    int vit_j2 = ui->vs_rodadas_vencidas[1];
    const char *venc    = vit_j1 > vit_j2 ? ui->nome_jogador : vit_j2 > vit_j1 ? ui->nome_jogador2 : "EMPATE";
    Color cor_venc = vit_j1 > vit_j2 ? COR_SUCESSO : vit_j2 > vit_j1 ? COR_AVISO : (Color){200, 200, 200, 255};

    char placar[128];
    snprintf(placar, sizeof(placar), "VENCEDOR: %s", venc);
    DrawText(placar, 380, 130, 34, cor_venc);

    char linha_j1[64], linha_j2[64];
    snprintf(linha_j1, sizeof(linha_j1), "%s: %d rodada(s) | %d pts", ui->nome_jogador,  vit_j1, ui->vs_pontos[0]);
    snprintf(linha_j2, sizeof(linha_j2), "%s: %d rodada(s) | %d pts", ui->nome_jogador2, vit_j2, ui->vs_pontos[1]);
    DrawText(linha_j1, 200, 220, 26, COR_SUCESSO);
    DrawText(linha_j2, 200, 260, 26, COR_AVISO);

    desenhar_botao(400,540,400,80,"Voltar ao Menu (ESC)");
}

void desenhar_resultado_memoria(const EstadoUI *ui)
{
    DrawText("MISSÃO CONCLUÍDA!", 390,78,44,COR_SUCESSO);
    char saud[128];
    snprintf(saud,sizeof(saud),"Parabéns, %s! Todos os pares encontrados!",ui->nome_jogador);
    DrawText(saud,100,150,24,COR_TEXTO);

    int pts = calcular_pontos_memoria(ui->jogo_memoria.tentativas);
    char linha_astronauta[128], linha_pontuacao[64], linha_pares[64];
    char linha_jogadas[64],     linha_pontos_missao[64];
    snprintf(linha_astronauta,    sizeof(linha_astronauta),    "Astronauta       : %s", ui->nome_jogador);
    snprintf(linha_pontuacao,     sizeof(linha_pontuacao),     "Pontuação Total  : %d/80", ui->jogo_memoria.pontuacao);
    snprintf(linha_pares,         sizeof(linha_pares),         "Pares            : %d/8", ui->jogo_memoria.pares_encontrados);
    snprintf(linha_jogadas,       sizeof(linha_jogadas),       "Jogadas          : %d", ui->jogo_memoria.tentativas);
    snprintf(linha_pontos_missao, sizeof(linha_pontos_missao), "Pontos de Missão : %d pts", pts);

    DrawText(linha_astronauta,    300, 228, 28, COR_TEXTO);
    DrawText(linha_pontuacao,     300, 268, 28, COR_TEXTO);
    DrawText(linha_pares,         300, 308, 28, COR_TEXTO);
    DrawText(linha_jogadas,       300, 348, 28, COR_TEXTO);
    DrawText(linha_pontos_missao, 300, 388, 28, pts > 60 ? COR_SUCESSO : COR_SECUNDARIA);

    const char *dica=heuristica_memoria(ui->jogo_memoria.tentativas,pts);
    DrawText(dica,120,430,17,COR_SECUNDARIA);
    DrawText("Resultado salvo!",460,462,20,COR_TEXTO);
    desenhar_botao(400,500,400,75,"Voltar ao Menu (ESC)");
}

void desenhar_resultado_memoria_vs(const EstadoUI *ui)
{
    DrawText("1v1 MAPAS ESTELARES - RESULTADO",230,60,36,COR_PRIMARIA);

    int pts_j1 = ui->mem_vs_pontos[0];
    int pts_j2 = ui->mem_vs_pontos[1];
    const char *venc    = pts_j1 > pts_j2 ? ui->nome_jogador : pts_j2 > pts_j1 ? ui->nome_jogador2 : "EMPATE";
    Color cor_venc = pts_j1 > pts_j2 ? COR_SUCESSO : pts_j2 > pts_j1 ? COR_AVISO : (Color){200, 200, 200, 255};
    char placar[128];
    snprintf(placar, sizeof(placar), "VENCEDOR: %s", venc);
    DrawText(placar, 400, 130, 32, cor_venc);

    char linha_j1[128], linha_j2[128];
    snprintf(linha_j1, sizeof(linha_j1), "%s: %d pares | %d pts", ui->nome_jogador,  ui->mem_vs_pares[0], pts_j1);
    snprintf(linha_j2, sizeof(linha_j2), "%s: %d pares | %d pts", ui->nome_jogador2, ui->mem_vs_pares[1], pts_j2);
    DrawText(linha_j1, 200, 220, 26, COR_SUCESSO);
    DrawText(linha_j2, 200, 260, 26, COR_AVISO);

    DrawText("Resultado salvo!",490,360,20,COR_TEXTO);
    desenhar_botao(400,500,400,75,"Voltar ao Menu (ESC)");
}

void desenhar_resultado_logica(const EstadoUI *ui)
{
    const JogoLogica *j = &ui->logica;
    DrawText("PROTOCOLO LÓGICO - FIM",360,78,40,COR_PRIMARIA);

    int pts = calcular_pontos_logica(j);
    char linha_astronauta[128], linha_acertos_vf[128];
    char linha_classif[128],    linha_pontos[128];
    snprintf(linha_astronauta, sizeof(linha_astronauta), "Astronauta  : %s", ui->nome_jogador);
    snprintf(linha_acertos_vf, sizeof(linha_acertos_vf), "Acertos V/F : %d/%d", j->acertos_vf,   j->questoes_total);
    snprintf(linha_classif,    sizeof(linha_classif),    "Classif.    : %d/%d", j->acertos_class, j->questoes_total);
    snprintf(linha_pontos,     sizeof(linha_pontos),     "Pontos      : %d", pts);

    DrawText(linha_astronauta, 300, 200, 26, COR_TEXTO);
    DrawText(linha_acertos_vf, 300, 240, 26, COR_TEXTO);
    DrawText(linha_classif,    300, 280, 26, COR_TEXTO);
    DrawText(linha_pontos,     300, 320, 26, pts > 80 ? COR_SUCESSO : COR_SECUNDARIA);
    DrawText("Resultado salvo!",460,380,20,COR_TEXTO);
    desenhar_botao(400,450,400,75,"Voltar ao Menu (ESC)");
}

void desenhar_resultado_precedencia(const EstadoUI *ui)
{
    const JogoPrecedencia *j = &ui->precedencia;
    DrawText("HIERARQUIA DE COMANDOS - FIM",260,78,38,COR_PRIMARIA);

    int pts = calcular_pontos_prec(j);
    char linha_astronauta[128], linha_acertos[128], linha_pontos[128];
    snprintf(linha_astronauta, sizeof(linha_astronauta), "Astronauta : %s", ui->nome_jogador);
    snprintf(linha_acertos,    sizeof(linha_acertos),    "Acertos    : %d/%d", j->acertos, j->questoes_total);
    snprintf(linha_pontos,     sizeof(linha_pontos),     "Pontos     : %d", pts);
    DrawText(linha_astronauta, 300, 200, 26, COR_TEXTO);
    DrawText(linha_acertos,    300, 240, 26, COR_TEXTO);
    DrawText(linha_pontos,     300, 280, 26, pts > 80 ? COR_SUCESSO : COR_SECUNDARIA);
    DrawText("Resultado salvo!",460,340,20,COR_TEXTO);
    desenhar_botao(400,410,400,75,"Voltar ao Menu (ESC)");
}

/* ── Telas: Estatísticas e Histórico ────────────────────────────── */

void desenhar_menu_jogo(void) {}

void desenhar_estatisticas(EstadoUI *ui)
{
    if (!ui->stats_carregadas) {
        preparar_linhas_estatisticas(ui->stats_linhas, &ui->stats_n_linhas);
        ui->stats_carregadas = true;
    }
    DrawText("ESTATÍSTICAS DE MISSÕES",280,30,38,COR_PRIMARIA);
    DrawLine(50,80,1150,80,COR_PRIMARIA);
    int y=100;
    for (int i=0; i<ui->stats_n_linhas && y<720; i++,y+=22)
        DrawText(ui->stats_linhas[i],60,y,18,COR_TEXTO);
    desenhar_botao(400,730,400,55,"Voltar ao Menu (ESC)");
}

void desenhar_historico(EstadoUI *ui)
{
    if (!ui->hist_carregado) {
        ui->hist_adiv_n    = carregar_historico(ui->hist_adiv, 10);
        ui->hist_mem_n     = carregar_historico_memoria(ui->hist_mem, 10);
        ui->hist_vs_n      = carregar_historico_vs(ui->hist_vs, 10);
        ui->hist_mem_vs_n  = carregar_historico_memoria_vs(ui->hist_mem_vs, 10);
        ui->hist_logica_n  = carregar_historico_puzzle(ui->hist_logica, 10, "logica");
        ui->hist_prec_n    = carregar_historico_puzzle(ui->hist_prec,   10, "precedencia");
        preparar_resumo_adivinhacao(ui->hist_resumo_adiv, sizeof(ui->hist_resumo_adiv));
        preparar_resumo_memoria(ui->hist_resumo_mem, sizeof(ui->hist_resumo_mem));
        ui->hist_carregado = true;
    }

    DrawText("HISTÓRICO DE MISSÕES", 330,20,38,COR_PRIMARIA);
    DrawLine(50,68,1150,68,COR_PRIMARIA);

    const char *difs[]={"Cadete","Piloto","Comandante"};

/* ── Col 1 (x=20): Adivinhação Solo + VS Adivinhação ─────────────── */
#define X1 20
    DrawText("Adivinhação Solo",  X1,78,18,COR_SECUNDARIA);
    DrawText(ui->hist_resumo_adiv,X1,98,12,COR_TEXTO);
    DrawLine(X1,114,375,114,COR_SECUNDARIA);
    if (ui->hist_adiv_n<=0)
        DrawText("Sem registros.",X1,118,15,COR_TEXTO);
    else {
        int y=118;
        for (int i=ui->hist_adiv_n-1; i>=0 && y<318; i--,y+=20) {
            RegistroPartida *r=&ui->hist_adiv[i];
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %-10s %s %d/%dt %dpts",
                     r->data,r->nome,difs[r->dificuldade],
                     r->tentativas_usadas,r->max_tentativas,r->pontos);
            DrawText(ln,X1,y,13,r->venceu?COR_SUCESSO:COR_ERRO);
        }
    }

    DrawLine(X1,326,375,326,COR_BOTAO);
    DrawText("Batalha de Sinais VS",X1,334,18,COR_SECUNDARIA);
    DrawLine(X1,354,375,354,COR_SECUNDARIA);
    if (ui->hist_vs_n<=0)
        DrawText("Sem registros.",X1,358,15,COR_TEXTO);
    else {
        int y=358;
        for (int i=ui->hist_vs_n-1; i>=0 && y<560; i--,y+=20) {
            RegistroVS *r=&ui->hist_vs[i];
            const char *venc = r->vencedor==1?r->nome1:r->vencedor==2?r->nome2:"Empate";
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %s vs %s | %s",
                     r->data,r->nome1,r->nome2,venc);
            DrawText(ln,X1,y,13,COR_TEXTO);
        }
    }

/* ── Col 2 (x=405): Memória Solo + VS Memória ────────────────────── */
#define X2 405
    DrawText("Mapas Estelares Solo",  X2,78,18,COR_SECUNDARIA);
    DrawText(ui->hist_resumo_mem,     X2,98,12,COR_TEXTO);
    DrawLine(X2,114,780,114,COR_SECUNDARIA);
    if (ui->hist_mem_n<=0)
        DrawText("Sem registros.",X2,118,15,COR_TEXTO);
    else {
        int y=118;
        for (int i=ui->hist_mem_n-1; i>=0 && y<318; i--,y+=20) {
            RegistroMemoria *r=&ui->hist_mem[i];
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %-10s %djog %dpts",
                     r->data,r->nome,r->tentativas,r->pontos);
            DrawText(ln,X2,y,13,COR_TEXTO);
        }
    }

    DrawLine(X2,326,780,326,COR_BOTAO);
    DrawText("1v1 Mapas Estelares", X2,334,18,COR_SECUNDARIA);
    DrawLine(X2,354,780,354,COR_SECUNDARIA);
    if (ui->hist_mem_vs_n<=0)
        DrawText("Sem registros.",X2,358,15,COR_TEXTO);
    else {
        int y=358;
        for (int i=ui->hist_mem_vs_n-1; i>=0 && y<560; i--,y+=20) {
            RegistroMemoriaVS *r=&ui->hist_mem_vs[i];
            const char *venc = r->pontos1>r->pontos2?r->nome1:r->pontos2>r->pontos1?r->nome2:"Empate";
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %s %dp vs %s %dp | %s",
                     r->data,r->nome1,r->pares1,r->nome2,r->pares2,venc);
            DrawText(ln,X2,y,13,COR_TEXTO);
        }
    }

/* ── Col 3 (x=795): Lógica + Precedência ─────────────────────────── */
#define X3 795
    DrawText("Protocolo Lógico",X3,78,18,COR_SECUNDARIA);
    DrawLine(X3,98,1170,98,COR_SECUNDARIA);
    if (ui->hist_logica_n<=0)
        DrawText("Sem registros.",X3,102,15,COR_TEXTO);
    else {
        int y=102;
        for (int i=ui->hist_logica_n-1; i>=0 && y<318; i--,y+=20) {
            RegistroPuzzle *r=&ui->hist_logica[i];
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %-10s %d/%d %dpts",
                     r->data,r->nome,r->acertos,r->total,r->pontos);
            DrawText(ln,X3,y,13,COR_TEXTO);
        }
    }

    DrawLine(X3,326,1170,326,COR_BOTAO);
    DrawText("Hierarquia de Comandos",X3,334,18,COR_SECUNDARIA);
    DrawLine(X3,354,1170,354,COR_SECUNDARIA);
    if (ui->hist_prec_n<=0)
        DrawText("Sem registros.",X3,358,15,COR_TEXTO);
    else {
        int y=358;
        for (int i=ui->hist_prec_n-1; i>=0 && y<560; i--,y+=20) {
            RegistroPuzzle *r=&ui->hist_prec[i];
            char ln[100];
            snprintf(ln,sizeof(ln),"%s %-10s %d/%d %dpts",
                     r->data,r->nome,r->acertos,r->total,r->pontos);
            DrawText(ln,X3,y,13,COR_TEXTO);
        }
    }

#undef X1
#undef X2
#undef X3

    DrawLine(50,570,1150,570,COR_BOTAO);
    DrawText("Estatísticas detalhadas disponíveis na tela de Estatísticas.",
             160,580,16,COR_TEXTO);
    desenhar_botao(400,620,400,55,"Voltar ao Menu (ESC)");
}

/* ── Cliques de memória solo ────────────────────────────────────── */

void processar_clique_mouse_memoria(EstadoUI *ui)
{
    if (ui->aguardando_ocultar) return;
    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

    Vector2 mouse = GetMousePosition();
    int tamanho_casa = 80, espacamento = 8, origem_x = 200, origem_y = 145;

    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
        int pos = i * 4 + j;
        float x = (float)(origem_x + (tamanho_casa + espacamento) * j);
        float y = (float)(origem_y + (tamanho_casa + espacamento) * i);
        Rectangle c = {x, y, (float)tamanho_casa, (float)tamanho_casa};
        if (!CheckCollisionPointRec(mouse,c)) continue;
        if (ui->jogo_memoria.acertadas[pos]) return;
        int p=pos+1;
        if (ui->clique_casa1==0) {
            if (!ui->jogo_memoria.reveladas[pos]) {
                ui->jogo_memoria.reveladas[pos]=true;
                ui->clique_casa1=p;
            }
        } else if (p!=ui->clique_casa1 && !ui->jogo_memoria.reveladas[pos]) {
            ui->clique_casa2=p;
            bool ok=fazer_jogada(&ui->jogo_memoria,ui->clique_casa1,ui->clique_casa2);
            if (ok) {
                /* bônus de 10s por par */
                ui->timer_memoria += TIMER_MEM_BONUS_SEG;
                ui->clique_casa1=0; ui->clique_casa2=0;
                if (jogo_memoria_finalizado(&ui->jogo_memoria))
                    ui->estado_atual=ESTADO_RESULTADO_MEMORIA;
            } else {
                ui->aguardando_ocultar=true;
                ui->timer_ocultar=90;
            }
        }
        return;
    }
}

/* ── Cliques de memória VS ──────────────────────────────────────── */

void processar_clique_mouse_memoria_vs(EstadoUI *ui)
{
    if (ui->mem_vs_aguardando) return;
    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

    Vector2 mouse = GetMousePosition();
    int tamanho_casa = 80, espacamento = 8, origem_x = 280, origem_y = 145;
    int jogador_ativo = ui->mem_vs_jogador;

    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
        int pos = i * 4 + j;
        float x = (float)(origem_x + (tamanho_casa + espacamento) * j);
        float y = (float)(origem_y + (tamanho_casa + espacamento) * i);
        Rectangle c = {x, y, (float)tamanho_casa, (float)tamanho_casa};
        if (!CheckCollisionPointRec(mouse,c)) continue;
        if (ui->mem_vs_jogo.acertadas[pos]) return;
        int p=pos+1;
        if (ui->mem_vs_clique1==0) {
            if (!ui->mem_vs_jogo.reveladas[pos]) {
                ui->mem_vs_jogo.reveladas[pos]=true;
                ui->mem_vs_clique1=p;
            }
        } else if (p!=ui->mem_vs_clique1 && !ui->mem_vs_jogo.reveladas[pos]) {
            ui->mem_vs_clique2=p;
            bool ok = fazer_jogada(&ui->mem_vs_jogo, ui->mem_vs_clique1, ui->mem_vs_clique2);
            if (ok) {
                ui->mem_vs_pares[jogador_ativo]++;
                ui->mem_vs_pontos[jogador_ativo] = ui->mem_vs_jogo.pontuacao;
                ui->mem_vs_timer[jogador_ativo] += TIMER_MEM_BONUS_SEG;
                ui->mem_vs_clique1=0; ui->mem_vs_clique2=0;
                if (jogo_memoria_finalizado(&ui->mem_vs_jogo))
                    ui->estado_atual=ESTADO_RESULTADO_MEMORIA_VS;
                /* jogador que acertou continua; não troca turno */
            } else {
                ui->mem_vs_aguardando=true;
                ui->mem_vs_timer_ocultar=90;
            }
        }
        return;
    }
}

/* ── Processamento de entrada ───────────────────────────────────── */

static void iniciar_jogo_modo(EstadoUI *ui, ModoJogo modo)
{
    switch (modo) {
    case MODO_SOLO_ADIV:
        ui->estado_atual = ESTADO_DIFICULDADE;
        break;
    case MODO_VS_ADIV:
        ui->estado_atual = ESTADO_DIFICULDADE;
        break;
    case MODO_SOLO_MEM:
        ui->jogo_memoria       = inicializar_jogo_memoria();
        ui->clique_casa1       = 0; ui->clique_casa2=0;
        ui->aguardando_ocultar = false; ui->timer_ocultar=0;
        ui->memoria_salva      = false;
        ui->timer_memoria      = TIMER_MEM_BASE_SEG;
        ui->timer_memoria_ativo = true;
        ui->estado_atual       = ESTADO_JOGANDO_MEMORIA;
        break;
    case MODO_VS_MEM:
        ui->mem_vs_jogo       = inicializar_jogo_memoria();
        ui->mem_vs_jogador    = 0;
        ui->mem_vs_pares[0]   = ui->mem_vs_pares[1]=0;
        ui->mem_vs_pontos[0]  = ui->mem_vs_pontos[1]=0;
        ui->mem_vs_timer[0]   = TIMER_MEM_BASE_SEG;
        ui->mem_vs_timer[1]   = TIMER_MEM_BASE_SEG;
        ui->mem_vs_clique1    = 0; ui->mem_vs_clique2=0;
        ui->mem_vs_aguardando = false;
        ui->mem_vs_timer_ocultar=0;
        ui->mem_vs_salvo      = false;
        ui->estado_atual      = ESTADO_JOGANDO_MEMORIA_VS;
        break;
    case MODO_LOGICA:
        ui->estado_atual = ESTADO_DIFICULDADE;
        break;
    case MODO_PRECEDENCIA:
        ui->estado_atual = ESTADO_DIFICULDADE;
        break;
    }
}

static void processar_menu_principal(EstadoUI *ui)
{
    static const int TECLAS_MENU[N_ITENS_MENU] = {
        KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE,
        KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE
    };

    int escolha = 0;
    for (int i = 0; i < N_ITENS_MENU; i++)
    {
        Rectangle r = {ITENS_MENU[i].x, ITENS_MENU[i].y, ITENS_MENU[i].w, ITENS_MENU[i].h};
        if (IsKeyReleased(TECLAS_MENU[i]) || clique_em_rect(r))
        {
            escolha = i + 1;
            break;
        }
    }
    if (!escolha) return;

    ModoJogo modos[] = {
        MODO_SOLO_ADIV, MODO_VS_ADIV, MODO_SOLO_MEM, MODO_VS_MEM,
        MODO_LOGICA, MODO_PRECEDENCIA
    };

    if (escolha >= 1 && escolha <= 6) {
        ui->modo_pendente = modos[escolha-1];
        memset(ui->nome_jogador,0,sizeof(ui->nome_jogador));
        ui->nome_indice=0;
        memset(ui->nome_jogador2,0,sizeof(ui->nome_jogador2));
        ui->nome_indice2=0;
        ui->estado_atual = ESTADO_INSERIR_NOME;
    } else if (escolha==7) {
        ui->stats_carregadas=false;
        ui->estado_atual=ESTADO_ESTATISTICAS;
    } else if (escolha==8) {
        ui->hist_carregado=false;
        ui->estado_atual=ESTADO_HISTORICO;
    } else if (escolha==9) {
        ui->estado_atual=ESTADO_SAIR;
    }
}

static void processar_nome(char *nome, int *idx, int max_len)
{
    int key=GetCharPressed();
    while (key>0) {
        if (key>=32 && key<127 && *idx<max_len-1) {
            nome[(*idx)++]=(char)key; nome[*idx]='\0';
        }
        key=GetCharPressed();
    }
    if (IsKeyReleased(KEY_BACKSPACE) && *idx>0) nome[--(*idx)]='\0';
}

void processar_entrada(EstadoUI *ui)
{
    switch (ui->estado_atual) {

    case ESTADO_MENU_PRINCIPAL:
    case ESTADO_MENU_JOGO:
        processar_menu_principal(ui);
        break;

    case ESTADO_INSERIR_NOME:
    {
        processar_nome(ui->nome_jogador,&ui->nome_indice,64);
        if (IsKeyReleased(KEY_ENTER)||clique_em_rect((Rectangle){400,420,400,70})) {
            if (ui->nome_indice==0) {
                strcpy(ui->nome_jogador,"Astronauta");
                ui->nome_indice=(int)strlen("Astronauta");
            }
            bool precisa_p2 = (ui->modo_pendente==MODO_VS_ADIV ||
                               ui->modo_pendente==MODO_VS_MEM);
            if (precisa_p2) {
                ui->estado_atual = ESTADO_INSERIR_NOME_P2;
            } else {
                iniciar_jogo_modo(ui, ui->modo_pendente);
            }
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;
    }

    case ESTADO_INSERIR_NOME_P2:
    {
        processar_nome(ui->nome_jogador2,&ui->nome_indice2,64);
        if (IsKeyReleased(KEY_ENTER)||clique_em_rect((Rectangle){400,420,400,70})) {
            if (ui->nome_indice2==0) {
                strcpy(ui->nome_jogador2,"Astronauta 2");
                ui->nome_indice2=(int)strlen("Astronauta 2");
            }
            iniciar_jogo_modo(ui, ui->modo_pendente);
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_INSERIR_NOME;
        break;
    }

    case ESTADO_DIFICULDADE:
    {
        Dificuldade dif=FACIL; bool escolheu=false;
        if (IsKeyReleased(KEY_ONE)  ||clique_em_rect((Rectangle){200,230,800,95})) { dif=FACIL;   escolheu=true; }
        if (IsKeyReleased(KEY_TWO)  ||clique_em_rect((Rectangle){200,380,800,95})) { dif=MEDIO;   escolheu=true; }
        if (IsKeyReleased(KEY_THREE)||clique_em_rect((Rectangle){200,530,800,95})) { dif=DIFICIL; escolheu=true; }

        if (escolheu) {
            ui->dificuldade_selecionada=dif;
            memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
            memset(ui->mensagem_erro,0,sizeof(ui->mensagem_erro));
            ui->entrada_numero=0; ui->indice_entrada=0;

            if (ui->modo_pendente==MODO_SOLO_ADIV) {
                ui->partida_atual  = iniciar_partida(dif);
                ui->partida_salva  = false;
                ui->timer_adiv     = TIMER_ADIV_SEG;
                ui->timer_adiv_ativo = true;
                ui->estado_atual   = ESTADO_JOGANDO_ADIVINHACAO;

            } else if (ui->modo_pendente==MODO_VS_ADIV) {
                ui->vs_partida       = iniciar_partida(dif);
                ui->vs_jogador_atual = 0;
                ui->vs_rodada        = 0;
                ui->vs_tentativas[0] = ui->vs_tentativas[1]=0;
                ui->vs_pontos[0]     = ui->vs_pontos[1]=0;
                ui->vs_rodadas_vencidas[0]=ui->vs_rodadas_vencidas[1]=0;
                ui->vs_rodada_acabou = false;
                ui->vs_jogo_acabou   = false;
                ui->vs_salvo         = false;
                ui->vs_timer         = TIMER_ADIV_SEG;
                ui->estado_atual     = ESTADO_JOGANDO_VS;

            } else if (ui->modo_pendente==MODO_LOGICA) {
                ui->logica       = inicializar_jogo_logica(dif);
                ui->logica_salva = false;
                ui->estado_atual = ESTADO_JOGANDO_LOGICA;

            } else if (ui->modo_pendente==MODO_PRECEDENCIA) {
                ui->precedencia       = inicializar_jogo_precedencia(dif);
                ui->precedencia_salva = false;
                ui->estado_atual      = ESTADO_JOGANDO_PRECEDENCIA;
            }
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_INSERIR_NOME;
        break;
    }

    /* ── Adivinhação solo ──────────────────────────────────── */
    case ESTADO_JOGANDO_ADIVINHACAO:
    {
        int key=GetCharPressed();
        while (key>0) {
            if (key>='0'&&key<='9'&&ui->indice_entrada<9) {
                ui->entrada_texto[ui->indice_entrada++]=(char)key;
                ui->entrada_texto[ui->indice_entrada]='\0';
            }
            key=GetCharPressed();
        }
        if (IsKeyReleased(KEY_BACKSPACE)&&ui->indice_entrada>0)
            ui->entrada_texto[--ui->indice_entrada]='\0';

        if (IsKeyReleased(KEY_ENTER)||clique_em_rect((Rectangle){140,470,420,60})) {
            if (ui->indice_entrada==0) {
                snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),"Digite um numero!");
            } else {
                int palpite = atoi(ui->entrada_texto);
                if (palpite < ui->partida_atual.min_range || palpite > ui->partida_atual.max_range) {
                    snprintf(ui->mensagem_erro, sizeof(ui->mensagem_erro),
                             "Fora do intervalo! %d a %d.",
                             ui->partida_atual.min_range, ui->partida_atual.max_range);
                } else {
                    ui->entrada_numero = palpite;
                    memset(ui->mensagem_erro, 0, sizeof(ui->mensagem_erro));
                    processar_palpite(&ui->partida_atual, palpite);
                    memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
                    ui->indice_entrada=0;
                    ui->timer_adiv = TIMER_ADIV_SEG;
                    if (partida_encerrada(&ui->partida_atual)) {
                        if (!ui->partida_salva) { salvar_partida_adivinhacao(ui); ui->partida_salva=true; }
                        ui->estado_atual=ESTADO_RESULTADO_ADIVINHACAO;
                    }
                }
            }
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_DIFICULDADE;
        break;
    }

    /* ── VS Adivinhação ────────────────────────────────────── */
    case ESTADO_JOGANDO_VS:
    {
        if (ui->vs_rodada_acabou) {
            /* espera ESC/Enter para avançar rodada ou encerrar */
            if (IsKeyReleased(KEY_ENTER)||IsKeyReleased(KEY_ESCAPE)) {
                if (ui->vs_jogo_acabou) {
                    if (!ui->vs_salvo) {
                        RegistroVS reg;
                        data_hoje(reg.data,sizeof(reg.data));
                        strncpy(reg.nome1,ui->nome_jogador,63);
                        strncpy(reg.nome2,ui->nome_jogador2,63);
                        reg.dificuldade = ui->dificuldade_selecionada;
                        reg.vitorias1   = ui->vs_rodadas_vencidas[0];
                        reg.vitorias2   = ui->vs_rodadas_vencidas[1];
                        reg.pontos1     = ui->vs_pontos[0];
                        reg.pontos2     = ui->vs_pontos[1];
                        int v0=ui->vs_rodadas_vencidas[0],v1=ui->vs_rodadas_vencidas[1];
                        reg.vencedor    = v0>v1?1:v1>v0?2:0;
                        salvar_partida_vs(&reg);
                        ui->vs_salvo=true;
                    }
                    ui->estado_atual=ESTADO_RESULTADO_VS;
                } else {
                    /* próxima rodada */
                    ui->vs_rodada++;
                    ui->vs_partida       = iniciar_partida(ui->dificuldade_selecionada);
                    ui->vs_tentativas[0] = ui->vs_tentativas[1]=0;
                    ui->vs_jogador_atual = 0;
                    ui->vs_rodada_acabou = false;
                    ui->vs_timer         = TIMER_ADIV_SEG;
                    memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
                    ui->indice_entrada=0;
                    memset(ui->mensagem_erro,0,sizeof(ui->mensagem_erro));
                }
            }
            break;
        }

        int jog = ui->vs_jogador_atual;
        int key=GetCharPressed();
        while (key>0) {
            if (key>='0'&&key<='9'&&ui->indice_entrada<9) {
                ui->entrada_texto[ui->indice_entrada++]=(char)key;
                ui->entrada_texto[ui->indice_entrada]='\0';
            }
            key=GetCharPressed();
        }
        if (IsKeyReleased(KEY_BACKSPACE)&&ui->indice_entrada>0)
            ui->entrada_texto[--ui->indice_entrada]='\0';

        if (IsKeyReleased(KEY_ENTER)||clique_em_rect((Rectangle){60,460,420,60})) {
            if (ui->indice_entrada==0) {
                snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),"Digite um numero!");
            } else {
                int palpite = atoi(ui->entrada_texto);
                if (palpite < ui->vs_partida.min_range || palpite > ui->vs_partida.max_range) {
                    snprintf(ui->mensagem_erro, sizeof(ui->mensagem_erro),
                             "Fora do intervalo %d a %d!",
                             ui->vs_partida.min_range, ui->vs_partida.max_range);
                } else {
                    ui->entrada_numero = palpite;
                    memset(ui->mensagem_erro, 0, sizeof(ui->mensagem_erro));
                    ui->vs_tentativas[jog]++;
                    Resultado res = processar_palpite(&ui->vs_partida, palpite);
                    memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
                    ui->indice_entrada=0;
                    ui->vs_timer=TIMER_ADIV_SEG;

                    if (res==ACERTOU) {
                        ui->vs_rodadas_vencidas[jog]++;
                        ui->vs_pontos[jog] += calcular_pontos(ui->dificuldade_selecionada,
                                                              ui->vs_tentativas[jog],true);
                        ui->vs_vencedor_rodada = jog+1;
                        ui->vs_rodada_acabou   = true;
                        ui->vs_jogo_acabou     = (ui->vs_rodada>=VS_MAX_RODADAS-1);
                        snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),
                                 "%s ACERTOU! Pressione Enter p/ continuar.",
                                 jog==0?ui->nome_jogador:ui->nome_jogador2);
                    } else {
                        /* verifica se ambos esgotaram tentativas */
                        bool ambos = ui->vs_tentativas[0]>=VS_MAX_TENTATIVAS &&
                                     ui->vs_tentativas[1]>=VS_MAX_TENTATIVAS;
                        if (ambos) {
                            ui->vs_vencedor_rodada=0;
                            ui->vs_rodada_acabou=true;
                            ui->vs_jogo_acabou=(ui->vs_rodada>=VS_MAX_RODADAS-1);
                            snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),
                                     "Empate! Ninguem acertou. Enter p/ continuar.");
                        } else {
                            /* alterna jogador (pula quem esgotou tentativas) */
                            int prox=(jog+1)%2;
                            if (ui->vs_tentativas[prox]>=VS_MAX_TENTATIVAS) prox=jog;
                            ui->vs_jogador_atual=prox;
                        }
                    }
                }
            }
        }
        break;
    }

    /* ── Memória solo ──────────────────────────────────────── */
    case ESTADO_JOGANDO_MEMORIA:
        processar_clique_mouse_memoria(ui);
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    /* ── 1v1 Memória ───────────────────────────────────────── */
    case ESTADO_JOGANDO_MEMORIA_VS:
        processar_clique_mouse_memoria_vs(ui);
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    /* ── Lógica ────────────────────────────────────────────── */
    case ESTADO_JOGANDO_LOGICA:
    {
        JogoLogica *j=&ui->logica;
        if (j->finalizado) { ui->estado_atual=ESTADO_RESULTADO_LOGICA; break; }

        if (j->fase==FASE_RESP_VF) {
            if (IsKeyReleased(KEY_V)||clique_em_rect((Rectangle){180,320,280,80}))
                responder_vf_logica(j,true);
            if (IsKeyReleased(KEY_F)||clique_em_rect((Rectangle){540,320,280,80}))
                responder_vf_logica(j,false);
        } else if (j->fase==FASE_CLASSIF) {
            if (IsKeyReleased(KEY_ONE)  ||clique_em_rect((Rectangle){ 60,360,340,75}))
                responder_classif_logica(j,CLASS_TAUTOLOGIA);
            if (IsKeyReleased(KEY_TWO)  ||clique_em_rect((Rectangle){430,360,340,75}))
                responder_classif_logica(j,CLASS_CONTRADICAO);
            if (IsKeyReleased(KEY_THREE)||clique_em_rect((Rectangle){800,360,340,75}))
                responder_classif_logica(j,CLASS_CONTINGENCIA);
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;
    }

    /* ── Precedência ───────────────────────────────────────── */
    case ESTADO_JOGANDO_PRECEDENCIA:
    {
        JogoPrecedencia *j=&ui->precedencia;
        if (j->finalizado) { ui->estado_atual=ESTADO_RESULTADO_PRECEDENCIA; break; }

        if (!j->mostrando_feedback) {
            float oy=310;
            for (int k=0;k<4;k++) {
                if (IsKeyReleased(KEY_ONE+k)||clique_em_rect((Rectangle){60,(float)(oy+k*75),1080,65}))
                    responder_precedencia(j,k);
            }
        }
        if (IsKeyReleased(KEY_ESCAPE)) ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;
    }

    /* ── Resultados ────────────────────────────────────────── */
    case ESTADO_RESULTADO_ADIVINHACAO:
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,540,400,80}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_VS:
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,540,400,80}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_MEMORIA:
        if (!ui->memoria_salva) { salvar_resultado_memoria(ui); ui->memoria_salva=true; }
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,500,400,75}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_MEMORIA_VS:
        if (!ui->mem_vs_salvo) {
            RegistroMemoria r1,r2;
            data_hoje(r1.data,sizeof(r1.data));
            data_hoje(r2.data,sizeof(r2.data));
            strncpy(r1.nome,ui->nome_jogador,63);
            strncpy(r2.nome,ui->nome_jogador2,63);
            r1.pontuacao=ui->mem_vs_pares[0];
            r2.pontuacao=ui->mem_vs_pares[1];
            r1.tentativas=ui->mem_vs_jogo.tentativas;
            r2.tentativas=ui->mem_vs_jogo.tentativas;
            r1.pontos=ui->mem_vs_pontos[0];
            r2.pontos=ui->mem_vs_pontos[1];
            salvar_partida_memoria_vs(&r1,&r2);
            ui->mem_vs_salvo=true;
        }
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,500,400,75}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_LOGICA:
        if (!ui->logica_salva) {
            RegistroPuzzle r;
            data_hoje(r.data,sizeof(r.data));
            strncpy(r.nome,ui->nome_jogador,63);
            r.acertos=ui->logica.acertos_vf+ui->logica.acertos_class;
            r.total  =ui->logica.questoes_total*2;
            r.pontos =calcular_pontos_logica(&ui->logica);
            strncpy(r.modo,"logica",sizeof(r.modo)-1);
            salvar_puzzle(&r);
            ui->logica_salva=true;
        }
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,450,400,75}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_RESULTADO_PRECEDENCIA:
        if (!ui->precedencia_salva) {
            RegistroPuzzle r;
            data_hoje(r.data,sizeof(r.data));
            strncpy(r.nome,ui->nome_jogador,63);
            r.acertos=ui->precedencia.acertos;
            r.total  =ui->precedencia.questoes_total;
            r.pontos =calcular_pontos_prec(&ui->precedencia);
            strncpy(r.modo,"precedencia",sizeof(r.modo)-1);
            salvar_puzzle(&r);
            ui->precedencia_salva=true;
        }
        if (IsKeyReleased(KEY_ESCAPE)||IsKeyReleased(KEY_ENTER)||
            clique_em_rect((Rectangle){400,410,400,75}))
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        break;

    case ESTADO_ESTATISTICAS:
        if (IsKeyReleased(KEY_ESCAPE)||clique_em_rect((Rectangle){400,730,400,55})) {
            ui->stats_carregadas=false;
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        }
        break;

    case ESTADO_HISTORICO:
        if (IsKeyReleased(KEY_ESCAPE)||clique_em_rect((Rectangle){400,620,400,55})) {
            ui->hist_carregado=false;
            ui->estado_atual=ESTADO_MENU_PRINCIPAL;
        }
        break;

    default: break;
    }
}

/* ── Atualização lógica (timers) ────────────────────────────────── */

void atualizar_ui(EstadoUI *ui)
{
    double dt = GetFrameTime();

    /* Timer de adivinhação solo */
    if (ui->estado_atual == ESTADO_JOGANDO_ADIVINHACAO && ui->timer_adiv_ativo) {
        ui->timer_adiv -= dt;
        if (ui->timer_adiv <= 0.0) {
            ui->timer_adiv = TIMER_ADIV_SEG;
            /* tempo esgotado = tentativa desperdiçada (sem palpite real) */
            ui->partida_atual.tentativas_usadas++;
            if (ui->partida_atual.tentativas_usadas >= ui->partida_atual.max_tentativas) {
                if (!ui->partida_salva) { salvar_partida_adivinhacao(ui); ui->partida_salva=true; }
                ui->estado_atual = ESTADO_RESULTADO_ADIVINHACAO;
            }
            memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
            ui->indice_entrada=0;
            snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),"Tempo esgotado! Tentativa perdida.");
        }
    }

    /* Timer de VS adivinhação */
    if (ui->estado_atual == ESTADO_JOGANDO_VS && !ui->vs_rodada_acabou) 
    {
        ui->vs_timer -= dt;
        if (ui->vs_timer <= 0.0) {
            ui->vs_timer = TIMER_ADIV_SEG;
            int jog=ui->vs_jogador_atual;
            ui->vs_tentativas[jog]++;
            memset(ui->entrada_texto,0,sizeof(ui->entrada_texto));
            ui->indice_entrada=0;
            snprintf(ui->mensagem_erro,sizeof(ui->mensagem_erro),
                     "Tempo de %s esgotado!",jog==0?ui->nome_jogador:ui->nome_jogador2);

            bool ambos = ui->vs_tentativas[0]>=VS_MAX_TENTATIVAS &&
                         ui->vs_tentativas[1]>=VS_MAX_TENTATIVAS;
            if (ambos) {
                ui->vs_vencedor_rodada=0;
                ui->vs_rodada_acabou=true;
                ui->vs_jogo_acabou=(ui->vs_rodada>=VS_MAX_RODADAS-1);
            } else {
                int prox=(jog+1)%2;
                if (ui->vs_tentativas[prox]>=VS_MAX_TENTATIVAS) prox=jog;
                ui->vs_jogador_atual=prox;
            }
        }
    }

    /* Timer de memória solo */
    if (ui->estado_atual == ESTADO_JOGANDO_MEMORIA && ui->timer_memoria_ativo) {
        if (!ui->aguardando_ocultar) {
            ui->timer_memoria -= dt;
            if (ui->timer_memoria <= 0.0) {
                ui->timer_memoria = 0.0;
                /* tempo esgotado: vai para resultado sem completar */
                if (!ui->memoria_salva) { salvar_resultado_memoria(ui); ui->memoria_salva=true; }
                ui->estado_atual=ESTADO_RESULTADO_MEMORIA;
            }
        }
    }

    /* Ocultar cartas memória solo */
    if (ui->estado_atual == ESTADO_JOGANDO_MEMORIA && ui->aguardando_ocultar) {
        ui->timer_ocultar--;
        if (ui->timer_ocultar <= 0) {
            if (ui->clique_casa1>0) ui->jogo_memoria.reveladas[ui->clique_casa1-1]=false;
            if (ui->clique_casa2>0) ui->jogo_memoria.reveladas[ui->clique_casa2-1]=false;
            ui->aguardando_ocultar=false;
            ui->clique_casa1=0; ui->clique_casa2=0;
        }
    }

    /* Timer de memória VS */
    if (ui->estado_atual == ESTADO_JOGANDO_MEMORIA_VS && !ui->mem_vs_aguardando) {
        int jog=ui->mem_vs_jogador;
        ui->mem_vs_timer[jog] -= dt;
        if (ui->mem_vs_timer[jog] <= 0.0) {
            ui->mem_vs_timer[jog] = 0.0;
            /* timer deste jogador esgotou: passa o turno */
            ui->mem_vs_jogador = (jog+1)%2;
            ui->mem_vs_clique1=0; ui->mem_vs_clique2=0;
        }
        /* se ambos esgotaram */
        if (ui->mem_vs_timer[0]<=0.0 && ui->mem_vs_timer[1]<=0.0)
            ui->estado_atual=ESTADO_RESULTADO_MEMORIA_VS;
    }

    /* Ocultar cartas memória VS */
    if (ui->estado_atual == ESTADO_JOGANDO_MEMORIA_VS && ui->mem_vs_aguardando) {
        ui->mem_vs_timer_ocultar--;
        if (ui->mem_vs_timer_ocultar<=0) {
            if (ui->mem_vs_clique1>0) ui->mem_vs_jogo.reveladas[ui->mem_vs_clique1-1]=false;
            if (ui->mem_vs_clique2>0) ui->mem_vs_jogo.reveladas[ui->mem_vs_clique2-1]=false;
            ui->mem_vs_aguardando=false;
            ui->mem_vs_clique1=0; ui->mem_vs_clique2=0;
            /* erra o par: passa turno */
            ui->mem_vs_jogador=(ui->mem_vs_jogador+1)%2;
        }
    }

    /* Timer de lógica */
    if (ui->estado_atual == ESTADO_JOGANDO_LOGICA)
        atualizar_timer_logica(&ui->logica, dt);

    /* Timer de precedência */
    if (ui->estado_atual == ESTADO_JOGANDO_PRECEDENCIA)
        atualizar_timer_prec(&ui->precedencia, dt);
}

/* ── Despacho de renderização ───────────────────────────────────── */

void desenhar_ui(EstadoUI *ui)
{
    switch (ui->estado_atual) {
    case ESTADO_MENU_PRINCIPAL:
    case ESTADO_MENU_JOGO:         desenhar_menu_principal();         break;
    case ESTADO_INSERIR_NOME:      desenhar_inserir_nome(ui);         break;
    case ESTADO_INSERIR_NOME_P2:   desenhar_inserir_nome_p2(ui);      break;
    case ESTADO_DIFICULDADE:       desenhar_menu_dificuldade(ui);     break;
    case ESTADO_JOGANDO_ADIVINHACAO: desenhar_jogo_adivinhacao(ui);   break;
    case ESTADO_JOGANDO_VS:          desenhar_jogo_vs(ui);            break;
    case ESTADO_JOGANDO_MEMORIA:     desenhar_jogo_memoria(ui);       break;
    case ESTADO_JOGANDO_MEMORIA_VS:  desenhar_jogo_memoria_vs(ui);    break;
    case ESTADO_JOGANDO_LOGICA:      desenhar_jogo_logica(ui);        break;
    case ESTADO_JOGANDO_PRECEDENCIA: desenhar_jogo_precedencia(ui);   break;
    case ESTADO_RESULTADO_ADIVINHACAO: desenhar_resultado_adivinhacao(ui); break;
    case ESTADO_RESULTADO_VS:          desenhar_resultado_vs(ui);         break;
    case ESTADO_RESULTADO_MEMORIA:     desenhar_resultado_memoria(ui);    break;
    case ESTADO_RESULTADO_MEMORIA_VS:  desenhar_resultado_memoria_vs(ui); break;
    case ESTADO_RESULTADO_LOGICA:      desenhar_resultado_logica(ui);     break;
    case ESTADO_RESULTADO_PRECEDENCIA: desenhar_resultado_precedencia(ui);break;
    case ESTADO_ESTATISTICAS:          desenhar_estatisticas(ui);         break;
    case ESTADO_HISTORICO:             desenhar_historico(ui);            break;
    default: break;
    }
}

/* ── Loop principal ─────────────────────────────────────────────── */

void executar_frontend(void)
{
    inicializar_raylib();
    InitMusica();

    EstadoUI ui;
    memset(&ui, 0, sizeof(EstadoUI));
    ui.estado_atual = ESTADO_MENU_PRINCIPAL;

    while (!WindowShouldClose() && ui.estado_atual != ESTADO_SAIR) {
        UpdateMusica();
        processar_entrada(&ui);
        atualizar_ui(&ui);

        BeginDrawing();
        ClearBackground(COR_FUNDO);
        desenhar_ui(&ui);
        EndDrawing();
    }

    UnloadMusica();
    CloseWindow();
}

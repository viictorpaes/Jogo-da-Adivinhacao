#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

/* Inclusão condicional para resolver o UTF-8 no Windows */
#ifdef _WIN32
#include <windows.h>
#endif

/* ==========================================================================
 * INCLUSÃO DOS MÓDULOS
 * ========================================================================== */
#include "include/tipos.h"
#include "utils/utils.h"
#include "ui/menu.h"
#include "game/jogo.h"
#include "history/historico.h"

/* 
 * NOTA: Descomente os headers abaixo quando for implementar a última etapa do MVP 
 */
/* #include "static/estatisticas.h" */

int main(void) {
    /* 
     * 0. CONFIGURAÇÃO DE ENCODING (Resolve os bugs visuais)
     */
    setlocale(LC_ALL, ""); /* Adota o padrão de acentuação do sistema */
    
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); /* Força o terminal do Windows a renderizar UTF-8 (bordas e ícones) */
    #endif

    /* 
     * 1. INICIALIZAÇÃO
     * Prepara a semente aleatória antes de qualquer coisa.
     */
    inicializar_rand();
    
    inicializar_historico();
    
    exibir_boas_vindas();

    /* 
     * 2. LOOP PRINCIPAL DO PROGRAMA
     * Mantém o programa rodando até o usuário escolher a opção SAIR.
     */
    while (true) {
        OpcaoMenu opcao = exibir_menu_principal();

        if (opcao == MENU_JOGAR) {
            /* Fluxo de uma nova partida */
            Dificuldade dif = exibir_menu_dificuldade();
            Partida partida_atual = iniciar_partida(dif);

            limpar_tela();
            printf("\n  Jogo iniciado! Tente adivinhar o numero entre %d e %d.\n", 
                   partida_atual.min_range, partida_atual.max_range);

            /* Loop interno da partida: continua até esgotar tentativas ou vencer */
            while (!partida_encerrada(&partida_atual)) {
                int palpite = ler_inteiro(partida_atual.min_range, partida_atual.max_range, "\n  Digite seu palpite: ");
                Resultado res = processar_palpite(&partida_atual, palpite);
                
                int tentativas_restantes = partida_atual.max_tentativas - partida_atual.tentativas_usadas;
                exibir_dica(res, tentativas_restantes);
            }

            /* Fim da partida: exibe o resumo e salva os dados */
            exibir_resultado_final(&partida_atual);
            
            /* --- INÍCIO DA INTEGRAÇÃO COM HISTÓRICO --- */
            RegistroPartida registro;
            
            /* Pega a data atual usando a função que criamos no utils.c */
            formatar_data_atual(registro.data); 
            
            /* Copia os dados da partida e a dificuldade escolhida para o registro */
            registro.dificuldade = dif;
            registro.tentativas_usadas = partida_atual.tentativas_usadas;
            registro.max_tentativas = partida_atual.max_tentativas;
            registro.numero_secreto = partida_atual.numero_secreto;
            registro.venceu = partida_atual.venceu;

            /* Manda gravar nos arquivos .csv e .txt */
            salvar_partida(&registro);
            /* --- FIM DA INTEGRAÇÃO --- */
            
            /* Mensagem de sucesso solicitada na issue */
            printf("  Partida finalizada! O progresso do jogador foi salvo em: data/historico.txt\n\n");
            
            pausar();
        } 
        else if (opcao == MENU_HISTORICO) {
            exibir_historico();
        } 
        else if (opcao == MENU_ESTATISTICAS) {
            /* exibir_estatisticas(); -> Descomentar no futuro */
            printf("\n  [Modulo de Estatisticas em construcao...]\n");
            pausar();
        } 
        else if (opcao == MENU_SAIR) {
            exibir_despedida();
            /* liberar_recursos(); -> Se houver alocação dinâmica no futuro */
            break; /* Interrompe o laço infinito e encerra o programa de forma limpa */
        }
    }

    return 0; /* Retorno padrão para execução com sucesso (sem erros fatais) */
}
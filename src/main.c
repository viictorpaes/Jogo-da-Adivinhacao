#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "include/tipos.h"
#include "utils/utils.h"
#include "ui/menu.h"
#include "game/jogo.h"
#include "game/jogar_memoria.h"
#include "history/historico.h"
#include "static/estatisticas.h"

int main(void) 
{
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
    inicializar_historico_memoria();

    exibir_boas_vindas();

    /* 
     * 2. LOOP PRINCIPAL DO PROGRAMA
     * Mantém o programa rodando até o usuário escolher a opção SAIR.
     */
    while (true) 
    {
        OpcaoMenu opcao = exibir_menu_principal();

        if (opcao == MENU_JOGAR) {
            /* Fluxo de uma nova partida */
            char nome_jogador[64];
            pedir_nome_jogador(nome_jogador, sizeof(nome_jogador));

            Dificuldade dif = exibir_menu_dificuldade();
            Partida partida_atual = iniciar_partida(dif);

            limpar_tela();
            printf("\n  Jogo iniciado!​​✅​ Tente adivinhar o número entre %d e %d.\n", 
                   partida_atual.min_range, partida_atual.max_range);

            /* Loop interno da partida: continua até esgotar tentativas ou vencer */
            while (!partida_encerrada(&partida_atual)) 
            {
                int palpite = ler_inteiro(partida_atual.min_range, partida_atual.max_range, "\n  Digite seu palpite: ");
                Resultado res = processar_palpite(&partida_atual, palpite);
                
                int tentativas_restantes = partida_atual.max_tentativas - partida_atual.tentativas_usadas;
                int range_total = partida_atual.max_range - partida_atual.min_range;
                exibir_dica(res, tentativas_restantes, palpite, partida_atual.numero_secreto, range_total);
            }

            /* Fim da partida: exibe o resumo e salva os dados */
            exibir_resultado_final(&partida_atual);

            /* Heurística estratégica */
            {
                const char *dica = heuristica_adivinhacao(
                    partida_atual.tentativas_usadas,
                    partida_atual.max_tentativas,
                    partida_atual.venceu, dif);
                printf("\n  💡 Dica: %s\n", dica);
            }

            /* --- INÍCIO DA INTEGRAÇÃO COM HISTÓRICO --- */
            RegistroPartida registro;

            formatar_data_atual(registro.data);
            snprintf(registro.nome, sizeof(registro.nome), "%s", nome_jogador);
            registro.dificuldade      = dif;
            registro.tentativas_usadas = partida_atual.tentativas_usadas;
            registro.max_tentativas   = partida_atual.max_tentativas;
            registro.numero_secreto   = partida_atual.numero_secreto;
            registro.venceu           = partida_atual.venceu;
            registro.pontos           = calcular_pontos(dif, partida_atual.tentativas_usadas,
                                                        partida_atual.venceu);

            /* Manda gravar nos arquivos .csv e .txt */
            salvar_partida(&registro);
            /* --- FIM DA INTEGRAÇÃO --- */
            
            /* Mensagem de sucesso solicitada na issue */
            printf("\nPartida finalizada!​​✅ O progresso do jogador foi salvo em: data/historico.txt e data/historico.csv\n\n");
            
            pausar();
        }

        else if (opcao == MENU_MEMORIA)
        {
            char nome_mem[64];
            pedir_nome_jogador(nome_mem, sizeof(nome_mem));
            jogar_memoria(nome_mem);
        }

        else if (opcao == MENU_HISTORICO)
        {
            exibir_historico_analitico();
        }

        else if (opcao == MENU_ESTATISTICAS)
        {
            exibir_estatisticas();
        }
         
        else if (opcao == MENU_SAIR) 
        {
            exibir_despedida();
            break;
        }
    }

    return 0;
}
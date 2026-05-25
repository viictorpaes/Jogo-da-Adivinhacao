#include "menu.h"
#include "../utils/utils.h"
#include <stdio.h>

#define BORDA_DUPLA   "​➿​➿​➿​​➿​➿​➿​​➿​➿​➿​➿​➿​➿​​➿​➿​➿​​➿​➿​➿​➿​➿​➿​➿​➿​➿​​​"
#define LINHA_SIMPLES "​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​➰​➰​➰​➰​➰​➰​"


void exibir_boas_vindas(void)
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|        🚀  MISSÃO ESPACIAL: ADIVINHAÇÃO  🚀        |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  Bem-vindo, Astronauta! Descubra o número secreto\n");
    printf("  antes que suas tentativas se esgotem no espaço.\n");
    printf("  Prepare-se para a missão! 🛸\n\n");
    pausar();
}

OpcaoMenu exibir_menu_principal(void)
{
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|                MENU PRINCIPAL 🚀                |\n");
    printf("%s\n\n", BORDA_DUPLA);

    printf("  SOLO / LÓGICA\n");
    printf("  1️⃣  Operação Resgate     (Adivinhação Solo) 🔭\n");
    printf("  3️⃣  Mapas Estelares      (Memória Solo) 🧠\n");
    printf("  5️⃣  Protocolo Lógico     (Fórmulas V/F) 🧮\n");
    printf("  6️⃣  Hierarquia de Cmds   (Precedência) ⚙️\n\n");

    printf("  VERSUS\n");
    printf("  2️⃣  Batalha de Sinais    (Adivinhação VS) ⚔️\n");
    printf("  4️⃣  1v1 Mapas Estelares  (Memória VS) 🃏\n\n");

    printf("  MISSÃO\n");
    printf("  7️⃣  Registros de Missão 📡\n");
    printf("  8️⃣  Painel de Controle 📊\n");
    printf("  9️⃣  Abortar Missão 🛑\n\n");
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 9, "  Digite sua escolha (1-9): ");

    return (OpcaoMenu)escolha;
}

Dificuldade exibir_menu_dificuldade(void) 
{
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|         👨‍🚀  SELECIONE SUA PATENTE ESPACIAL  👨‍🚀         |\n");
    printf("%s\n", BORDA_DUPLA);
    printf("  Qual é a sua patente espacial, Astronauta?\n\n");
    
    printf("  1️⃣​ FÁCIL: Cientista        (1 a %d, %d tentativas)\n", FACIL_MAX, FACIL_TENTATIVAS);
    printf("  2️⃣​ MÉDIO: Piloto           (1 a %d, %d tentativas)\n", MEDIO_MAX, MEDIO_TENTATIVAS);
    printf("  3️⃣​ DIFÍCIL: Buzz Lightyear (1 a %d, %d tentativas)\n\n", DIFICIL_MAX, DIFICIL_TENTATIVAS);
    
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 3, "  Escolha o nível: ");

    if (escolha == 1) return FACIL;
    if (escolha == 2) return MEDIO;
    return DIFICIL;
}

static const char *mensagem_proximidade(int palpite, int numero_secreto, int range_total)
{
    int distancia = palpite - numero_secreto;
    if (distancia < 0) distancia = -distancia;

    int porcentagem = (distancia * 100) / (range_total > 0 ? range_total : 1);

    if (porcentagem < 5)  return "📡 Frequência muito próxima! Você está quase lá!";
    if (porcentagem < 15) return "🔭 Sinal detectado! Continue ajustando...";
    if (porcentagem < 40) return "📟 Interferência estática... Sinal fraco.";
    return "🛰️  Sem sinal no espaço... Muito longe!";
}

void exibir_dica(Resultado r, int tentativas_restantes, int palpite, int numero_secreto, int range_total)
{
    printf("\n%s\n", LINHA_SIMPLES);

    if (r == ACERTOU)
    {
        printf("  📡 Sinal estabelecido! Resgate a caminho!\n");
        printf("  ✅ MISSÃO CUMPRIDA! 👏 Você encontrou o número secreto, Astronauta!\n");
    }
    else
    {
        if (r == MAIOR)
            printf("  🚨 TRANSMISSÃO: O número secreto é MAIOR! Aponte para cima! ^\n");
        else
            printf("  🚨 TRANSMISSÃO: O número secreto é MENOR! Volte à órbita! v\n");

        printf("  %s\n", mensagem_proximidade(palpite, numero_secreto, range_total));
        printf("  Tentativas restantes: %d\n", tentativas_restantes);
    }

    printf("%s\n\n", LINHA_SIMPLES);
}

void exibir_erro_input(void) 
{
    printf("\n  ❌ Sinal de comunicação inválido! Tente novamente, Astronauta. 🫡\n");
}

void exibir_despedida(void)
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|          🛸  MISSÃO ENCERRADA — ATÉ LOGO!  🛸         |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  👋 Encerrando sistemas da nave... De volta à Terra!\n\n");
}

void pedir_nome_jogador(char *nome, int max)
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|         🪐  IDENTIFICAÇÃO DO ASTRONAUTA  🪐          |\n");
    printf("%s\n\n", BORDA_DUPLA);

    ler_string(nome, max, "  Nome do astronauta: ");

    if (nome[0] == '\0') 
    {
        int i = 0;
        const char *padrao = "Astronauta";
        while (i < max - 1 && padrao[i]) { nome[i] = padrao[i]; i++; }
        nome[i] = '\0';
    }

    printf("\n  Bem-vindo à nave, %s! Prepare-se para a missão. 🚀\n\n", nome);
    pausar();
}
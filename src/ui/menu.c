#include "menu.h"
#include "../utils/utils.h"
#include <stdio.h>

#define BORDA_DUPLA   "​➿​➿​➿​​➿​➿​➿​​➿​➿​➿​➿​➿​➿​​➿​➿​➿​​➿​➿​➿​​​"
#define LINHA_SIMPLES "​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​​➰​➰​➰​"


void exibir_boas_vindas(void) 
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|              JOGO DA ADIVINHAÇÃO               |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  Descubra o número secreto antes que suas tentativas acabem.\n");
    printf("  Boa sorte!🍀​\n\n");
    pausar();
}

OpcaoMenu exibir_menu_principal(void)
{
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|                MENU PRINCIPAL                 |\n");
    printf("%s\n\n", BORDA_DUPLA);

    
    printf("  1️⃣  Jogar - Jogo da Adivinhação\n");
    printf("  2️⃣  Jogar - Jogo da Memória\n");
    printf("  3️⃣  Ver Histórico\n");
    printf("  4️⃣  Estatísticas\n");
    printf("  5️⃣  Sair\n\n");
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 5, "  Digite sua escolha: ");

    return (OpcaoMenu)escolha;
}

Dificuldade exibir_menu_dificuldade(void) 
{
    int escolha;

    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|             SELECIONE A DIFICULDADE            |\n");
    printf("%s\n\n", BORDA_DUPLA);
    
    printf("  1️⃣​ FÁCIL   (1 a %d, %d tentativas)\n", FACIL_MAX, FACIL_TENTATIVAS);
    printf("  2️⃣​ MÉDIO   (1 a %d, %d tentativas)\n", MEDIO_MAX, MEDIO_TENTATIVAS);
    printf("  3️⃣​ DIFÍCIL (1 a %d, %d tentativas)\n\n", DIFICIL_MAX, DIFICIL_TENTATIVAS);
    
    printf("%s\n", LINHA_SIMPLES);

    escolha = ler_inteiro(1, 3, "  Escolha o nível: ");

    if (escolha == 1) return FACIL;
    if (escolha == 2) return MEDIO;
    return DIFICIL;
}

void exibir_dica(Resultado r, int tentativas_restantes) 
{
    printf("\n%s\n", LINHA_SIMPLES);
    
    if (r == MAIOR) 
    {
        printf(" ​🚨​DICA: O número secreto e MAIOR que seu palpite.\n");
    } 

    else if (r == MENOR) 
    {
        printf(" ​🚨​DICA: O número secreto e MENOR que seu palpite.\n");
    } 

    else if (r == ACERTOU) 
    {
        printf("  PARABÉNS!👏 Você encontrou o número secreto.\n");
    }

    if (r != ACERTOU) 
    {
        printf("  Tentativas restantes: %d\n", tentativas_restantes);
    }
    
    printf("%s\n\n", LINHA_SIMPLES);
}

void exibir_erro_input(void) 
{
    printf("\n   Entrada inválida.​❌​ Por favor, tente novamente.​​🫡​\n");
}

void exibir_despedida(void)
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|              ​​🤝​ OBRIGADO POR JOGAR!​​🤝​              |\n");
    printf("%s\n\n", BORDA_DUPLA);
    printf("  ​​👋​Encerrando o sistema...\n\n");
}

void pedir_nome_jogador(char *nome, int max)
{
    limpar_tela();
    printf("\n%s\n", BORDA_DUPLA);
    printf("|             IDENTIFIQUE-SE, JOGADOR               |\n");
    printf("%s\n\n", BORDA_DUPLA);

    ler_string(nome, max, "  Seu nome: ");

    if (nome[0] == '\0') {
        int i = 0;
        const char *padrao = "Jogador";
        while (i < max - 1 && padrao[i]) { nome[i] = padrao[i]; i++; }
        nome[i] = '\0';
    }

    printf("\n  Olá, %s! Vamos começar.​🎮​\n\n", nome);
    pausar();
}
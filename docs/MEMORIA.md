# 🎮 Jogo da Memória 4x4

## Descrição
Um jogo de memória interativo em C que desafia o jogador a encontrar pares de números em um tabuleiro 4x4 embaralhado.

## Características

### Tabuleiro
- **Dimensões**: 4x4 = 16 casas
- **Pares**: 8 pares de números (1 a 8)
- **Estado**: Cada casa pode estar oculta, revelada ou acertada

### Mecânica de Jogo
1. **Embaralhamento**: Os números são embaralhados aleatoriamente usando o algoritmo Fisher-Yates
2. **Escolha**: O jogador escolhe duas casas por rodada
3. **Revelação**: As casas são temporariamente reveladas para o jogador ver os números
4. **Verificação**: Se os números forem iguais, é um acerto! Caso contrário, as casas voltam a ser ocultas
5. **Pontuação**: Cada par encontrado = 10 pontos

### Sistema de Pontuação
- ✅ **Acerto de Par**: +10 pontos
- 🎉 **Bônus**: Estatísticas de desempenho ao final

## Como Jogar

### Compilação
```bash
gcc -std=c11 -Wall -Wextra -I./src/game -I./src/utils -I./src/history -I./src/static -I./src/include -I./src/ui \
    src/main.c src/game/jogo.c src/game/memorygame.c src/game/jogar_memoria.c \
    src/utils/utils.c src/history/historico.c src/static/estatisticas.c src/ui/menu.c \
    -o jogo.exe
```

### Execução
```bash
./jogo.exe
```

### No Jogo
1. Selecione a opção **[2] Jogar Memória** no menu principal
2. O tabuleiro será exibido com as casas numeradas de 1 a 16
3. Digite os números das duas casas que deseja revelar
4. O sistema mostrará os números
5. Se forem iguais, você ganha 10 pontos!
6. Continue até encontrar todos os 8 pares

## Exemplo de Tabuleiro

```
    [1]   [2]   [3]   [4]
[1]   ?     ?     ?     ?
[2]   ?     ?     ?     ?
[3]   ?     ?     ?     ?
[4]   ?     ?     ?     ?

Pontuação: 20 | Pares: 2/8
```

## Estrutura do Projeto

### Arquivos Principais
- `src/game/memorygame.h` - Header com definições
- `src/game/memorygame.c` - Implementação do jogo
- `src/game/jogar_memoria.h` - Interface de jogo
- `src/game/jogar_memoria.c` - Loop principal do jogo

### Estruturas de Dados
```c
typedef struct {
    int numeros[16];      // Números do tabuleiro (1-8, duplicados)
    bool reveladas[16];   // Estado de cada casa
    bool acertadas[16];   // Pares já encontrados
    int pontuacao;        // Pontuação do jogador
    int tentativas;       // Número de tentativas
    int pares_encontrados;// Total de pares encontrados
} JogoMemoria;
```

## Funções Principais

| Função | Descrição |
|--------|-----------|
| `inicializar_jogo_memoria()` | Cria novo jogo com tabuleiro embaralhado |
| `exibir_tabuleiro()` | Mostra estado atual do tabuleiro |
| `fazer_jogada()` | Processa escolha de duas casas |
| `jogo_memoria_finalizado()` | Verifica se todos os pares foram encontrados |
| `exibir_resultado_memoria()` | Mostra estatísticas finais |

## Validações
- ✅ Posições devem estar entre 1 e 16
- ✅ Não é permitido escolher a mesma casa duas vezes
- ✅ Não é permitido escolher casas já acertadas
- ✅ Embaralhamento pseudoaleatório a cada novo jogo

## Exemplo de Jogada

```
Escolha as duas casas (1-16):
Primeira casa: 1
Segunda casa: 5

Casa 1 revelou: 3
Casa 5 revelou: 3

✅ Acertou! Os números são iguais: 3 = 3
🎉 +10 pontos! Total: 10
```

## Tecnologias Utilizadas
- **Linguagem**: C (C11)
- **Compilador**: GCC
- **Bibliotecas Padrão**: stdio, stdlib, stdbool, string, time
- **Sistema de Operacional**: Windows/Linux/macOS

## Melhorias Futuras
- [ ] Sistema de dificuldades (tabuleiro maior)
- [ ] Modo multiplayer
- [ ] Ranking de pontuações
- [ ] Temas visuais diferentes
- [ ] Sons e efeitos

## Autor
Criado como parte do projeto "Jogo da Adivinhação"

---

**Divirta-se! 🎉**

<h1 align="center">Jogo da Memória 4×4<br>
<img src="https://img.shields.io/badge/-Memória-111827?style=flat-square&logo=markdown&logoColor=white" height="25"/></h1>

<p align="center">Documentação do módulo <code>game/memorygame</code> — mecânica, estrutura de dados e funções.</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-111827?style=flat-square&logo=c&logoColor=A8B9CC"/>
  <img src="https://img.shields.io/badge/-C11-111827?style=flat-square&logo=c&logoColor=white"/>
  <img src="https://img.shields.io/badge/-GCC-111827?style=flat-square&logo=gnu&logoColor=white"/>
  <img src="https://img.shields.io/badge/-Tabuleiro%204×4-111827?style=flat-square"/>
</p>

---

## 📋 Descrição

Um jogo de memória interativo em C onde o jogador precisa encontrar todos os **8 pares de números** em um tabuleiro 4×4 embaralhado. Disponível tanto na versão de console quanto na versão gráfica com Raylib.

---

## ⚙️ Mecânica de Jogo

| Etapa | Descrição |
| :--- | :--- |
| **Embaralhamento** | Os 16 números são embaralhados com o algoritmo **Fisher-Yates** a cada nova partida |
| **Escolha** | O jogador escolhe duas casas por rodada |
| **Revelação** | As casas são temporariamente reveladas |
| **Verificação** | Par correto → casas permanecem; par errado → voltam a ficar ocultas |
| **Fim** | Partida encerrada ao encontrar todos os 8 pares |

### Sistema de Pontuação

| Evento | Pontos |
| :--- | :---: |
| Acerto de par | `+10` |
| Par errado | `0` |

Ao final, são exibidas: pontuação total, pares encontrados, tentativas realizadas e eficiência (acertos/tentativa).

---

## 🏗️ Estrutura de Dados

```c
typedef struct 
{
    int  numeros[16];       // Números do tabuleiro (1-8, duplicados)
    bool reveladas[16];     // Estado de cada casa (visível ou oculta)
    bool acertadas[16];     // Pares já confirmados
    int  pontuacao;         // Pontuação acumulada
    int  tentativas;        // Total de tentativas realizadas
    int  pares_encontrados; // Pares acertados até o momento
} JogoMemoria;
```

---

## 🔧 Funções Principais

| Função | Descrição |
| :--- | :--- |
| `inicializar_jogo_memoria(JogoMemoria *)` | Cria novo jogo com tabuleiro embaralhado |
| `exibir_tabuleiro(const JogoMemoria *)` | Mostra estado atual do tabuleiro no terminal |
| `fazer_jogada(JogoMemoria *, int casa1, int casa2)` | Processa escolha de duas casas; retorna `1` se acertou o par |
| `jogo_memoria_finalizado(const JogoMemoria *)` | Retorna `1` quando todos os 8 pares foram encontrados |
| `exibir_resultado_memoria(const JogoMemoria *)` | Exibe estatísticas finais da partida |
| `jogar_memoria(void)` | Executa o loop completo do jogo (console) |

---

## 🗂️ Arquivos do Módulo

| Arquivo | Responsabilidade |
| :--- | :--- |
| `src/game/memorygame.h` | Definições da struct `JogoMemoria` e assinaturas |
| `src/game/memorygame.c` | Implementação do tabuleiro e lógica de pares |
| `src/game/jogar_memoria.h` | Interface do loop de jogo |
| `src/game/jogar_memoria.c` | Loop principal e fluxo de turnos (console) |

---

## 🕹️ Como Jogar (Console)

1. Selecione a opção **[2] Jogar Memória** no menu principal
2. O tabuleiro é exibido com as 16 casas numeradas de `1` a `16`
3. Digite os números de duas casas que deseja revelar
4. Se os números forem iguais, você ganha **+10 pontos**
5. Continue até encontrar todos os **8 pares**

### Exemplo de Tabuleiro

```
    [1]   [2]   [3]   [4]
[1]   ?     ?     ?     ?
[2]   ?     ?     ?     ?
[3]   ?     ?     ?     ?
[4]   ?     ?     ?     ?

Pontuação: 20 | Pares: 2/8
```

### Exemplo de Jogada

```
Escolha as duas casas (1-16):
Primeira casa: 1
Segunda casa: 5

Casa 1 revelou: 3
Casa 5 revelou: 3

✅ Acertou! 3 = 3  →  +10 pontos! Total: 10
```

---

## ✅ Validações

- Posições devem estar entre `1` e `16`
- Não é permitido escolher a mesma casa duas vezes na mesma rodada
- Não é permitido escolher casas já acertadas
- Embaralhamento pseudoaleatório (Fisher-Yates) a cada novo jogo

---

## 🔗 Compilação Manual

```bash
gcc -std=c11 -Wall -Wextra \
    -I./src/game -I./src/utils -I./src/history \
    -I./src/static -I./src/include -I./src/ui \
    src/main.c src/game/jogo.c src/game/memorygame.c \
    src/game/jogar_memoria.c src/utils/utils.c \
    src/history/historico.c src/static/estatisticas.c \
    src/ui/menu.c -o jogo
```

> [!NOTE]
> Prefira usar `make` ou `make run` — o Makefile já gerencia todas as dependências e flags de compilação corretamente.

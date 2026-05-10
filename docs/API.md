<h1 align="center">API do Projeto<br>
<img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="25"/></h1>

<p align="center">Especificação das funções públicas e contratos entre os módulos.</p>

---

## 🔧 Módulo `utils`
<img src="https://img.shields.io/badge/-Módulo%20Utils-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/utils/utils.h` / `src/utils/utils.c`

| Função | Descrição |
| :--- | :--- |
| `void utils_inicializar_semente(void)` | Inicializa o RNG com entropia do sistema (`time` + `pid`) |
| `int utils_aleatorio_intervalo(int min, int max)` | Retorna um inteiro aleatório no intervalo `[min, max]` sem viés de módulo |
| `char *utils_ler_linha(char *buffer, size_t tamanho)` | Leitura segura de linha via `fgets`, descarta newline |
| `int utils_converter_int_seguro(const char *string, int *resultado)` | Converte string para inteiro; retorna `0` em falha, `1` em sucesso |
| `int utils_ler_int_prompt(const char *mensagem, int min, int max)` | Exibe prompt e lê inteiro validado dentro do intervalo |
| `void utils_limpar_stdin(void)` | Descarta caracteres residuais do buffer de entrada |
| `void utils_pausar(const char *mensagem)` | Exibe mensagem e aguarda confirmação do usuário |
| `void partida_inicializar(Partida *p, const char *nome)` | Inicializa a struct `Partida` com o nome do jogador e valores zerados |
| `void partida_imprimir(const Partida *p)` | Imprime os dados de uma partida no terminal |

---

## 🎮 Módulo `ui` — Console
<img src="https://img.shields.io/badge/-Módulo%20UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18"><br>
`src/ui/menu.h` / `src/ui/menu.c`

| Função | Descrição |
| :--- | :--- |
| `int menu_exibir_principal(void)` | Exibe o menu principal e retorna a opção escolhida (`1..4`) |
| `dificuldade_t menu_selecionar_dificuldade(void)` | Exibe o menu de dificuldade e retorna o enum selecionado |

---

## 🎨 Módulo `ui` — Raylib
<img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="18"><br>
`src/ui/frontend.h` / `src/ui/frontend.c`

| Função | Descrição |
| :--- | :--- |
| `void frontend_iniciar(void)` | Cria a janela Raylib (1200×800) e entra no loop principal de renderização |
| `void frontend_atualizar(EstadoUI *estado)` | Processa entrada do usuário e atualiza o estado da aplicação |
| `void frontend_desenhar(const EstadoUI *estado)` | Renderiza a tela atual com base no estado (`menu`, `jogo`, `resultado`, etc.) |

---

## ⚙️ Módulo `game` — Adivinhação
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/game/jogo.h` / `src/game/jogo.c`

| Função | Descrição |
| :--- | :--- |
| `int jogo_gerar_numero(dificuldade_t nivel)` | Sorteia o número secreto de acordo com o nível de dificuldade |
| `feedback_t jogo_avaliar_palpite(int palpite, int secreto)` | Compara o palpite e retorna o enum de feedback (`FRIO`, `MORNO`, `QUENTE`, etc.) |
| `int jogo_calcular_pontuacao(dificuldade_t nivel, int tentativas)` | Calcula a pontuação final com base no nível e no número de tentativas |

---

## 🃏 Módulo `game` — Memória
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/game/memorygame.h` / `src/game/memorygame.c`<br>
`src/game/jogar_memoria.h` / `src/game/jogar_memoria.c`

| Função | Descrição |
| :--- | :--- |
| `void inicializar_jogo_memoria(JogoMemoria *jogo)` | Cria novo tabuleiro 4×4 com pares embaralhados (Fisher-Yates) |
| `void exibir_tabuleiro(const JogoMemoria *jogo)` | Imprime o estado atual do tabuleiro no terminal |
| `int fazer_jogada(JogoMemoria *jogo, int casa1, int casa2)` | Processa a escolha de duas casas; retorna `1` se acertou o par |
| `int jogo_memoria_finalizado(const JogoMemoria *jogo)` | Retorna `1` quando todos os 8 pares foram encontrados |
| `void exibir_resultado_memoria(const JogoMemoria *jogo)` | Exibe estatísticas finais (pontuação, pares, tentativas, eficiência) |
| `void jogar_memoria(void)` | Executa o loop completo do Jogo da Memória |

---

## 📂 Módulo `history`
<img src="https://img.shields.io/badge/-Módulo%20History-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/history/historico.h` / `src/history/historico.c`

| Função | Descrição |
| :--- | :--- |
| `int historico_salvar(const Partida *p)` | Persiste uma partida no arquivo `data/historico.csv` |
| `int historico_carregar(Partida *lista, int max)` | Lê o CSV e popula o array de `Partida`; retorna quantidade lida |

---

## 📊 Módulo `static` — Estatísticas
<img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/static/estatisticas.h` / `src/static/estatisticas.c`

| Função | Descrição |
| :--- | :--- |
| `float estatisticas_media_tentativas(const Partida *lista, int n)` | Calcula a média de tentativas de uma lista de partidas |
| `void estatisticas_exibir_ranking(const Partida *lista, int n)` | Exibe o ranking dos melhores desempenhos por pontuação |
| `void estatisticas_melhor_pior(const Partida *lista, int n, Partida *melhor, Partida *pior)` | Retorna a melhor e a pior sessão pelo número de tentativas |

---

## 💡 Exemplo de Uso Rápido

```c
#include "utils/utils.h"
#include "ui/menu.h"
#include "game/jogo.h"

int main(void) {
    utils_inicializar_semente();

    int opcao = menu_exibir_principal();
    if (opcao == 1) {
        dificuldade_t nivel = menu_selecionar_dificuldade();
        int secreto = jogo_gerar_numero(nivel);
        /* loop de palpites... */
    }

    return 0;
}
```

> [!NOTE]
> Todos os módulos dependem de `src/include/tipos.h` para as definições de `Partida`, `dificuldade_t` e `feedback_t`. Inclua-o antes dos demais cabeçalhos quando necessário.

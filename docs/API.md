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

### Adivinhação Solo

| Função | Descrição |
| :--- | :--- |
| `bool inicializar_historico(void)` | Cria `data/historico.csv` e `.txt` se não existirem |
| `bool salvar_partida(const RegistroPartida *r)` | Persiste um registro de adivinhação (CSV + TXT) |
| `int carregar_historico(RegistroPartida *buf, int max)` | Lê o CSV e popula o array; retorna quantidade lida |
| `void exibir_historico(void)` | Imprime o histórico de adivinhação no terminal |
| `void liberar_historico(void)` | Libera recursos associados ao histórico |

### Memória Solo

| Função | Descrição |
| :--- | :--- |
| `bool inicializar_historico_memoria(void)` | Cria `data/historico_memoria.*` se não existirem |
| `bool salvar_partida_memoria(const RegistroMemoria *r)` | Persiste um registro de memória (CSV + TXT) |
| `int carregar_historico_memoria(RegistroMemoria *buf, int max)` | Lê o CSV e popula o array; retorna quantidade lida |
| `void exibir_historico_memoria(void)` | Imprime o histórico de memória no terminal |

### Adivinhação VS

| Função | Descrição |
| :--- | :--- |
| `bool inicializar_historico_vs(void)` | Cria `data/historico_vs.*` se não existirem |
| `bool salvar_partida_vs(const RegistroVS *r)` | Persiste um registro VS de adivinhação (CSV + TXT) |
| `int carregar_historico_vs(RegistroVS *buf, int max)` | Lê o CSV e popula o array; retorna quantidade lida |

### Memória VS

| Função | Descrição |
| :--- | :--- |
| `bool inicializar_historico_memoria_vs(void)` | Cria `data/historico_memoria_vs.*` se não existirem |
| `bool salvar_partida_memoria_vs(const RegistroMemoria *r1, const RegistroMemoria *r2)` | Persiste os registros dos dois jogadores (CSV + TXT) |
| `int carregar_historico_memoria_vs(RegistroMemoriaVS *buf, int max)` | Lê o CSV e popula o array; retorna quantidade lida |

### Protocolo Lógico e Hierarquia de Comandos

| Função | Descrição |
| :--- | :--- |
| `bool inicializar_historico_logica(void)` | Cria `data/historico_logica.*` se não existirem |
| `bool inicializar_historico_precedencia(void)` | Cria `data/historico_precedencia.*` se não existirem |
| `bool salvar_puzzle(const RegistroPuzzle *r)` | Persiste um registro de puzzle (Lógica ou Precedência) com base no campo `r->modo` |
| `int carregar_historico_puzzle(RegistroPuzzle *buf, int max, const char *modo)` | Lê o CSV do modo indicado (`"logica"` ou `"precedencia"`) e popula o array |

---

## 🧮 Módulo `game` — Protocolo Lógico
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/game/logica.h` / `src/game/logica.c`

| Função | Descrição |
| :--- | :--- |
| `JogoLogica inicializar_jogo_logica(Dificuldade dif)` | Cria novo jogo com número de questões e timer por questão baseados na dificuldade |
| `void gerar_proxima_questao_logica(JogoLogica *j)` | Gera uma nova fórmula proposicional aleatória e define a resposta correta |
| `void responder_vf_logica(JogoLogica *j, bool resposta)` | Registra a resposta V/F do jogador e avança para a fase de classificação |
| `void responder_classif_logica(JogoLogica *j, ClassFormula resp)` | Registra a classificação (Tautologia/Contradição/Contingência) e encerra a questão |
| `void atualizar_timer_logica(JogoLogica *j, double dt)` | Decrementa o timer da questão atual; avança automaticamente ao esgotar |
| `int calcular_pontos_logica(const JogoLogica *j)` | Retorna a pontuação final com base nos acertos e no nível de dificuldade |

---

## 🔢 Módulo `game` — Hierarquia de Comandos (Precedência)
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/game/precedencia.h` / `src/game/precedencia.c`

| Função | Descrição |
| :--- | :--- |
| `JogoPrecedencia inicializar_jogo_precedencia(Dificuldade dif)` | Cria novo jogo com número de questões e timer por questão baseados na dificuldade |
| `void gerar_proxima_questao_prec(JogoPrecedencia *j)` | Seleciona aleatoriamente uma questão do banco sem repetição e embaralha as opções |
| `void responder_precedencia(JogoPrecedencia *j, int opcao)` | Registra a opção escolhida (0–3), verifica o acerto e inicia o feedback |
| `void atualizar_timer_prec(JogoPrecedencia *j, double dt)` | Decrementa o timer da questão atual; avança automaticamente ao esgotar |
| `int calcular_pontos_prec(const JogoPrecedencia *j)` | Retorna a pontuação final com base nos acertos e no nível de dificuldade |

---

## 🎲 Módulo `game` — Jogos Extras (Orquestrador Terminal)
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/game/jogos_extras.h` / `src/game/jogos_extras.c`

| Função | Descrição |
| :--- | :--- |
| `void jogar_adivinhacao_vs(void)` | Loop completo do modo Batalha de Sinais (2 jogadores, até 3 rodadas) no terminal |
| `void jogar_memoria_vs(void)` | Loop completo do modo 1v1 Mapas Estelares (turnos alternados) no terminal |
| `void jogar_logica_terminal(void)` | Loop completo do Protocolo Lógico (console), incluindo seleção de dificuldade e salvamento |
| `void jogar_precedencia_terminal(void)` | Loop completo da Hierarquia de Comandos (console), incluindo seleção de dificuldade e salvamento |

---

## 📊 Módulo `static` — Estatísticas
<img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
`src/static/estatisticas.h` / `src/static/estatisticas.c`

| Função | Descrição |
| :--- | :--- |
| `int calcular_pontos(Dificuldade dif, int tentativas, bool venceu)` | Calcula a pontuação do Jogo da Adivinhação com base no nível e tentativas |
| `int calcular_pontos_memoria(int tentativas)` | Calcula a pontuação do Jogo da Memória com bônus de eficiência |
| `const char *heuristica_adivinhacao(int tentativas, int max, bool venceu, Dificuldade dif)` | Retorna string estática com dica estratégica exibida na tela de resultado |
| `const char *heuristica_memoria(int tentativas, int pontos)` | Retorna string estática com feedback motivacional do Jogo da Memória |
| `void preparar_resumo_adivinhacao(char *buf, int len)` | Preenche `buf` com resumo estatístico (média, min, max, desvio) do histórico de adivinhação |
| `void preparar_resumo_memoria(char *buf, int len)` | Preenche `buf` com resumo estatístico do histórico de memória |
| `void preparar_linhas_estatisticas(char linhas[][STATS_LINHA_LEN], int *n_linhas)` | Preenche o array `linhas` com todas as métricas formatadas para exibição no frontend |
| `void exibir_estatisticas(void)` | Exibe o painel completo de estatísticas no terminal |
| `void exibir_historico_analitico(void)` | Exibe o histórico de adivinhação com resumo analítico (funções recursivas) |

---

## 💡 Exemplo de Uso Rápido

```c
#include "utils/utils.h"
#include "ui/menu.h"
#include "game/jogo.h"

int main(void) 
{
    utils_inicializar_semente();

    int opcao = menu_exibir_principal();
    if (opcao == 1) 
    {
        dificuldade_t nivel = menu_selecionar_dificuldade();
        int secreto = jogo_gerar_numero(nivel);
    }

    return 0;
}
```

> [!NOTE]
> Todos os módulos dependem de `src/include/tipos.h` para as definições de `Partida`, `dificuldade_t` e `feedback_t`. Inclua-o antes dos demais cabeçalhos quando necessário.

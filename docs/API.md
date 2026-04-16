<h1 align="center"> Documentação da API <br>
<img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="25"/></h1>

<h2 align="center">🛠️ Módulos e Funções</h2>

### 🧰 Módulo: Utils
`src/utils/utils.h` | `src/utils/utils.c`
<br>
<img src="https://img.shields.io/badge/-Util-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"/>

| Função | Descrição |
| :--- | :--- |
| `void utils_inicializar_semente(void)` | Inicializa o gerador de números aleatórios (srand). |
| `int utils_aleatorio_intervalo(int min, int max)` | Retorna um número inteiro aleatório entre o valor mínimo e máximo. |
| `char *utils_ler_linha(char *buffer, size_t tamanho)` | Lê uma string do terminal de forma segura, evitando estouro de buffer. |
| `int utils_converter_int_seguro(const char *str, int *resultado)` | Converte string para inteiro e retorna sucesso (0 ou 1). |
| `int utils_ler_int_prompt(const char *msg, int min, int max)` | Exibe uma mensagem, lê a entrada e valida se está no intervalo permitido. |
| `void utils_limpar_stdin(void)` | Limpa o buffer de entrada do teclado para evitar resíduos em leituras futuras. |
| `void utils_pausar(const char *mensagem)` | Exibe uma mensagem e aguarda o usuário pressionar Enter. |

---

### 🖥️ Módulo: UI (Menu)
`src/ui/menu.h` | `src/ui/menu.c`
<br>
<img src="https://img.shields.io/badge/-Interface-111827?style=flat-square&logo=materialdesign&logoColor=white" height="18"/>

* `int menu_exibir_principal(void)`
    * Exibe as opções principais (Jogar, Histórico, Estatísticas, Sair).
    * **Retorno:** Inteiro representando a opção escolhida (**1 a 4**).
* `dificuldade_t menu_selecionar_dificuldade(void)`
    * Exibe o submenu de níveis (Fácil, Médio, Difícil).
    * **Retorno:** Enum do tipo `dificuldade_t`.

---

### 🎮 Módulo: Game
`src/game/jogo.h` | `src/game/jogo.c`
<br>
<img src="https://img.shields.io/badge/-Jogo-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>

* `void partida_inicializar(Partida *p, const char *nome)`
    * Configura uma nova estrutura de partida com o nome do jogador e zera as tentativas.
* `void partida_imprimir(const Partida *p)`
    * Exibe na tela o resumo dos dados da partida atual (nome, pontuação, tentativas).

---

### 📂 Outros Módulos
| Módulo | Finalidade | Badge |
| :--- | :--- | :--- |
| **History** | Persistência de dados em arquivos `CSV` e `TXT`. | <img src="https://img.shields.io/badge/-Histórico-111827?style=flat-square&logo=c&logoColor=00599C" height="15"/> |
| **Static** | Processamento de dados para gerar médias e recordes. | <img src="https://img.shields.io/badge/-Estatística-111827?style=flat-square&logo=c&logoColor=white" height="15"/> |

---

### 🚀 Exemplo de Uso Rápido

```c
#include "utils/utils.h"
#include "ui/menu.h"

int main(void) {
    // Preparação inicial
    utils_inicializar_semente();

    // Fluxo do Menu
    int opcao = menu_exibir_principal();

    if (opcao == 1) {
        // Inicia a lógica contida no módulo game
        // Exemplo: partida_inicializar(&p, "Jogador");
    }

    return 0;
}
```
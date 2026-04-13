# API do projeto (visão rápida)

Módulos e funções relevantes (resumo):

- `utils` (`src/utils/utils.h` / `src/utils/utils.c`)
  - `void utils_seed_rand(void);`
  - `int utils_rand_range(int minimo, int maximo);`
  - `char *utils_read_line(char *buffer, size_t tam);`
  - `int utils_parse_int_safe(const char *str, int *saida);`
  - `int utils_read_int_prompt(const char *mensagem_prompt, int minimo, int maximo);`
  - `void utils_clear_stdin(void);`
  - `void utils_pause(const char *mensagem);`
  - `void partida_init(Partida *partida, const char *nome_jogador);`
  - `void partida_print(const Partida *partida);`

- `menu` (`src/ui/menu.c`)
  - `int menu_exibir_principal(void);` — exibe menu e retorna opção escolhida (1..4).
  - `dificuldade_t menu_selecionar_dificuldade(void);` — retorna dificuldade selecionada.

Outros módulos (visão):
- `game` — contém o loop principal do jogo e lógica de palpites.
- `history` — funções para salvar e carregar entradas de `historico.csv`.
- `static` — funções para análise e estatísticas a partir do histórico.

Uso rápido (exemplo):

```c
#include "utils/utils.h"
#include "ui/menu.h"

int main(void) {
    utils_seed_rand();
    int opc = menu_exibir_principal();
    if (opc == 1) { /* iniciar jogo */ }
}
```

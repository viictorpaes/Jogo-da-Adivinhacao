# API do projeto (visão rápida)

Módulos e funções relevantes (resumo):

- `utils` (`src/utils/utils.h` / `src/utils/utils.c`)
  - `void utils_inicializar_semente(void);`
  - `int utils_aleatorio_intervalo(int min, int max);`
  - `char *utils_ler_linha(char *buffer, size_t tamanho);`
  - `int utils_converter_int_seguro(const char *string, int *resultado);`
  - `int utils_ler_int_prompt(const char *mensagem, int min, int max);`
  - `void utils_limpar_stdin(void);`
  - `void utils_pausar(const char *mensagem);`
  - `void partida_inicializar(Partida *p, const char *nome);`
  - `void partida_imprimir(const Partida *p);`

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
  utils_inicializar_semente();
  int opcao = menu_exibir_principal();
  if (opcao == 1)
  { /* iniciar jogo */ 
  }

    return 0;

}
```

<h1 align="center">Architecture Decision Records (ADR) <br>
<img src="https://img.shields.io/badge/-ADR-111827?style=flat-square&logo=blueprint&logoColor=4CAF50" height="24"/></h1>

> Registro das decisões arquiteturais relevantes tomadas durante o desenvolvimento do projeto.  
> Formato: contexto → decisão → consequências.


## ADR-001: Dois pontos de entrada independentes (console vs Raylib)

![Status](https://img.shields.io/badge/status-aceito-brightgreen?style=flat-square) ![Categoria](https://img.shields.io/badge/categoria-arquitetura-blue?style=flat-square)

### Contexto

O projeto precisava suportar duas interfaces distintas — terminal (console) e gráfica (Raylib) — sem duplicar a lógica de negócio.

### Decisão

Manter dois pontos de entrada separados (`main.c` e `main_raylib.c`) que compartilham os módulos de lógica (`game/`, `history/`, `static/`, `utils/`), diferindo apenas na camada de apresentação (`ui/menu.c` para console, `ui/frontend.c` para Raylib).

### Consequências

| | |
|---|---|
| ✅ | Lógica de negócio reutilizada sem modificação |
| ✅ | Cada versão pode evoluir independentemente |
| ⚠️ | Makefile precisa de dois targets separados (`make run` e `make raylib`) |

---

## ADR-002: Persistência em arquivos CSV + TXT

![Status](https://img.shields.io/badge/status-aceito-brightgreen?style=flat-square) ![Categoria](https://img.shields.io/badge/categoria-persistência-orange?style=flat-square)

### Contexto

Os dados de histórico precisavam ser persistentes entre sessões e legíveis tanto pelo programa quanto por ferramentas externas (ex.: Excel, scripts).

### Decisão

Salvar cada partida em dois formatos simultâneos:

- **CSV** (`data/historico.csv`): estruturado para leitura programática
- **TXT** (`data/historico.txt`): formatado para leitura humana no terminal

### Consequências

| | |
|---|---|
| ✅ | CSV facilita análise externa e importação de dados |
| ✅ | TXT permite `exibir_historico()` simples via leitura de arquivo |
| ⚠️ | Duas escritas por partida (baixo custo, aceitável) |

---

## ADR-003: Funções recursivas para cálculo de estatísticas

![Status](https://img.shields.io/badge/status-aceito-brightgreen?style=flat-square) ![Categoria](https://img.shields.io/badge/categoria-algoritmo-purple?style=flat-square)

### Contexto

O Capstone 2 exige o uso de recursão para os cálculos estatísticos (soma, mínimo, máximo, soma de quadrados).

### Decisão

Implementar `soma_recursiva`, `minimo_recursivo`, `maximo_recursivo` e `soma_quadrados_recursiva` como funções `static` internas em `estatisticas.c`. Usá-las em `preparar_linhas_estatisticas` e nas funções de resumo (`preparar_resumo_*`).

### Consequências

| | |
|---|---|
| ✅ | Atende ao requisito acadêmico de recursão |
| ✅ | Cálculo de desvio padrão viabilizado pela `soma_quadrados_recursiva` |
| ⚠️ | Para históricos muito grandes (> 1000 registros), a recursão pode causar stack overflow — aceitável para este escopo |

---

## ADR-004: Estado da UI em struct única (`EstadoUI`)

![Status](https://img.shields.io/badge/status-aceito-brightgreen?style=flat-square) ![Categoria](https://img.shields.io/badge/categoria-ui%2Festado-blueviolet?style=flat-square)

### Contexto

A versão Raylib precisava gerenciar múltiplas telas e estados (menu, jogo, resultado, histórico, estatísticas) de forma coesa.

### Decisão

Usar uma única struct `EstadoUI` com um campo `EstadoAplicacao estado_atual` (enum) que controla o fluxo. Toda a informação transiente da sessão (nome, partida em curso, cache de histórico) fica nessa struct.

### Consequências

| | |
|---|---|
| ✅ | Código de renderização e input centralizados e rastreáveis |
| ✅ | Fácil de serializar/debugar o estado atual |
| ⚠️ | Struct cresce conforme novas telas são adicionadas — pode exigir refatoração futura |

---

## ADR-005: Heurísticas como strings estáticas retornadas por função

![Status](https://img.shields.io/badge/status-aceito-brightgreen?style=flat-square) ![Categoria](https://img.shields.io/badge/categoria-memória-red?style=flat-square)

### Contexto

As mensagens de feedback estratégico/motivacional (Capstone 2) precisavam ser mostradas nas telas de resultado, sem alocar memória dinamicamente.

### Decisão

As funções `heuristica_adivinhacao` e `heuristica_memoria` retornam `const char *` apontando para literais de string estáticos (armazenados no segmento de dados do executável).

### Consequências

| | |
|---|---|
| ✅ | Zero alocação dinâmica, sem risco de leak |
| ✅ | Thread-safe (literais são imutáveis) |
| ⚠️ | Para adicionar novas heurísticas localizadas/dinâmicas no futuro, a interface precisará mudar |

---

> Adicione novos ADRs conforme decisões relevantes forem tomadas no projeto.

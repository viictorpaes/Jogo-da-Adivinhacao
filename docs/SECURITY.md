<h1 align="center">Segurança do RNG<br>
<img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="25"/></h1>

<p align="center"><b>Lógica de geração de números aleatórios em ambos os jogos, considerações sobre previsibilidade, viés estatístico e boas práticas para evitar vazamentos acidentais durante partidas ativas.</b></p>

## 🎮 Geração de Aleatoriedade por Módulo

O projeto usa `rand()` em dois contextos distintos — ambos dependem da mesma seed inicializada por `inicializar_rand()`:

### Jogo da Adivinhação — número secreto

O número secreto é sorteado de forma inline em [`src/game/jogo.c`](../src/game/jogo.c#L29) dentro do intervalo definido pelo nível de dificuldade:

| Nível | Intervalo | Tentativas | Desafio |
| :--- | :---: | :---: | :--- |
| **Fácil** | `[1, 10]` | 5 | 🟢 Baixo |
| **Médio** | `[1, 50]` | 8 | 🟡 Moderado |
| **Difícil** | `[1, 100]` | 10 | 🔴 Alto |

```c
// src/game/jogo.c:29 — geração inline
nova_partida.numero_secreto =
    (rand() % (nova_partida.max_range - nova_partida.min_range + 1))
    + nova_partida.min_range;
```

> [!NOTE]
> A função `rand_intervalo(min, max)` em [`src/utils/utils.c`](../src/utils/utils.c#L68) centraliza exatamente essa mesma lógica — mas **não é chamada** por `jogo.c`. Migrar o sorteio para `rand_intervalo()` eliminaria a duplicação e facilitaria uma futura troca por CSPRNG em um único ponto.

### Jogo da Memória — embaralhamento Fisher-Yates

O tabuleiro 4×4 (`TOTAL_CASAS = 16`) é embaralhado via algoritmo Fisher-Yates em [`src/game/memorygame.c`](../src/game/memorygame.c#L19):

```c
// src/game/memorygame.c:19 — Fisher-Yates com rand() direto
for (i = TOTAL_CASAS - 1; i > 0; i--) 
{
    j = rand() % (i + 1);
}
```

O Fisher-Yates exige `rand() % (i+1)` para cada posição `i` de 15 a 1. Para `i ≤ 15`, o viés máximo de módulo é idêntico ao caso `N = 16` — desprezível (< 0,005%).

### Inicialização da seed

Ambos os módulos consomem a seed inicializada **uma única vez** em `main()` — [`src/utils/utils.c`](../src/utils/utils.c#L63):

```c
void inicializar_rand(void) 
{
    srand((unsigned int)time(NULL));
}
```

> [!NOTE]
> `inicializar_rand()` é chamada **uma única vez** no início de `main()`, antes de qualquer partida. Chamar `srand()` múltiplas vezes reinicia a sequência e pode aumentar a previsibilidade.

---

## ✋ Viés de Módulo (*Mapping Bias*)

> [!WARNING]
> O código atual usa `rand() % N`. Quando `RAND_MAX + 1` não é múltiplo exato de `N`, alguns valores têm probabilidade ligeiramente maior de serem gerados.

Para os intervalos deste jogo (50, 100, 200 valores) e para o embaralhamento (N ≤ 16), o viés máximo é inferior a **0,005%** — imperceptível em gameplay. Para contextos que exijam distribuição uniforme rigorosa:

| Plataforma | Alternativa sem viés |
| :--- | :--- |
| <img src="https://img.shields.io/badge/macOS-020617?style=flat&logo=apple&logoColor=white" alt="macOS"/> | `arc4random_uniform(N)` — CSPRNG nativo, sem `srand()` |
| <img src="https://img.shields.io/badge/Linux-020617?style=flat&logo=linux&logoColor=yellow" alt="Linux"/> | `getrandom()` syscall + *rejection sampling* |
| Portabilidade | `rand()` com *rejection sampling* manual |

**Esquema de *rejection sampling*:**
1. Calcule `limite = RAND_MAX - (RAND_MAX % N)`
2. Rejeite valores `>= limite` e leia novamente
3. Use `valor % N` após aceitar


## 🔮 Sementeamento e Previsibilidade

> [!IMPORTANT]
> `srand(time(NULL))` é determinístico — quem conhecer o timestamp exato de início consegue reproduzir o número secreto **e** o layout do tabuleiro de memória.

Em um jogo single-player local sem adversário remoto, essa limitação não representa risco prático. Vale documentá-la para contextos futuros:

| Situação | Solução |
| :--- | :--- |
| macOS / BSD | `arc4random_uniform()` — sem `srand()`, não previsível |
| Linux moderno | `getrandom()` ou `/dev/urandom` + libsodium |
| Fins didáticos (implementação atual) | `srand(time(NULL))` — simples, suficiente para jogo local |


## 🔻 Persistência do Número Secreto

> [!CAUTION]
> Nunca imprima `numero_secreto` em `stdout`, `stderr` ou arquivos de log **durante uma partida ativa** — apenas ao término ou no histórico.

Ao fim de cada partida os dados são revelados ao jogador e salvos no histórico para auditoria. O módulo [`src/history/historico.c`](../src/history/historico.c) mantém dois pares de arquivos independentes:

**Jogo da Adivinhação** — `data/historico.csv` / `data/historico.txt`:

| Campo | Salvo | Finalidade |
| :--- | :---: | :--- |
| Data | ✅ | Registro temporal |
| Nome | ✅ | Identificação do jogador |
| Dificuldade | ✅ | Contexto da partida |
| Tentativas usadas / máx. | ✅ | Métricas de desempenho |
| Número secreto | ✅ | Auditoria e revisão pós-partida |
| Resultado (vitória/derrota) | ✅ | Histórico |
| Pontuação | ✅ | Ranking |

**Jogo da Memória** — `data/historico_memoria.csv` / `data/historico_memoria.txt`:

| Campo | Salvo | Finalidade |
| :--- | :---: | :--- |
| Data | ✅ | Registro temporal |
| Nome | ✅ | Identificação do jogador |
| Pontuação de pares | ✅ | Acertos no tabuleiro |
| Tentativas | ✅ | Eficiência na sessão |
| Pontos | ✅ | Ranking |

> [!NOTE]
> O número secreto já foi revelado ao jogador no fim da partida antes de ser persistido, portanto a gravação é intencional e não constitui vazamento. O layout do tabuleiro de memória não é persistido — apenas o resultado final.


## 🛡️ Segurança de Entrada

O código usa funções seguras de I/O em todas as entradas do usuário:

| Função | Local | Proteção |
| :--- | :--- | :--- |
| `fgets(buf, n, stdin)` | `ler_string()` em [`utils.c:41`](../src/utils/utils.c#L41) | Limita leitura a `n-1` bytes — sem buffer overflow |
| `strcspn(buf, "\n")` | `ler_string()` em [`utils.c:43`](../src/utils/utils.c#L43) | Remove `\n` residual sem acesso fora dos limites |
| `scanf("%d", &valor)` | `ler_inteiro()` em [`utils.c:21`](../src/utils/utils.c#L21) | Lê apenas inteiro; descarta resto da linha com `getchar()` |
| `sscanf(linha, "...", ...)` | `carregar_historico()` em [`historico.c:116`](../src/history/historico.c#L116) | Tamanhos explícitos em todos os especificadores (`%10[^,]`, `%63[^,]`) |
| `fopen()` com verificação de `NULL` | `salvar_partida()` em [`historico.c:62`](../src/history/historico.c#L62) | Falha silenciosa com aviso em vez de comportamento indefinido |
| `strncpy` + null-term explícita | `encontrar_ou_inserir()` em [`estatisticas.c:167`](../src/static/estatisticas.c#L167) | Cópia de nome limitada a `sizeof - 1` com `'\0'` garantido |
| `snprintf(buf, len, ...)` | `preparar_resumo_*()` em [`estatisticas.c`](../src/static/estatisticas.c) | Formatação segura com tamanho máximo sempre especificado |
| `localtime()` retorno verificado | `formatar_data_atual()` em [`utils.c:84`](../src/utils/utils.c#L84) | Null-check antes de `strftime()` — fallback para `"0000-00-00"` |


## 🖥️ Chamadas ao Sistema (`system()`)

`limpar_tela()` em [`src/utils/utils.c:48`](../src/utils/utils.c#L48) usa `system()` com strings literais fixas:

```c
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
```

Como o argumento nunca deriva de entrada do usuário, não há risco de injeção de comando. O custo é o fork de um processo de shell extra a cada limpeza de tela — aceitável para um jogo de console. Alternativas sem `system()` (`printf("\033[2J\033[H")` em ANSI) eliminariam o fork mas reduziriam a compatibilidade com terminais Windows.


## 🔁 Recursão em Estatísticas

As funções `soma_recursiva`, `minimo_recursivo`, `maximo_recursivo` e `soma_quadrados_recursiva` em [`src/static/estatisticas.c`](../src/static/estatisticas.c) são chamadas com profundidade até `MAX_HISTORICO = 500` — definido em [`src/include/tipos.h:18`](../src/include/tipos.h#L18).

Uma pilha de chamadas de profundidade 500, cada frame com poucos inteiros locais (~16–32 bytes), ocupa aproximadamente **8–16 KB** — bem dentro do limite padrão de 1–8 MB da maioria dos sistemas operacionais. Não representa risco de stack overflow para uso normal.

> [!NOTE]
> Se `MAX_HISTORICO` for aumentado para valores da ordem de dezenas de milhares, considerar converter as funções para versões iterativas.


## ⛳ Threat Model (Resumo)

| Ameaça | Status | Mitigação |
| :--- | :---: | :--- |
| Previsão do número via cronometragem do seed | ⚠️ Aceito | Jogo local sem adversário remoto; `arc4random_uniform()` eliminaria o risco |
| Vazamento de `numero_secreto` durante partida ativa | ✅ Mitigado | Número não é impresso enquanto a partida está em andamento |
| Previsão do layout do tabuleiro de memória | ⚠️ Aceito | Mesma seed; sem adversário remoto; `arc4random_uniform()` eliminaria o risco |
| Viés estatístico via `rand() % N` | ⚠️ Baixo | Intervalos pequenos (`≤ 200`, embaralhamento `≤ 16`) tornam o viés desprezível |
| Seed fixo hardcoded no binário | ✅ Mitigado | Seed sempre definida por `time(NULL)` em runtime |
| Buffer overflow em entradas do usuário | ✅ Mitigado | `fgets()` com tamanho explícito; `scanf` com flush do buffer |
| Corrupção de dados no histórico | ✅ Mitigado | `fopen()` verificado; parsing com tamanhos explícitos no `sscanf` |
| Injeção de comando via `system()` | ✅ Mitigado | Argumentos são strings literais fixas em tempo de compilação |
| Stack overflow nas funções recursivas de estatísticas | ✅ Mitigado | Profundidade máxima 500 (~16 KB de pilha) — dentro dos limites do SO |
| Duplicação da lógica de RNG (`rand_intervalo()` não usada) | ⚠️ Técnico | `rand_intervalo()` existe mas não é chamada; migração centralizaria futuras melhorias |


## ✅ Checklist de Implementação Segura

- [x] Seed inicializada uma única vez em `main()` via `inicializar_rand()`
- [x] `numero_secreto` não é impresso ou salvo **durante** a partida ativa
- [x] Entradas de texto usam `fgets()` com tamanho máximo — sem buffer overflow
- [x] Newline residual removida via `strcspn()` em `ler_string()`
- [x] `fopen()` verificado antes de qualquer escrita no histórico
- [x] Parsing do CSV com tamanhos explícitos em todos os especificadores do `sscanf`
- [x] `strncpy` com null-termination explícita ao copiar nomes no ranking
- [x] `snprintf` com tamanho limitado em toda formatação de strings
- [x] `localtime()` retorno verificado antes de `strftime()`
- [x] `system()` chamado apenas com strings literais fixas — sem injeção possível
- [ ] Migrar sorteio em `jogo.c` para usar `rand_intervalo()` ao invés de inline
- [ ] Migrar embaralhamento em `memorygame.c` para usar `rand_intervalo()` ao invés de `rand()` direto
- [ ] Substituir `rand() % N` por `arc4random_uniform(N)` em macOS/BSD
- [ ] Usar `getrandom()` ou `/dev/urandom` em Linux para RNG sem viés
- [ ] Implementar *rejection sampling* para distribuição uniforme rigorosa

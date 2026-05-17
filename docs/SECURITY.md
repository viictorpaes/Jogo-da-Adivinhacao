<h1 align="center">Segurança do RNG<br>
<img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="25"/></h1>

<p align="center"><b>Lógica de geração do número secreto, considerações sobre previsibilidade, viés estatístico e boas práticas para evitar vazamentos acidentais durante partidas ativas.</b></p>

---

## 🎮 Geração do Número Secreto por Nível

O número secreto é um inteiro dentro de um intervalo que depende do nível de dificuldade escolhido, definido em [`src/include/tipos.h`](../src/include/tipos.h):

| Nível | Intervalo | Tentativas | Desafio |
| :--- | :---: | :---: | :--- |
| **Fácil** | `[1, 50]` | 10 | 🟢 Baixo |
| **Médio** | `[1, 100]` | 7 | 🟡 Moderado |
| **Difícil** | `[1, 200]` | 5 | 🔴 Alto |

**Implementação atual** — geração inline em [`src/game/jogo.c`](../src/game/jogo.c#L29):

```c
// Seed já inicializada em main() via inicializar_rand()
nova_partida.numero_secreto =
    (rand() % (nova_partida.max_range - nova_partida.min_range + 1))
    + nova_partida.min_range;
```

**Inicialização da seed** — [`src/utils/utils.c`](../src/utils/utils.c#L63):

```c
void inicializar_rand(void) {
    srand((unsigned int)time(NULL));
}
```

> [!NOTE]
> `inicializar_rand()` é chamada **uma única vez** no início de `main()`, antes de qualquer partida. Chamar `srand()` múltiplas vezes reinicia a sequência e pode aumentar a previsibilidade.

---

## ✋ Viés de Módulo (*Mapping Bias*)

> [!WARNING]
> O código atual usa `rand() % N`. Quando `RAND_MAX + 1` não é múltiplo exato de `N`, alguns valores têm probabilidade ligeiramente maior de serem gerados.

Para os intervalos deste jogo (50, 100 e 200 valores), o viés máximo é inferior a **0,005%** — imperceptível em gameplay. Para contextos que exijam distribuição uniforme rigorosa:

| Plataforma | Alternativa sem viés |
| :--- | :--- |
| <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/> | `arc4random_uniform(N)` — CSPRNG nativo, sem `srand()` |
| <img src="https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black" alt="Linux"/> | `getrandom()` syscall + *rejection sampling* |
| Portabilidade | `rand()` com *rejection sampling* manual |

**Esquema de *rejection sampling*:**
1. Calcule `limite = RAND_MAX - (RAND_MAX % N)`
2. Rejeite valores `>= limite` e leia novamente
3. Use `valor % N` após aceitar

---

## 🔮 Sementeamento e Previsibilidade

> [!IMPORTANT]
> `srand(time(NULL))` é determinístico — quem conhecer o timestamp exato de início consegue reproduzir o número secreto.

Em um jogo single-player local sem adversário remoto, essa limitação não representa risco prático. Vale documentá-la para contextos futuros:

| Situação | Solução |
| :--- | :--- |
| macOS / BSD | `arc4random_uniform()` — sem `srand()`, não previsível |
| Linux moderno | `getrandom()` ou `/dev/urandom` + libsodium |
| Fins didáticos (implementação atual) | `srand(time(NULL))` — simples, suficiente para jogo local |

---

## 🔻 Persistência do Número Secreto

> [!CAUTION]
> Nunca imprima `numero_secreto` em `stdout`, `stderr` ou arquivos de log **durante uma partida ativa** — apenas ao término ou no histórico.

Ao fim de cada partida o número secreto é revelado ao jogador e salvo no histórico para auditoria. Campos gravados em `data/historico.csv` e `data/historico.txt` ([`src/history/historico.c`](../src/history/historico.c#L76)):

| Campo | Salvo | Finalidade |
| :--- | :---: | :--- |
| Data | ✅ | Registro temporal |
| Nome | ✅ | Identificação do jogador |
| Dificuldade | ✅ | Contexto da partida |
| Tentativas usadas / máx. | ✅ | Métricas de desempenho |
| Número secreto | ✅ | Auditoria e revisão pós-partida |
| Resultado (vitória/derrota) | ✅ | Histórico |
| Pontuação | ✅ | Ranking |

> [!NOTE]
> O número secreto já foi revelado ao jogador no fim da partida antes de ser persistido, portanto a gravação é intencional e não constitui vazamento.

---

## 🛡️ Segurança de Entrada

O código usa funções seguras de I/O em todas as entradas do usuário:

| Função | Local | Proteção |
| :--- | :--- | :--- |
| `fgets(buf, n, stdin)` | `ler_string()` em `utils.c` | Limita leitura a `n-1` bytes — sem buffer overflow |
| `scanf("%d", &valor)` | `ler_inteiro()` em `utils.c` | Lê apenas inteiro; descarta resto da linha com `getchar()` |
| `sscanf(linha, "...", ...)` | `carregar_historico()` em `historico.c` | Tamanhos explícitos em todos os especificadores (`%10[^,]`, `%63[^,]`) |
| `fopen()` com verificação de `NULL` | `salvar_partida()` em `historico.c` | Falha silenciosa com aviso em vez de comportamento indefinido |

---

## ⛳ Threat Model (Resumo)

| Ameaça | Status | Mitigação |
| :--- | :---: | :--- |
| Previsão do número via cronometragem do seed | ⚠️ Aceito | Jogo local sem adversário remoto; `arc4random_uniform()` eliminaria o risco |
| Vazamento de `numero_secreto` durante partida ativa | ✅ Mitigado | Número não é impresso enquanto a partida está em andamento |
| Viés estatístico via `rand() % N` | ⚠️ Baixo | Intervalos pequenos (`≤ 200`) tornam o viés desprezível em gameplay |
| Seed fixo hardcoded no binário | ✅ Mitigado | Seed sempre definida por `time(NULL)` em runtime |
| Buffer overflow em entradas do usuário | ✅ Mitigado | `fgets()` com tamanho explícito; `scanf` com flush do buffer |
| Corrupção de dados no histórico | ✅ Mitigado | `fopen()` verificado; parsing com tamanhos explícitos no `sscanf` |

---

## ✅ Checklist de Implementação Segura

- [x] Seed inicializada uma única vez em `main()` via `inicializar_rand()`
- [x] `numero_secreto` não é impresso ou salvo **durante** a partida ativa
- [x] Entradas de texto usam `fgets()` com tamanho máximo — sem buffer overflow
- [x] `fopen()` verificado antes de qualquer escrita no histórico
- [x] Parsing do CSV com tamanhos explícitos em todos os especificadores do `sscanf`
- [ ] Substituir `rand() % N` por `arc4random_uniform(N)` em macOS/BSD
- [ ] Usar `getrandom()` ou `/dev/urandom` em Linux para RNG sem viés
- [ ] Implementar *rejection sampling* para distribuição uniforme rigorosa

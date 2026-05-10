<h1 align="center">Segurança do RNG<br>
<img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="25"/></h1>

<p align="center"><b>Lógica de geração do número secreto, considerações sobre previsibilidade e boas práticas para evitar vazamentos ou engenharia reversa.</b></p>

---

## 🎮 Geração do Número Secreto por Nível

O número secreto é um inteiro dentro de um intervalo que depende do nível de dificuldade escolhido:

| Nível | Intervalo | Desafio |
| :--- | :---: | :--- |
| **Fácil** | `[1, 50]` | 🟢 Baixo |
| **Médio** | `[1, 100]` | 🟡 Moderado |
| **Difícil** | `[1, 500]` | 🔴 Alto |

**Fluxo de geração:**
1. Inicializar o RNG (seed);
2. Calcular um valor aleatório uniforme dentro do intervalo; e
3. Guardar o número **apenas em memória** — nunca registrar em logs antes do fim da partida.

```c
utils_inicializar_semente(); // seed com time + pid ou /dev/urandom
if (nivel == FACIL) intervalo = 50;
else if (nivel == MEDIO) intervalo = 100;
else intervalo = 500;

numero_secreto = utils_aleatorio_intervalo(1, intervalo);
```

---

## ✋ Evitando Viés de Módulo (*Mapping Bias*)

Usar `rand() % N` pode introduzir viés quando o espaço da RNG não for múltiplo exato de `N`.

| Plataforma | Recomendação |
| :--- | :--- |
| <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/> | `arc4random_uniform(N)` — evita viés internamente, não precisa de `srand()` |
| <img src="https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black" alt="Linux"/> | `getrandom()` ou `/dev/urandom` com *rejection sampling* |
| Portabilidade | `rand()` com *rejection sampling* manual (documentar limitação) |

**Esquema de *rejection sampling*:**
1. Calcule `max_aceitavel = floor(RANGE_MAX / N) * N - 1`
2. Leia um valor da RNG enquanto for maior que `max_aceitavel`
3. Use `valor % N` após aceitar

---

## 🔮 Sementeamento e Previsibilidade

> [!IMPORTANT]
> `srand(time(NULL))` é previsível — um atacante que conhece o horário de execução pode reproduzir a sequência.

**Mitigações recomendadas:**

| Situação | Solução |
| :--- | :--- |
| macOS / BSD | `arc4random_uniform()` — não determinístico, sem `srand()` |
| Linux moderno | `getrandom()` ou `/dev/urandom` + libsodium |
| Fins didáticos | `srand(time(NULL) ^ getpid())` — documentado como inseguro para produção |

---

## 🔻 Logs, Persistência e Vazamento Acidental

> [!CAUTION]
> Nunca registre `numero_secreto` em arquivos de log, `stdout` ou `stderr` durante uma partida ativa.

- O histórico salva apenas **metadados**: nome, tentativas, pontuação, nível — nunca o número secreto.
- Cuidado com dumps de memória e arquivos temporários de debug.

---

## 🔃 Modo de Teste / Reproducibilidade

Para testes automatizados, mantenha uma via controlada de determinismo:

```bash
# Força seed determinístico (apenas para CI/testing)
JOGO_SEED=42 ./jogo
```

```c
const char *seed_env = getenv("JOGO_SEED");
if (seed_env) 
{
    srand((unsigned int)atoi(seed_env)); 
} 
else 
{
    utils_inicializar_semente(); 
}
```

> [!NOTE]
> Documentar claramente que `JOGO_SEED` desabilita a aleatoriedade segura e deve ser usado **apenas em CI/testing**.

---

## ⛳ Threat Model (Resumo)

| Ameaça | Mitigação |
| :--- | :--- |
| Cronometragem do seed | RNG não previsível (`arc4random` / `getrandom`) |
| Engenharia reversa via logs | Não persistir o número secreto durante a partida |
| Seed fixo em produção | Seed controlado restrito a flag de ambiente |
| Análise de histórico | Histórico salva apenas metadados, não a resposta |

---

## ✅ Checklist de Implementação Segura

- [ ] Usar `arc4random_uniform()` em macOS/BSD para gerar o valor no intervalo
- [ ] Em Linux, usar `getrandom()` ou `/dev/urandom` com rejeição para evitar viés
- [ ] Não escrever `numero_secreto` em logs ou arquivos durante a partida
- [ ] Fornecer `JOGO_SEED` para testes de integração — documentado e isolado do modo de produção
- [ ] Documentar qualquer fallback (`srand(time() ^ getpid())`) como inseguro para produção

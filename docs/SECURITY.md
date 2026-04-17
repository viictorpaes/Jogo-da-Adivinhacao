<h1 align="center">SECURITY.md <br>
<img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" alt="Segurança"></h1>

<b>Este documento descreve a <mark>lógica de geração do número secreto do jogo</mark> conforme o nível de dificuldade e aponta considerações de segurança relacionadas ao gerador de números aleatórios (RNG), sementes e práticas para evitar previsibilidade e vazamento da solução.</b>

## Resumo da lógica por nível de dificuldade🎮

O jogo gera um número secreto inteiro dentro de um intervalo que depende do nível de dificuldade escolhido:

- Fácil: intervalo [1, 50]🟢
- Médio: intervalo [1, 100]🟡
- Difícil: intervalo [1, 500]🔴

A lógica básica é:
1. Inicializar o gerador de números aleatórios (seed);
2. Calcular/obter um valor aleatório uniforme dentro do intervalo apropriado; e
3. Guardar esse número apenas em memória (não registrar em logs) até o fim da partida.

Exemplo (pseudocódigo):

```c
// pseudocódigo ilustrativo
utils_inicializar_semente(); // ex.: seed com time + pid ou /dev/urandom
if (nivel == FACIL) intervalo = 50;
else if (nivel == MEDIO) intervalo = 100;
else intervalo = 500;

numero_secreto = gerar_uniforme(1, intervalo);
```

## Evitando viés de módulo (mapping bias)✋

Ao mapear um inteiro aleatório para um intervalo `[1..N]`, evitar usar `rand() % N` porque isso pode introduzir viés quando o espaço da RNG não for múltiplo exato de N.

Recomendações práticas:
- Em macOS/BSD, prefira `arc4random_uniform(N)` — ela evita viés internamente. <br> 
<img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/>
- Em Linux, use `getrandom()` ou leia `/dev/urandom` e aplique *rejection sampling* para evitar viés, ou use uma implementação de função que faça isso por você. <br>
<img src="https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black" alt="Linux"/>
- Se usar `rand()`/`srand()` por simplicidade, implemente rejection sampling ou escolha uma função utilitária que já trate o viés.

Exemplo de *rejection sampling* (esquemático):

1. Calcule `max_aceitavel = floor(RANGE_MAX / N) * N - 1` (onde RANGE_MAX é o máximo possível da RNG).
2. Leia um valor da RNG enquanto for maior que `max_aceitavel`.
3. Use `valor % N` após aceitar.

Mas, sempre que possível, prefira APIs modernas que já retornem valores sem viés.

## Sementeamento (seeding) e previsibilidade🔮

Problema: semente fraca (por exemplo `srand(time(NULL))` em um servidor ou numente local) pode tornar o número previsível por um atacante que conhece o horário de execução.

Mitigação:
- Em ambientes onde segurança/anti-cheat é importante, usar fontes de entropia do sistema: `getrandom()` (Linux) ou `arc4random()` / `arc4random_uniform()` (BSD/macOS). Estas funções são não determinísticas e devem ser preferidas.
- Para plataformas onde apenas `rand()` está disponível e compatibilidade é necessária, combine múltiplas fontes ao seed: tempo de alta resolução (microsegundos), PID do processo, leitura de `/dev/urandom` (se disponível). Ex.:

  seed = time_ns ^ getpid() ^ hash(free_entropy_bytes);

- Evite usar apenas `time(NULL)` em produção — é previsível.

## Recomendação prática por plataforma

- macOS / BSD: usar `arc4random_uniform(intervalo)` para gerar o número sem viés. Não precisa fazer `srand()`. <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/>

- Linux moderno: usar `getrandom()` ou ler `/dev/urandom` e transformar a saída em um inteiro no intervalo desejado (preferir `getrandom` quando disponível). Alternativamente, usar libs como libsodium para random seguro. <img src="https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black" alt="Linux"/>

- Portabilidade mínima: se o objetivo é educação e compatibilidade simples, documentar claramente que `utils_inicializar_semente()` usa `srand(time(NULL) ^ getpid())` e que isto é aceitável apenas para fins didáticos e testes.

## Logs, persistência e vazamento acidental 🔻

- Nunca logue o `numero_secreto` em arquivos de log nem em stdout/stderr durante uma partida ativa.
- Se o histórico salva detalhes técnicos da partida, registre apenas metadados (nome do jogador, número de tentativas, sucesso/falha, nível), não o número secreto.
- Tenha cuidado com dumps de memória e arquivos temporários de debug — não conter a senha/numero secreto.

## Modo de teste / reproducibilidade 🔃

Para permitir testes automatizados, mantenha uma via controlada de determinismo:
- Permitir uma variável de ambiente `JOGO_SEED` ou uma flag `--seed` que, quando presente, força seed determinístico (útil para testes unitários). Ex.:

  - Se `JOGO_SEED` definido, inicializar RNG com esse valor.
  - Caso contrário, usar RNG seguro/aleatório.

Documentar claramente que o modo com `JOGO_SEED` desabilita a aleatoriedade segura e deve ser usado apenas em CI/testing.

## Threat model (rápido)⛳️

- Ameaças principais: jogador mal-intencionado que quer descobrir o número por engenharia reversa, cronometragem do seed, acesso a logs ou dados históricos.
- Medidas mitigatórias: RNG não previsível, não persistir o número, evitar saltos de seed previsíveis, permitir seed controlado apenas em testes.

## Checklist de implementação segura (resumo)✅

- [ ] Usar `arc4random_uniform()` em macOS/BSD para gerar o valor no intervalo.
- [ ] Em Linux, usar `getrandom()` ou `/dev/urandom` com rejeição para mapear para o intervalo sem viés.
- [ ] Não escrever `numero_secreto` em logs ou arquivos.
- [ ] Fornecer `--seed`/`JOGO_SEED` para testes de integração (documentado e isolado do modo de produção).
- [ ] Documentar qualquer fallback (ex.: `srand(time() ^ getpid())`) e marcar como inseguro para produção.
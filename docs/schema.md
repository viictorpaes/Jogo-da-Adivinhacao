<h1 align="center">Schema de Dados<br>
<img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="25"/></h1>

<p align="center">Definição das estruturas de dados utilizadas para persistir o histórico de partidas em todos os modos de jogo.</p>

---

## 1. Adivinhação Solo — `data/historico.*`
<img src="https://img.shields.io/badge/-Adivinhação%20Solo-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>

Gerado por `salvar_partida(const RegistroPartida *)` em `src/history/historico.c`.

### Colunas (`historico.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida (`YYYY-MM-DD`) | `2026-05-23` |
| `nome` | `string` | Nome do jogador | `Lucas` |
| `dificuldade` | `enum` | `FÁCIL`, `MÉDIO` ou `DIFÍCIL` | `DIFÍCIL` |
| `tentativas_usadas` | `int` | Tentativas realizadas | `4` |
| `max_tentativas` | `int` | Limite de tentativas do nível | `10` |
| `numero_secreto` | `int` | Número sorteado (revelado pós-partida) | `73` |
| `resultado` | `enum` | `VITÓRIA` ou `DERROTA` | `VITÓRIA` |
| `pontos` | `int` | Pontuação calculada | `45` |

### Exemplo de linha

```
2026-05-23,Lucas,DIFÍCIL,4,10,73,VITÓRIA,45
```

---

## 2. Memória Solo — `data/historico_memoria.*`
<img src="https://img.shields.io/badge/-Memória%20Solo-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>

Gerado por `salvar_partida_memoria(const RegistroMemoria *)`.

### Colunas (`historico_memoria.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida | `2026-05-20` |
| `nome` | `string` | Nome do jogador | `Lucas` |
| `pontuacao` | `int` | Pares acertados × 10 | `80` |
| `tentativas` | `int` | Total de jogadas realizadas | `14` |
| `pontos` | `int` | Pontuação final (inclui bônus de eficiência) | `70` |

### Exemplo de linha

```
2026-05-20,Lucas,80,14,70
```

---

## 3. Adivinhação VS — `data/historico_vs.*`
<img src="https://img.shields.io/badge/-Adivinhação%20VS-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>

Gerado por `salvar_partida_vs(const RegistroVS *)`.

### Colunas (`historico_vs.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida | `2026-05-23` |
| `nome1` | `string` | Nome do Jogador 1 | `Ana` |
| `nome2` | `string` | Nome do Jogador 2 | `Pedro` |
| `dificuldade` | `string` | Nível / Patente usados na sessão | `CADETE` |
| `vitorias1` | `int` | Rodadas vencidas pelo J1 | `2` |
| `vitorias2` | `int` | Rodadas vencidas pelo J2 | `1` |
| `pontos1` | `int` | Pontuação acumulada do J1 | `65` |
| `pontos2` | `int` | Pontuação acumulada do J2 | `50` |
| `vencedor` | `int` | `1` (J1 venceu) ou `2` (J2 venceu) | `1` |

### Exemplo de linha

```
2026-05-23,Ana,Pedro,CADETE,2,1,65,50,1
```

---

## 4. Memória VS — `data/historico_memoria_vs.*`
<img src="https://img.shields.io/badge/-Memória%20VS-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>

Gerado por `salvar_partida_memoria_vs(const RegistroMemoria *r1, const RegistroMemoria *r2)`.

### Colunas (`historico_memoria_vs.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida | `2026-05-23` |
| `nome1` | `string` | Nome do Jogador 1 | `Ana` |
| `pares1` | `int` | Pares acertados pelo J1 | `5` |
| `pontos1` | `int` | Pontuação do J1 | `50` |
| `nome2` | `string` | Nome do Jogador 2 | `Pedro` |
| `pares2` | `int` | Pares acertados pelo J2 | `3` |
| `pontos2` | `int` | Pontuação do J2 | `30` |

### Exemplo de linha

```
2026-05-23,Ana,5,50,Pedro,3,30
```

---

## 5. Protocolo Lógico — `data/historico_logica.*`
<img src="https://img.shields.io/badge/-Protocolo%20Lógico-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>

Gerado por `salvar_puzzle(const RegistroPuzzle *)` com `modo = "logica"`.

### Colunas (`historico_logica.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida | `2026-05-23` |
| `nome` | `string` | Nome do jogador | `Lucas` |
| `acertos` | `int` | Questões respondidas corretamente | `9` |
| `total` | `int` | Total de questões da sessão | `16` |
| `pontos` | `int` | Pontuação final | `60` |
| `modo` | `string` | Sempre `logica` | `logica` |

### Exemplo de linha

```
2026-05-23,Lucas,9,16,60,logica
```

---

## 6. Hierarquia de Comandos — `data/historico_precedencia.*`
<img src="https://img.shields.io/badge/-Hierarquia%20de%20Cmds-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>

Gerado por `salvar_puzzle(const RegistroPuzzle *)` com `modo = "precedencia"`.

### Colunas (`historico_precedencia.csv`)

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data` | `string` | Data da partida | `2026-05-23` |
| `nome` | `string` | Nome do jogador | `Lucas` |
| `acertos` | `int` | Questões respondidas corretamente | `3` |
| `total` | `int` | Total de questões da sessão | `8` |
| `pontos` | `int` | Pontuação final | `30` |
| `modo` | `string` | Sempre `precedencia` | `precedencia` |

### Exemplo de linha

```
2026-05-23,Lucas,3,8,30,precedencia
```

---

## ⚠️ Notas de Implementação

> [!IMPORTANT]
> Evitar vírgulas no nome do jogador, pois o separador do CSV é `,`. Se necessário, troque o separador para `;` ou implemente escape no módulo `history/historico.c`.

> [!NOTE]
> O campo `data` usa o formato `YYYY-MM-DD`. Gerado via `strftime` com `"%Y-%m-%d"` em `utils.c`.

> [!NOTE]
> Todos os arquivos de histórico são inicializados com o cabeçalho correto na primeira execução pelas funções `inicializar_historico_*()`. Chamadas subsequentes não sobrescrevem dados existentes.

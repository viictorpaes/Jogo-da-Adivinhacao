<h1 align="center">Jornadas de Usuário
<br>
<img src="https://img.shields.io/badge/Jornadas_de_Usuário-111827?style=flat-square&logo=googlemaps&logoColor=white" height="20"/>
<img src="https://img.shields.io/badge/UX-Flows-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="20"/>
</h1>

Mapeamento das principais jornadas que um jogador pode percorrer no **CesarNumber**, identificando pontos de decisão, fricção e oportunidades de melhoria.

---

## Jornada 1 — Jogar (Entrada Rápida)

<img src="https://img.shields.io/badge/Persona-Ana_/_Bruno-22c55e?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Tempo_estimado-1–5_min-111827?style=flat-square&logo=clockify&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Alta-ef4444?style=flat-square" height="18"/>

```
Abrir o jogo
    └── Menu Principal
          └── Selecionar "Jogar"
                └── Escolher Dificuldade (Fácil / Médio / Difícil)
                      └── Loop de Tentativas
                            ├── [Acerto✅] → Resumo da Partida → Salvar? → Menu
                            └── [Limite⚠️] → Revelar Número → Resumo → Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Abertura | Executa o binário | Exibe menu principal | — |
| Escolha de modo | Seleciona "Jogar" | Exibe seleção de dificuldade | — |
| Dificuldade | Escolhe nível | Gera número secreto + informa intervalo | — |
| Tentativa | Insere palpite | Feedback termodinâmico + direção | Entrada inválida não explicada |
| Fim de partida | — | Exibe resumo com tentativas e pontuação | — |
| Pós-partida | Escolhe próxima ação | Salvar / Jogar novamente / Sair | Falta de confirmação ao sair |

> [!IMPORTANT]
> Cada jornada deve terminar com uma **ação clara**: voltar ao menu, reiniciar ou sair. Nunca deixar o usuário sem saída visível.

---

## Jornada 2 — Ver Histórico

<img src="https://img.shields.io/badge/Persona-Bruno_/_Carla-f59e0b?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Tempo_estimado-1–2_min-111827?style=flat-square&logo=clockify&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Ver Histórico"
          └── Listar Partidas (CSV / TXT)
                └── [Opcional] Detalhes de uma partida
                      └── Voltar ao Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Acesso | Seleciona "Histórico" | Lê `data/historico.csv` | Arquivo inexistente → erro não tratado |
| Listagem | — | Exibe partidas com data, tentativas, pontuação | Histórico extenso sem paginação |
| Detalhes | Seleciona uma entrada | Exibe detalhes da sessão | Funcionalidade não implementada ainda |
| Retorno | Escolhe voltar | Menu principal | — |

---

## Jornada 3 — Consultar Estatísticas

<img src="https://img.shields.io/badge/Persona-Carla-ef4444?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Tempo_estimado-30s–1_min-111827?style=flat-square&logo=clockify&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Estatísticas"
          └── Exibir métricas agregadas
                └── Voltar ao Menu
```

| Métrica Exibida | Fonte de Dados | Status |
| :--- | :--- | :---: |
| Média de tentativas | `historico.csv` | ✅ Implementando |
| Melhor pontuação | `historico.csv` | ✅ Implementando |
| Total de vitórias / derrotas | `historico.csv` | ✅ Implementando |
| Pior desempenho | `historico.csv` | ✅ Implementando |

---

## Jornada 4 — Jogo da Memória

<img src="https://img.shields.io/badge/Persona-Ana_/_Bruno-22c55e?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Modo-Raylib_Visual-111827?style=flat-square&logo=raylib&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal (Raylib)
    └── Selecionar "Jogo da Memória"
          └── Exibir grade de cartas
                └── Selecionar par de cartas
                      ├── [Par correto✅] → Cartas reveladas permanentemente
                      └── [Par errado❌] → Cartas viram novamente
                            └── [Todas reveladas🃏] → Tela de vitória → Menu
```

> [!NOTE]
> O Jogo da Memória está disponível apenas na versão **Raylib** (`make raylib`). O modo terminal oferece somente o jogo de adivinhação.

---

## Resumo das Jornadas

| Jornada | Personas | Duração Típica | Status |
| :--- | :--- | :---: | :---: |
| Jogar (Adivinhação) | Ana, Bruno, Carla | 1–5 min | ✅ Completo |
| Ver Histórico | Bruno, Carla | 1–2 min | ✅ Completo |
| Consultar Estatísticas | Carla | < 1 min | ✅ Completo |
| Jogo da Memória (Raylib) | Ana, Bruno | 2–5 min | ✅ Completo |

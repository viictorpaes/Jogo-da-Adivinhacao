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
          └── Selecionar "Missão: Adivinhação"
                └── Informar nome (Astronauta)
                      └── Escolher Patente Espacial (Cientista / Piloto / Buzz Lightyear)
                            └── Loop de Tentativas
                                  ├── [Acerto✅] → Resumo → Salvo automaticamente → Menu
                                  └── [Limite⚠️] → Revelar Número → Resumo → Salvo automaticamente → Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Abertura | Executa o binário | Exibe tela de boas-vindas + menu principal | — |
| Identificação | Informa nome | Sistema registra nome do astronauta | Nome vazio usa "Astronauta" como padrão |
| Escolha de modo | Seleciona "Missão: Adivinhação" | Exibe seleção de patente | — |
| Patente | Escolhe nível | Gera número secreto + informa intervalo e tentativas | — |
| Tentativa | Insere palpite | Sinal espacial (% do intervalo) + direção (maior/menor) | — |
| Fim de partida | — | Exibe resumo com tentativas e pontuação | — |
| Pós-partida | Pressiona ENTER | Salva automaticamente e retorna ao menu | Sem opção de não salvar |

> [!IMPORTANT]
> Cada jornada deve terminar com uma **ação clara**: voltar ao menu, reiniciar ou sair. Nunca deixar o usuário sem saída visível.

---

## Jornada 2 — Ver Histórico

<img src="https://img.shields.io/badge/Persona-Bruno_/_Carla-f59e0b?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Tempo_estimado-1–2_min-111827?style=flat-square&logo=clockify&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Registros de Missão"
          └── Listar Partidas (paginado, 15 por tela)
                └── Pressionar ENTER para avançar páginas
                      └── Voltar ao Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Acesso | Seleciona "Registros de Missão" | Lê `data/historico.txt` (criado automaticamente se inexistente) | — |
| Listagem | — | Exibe partidas com data, nome, dificuldade, tentativas, pontuação (15 por página) | Sem filtros ou busca por nome |
| Paginação | Pressiona ENTER | Avança para próxima página | — |
| Retorno | Pressiona ENTER na última página | Menu principal | — |

---

## Jornada 3 — Consultar Estatísticas

<img src="https://img.shields.io/badge/Persona-Carla-ef4444?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Tempo_estimado-30s–1_min-111827?style=flat-square&logo=clockify&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Painel de Controle"
          └── Exibir métricas agregadas (Adivinhação + Memória + Ranking)
                └── Pressionar ENTER → Voltar ao Menu
```

| Métrica Exibida | Fonte de Dados | Status |
| :--- | :--- | :---: |
| Total de partidas, vitórias e derrotas (%) | `historico.csv` | ✅ Implementado |
| Média de tentativas por dificuldade | `historico.csv` | ✅ Implementado |
| Melhor pontuação por dificuldade | `historico.csv` | ✅ Implementado |
| Estatísticas do Jogo da Memória | `historico_memoria.csv` | ✅ Implementado |
| Ranking geral combinado (top 10) | `historico.csv` + `historico_memoria.csv` | ✅ Implementado |

---

## Jornada 4 — Jogo da Memória

<img src="https://img.shields.io/badge/Persona-Ana_/_Bruno-22c55e?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Modo-Terminal_e_Raylib-111827?style=flat-square&logo=gnubash&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Missão: Jogo da Memória"
          └── Identificação do Astronauta (nome)
                └── Exibir tabuleiro 4×4 (16 casas, 8 pares de números)
                      └── Selecionar duas casas (1–16)
                            ├── [Par correto✅] → Casas reveladas permanentemente
                            └── [Par errado❌] → Casas ocultadas novamente
                                  └── [Todos os pares encontrados🃏] → Resumo → Salvo automaticamente → Menu
```

> [!NOTE]
> O Jogo da Memória está disponível no **modo terminal** (`make run`) e também na versão **Raylib** (`make raylib`). Cada acerto vale 10 pontos (máx. 80); a pontuação de eficiência desconta 5 pts por jogada além do mínimo teórico de 8.

---

## Resumo das Jornadas

| Jornada | Personas | Duração Típica | Status |
| :--- | :--- | :---: | :---: |
| Missão: Adivinhação | Ana, Bruno, Carla | 1–5 min | ✅ Completo |
| Registros de Missão | Bruno, Carla | 1–2 min | ✅ Completo |
| Painel de Controle (Estatísticas) | Carla | < 1 min | ✅ Completo |
| Missão: Jogo da Memória (Terminal + Raylib) | Ana, Bruno | 2–5 min | ✅ Completo |

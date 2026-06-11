<h1 align="center">Jornadas de Usuário
<br>
<img src="https://img.shields.io/badge/Jornadas_de_Usuário-111827?style=flat-square&logo=googlemaps&logoColor=white" height="20"/>
<img src="https://img.shields.io/badge/UX-Flows-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="20"/>
</h1>

Mapeamento das principais jornadas que um jogador pode percorrer no **CesarNumber**, identificando pontos de decisão, fricção e oportunidades de melhoria.

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

## Jornada 5 — Protocolo Lógico

<img src="https://img.shields.io/badge/Persona-Ana_/_Bruno_/_Carla-ef4444?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Modo-Terminal_e_Raylib-111827?style=flat-square&logo=gnubash&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Alta-ef4444?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Protocolo Lógico"
          └── Escolher Patente (Cadete / Piloto / Comandante)
                └── Loop de Questões
                      ├── Exibir fórmula proposicional (ex: (P ^ Q) -> ~R)
                      ├── Avaliar valor-verdade da fórmula para os valores exibidos
                      ├── [Timer esgotado⏰] → conta como erro, próxima questão
                      ├── [Acerto✅] → pontos acumulados
                      └── [Fim das questões🏁] → Resumo com patente → Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Seleção de patente | Escolhe dificuldade | Define nº de questões, variáveis e tempo por questão | — |
| Leitura da fórmula | — | Exibe fórmula + valores das variáveis + timer animado | Fórmulas com 3 variáveis podem ser complexas para iniciantes |
| Resposta | Pressiona `V` (Verdadeiro) ou `F` (Falso) | Registra acerto/erro, exibe próxima questão | Timer continua correndo durante a leitura |
| Classificação | Pressiona `T`, `C` ou `G` | Avalia contra todas as combinações da tabela-verdade | Conceitos de tautologia/contradição requerem conhecimento prévio |
| Resultado | — | Exibe pontuação total e patente conquistada | — |

> [!NOTE]
> No Raylib, o timer é exibido como barra animada com mudança de cor (verde → laranja → vermelho). No terminal, o countdown aparece em segundos ao lado da questão.

## Jornada 6 — Hierarquia de Comandos (Precedência)

<img src="https://img.shields.io/badge/Persona-Bruno_/_Carla-f59e0b?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Modo-Terminal_e_Raylib-111827?style=flat-square&logo=gnubash&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

```
Menu Principal
    └── Selecionar "Hierarquia de Comandos"
          └── Escolher Dificuldade (Fácil / Médio / Difícil)
                └── Loop de Questões
                      ├── Exibir expressão sem parênteses (ex: ~P ^ ~Q -> R <-> S)
                      ├── Escolher entre 4 alternativas de parentesização (embaralhadas)
                      ├── [Timer esgotado⏰] → conta como erro, próxima questão
                      ├── [Acerto✅] → pontos acumulados
                      └── [Fim das questões🏁] → Resumo com patente → Menu
```

| Etapa | Ação do Usuário | Resposta do Sistema | Ponto de Fricção |
| :--- | :--- | :--- | :--- |
| Seleção de dificuldade | Escolhe nível | Define operadores presentes e tempo por questão | — |
| Leitura da expressão | — | Exibe expressão + 4 alternativas embaralhadas + timer | Alternativas mudam de posição a cada exibição para evitar memorização |
| Resposta | Pressiona `1`, `2`, `3` ou `4` | Registra acerto/erro, exibe próxima questão | — |
| Resultado | — | Exibe pontuação total e patente conquistada | — |

> [!NOTE]
> As 4 alternativas são reembaralhadas com Fisher-Yates a cada exibição. Isso evita que o jogador memorize a posição da resposta correta entre sessões.

## Jornada 7 — Modos Versus (1v1)

<img src="https://img.shields.io/badge/Persona-Bruno_/_Carla-f59e0b?style=flat-square" height="18"/> <img src="https://img.shields.io/badge/Jogadores-2_(mesmo_dispositivo)-111827?style=flat-square&logo=gamepad&logoColor=white" height="18"/> <img src="https://img.shields.io/badge/Prioridade-Média-f59e0b?style=flat-square" height="18"/>

### 7a — Adivinhação VS (Batalha de Sinais)

```
Menu Principal
    └── Selecionar "Adivinhação VS"
          └── Informar nome dos 2 astronautas
                └── Escolher dificuldade
                      └── Loop de 3 Rodadas
                            ├── Turnos alternados — quem acertar primeiro ganha a rodada
                            ├── [12 tentativas sem acerto⚠️] → Rodada empatada
                            └── [3 rodadas concluídas🏁] → Placar final → Menu
```

### 7b — Memória VS (1v1 Mapas Estelares)

```
Menu Principal
    └── Selecionar "Memória VS"
          └── Informar nome dos 2 astronautas
                └── Tabuleiro 4×4 compartilhado
                      ├── Turnos alternados — cada jogador revela 2 casas
                      ├── [Par correto✅] → +10 pts ao jogador + turno extra
                      └── [8 pares encontrados🃏] → Placar final → vencedor declarado → Menu
```

| Aspecto | Adivinhação VS | Memória VS |
| :--- | :--- | :--- |
| **Estrutura** | 3 rodadas, turnos alternados | 1 tabuleiro compartilhado |
| **Critério de vitória** | Mais vitórias de rodada | Mais pares encontrados |
| **Bônus** | — | Acerto garante turno extra |
| **Duração típica** | 5–10 min | 3–8 min |
| **Persistência** | `data/historico_vs.csv` | `data/historico_memoria_vs.csv` |

> [!IMPORTANT]
> Ambos os modos VS são **local multiplayer** — os dois jogadores compartilham o mesmo teclado/mouse. Cada jogador deve chamar o colega quando for seu turno.

## Resumo das Jornadas

| Jornada | Personas | Duração Típica | Status |
| :--- | :--- | :---: | :---: |
| Missão: Adivinhação Solo | Ana, Bruno, Carla | 1–5 min | ✅ Completo |
| Registros de Missão | Bruno, Carla | 1–2 min | ✅ Completo |
| Painel de Controle (Estatísticas) | Carla | < 1 min | ✅ Completo |
| Missão: Jogo da Memória Solo | Ana, Bruno | 2–5 min | ✅ Completo |
| Protocolo Lógico | Ana, Bruno, Carla | 3–8 min | ✅ Completo |
| Hierarquia de Comandos | Bruno, Carla | 3–8 min | ✅ Completo |
| Adivinhação VS (Batalha de Sinais) | Bruno, Carla | 5–10 min | ✅ Completo |
| Memória VS (1v1 Mapas Estelares) | Ana, Bruno | 3–8 min | ✅ Completo |
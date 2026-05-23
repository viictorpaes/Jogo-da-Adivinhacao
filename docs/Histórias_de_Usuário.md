# Histórias de Usuário — Missão Espacial: <br> Adivinhação, Memória, Protocolo Lógico & **Hierarquia de Comandos**

> **Formato:** Como `[papel]`, quero `[funcionalidade]`, para que `[benefício]`.

![Histórias Implementadas](https://img.shields.io/badge/HUs%20Implementadas-28-brightgreen?style=flat-square&logo=checkmarx&logoColor=white)
![Histórias Futuras](https://img.shields.io/badge/HUs%20Futuras-16-blue?style=flat-square&logo=rocket&logoColor=white)

---

## 🎮 Jogos Disponíveis

| # | Nome do Jogo | Modalidade | Módulo |
|---|---|---|---|
| 1 | 🔭 **Missão: Adivinhação** | Solo | `src/game/jogo.c` |
| 2 | ⚔️ **Batalha de Sinais** | Adivinhação VS — 2 jogadores | `src/game/jogo.c` |
| 3 | 🧠 **Jogo da Memória** | Solo | `src/game/jogar_memoria.c` / `src/game/memorygame.c` |
| 4 | 🪐 **1v1 Mapas Estelares** | Memória VS — 2 jogadores | `src/game/memorygame.c` |
| 5 | 🧮 **Protocolo Lógico** | Fórmulas Proposicionais V/F — Solo | `src/game/logica.c` |
| 6 | 🔢 **Hierarquia de Comandos** | Precedência de Operadores — Solo | `src/game/precedencia.c` |

> Todos os jogos estão disponíveis na versão **terminal** (`src/main.c`) e na versão **gráfica Raylib** (`src/main_raylib.c` + `src/ui/frontend.c`).

---

## ✅ Implementadas

### 🏠 Tela Inicial e Navegação

| # | História |
|---|---|
| HU-01 | Como **visitante**, quero ver o menu principal ao iniciar o jogo, para que eu possa escolher entre os modos disponíveis (Adivinhação / Memória) ou consultar o ranking. |
| HU-02 | Como **visitante**, quero acessar o ranking diretamente do menu principal, para que eu conheça os melhores jogadores antes de começar a jogar. |

---

### ⚙️ Configuração de Partida

| # | História |
|---|---|
| HU-03 | Como **jogador**, quero inserir meu nome antes de começar, para que meu resultado seja identificado no ranking e no histórico de partidas. |
| HU-04 | Como **jogador**, quero escolher o nível de dificuldade (Fácil / Médio / Difícil), para que eu possa ajustar o intervalo de números e o número de tentativas ao meu nível. |

---

### 🔭 Jogo de Adivinhação (Solo — Terminal e Raylib)

| # | História |
|---|---|
| HU-05 | Como **jogador**, quero que um número aleatório seja gerado a cada partida com base no tempo do sistema, para que o jogo seja imprevisível e justo. |
| HU-06 | Como **jogador**, quero comparar meu palpite com o número secreto e receber feedback de "maior" ou "menor", para que eu possa ajustar minha estratégia de busca. |
| HU-07 | Como **jogador**, quero receber feedback de proximidade espacial após cada tentativa ("Sem sinal" / "Interferência estática" / "Sinal detectado" / "Frequência muito próxima" / "Sinal estabelecido!"), para que eu saiba quão perto estou do alvo de forma imersiva. |
| HU-08 | Como **jogador**, quero que entradas inválidas (fora do intervalo ou não numéricas) sejam rejeitadas com mensagem de erro, para que o jogo não seja interrompido por inputs incorretos. |
| HU-09 | Como **jogador**, quero saber quantas tentativas restam a cada rodada, para que eu possa gerenciar minha estratégia antes de esgotar as chances. |
| HU-10 | Como **jogador**, quero um cronômetro regressivo por tentativa (15s), para que cada palpite tenha urgência e uma tentativa seja consumida automaticamente ao esgotar o tempo. |

---

### ⚔️ Batalha de Sinais (Adivinhação VS — 2 Jogadores)

| # | História |
|---|---|
| HU-11 | Como **jogador**, quero disputar a adivinhação contra outro jogador em turnos alternados no mesmo dispositivo, para que a competição seja possível sem necessidade de rede. |
| HU-12 | Como **jogador VS**, quero que o jogo se estenda por até 3 rodadas com placar acumulado, para que o vencedor seja determinado pela melhor de 3 e não por uma única tentativa. |

---

### 🌕 Jogo da Memória (Solo)

| # | História |
|---|---|
| HU-13 | Como **jogador**, quero virar pares de cartas em um grid 4×4 para combiná-los, para que eu complete o tabuleiro memorizando as posições das coordenadas. |
| HU-14 | Como **jogador**, quero um cronômetro regressivo na memória (base 30s + bônus de 10s por par acertado), para que cada erro custe tempo e acertos prolonguem a partida. |
| HU-15 | Como **jogador**, quero ver um contador de pares encontrados e jogadas realizadas em tempo real, para que eu acompanhe meu desempenho durante a partida. |
| HU-16 | Como **jogador**, quero que cartas erradas fiquem visíveis por um instante antes de serem ocultadas novamente, para que eu tenha chance de memorizar as posições. |

---

### 🪐 1v1 Mapas Estelares (Memória VS)

| # | História |
|---|---|
| HU-24 | Como **jogador**, quero disputar o jogo da memória contra outro jogador em turnos no mesmo dispositivo, com timer independente por jogador, para que a partida seja equilibrada e competitiva. |
| HU-25 | Como **jogador VS de memória**, quero que quem acertar um par continue jogando e quem errar passe o turno ao adversário, para que a estratégia de manter turnos longos seja recompensada. |

---

### 🧮 Protocolo Lógico (Fórmulas V/F)

| # | História |
|---|---|
| HU-26 | Como **jogador**, quero avaliar se uma fórmula proposicional é Verdadeira ou Falsa para os valores dados de P, Q e R, para que eu pratique lógica proposicional de forma interativa. |
| HU-27 | Como **jogador**, quero classificar cada fórmula como Tautologia, Contradição ou Contingência após respondê-la, para que eu aprofunde meu entendimento sobre classificação lógica. |
| HU-28 | Como **jogador**, quero receber um timer por questão (15–30s conforme dificuldade) e feedback imediato ao final, para que a pressão do tempo torne o estudo mais desafiador. |

---

### 🔢 Hierarquia de Comandos (Precedência de Operadores)

| # | História |
|---|---|
| HU-29 | Como **jogador**, quero receber uma expressão lógica sem parênteses e escolher qual opção de parentetização respeita a precedência dos operadores (~, ^, V, ->, <->), para que eu pratique a ordem de avaliação de fórmulas. |
| HU-30 | Como **jogador**, quero que as opções de resposta sejam embaralhadas a cada questão, para que a posição da alternativa correta não seja previsível. |
| HU-31 | Como **jogador**, quero receber feedback visual destacando a resposta correta ao final de cada questão e uma pontuação acumulada, para que eu saiba onde errei e motive a melhora. |

---

### 📁 Registro e Histórico

| # | História |
|---|---|
| HU-17 | Como **jogador**, quero que meu número de tentativas seja salvo ao final de cada partida em um arquivo, para que o progresso não seja perdido ao fechar o terminal. |
| HU-18 | Como **jogador**, quero consultar o histórico completo de partidas armazenado no arquivo, para que eu revise todas as sessões já jogadas. |

---

### 📊 Estatísticas e Ranking

| # | História |
|---|---|
| HU-19 | Como **jogador**, quero ver a média de tentativas calculada a partir do meu histórico, para que eu acompanhe minha evolução ao longo das partidas. |
| HU-20 | Como **jogador**, quero ver minha melhor e pior sessão com base no número de tentativas, para que eu identifique meu desempenho máximo e mínimo registrado. |
| HU-21 | Como **visitante**, quero ver o ranking com os melhores jogadores ordenado por menos tentativas, para que os mais eficientes sejam destacados no topo. |

---

### 🎨 Interface Gráfica (Raylib)

| # | História |
|---|---|
| HU-22 | Como **jogador**, quero uma versão gráfica do jogo com janela dedicada (1200×800), para que a experiência seja mais visual e atraente do que a versão de terminal. |
| HU-23 | Como **jogador na versão gráfica**, quero navegar pelos menus com mouse e teclado, para que a interação seja fluida e intuitiva. |

<hr>

## 🚀 Podem Ser Implementadas no Futuro

> As histórias abaixo são viáveis com base na infraestrutura já existente (módulos, arquivos de dados e estrutura modular do projeto).

---

### 🔐 Perfil Persistente do Jogador

> *A estrutura de histórico em CSV e o módulo `history/` já salvam dados por nome — falta uma camada de autenticação e persistência de sessão.*

| # | História |
|---|---|
| HU-F01 | Como **jogador recorrente**, quero criar um perfil com apelido único que persista entre sessões, para que meu histórico acumulado não dependa de digitar o mesmo nome manualmente. |
| HU-F02 | Como **jogador cadastrado**, quero que minhas partidas sejam associadas automaticamente ao meu perfil ao iniciar o jogo, para que o registro seja feito sem esforço adicional. |

---

### 👤 Estatísticas Avançadas do Jogador

> *Os arquivos CSV já armazenam dados suficientes para calcular métricas adicionais.*

| # | História |
|---|---|
| HU-F03 | Como **jogador**, quero ver um resumo de desempenho separado por modo de jogo (Adivinhação / Memória / VS), para que eu compare minha evolução em cada modalidade. |
| HU-F04 | Como **jogador**, quero ver um gráfico simples de tentativas por partida em ordem cronológica no terminal, para que eu visualize tendência de melhora ao longo do tempo. |
| HU-F05 | Como **jogador**, quero ver conquistas desbloqueadas (ex.: "Acertou na 1ª tentativa", "Zerou no Difícil"), para que eu me sinta recompensado por marcos atingidos. |

---

### 🎮 Novos Modos e Recursos de Jogo

| # | História |
|---|---|
| HU-F06 | Como **jogador**, quero receber efeitos sonoros ao acertar, errar ou esgotar as tentativas na versão Raylib, para que a experiência seja mais imersiva. |
| HU-F07 | Como **jogador no modo VS**, quero disputar rodadas online contra outro jogador via rede local, para que a Batalha de Sinais possa ser jogada remotamente. |
| HU-F08 | Como **jogador**, quero um modo torneio com chaveamento eliminatório entre múltiplos jogadores, para que grupos possam competir em campeonatos. |
| HU-F09 | Como **jogador no modo Memória**, quero uma animação de virada de carta com efeito de flip, para que a interação visual seja mais satisfatória. |

---

### 🏆 Ranking Avançado

| # | História |
|---|---|
| HU-F10 | Como **visitante**, quero filtrar o ranking por modo de jogo (Adivinhação / Memória / VS), para que eu compare desempenhos separados por modalidade. |
| HU-F11 | Como **visitante**, quero filtrar o ranking por período (diário / semanal / mensal), para que eu acompanhe os jogadores mais ativos recentemente. |
| HU-F12 | Como **visitante**, quero ver medalhas 🥇🥈🥉 para o top 3 e posição numérica para os demais, para que o pódio seja destacado visualmente. |
| HU-F13 | Como **jogador**, quero ver minha posição no ranking global imediatamente após salvar uma partida, para que eu saiba onde estou entre todos os jogadores registrados. |

---

### 🔔 Experiência e Acessibilidade

| # | História |
|---|---|
| HU-F14 | Como **jogador**, quero escolher entre tema claro e tema escuro na versão Raylib, para que o visual se adapte à minha preferência ou ambiente de jogo. |
| HU-F15 | Como **jogador**, quero compartilhar meu resultado com uma mensagem gerada automaticamente, para que eu mostre minha conquista a outros jogadores. |
| HU-F16 | Como **jogador com necessidades especiais**, quero que mensagens de feedback usem cores de alto contraste e símbolos além de cores, para que o jogo seja acessível independentemente de percepção de cores. |

---

## 📋 Resumo

| Status | Quantidade |
|---|---|
| ✅ Implementadas | 28 histórias |
| 🚀 Futuras | 16 histórias |
| **Total** | **44 histórias** |

---

> Histórias originais do backlog (HU1–HU10) disponíveis com diagramas de atividade em [`/img/`](../img/) e no [Trello](https://trello.com/b/yp8S6Ek9/jogo-de-adivinhacao-projetos-2-pif-fds-ihc).

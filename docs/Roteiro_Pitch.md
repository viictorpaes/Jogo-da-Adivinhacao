<h1 align="center">Roteiro — Vídeo Demo (2 min)<br>
<img src="https://img.shields.io/badge/Pitch-17%2F06%2F2026-111827?style=flat-square&logo=slides&logoColor=white" height="25"/>
<img src="https://img.shields.io/badge/Duração-2_min_máx-ef4444?style=flat-square&logo=clockify&logoColor=white" height="25"/>
<img src="https://img.shields.io/badge/Formato-Screencast-red?style=flat-square&logo=youtube&logoColor=FF0000" height="25"/></h1>

<p align="center"><b>Roteiro cena a cena para o vídeo demo de até 2 minutos do CesarNumber — Missão Espacial.</b></p>

## ⏱️ Estrutura de Cenas (120 segundos)

| # | Cena | Tempo | O que mostrar | Narração |
| :---: | :--- | :---: | :--- | :--- |
| 1 | **Abertura** | 0:00–0:12 | Tela do menu principal Raylib com trilha sonora tocando | *"CesarNumber — 6 modos de jogo, escrito em C puro, rodando em macOS, Linux e Windows."* |
| 2 | **Adivinhação Solo** | 0:12–0:38 | Entrar em Operação Resgate (Piloto), digitar nome, fazer 3 palpites com feedbacks de sinal, mostrar timer regressivo ficando laranja | *"No modo Solo, o astronauta adivinha o número secreto. Cada palpite devolve um sinal de proximidade — e o timer pressiona."* |
| 3 | **Modo Duo** | 0:38–1:00 | Entrar no modo Duo, mostrar os dois jogadores alternando palpites, exibir quem acertou primeiro e a pontuação | *"No Duo, dois jogadores se enfrentam na mesma máquina. Velocidade e lógica decidem quem vence."* |
| 4 | **Mapas Estelares** | 1:00–1:18 | Tabuleiro 4×4, virar uma carta, virar outra errada (animação de fechar), depois revelar um par correto com brilho de acerto | *"Mapas Estelares é um jogo de memória espacial — encontre todos os pares antes que o tempo acabe."* |
| 5 | **Protocolo Lógico** | 1:18–1:36 | Abrir Protocolo Lógico (Piloto), mostrar uma fórmula proposicional, responder V/F nas colunas, receber classificação Tautologia | *"Protocolo Lógico exige raciocínio formal: preencha a tabela-verdade e classifique a fórmula em tempo real."* |
| 6 | **Estatísticas** | 1:36–1:50 | Painel de Estatísticas com ranking, média de tentativas e desvio padrão; rolar levemente para o Histórico filtrado por jogador | *"Tudo é persistido — histórico por jogador, ranking de pontos e estatísticas analíticas por modo."* |
| 7 | **Encerramento** | 1:50–2:00 | Voltar ao menu Raylib por 3 s → corte para terminal rodando `make run` por 3 s → logo ou slide final | *"Terminal ou Raylib — mesmo código, duas interfaces. CesarNumber."* |

> [!WARNING]
> **2 minutos é o limite absoluto.** Ensaie cada cena com cronômetro. Se uma transição atrasar, corte o Modo Duo (Cena 3) e redistribua os 22 s entre as outras cenas.


## 🎬 Detalhamento por Cena

### Cena 1 — Abertura (0:00–0:12)

**Na tela:** menu principal do Raylib já aberto, música tocando, fundo animado visível.  
**Ação:** nenhuma interação pelos primeiros 5 s — deixar o visual e o áudio falar. Depois mover o cursor lentamente sobre as opções do menu até pousar em "Operação Resgate".

> *"CesarNumber — 6 modos de jogo, escrito em C puro, rodando em macOS, Linux e Windows."*


### Cena 2 — Adivinhação Solo (0:12–0:38)

**Na tela:** entrar em Operação Resgate → digitar nome → selecionar patente Piloto → jogar.  
**Ação:** fazer 3 palpites deliberadamente errados para mostrar o feedback de sinal (`Sinal detectado!`, `Frequência muito próxima!`, `Muito distante!`). Deixar o timer chegar ao laranja. Acertar no 4.º palpite.

> *"No modo Solo, o astronauta adivinha o número secreto. Cada palpite devolve um sinal de proximidade — e o timer pressiona."*

> [!TIP]
> Prepare o número de antemão (consulte o histórico ou fixe uma semente). Isso garante acertar no momento certo sem arriscar estourar o tempo da cena.


### Cena 3 — Modo Duo (0:38–1:00)

**Na tela:** selecionar Modo Duo no menu → inserir nome dos dois jogadores → iniciar partida.  
**Ação:** Jogador 1 faz um palpite (errado), Jogador 2 faz um palpite (acerta). Mostrar a tela de vitória com a pontuação dos dois.

> *"No Duo, dois jogadores se enfrentam na mesma máquina. Velocidade e lógica decidem quem vence."*

> [!TIP]
> Combine com um colega antes: Jogador 1 chuta longe, Jogador 2 acerta. O fluxo fica limpo e não ocupa mais de 22 s.


### Cena 4 — Mapas Estelares (1:00–1:18)

**Na tela:** selecionar Mapas Estelares Solo → grid 4×4 aparece com cartas viradas.  
**Ação:** virar carta A (símbolo ★) → virar carta B (símbolo ♦, diferente) → animação de fechar. Em seguida virar carta C (★) → carta D (★, par correto) → animação de brilho de acerto.

> *"Mapas Estelares é um jogo de memória espacial — encontre todos os pares antes que o tempo acabe."*


### Cena 5 — Protocolo Lógico (1:18–1:36)

**Na tela:** selecionar Protocolo Lógico (Piloto) → exibir fórmula proposicional (ex.: `p → (p ∨ q)`).  
**Ação:** preencher duas colunas V/F → receber a classificação "Tautologia" em destaque. Mostrar o timer no canto.

> *"Protocolo Lógico exige raciocínio formal: preencha a tabela-verdade e classifique a fórmula em tempo real."*


### Cena 6 — Estatísticas (1:36–1:50)

**Na tela:** menu → Estatísticas → painel carregado com dados reais (jogar partidas antes da gravação).  
**Ação:** rolar devagar para mostrar ranking de pontos, média de tentativas, desvio padrão. Se couber no tempo, filtrar o Histórico pelo nome usado na Cena 2.

> *"Tudo é persistido — histórico por jogador, ranking de pontos e estatísticas analíticas por modo."*


### Cena 7 — Encerramento (1:50–2:00)

**Na tela:** voltar ao menu Raylib → deixar a trilha sonora por 3 s → corte para terminal com `make run` executando a versão console por 3 s → slide final com logo do projeto.

> *"Terminal ou Raylib — mesmo código, duas interfaces. CesarNumber."*


## 🛠️ Configuração Recomendada para Gravação

| Item | Recomendação |
| :--- | :--- |
| **Resolução** | 1920×1080 (ou janela 1200×800 do Raylib em tela cheia de gravação) |
| **Frame rate** | 60 fps — o timer animado fica mais suave |
| **Ferramenta de captura** | OBS Studio, QuickTime (macOS) ou ShareX (Windows) |
| **Áudio** | Manter a trilha sonora do jogo; **não** gravar microfone — colocar narração em off na edição |
| **Edição** | DaVinci Resolve (gratuito) ou CapCut para cortes e legendas de cena |
| **Formato de entrega** | `.mp4` H.264, sem cortes abruptos entre cenas |

> [!NOTE]
> Grave cada cena separadamente e edite depois — é mais rápido do que tentar acertar tudo em uma única tomada.

## ✅ Checklist Pré-Gravação

- [x] `make raylib` compila e roda sem erros na máquina de gravação
- [x] Histórico com dados reais gravado em `data/` (jogar algumas partidas antes)
- [x] Resolução de tela e gravação confirmadas (sem notificações ou janelas abertas)
- [x] Exportar o vídeo final e assistir do início ao fim antes de subir

> [!NOTE]
> Consulte [GAMES.md](GAMES.md) para as regras detalhadas de cada modo e [ARCHITECTURE.md](ARCHITECTURE.md) para a estrutura modular do projeto.
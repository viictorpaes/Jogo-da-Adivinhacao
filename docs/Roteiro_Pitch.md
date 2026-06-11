<h1 align="center">Roteiro — Vídeo Demo (1 min)<br>
<img src="https://img.shields.io/badge/Pitch-16%2F06%2F2026-111827?style=flat-square&logo=slides&logoColor=white" height="25"/>
<img src="https://img.shields.io/badge/Duração-1_min_máx-ef4444?style=flat-square&logo=clockify&logoColor=white" height="25"/>
<img src="https://img.shields.io/badge/Formato-Screencast-red?style=flat-square&logo=youtube&logoColor=FF0000" height="25"/></h1>

<p align="center"><b>Roteiro cena a cena para o vídeo demo de até 1 minuto do CesarNumber — Missão Espacial.</b></p>

## ⏱️ Estrutura de Cenas (60 segundos)

| # | Cena | Tempo | O que mostrar | Narração |
| :---: | :--- | :---: | :--- | :--- |
| 1 | **Abertura** | 0:00–0:06 | Tela do menu principal Raylib com trilha sonora tocando | *"CesarNumber — 6 modos de jogo, em C, rodando em 3 sistemas operacionais."* |
| 2 | **Adivinhação Solo** | 0:06–0:22 | Entrar em Operação Resgate (Piloto), fazer 2 palpites, mostrar o timer regressivo e o feedback de sinal | *"No modo Solo, o astronauta adivinha o número secreto com timer e feedback de proximidade."* |
| 3 | **Memória & Lógica** | 0:22–0:38 | Corte rápido: tabuleiro 4×4 de Mapas Estelares com par revelado → corte para Protocolo Lógico com uma fórmula e classificação | *"Mapas Estelares testa memória. Protocolo Lógico avalia tabelas-verdade em tempo real."* |
| 4 | **Estatísticas** | 0:38–0:50 | Painel de Estatísticas com ranking, médias e desvio padrão; rolar levemente para mostrar o Histórico | *"Tudo é persistido — histórico filtrado por jogador e estatísticas analíticas por modo."* |
| 5 | **Encerramento** | 0:50–1:00 | Voltar ao menu; exibir terminal rodando `make run` por 3 s; encerrar com logo ou slide estático | *"Terminal ou Raylib — mesmo código, duas interfaces. macOS, Linux e Windows."* |

> [!WARNING]
> **60 segundos é o limite absoluto.** Corte qualquer cena que ultrapasse o tempo — prefira mostrar menos modos com fluidez do que tentar cobrir todos com pressa.


## 🎬 Detalhamento por Cena

### Cena 1 — Abertura (0:00–0:06)

**Na tela:** menu principal do Raylib já aberto, música tocando.  
**Ação:** nenhuma interação — deixar o visual falar por 3 s, depois mover o cursor para "Operação Resgate".

> *"CesarNumber — 6 modos de jogo, em C, rodando em 3 sistemas operacionais."*


### Cena 2 — Adivinhação Solo (0:06–0:22)

**Na tela:** entrar em Operação Resgate → digitar nome → selecionar patente Piloto → jogar.  
**Ação:** fazer 2 palpites deliberadamente errados para mostrar o feedback de sinal (`Sinal detectado!`, `Frequência muito próxima!`), depois acertar ou deixar o timer chegar ao laranja/vermelho.

> *"No modo Solo, o astronauta adivinha o número secreto com timer e feedback de proximidade."*

> [!TIP]
> Pratique antes: os palpites certos para um número entre 1–50 são fáceis de preparar com uma semente fixada ou simplesmente conhecendo o número de antemão pelo histórico.


### Cena 3 — Memória & Lógica (0:22–0:38)

**Na tela (parte A — 8 s):** abrir Mapas Estelares Solo, mostrar o grid 4×4, revelar um par correto (brilho de acerto).  
**Corte imediato.**  
**Na tela (parte B — 8 s):** abrir Protocolo Lógico (Piloto), mostrar uma fórmula, responder V/F, classificar como Tautologia — tudo dentro do timer.

> *"Mapas Estelares testa memória. Protocolo Lógico avalia tabelas-verdade em tempo real."*


### Cena 4 — Estatísticas (0:38–0:50)

**Na tela:** menu → Estatísticas → painel carregado com dados reais.  
**Ação:** rolar devagar para revelar ranking de pontos e, se couber, o Histórico filtrado por nome.

> *"Tudo é persistido — histórico filtrado por jogador e estatísticas analíticas por modo."*

### Cena 5 — Encerramento (0:50–1:00)

**Na tela:** voltar ao menu Raylib por 3 s → corte para terminal com `make run` executando a versão console por 3 s → logo ou slide final.

> *"Terminal ou Raylib — mesmo código, duas interfaces. macOS, Linux e Windows."*

## 🛠️ Configuração Recomendada para Gravação

| Item | Recomendação |
| :--- | :--- |
| **Resolução** | 1920×1080 (ou janela 1200×800 do Raylib em tela cheia de gravação) |
| **Frame rate** | 60 fps — o timer animado fica mais suave |
| **Ferramenta de captura** | OBS Studio, QuickTime (macOS) ou ShareX (Windows) |
| **Áudio** | Manter a trilha sonora do jogo; **não** gravar microfone — colocar narração em off na edição |
| **Edição** | DaVinci Resolve (gratuito) ou CapCut para cortes e legenda de cena |
| **Formato de entrega** | `.mp4` H.264, sem cortes abruptos entre cenas |

> [!NOTE]
> Grave cada cena separadamente e edite depois — é mais rápido do que tentar acertar tudo em uma única tomada.

## ✅ Checklist Pré-Gravação

- [ ] `make raylib` compila e roda sem erros na máquina de gravação
- [ ] Histórico com dados reais gravado em `data/` (jogar algumas partidas antes)
- [ ] Resolução de tela e gravação confirmadas (sem notificações ou janelas abertas)
- [ ] Trilha sonora audível no nível correto (não distorce na captura)
- [ ] Cronometrar um ensaio completo — se passar de 55 s, cortar Cena 3 para apenas um modo
- [ ] Exportar o vídeo final e assistir do início ao fim antes de subir

> [!NOTE]
> Consulte [GAMES.md](GAMES.md) para as regras detalhadas de cada modo e [ARCHITECTURE.md](ARCHITECTURE.md) para a estrutura modular do projeto.
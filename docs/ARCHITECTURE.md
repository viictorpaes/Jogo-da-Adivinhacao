<h1 align="center">Arquitetura do Projeto<br>
<img src="https://img.shields.io/badge/Architecture-111827?style=flat-square&logo=instructure&logoColor=white" height="25"/></h1>

<p align="center"><b>Visão geral — organização modular, responsabilidades e como os módulos interagem.</b></p>

<h2 align="center">🏗️ Estrutura de Diretórios</h2>

<pre>
Jogo-da-Adivinhacao/
├── .gitignore <img src="https://img.shields.io/badge/-.gitignore-111827?style=flat-square&logo=git&logoColor=F05032" height="18">
├── .clang-format <img src="https://img.shields.io/badge/-.clang--format-111827?style=flat-square&logo=llvm&logoColor=004488" height="18"/>
├── .prettierrc <img src="https://img.shields.io/badge/-Prettier-111827?style=flat-square&logo=prettier&logoColor=F7B93E" height="18"/>
├── Makefile <img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000" height="18">
├── protótipo.fig <img src="https://img.shields.io/badge/-Figma-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"/>
├── README.md <img src="https://img.shields.io/badge/-Markdown-111827?style=flat-square&logo=markdown&logoColor=white" height="18"/>
├── LICENSE <img src="https://img.shields.io/badge/License-MIT-orange?style=flat-square" height="18"/>
├── .github <img src="https://img.shields.io/badge/-GitHub%20Actions-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="18">/
│   ├── workflows <img src="https://img.shields.io/badge/-Workflows-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="18">/
│   │   └── release.yml <img src="https://img.shields.io/badge/-CI%2FCD-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="18"/>
│   └── md <img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=markdown&logoColor=white" height="18">/
│       └── Deploy.md <img src="https://img.shields.io/badge/-Deploy-111827?style=flat-square&logo=github&logoColor=white" height="18"/>
├── docs <img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=read-the-docs&logoColor=0078D4" height="18">/
│   ├── ADR.md <img src="https://img.shields.io/badge/-ADR-111827?style=flat-square&logo=blueprint&logoColor=4CAF50" height="18"/>
│   ├── API.md <img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="18"/>
│   ├── <mark>ARCHITECTURE.md</mark> <img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="18"/>
│   ├── CONTRIBUTING.md <img src="https://img.shields.io/badge/-CONTRIBUTING-yellow?style=flat-square&logo=surveymonkey&logoColor=white" height="18"/>
│   ├── GAMES.md <img src="https://img.shields.io/badge/-🎮Games-111827?style=flat-square&logo=gamepad&logoColor=4CAF50" height="18"/>
│   ├── FRONTEND_RAYLIB.md <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="18"/>
│   ├── Histórias_de_Usuário.md <img src="https://img.shields.io/badge/-HUs-111827?style=flat-square&logo=trello&logoColor=0052CC" height="18"/>
│   ├── CHANGELOG.md <img src="https://img.shields.io/badge/-CHANGELOG-111827?style=flat-square&logo=checkmarx&logoColor=brightgreen" height="18"/>
│   ├── schema.md <img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="18">
│   ├── SECURITY.md <img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="18">
│   ├── ROADMAP.md <img src="https://img.shields.io/badge/-ROADMAP-111827?style=flat-square&logo=markdown&logoColor=green" height="18"/>
│   └── Regras_Evento.md <img src="https://img.shields.io/badge/-Regras%20Evento-111827?style=flat-square&logo=markdown&logoColor=FFD700" height="18"/>
├── img <img src="https://img.shields.io/badge/-Assets-111827?style=flat-square&logo=git-lfs&logoColor=white" height="18">/
├── data <img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18">/
│   ├── historico.csv / .txt <img src="https://img.shields.io/badge/-Adivinha%C3%A7%C3%A3o%20Solo-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   ├── historico_memoria.csv / .txt <img src="https://img.shields.io/badge/-Mem%C3%B3ria%20Solo-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
│   ├── historico_vs.csv / .txt <img src="https://img.shields.io/badge/-VS%20Adivinha%C3%A7%C3%A3o-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   ├── historico_memoria_vs.csv / .txt <img src="https://img.shields.io/badge/-VS%20Mem%C3%B3ria-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
│   ├── historico_logica.csv / .txt <img src="https://img.shields.io/badge/-L%C3%B3gica-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   └── historico_precedencia.csv / .txt <img src="https://img.shields.io/badge/-Preced%C3%AAncia-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
└── src <img src="https://img.shields.io/badge/-<>src-111827?style=flat-square&logo=visualstudiocode&logoColor=007ACC" height="18"/>/
    ├── main.c <img src="https://img.shields.io/badge/-Entry%20Console-111827?style=flat-square&logo=c&logoColor=FF0000" height="18"/>
    ├── main_raylib.c <img src="https://img.shields.io/badge/-Entry%20Raylib-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    ├── game <img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">/
    │   ├── jogo.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── jogo.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── memorygame.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── memorygame.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── jogar_memoria.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── jogar_memoria.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── logica.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── logica.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── precedencia.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── precedencia.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── jogos_extras.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── jogos_extras.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── ui <img src="https://img.shields.io/badge/-Módulo%20UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18">/
    │   ├── menu.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    │   ├── menu.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    │   ├── frontend.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    │   └── frontend.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    ├── ux <img src="https://img.shields.io/badge/-Módulo_UX-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18">/
    │   ├── acessibilidade.md <img src="https://img.shields.io/badge/-%E2%99%BF%20Acessibilidade-111827?style=flat-square" height="18">
    │   ├── jogar.md <img src="https://img.shields.io/badge/-%F0%9F%8E%AE%20Jogar-111827?style=flat-square" height="18">
    │   ├── jornadas.md <img src="https://img.shields.io/badge/-Jornadas-111827?style=flat-square&logo=googlemaps&logoColor=4285F4" height="18">
    │   └── personas.md <img src="https://img.shields.io/badge/-%F0%9F%91%A5%20Personas-111827?style=flat-square" height="18">
    ├── history <img src="https://img.shields.io/badge/-Módulo%20History-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">/
    │   ├── historico.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── historico.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── utils <img src="https://img.shields.io/badge/-Módulo%20Utils-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">/
    │   ├── utils.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── utils.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── static <img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">/
    │   ├── estatisticas.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── estatisticas.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── music <img src="https://img.shields.io/badge/-Módulo%20Music-111827?style=flat-square&logo=musicbrainz&logoColor=BA478F" height="18">/
    │   ├── musica.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── musica.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   └── StarWarsMainTheme.mp3 <img src="https://img.shields.io/badge/-MP3-111827?style=flat-square&logo=audacity&logoColor=FF6600" height="18"/>
    └── include <img src="https://img.shields.io/badge/-Tipos%20Globais-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">/
        └── tipos.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
</pre>

---

## ⚙️ Configurações e Tooling

### Gitignore
<img src="https://img.shields.io/badge/-.gitignore-111827?style=flat-square&logo=git&logoColor=F05032" height="18"><br>
Responsável por manter o repositório limpo, instruindo o Git a ignorar binários compilados, arquivos de objeto (`.o`) e configurações locais de IDE, evitando o versionamento de arquivos desnecessários.

### Padronização de Código C
<img src="https://img.shields.io/badge/-.clang--format-111827?style=flat-square&logo=llvm&logoColor=004488" height="18"/><br>
Define as regras de estilo para os arquivos `.c` e `.h`. Utiliza o padrão LLVM para garantir que a indentação, espaçamento e quebras de linha sejam consistentes entre todos os contribuidores.

### Formatação de Documentos
<img src="https://img.shields.io/badge/-Prettier-111827?style=flat-square&logo=prettier&logoColor=F7B93E" height="18"/><br>
Configuração voltada para a consistência dos arquivos Markdown e esquemas. Garante que tabelas de documentação e arquivos de texto mantenham uma formatação profissional e legível.

### Automação de Compilação
<img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000" height="18"><br>
Gerencia o processo de build do projeto. Suporta duas versões compiláveis — console e Raylib — e automatiza a compilação modular com todas as dependências.

| Comando | Descrição |
| :--- | :--- |
| `make` / `make all` | Compila a versão terminal |
| `make run` | Compila e executa a versão terminal |
| `make build-raylib` | Compila a versão visual sem executar |
| `make raylib` | Compila e executa a versão visual |
| `make clean` | Remove binários compilados |
| `make format` | Formata o código com clang-format |
| `make test` | Executa os testes do projeto |
| `make DEBUG=1` | Compila com símbolos de depuração (`-g -O0`) |
| `make help` | Exibe todos os comandos disponíveis |

---

## 🤖 CI/CD e Deploy (`.github/`)

<img src="https://img.shields.io/badge/-GitHub%20Actions-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="18"/><br>
Automatiza o build multiplataforma e a publicação de releases. A pasta `.github/` contém dois subdiretórios:

| Subdiretório | Conteúdo | Responsabilidade |
| :--- | :--- | :--- |
| `workflows/release.yml` <img src="https://img.shields.io/badge/-CI%2FCD-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="16"/> | Pipeline YAML do GitHub Actions | Compila a versão Raylib em **macOS**, **Linux (Ubuntu 22.04)** e **Windows (MSYS2/MinGW64)** em paralelo; publica os três binários como **GitHub Release** ao detectar uma tag `v*` |
| `md/Deploy.md` <img src="https://img.shields.io/badge/-Deploy-111827?style=flat-square&logo=github&logoColor=white" height="16"/> | Documentação do pipeline | Descreve gatilhos, matriz de jobs, estrutura dos artefatos, DLLs empacotadas e instruções para publicar uma nova release |

O pipeline é disparado de duas formas:

- **`push` de tag `v*`** — compila e publica a Release automaticamente  
- **`workflow_dispatch`** — compila sem publicar (útil para validar builds)

> Consulte [`.github/md/Deploy.md`](../.github/md/Deploy.md) para a documentação completa do fluxo de CI/CD.

---

## 🎨 Design e UX

### Protótipo de Interface
<img src="https://img.shields.io/badge/-Figma-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"/><br>
Referência visual utilizada para planejar a interface baseada em texto. O arquivo `.fig` serviu de guia para o layout dos menus e o fluxo de telas apresentado ao usuário.

### Estratégia de Experiência (`ux/`)
<img src="https://img.shields.io/badge/-UX-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"><br>
Contém a documentação de personas, jornadas de usuário e diretrizes de acessibilidade. Garante que o jogo seja inclusivo e que a curva de aprendizado para o jogador seja mínima.<br>
<img src="https://img.shields.io/badge/-%E2%99%BF%20Acessibilidade-111827?style=flat-square" height="18"> <img src="https://img.shields.io/badge/-%F0%9F%8E%AE%20Jogar-111827?style=flat-square" height="18"> <img src="https://img.shields.io/badge/-Jornadas-111827?style=flat-square&logo=googlemaps&logoColor=4285F4" height="18"> <img src="https://img.shields.io/badge/-%F0%9F%91%A5%20Personas-111827?style=flat-square" height="18">

---

## 📚 Documentação Técnica (`docs/`)

<img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=read-the-docs&logoColor=0078D4" height="18"><br>
Centraliza o conhecimento do projeto:

| Arquivo | Conteúdo |
| :--- | :--- |
| **ADR.md** <img src="https://img.shields.io/badge/-ADR-111827?style=flat-square&logo=blueprint&logoColor=4CAF50" height="16"/> | Registro das decisões arquiteturais (5 ADRs): dual entry-point, persistência CSV+TXT, recursão em estatísticas, `EstadoUI` e heurísticas estáticas |
| **API.md** <img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="16"/> | Especificação das funções e contratos entre os módulos |
| **ARCHITECTURE.md** <img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="16"/> | Visão macro do sistema e padrões de projeto |
| **GAMES.md** <img src="https://img.shields.io/badge/-Games-111827?style=flat-square&logo=gamepad&logoColor=4CAF50" height="16"/> | Descrição detalhada dos 6 modos de jogo: regras, dificuldades, pontuação, struct, funções e módulos fonte para Console e Raylib |
| **CHANGELOG.md** <img src="https://img.shields.io/badge/-CHANGELOG-111827?style=flat-square&logo=checkmarx&logoColor=brightgreen" height="16"/> | Plano de testes distribuídos entre os módulos Adivinhação, Memória, Lógica, Precedência, Histórico, Estatísticas e Regressão |
| **CONTRIBUTING.md** <img src="https://img.shields.io/badge/-CONTRIBUTING-yellow?style=flat-square&logo=surveymonkey&logoColor=white" height="16"/> | Contribuidores do projeto |
| **FRONTEND_RAYLIB.md** <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="16"/> | Instruções de compilação e uso da versão gráfica (janela 1200×800, 6 modos) |
| **Histórias_de_Usuário.md** <img src="https://img.shields.io/badge/-HUs-111827?style=flat-square&logo=trello&logoColor=0052CC" height="16"/> | 28 histórias implementadas e 16 futuras no formato 3Cs |
| **ROADMAP.md** <img src="https://img.shields.io/badge/-ROADMAP-111827?style=flat-square&logo=markdown&logoColor=green" height="16"/> | Registro das sprints do projeto com tarefas e responsáveis por integrante da equipe |
| **schema.md** <img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="16"/> | Definição das 6 estruturas de dados para salvar o histórico por modo |
| **SECURITY.md** <img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="16"/> | Lógica do RNG e boas práticas para evitar previsibilidade |
| **Regras_Evento.md** <img src="https://img.shields.io/badge/-Regras%20Evento-111827?style=flat-square&logo=markdown&logoColor=FFD700" height="16"/> | Regras oficiais de evento/competição vinculadas ao projeto |

---

## 📊 Persistência de Dados (`data/`)

<img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18"><br>
Diretório que contém os arquivos físicos de dados de todos os modos de jogo. Cada modo mantém um par de arquivos independente: o `.txt` é legível pelo módulo `history/`, enquanto o `.csv` espelha os mesmos dados em formato tabular para análise externa.

| Par de arquivos (`csv` + `txt`) | Modo | Campos principais |
| :--- | :--- | :--- |
| `historico.*` | Adivinhação Solo | data, nome, dificuldade, tentativas, secreto, resultado, pts |
| `historico_memoria.*` | Memória Solo | data, nome, pontuacao, tentativas, pts |
| `historico_vs.*` | Adivinhação VS | data, nome1, nome2, dificuldade, vitórias, pts por jogador, vencedor |
| `historico_memoria_vs.*` | Memória 1v1 | data, nome1/2, pares, pts por jogador |
| `historico_logica.*` | Protocolo Lógico | data, nome, acertos, total, pts, modo |
| `historico_precedencia.*` | Hierarquia de Cmds | data, nome, acertos, total, pts, modo |

---

## 🎵 Trilha Sonora (`src/music/`)

<img src="https://img.shields.io/badge/-Módulo%20Music-111827?style=flat-square&logo=musicbrainz&logoColor=BA478F" height="18"/><br>
Encapsula toda a gestão de áudio da versão gráfica (Raylib). O módulo isola as chamadas à API de som para que nenhum outro módulo precise incluir `raylib.h` apenas por causa de áudio.

| Arquivo | Responsabilidade |
| :--- | :--- |
| `musica.c` / `musica.h` <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="16"/><img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="16"/> | Inicialização, atualização por frame, pausa e liberação do stream de áudio via `InitAudioDevice` / `LoadMusicStream` |
| `StarWarsMainTheme.mp3` <br> <img src="https://img.shields.io/badge/-MP3-111827?style=flat-square&logo=audacity&logoColor=FF6600" height="16"/> | Arquivo de áudio MP3 carregado em streaming — reproduzido em loop contínuo enquanto a janela do jogo estiver aberta |

A música roda em **loop infinito**, mesmo com (`looping = false`) e é atualizada a cada frame com: 

```c
UpdateMusicStream(musicaStarWars);
    if (GetMusicTimePlayed(musicaStarWars) >= 70.0f) 
    {
        SeekMusicStream(musicaStarWars, 0.0f);
    }
``` 
chamada no game no <b>loop principal de `main_raylib.c`</b>.

---

## 💻 Módulo Principal (`src/`)

### Pontos de Entrada
<img src="https://img.shields.io/badge/-Entry%20Console-111827?style=flat-square&logo=c&logoColor=FF0000" height="18"/> <img src="https://img.shields.io/badge/-Entry%20Raylib-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/><br>
O projeto possui dois pontos de entrada independentes:

| Arquivo | Versão |
| :--- | :--- |
| `main.c` | Orquestra a versão de console — inicializa o sistema e invoca o loop principal do menu |
| `main_raylib.c` | Ponto de entrada da versão gráfica — inicializa o contexto Raylib e entrega o controle ao frontend |

### Motor do Jogo (`game/`)
<img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
O núcleo lógico do projeto. Contém seis modos de jogo com suas respectivas implementações:

| Arquivo | Responsabilidade |
| :--- | :--- |
| `jogo.c` / `jogo.h` | Sorteio de números, validação de palpites e regras de pontuação/dificuldade do Jogo da Adivinhação (Solo e VS) |
| `memorygame.c` / `memorygame.h` | Estrutura de dados do tabuleiro 4×4, embaralhamento (Fisher-Yates) e lógica de pares (Solo e 1v1) |
| `jogar_memoria.c` / `jogar_memoria.h` | Loop principal e fluxo de turnos do Jogo da Memória no terminal |
| `logica.c` / `logica.h` | Geração de fórmulas proposicionais, avaliação de tabela-verdade, classificação (tautologia/contradição/contingência) e timer por questão. Operadores lógicos nomeados em português (`OP_VARIAVEL`, `OP_NEGACAO`, `OP_CONJUNCAO`, `OP_DISJUNCAO`, `OP_IMPLICACAO`, `OP_BIIMPLICACAO`) |
| `precedencia.c` / `precedencia.h` | Banco de questões de múltipla-escolha sobre precedência de operadores lógicos, embaralhamento de opções e timer por questão |
| `jogos_extras.c` / `jogos_extras.h` | Orquestrador dos modos VS e lógica no terminal — expõe `jogar_adivinhacao_vs`, `jogar_memoria_vs`, `jogar_logica_terminal` e `jogar_precedencia_terminal`, integrando os submódulos do `game/` para execução no console |

### Interface do Usuário (`ui/`)
<img src="https://img.shields.io/badge/-Módulo%20UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18"><br>
Isola toda a camada de apresentação, facilitando futuras mudanças visuais sem afetar a lógica do jogo:

| Arquivo | Responsabilidade |
| :--- | :--- |
| `menu.c` / `menu.h` | Exibição de textos e artes ASCII para a versão de console |
| `frontend.c` / `frontend.h` | Renderização e interação da versão gráfica com Raylib (janela 1200×800). Inclui sistema visual de timer com 3 estados de cor — verde (>50 %), laranja (20–50 %), vermelho (<20 %) — via `cor_timer()` e helper unificado `desenhar_timer()` |

### Gerência de Histórico (`history/`)
<img src="https://img.shields.io/badge/-Módulo%20History-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Responsável por salvar e carregar os dados do jogador. Faz a ponte entre as estruturas de memória do C e os arquivos salvos no disco no diretório `data/`. Suporta **filtro por jogador** via `hist_filtro_nome` + `hist_com_filtro`, com lista `nomes_hist[]` (até 100 entradas) para autocomplete; carregamento lazy dos 6 tipos de histórico em uma única chamada.

### Utilidades (`utils/`)
<img src="https://img.shields.io/badge/-Módulo%20Utils-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Contém funções genéricas reutilizáveis por todos os módulos, como leitura segura de input, geração de números aleatórios sem viés e inicialização da semente de aleatoriedade.

### Pontuação, Heurísticas e Estatísticas (`static/`)
<img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Módulo com três responsabilidades: cálculo de pontuação (`calcular_pontos`, `calcular_pontos_memoria`), geração de heurísticas estratégicas exibidas ao final de cada partida (`heuristica_adivinhacao`, `heuristica_memoria`) e análise do histórico de partidas para exibir métricas de desempenho como ranking e média de tentativas. Também prepara linhas formatadas de estatísticas consumidas pelo frontend gráfico.

### Tipos Globais (`include/`)
<img src="https://img.shields.io/badge/-Tipos%20Globais-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Centraliza a definição de `structs`, `enums` e `typedefs` globais em `tipos.h`. Garante que todos os módulos utilizem as mesmas estruturas de dados de forma organizada. Inclui as constantes de timer por dificuldade (`TIMER_ADIV_BONUS`, `TIMER_ADIV_PENALIDADE`, `TIMER_MEM_BONUS_SEG`, `TIMER_MEM_PENALIDADE_SEG`) e a função `timer_adiv_para_dif()` para resolução do tempo conforme a dificuldade selecionada.

---

## 🔗 Mapa de Dependências

```
main.c (console)                  main_raylib.c (gráfico)
    ├── ui/menu.h                      ├── ui/frontend.h
    ├── game/jogo.h                    ├── game/jogo.h
    ├── game/jogar_memoria.h           ├── game/memorygame.h
    ├── game/jogos_extras.h            ├── game/jogar_memoria.h
    │   ├── game/jogo.h                ├── game/logica.h
    │   ├── game/memorygame.h          ├── game/precedencia.h
    │   ├── game/logica.h              ├── history/historico.h
    │   └── game/precedencia.h         ├── static/estatisticas.h
    ├── history/historico.h            ├── utils/utils.h
    ├── static/estatisticas.h          └── music/musica.h  (áudio em loop)
    └── utils/utils.h
    └── include/tipos.h  (compartilhado por todos os módulos)
```

> [!NOTE]
> Cada módulo expõe apenas sua interface via arquivo `.h`. O módulo `game/` não precisa saber como `history/` grava os arquivos — ele apenas consome a API definida no cabeçalho. Isso garante **encapsulamento** e facilita testes e manutenção independentes.

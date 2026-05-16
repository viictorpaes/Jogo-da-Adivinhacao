<h1 align="center">Arquitetura do Projeto<br>
<img src="https://img.shields.io/badge/Architecture-111827?style=flat-square&logo=instructure&logoColor=white" height="25"/></h1>

<p align="center">Visão geral — organização modular, responsabilidades e como os módulos interagem.</p>

<h2 align="center">🏗️ Estrutura de Diretórios</h2>

<pre>
Jogo-da-Adivinhacao/
├── .gitignore <img src="https://img.shields.io/badge/-.gitignore-111827?style=flat-square&logo=git&logoColor=F05032" height="18">
├── .clang-format <img src="https://img.shields.io/badge/-.clang--format-111827?style=flat-square&logo=llvm&logoColor=004488" height="18"/>
├── .prettierrc <img src="https://img.shields.io/badge/-Prettier-111827?style=flat-square&logo=prettier&logoColor=F7B93E" height="18"/>
├── Makefile <img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000" height="18">
├── protótipo.fig <img src="https://img.shields.io/badge/-Figma-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"/>
├── README.md <img src="https://img.shields.io/badge/-Markdown-111827?style=flat-square&logo=markdown&logoColor=white" height="18"/>
├── LICENSE <img src="https://img.shields.io/badge/License-MIT-yellow?style=flat-square" height="18"/>
├── docs/ <img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=read-the-docs&logoColor=0078D4" height="18">
│   ├── API.md <img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="18"/>
│   ├── <mark>ARCHITECTURE.md</mark> <img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="18"/>
│   ├── AUTHORS.md <img src="https://img.shields.io/badge/-AUTHORS-8B0000?style=flat-square&logo=surveymonkey&logoColor=white" height="18"/>
│   ├── FRONTEND_RAYLIB.md <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="18"/>
│   ├── Histórias_de_Usuário.md <img src="https://img.shields.io/badge/-HUs-111827?style=flat-square&logo=trello&logoColor=0052CC" height="18"/>
│   ├── MEMORIA.md <img src="https://img.shields.io/badge/-Memória-111827?style=flat-square&logo=markdown&logoColor=white" height="18"/>
│   ├── schema.md <img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="18">
│   └── SECURITY.md <img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="18">
├── img/ <img src="https://img.shields.io/badge/-Assets-111827?style=flat-square&logo=git-lfs&logoColor=white" height="18">
├── data/ <img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18">
│   ├── historico.csv <img src="https://img.shields.io/badge/-CSV-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   ├── historico.txt <img src="https://img.shields.io/badge/-TXT-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
│   ├── historico_memoria.csv <img src="https://img.shields.io/badge/-CSV-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   └── historico_memoria.txt <img src="https://img.shields.io/badge/-TXT-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
└── src/ <img src="https://img.shields.io/badge/-<>src-111827?style=flat-square&logo=visualstudiocode&logoColor=007ACC" height="18"/>
    ├── main.c <img src="https://img.shields.io/badge/-Entry%20Console-111827?style=flat-square&logo=c&logoColor=FF0000" height="18"/>
    ├── main_raylib.c <img src="https://img.shields.io/badge/-Entry%20Raylib-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    ├── game/ <img src="https://img.shields.io/badge/-Módulo%20Game-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── jogo.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── jogo.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── memorygame.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   ├── memorygame.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    │   ├── jogar_memoria.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── jogar_memoria.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── ui/ <img src="https://img.shields.io/badge/-Módulo%20UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18">
    │   ├── menu.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    │   ├── menu.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    │   ├── frontend.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    │   └── frontend.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=FF6B35" height="18"/>
    ├── ux/ <img src="https://img.shields.io/badge/-Módulo_UX-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18">
    │   ├── acessibilidade.md <img src="https://img.shields.io/badge/-%E2%99%BF%20Acessibilidade-111827?style=flat-square" height="18">
    │   ├── jogar.md <img src="https://img.shields.io/badge/-%F0%9F%8E%AE%20Jogar-111827?style=flat-square" height="18">
    │   ├── jornadas.md <img src="https://img.shields.io/badge/-Jornadas-111827?style=flat-square&logo=googlemaps&logoColor=4285F4" height="18">
    │   └── personas.md <img src="https://img.shields.io/badge/-%F0%9F%91%A5%20Personas-111827?style=flat-square" height="18">
    ├── history/ <img src="https://img.shields.io/badge/-Módulo%20History-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── historico.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── historico.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── utils/ <img src="https://img.shields.io/badge/-Módulo%20Utils-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── utils.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── utils.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── static/ <img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── estatisticas.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── estatisticas.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    └── include/ <img src="https://img.shields.io/badge/-Tipos%20Globais-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
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
| `make` | Compila a versão terminal |
| `make run` | Compila e executa a versão terminal |
| `make build-raylib` | Compila a versão visual sem executar |
| `make raylib` | Compila e executa a versão visual |
| `make clean` | Remove binários compilados |
| `make format` | Formata o código com clang-format |

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
| **API.md** <img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="16"/> | Especificação das funções e contratos entre os módulos |
| **ARCHITECTURE.md** <img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="16"/> | Visão macro do sistema e padrões de projeto |
| **AUTHORS.md** <img src="https://img.shields.io/badge/-AUTHORS-8B0000?style=flat-square&logo=surveymonkey&logoColor=white" height="16"/> | Contribuidores do projeto |
| **FRONTEND_RAYLIB.md** <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="16"/> | Instruções de compilação e uso da versão gráfica |
| **Histórias_de_Usuário.md** <img src="https://img.shields.io/badge/-HUs-111827?style=flat-square&logo=trello&logoColor=0052CC" height="16"/> | 23 histórias implementadas e 16 futuras no formato 3Cs |
| **MEMORIA.md** <img src="https://img.shields.io/badge/-Memória-111827?style=flat-square&logo=markdown&logoColor=white" height="16"/> | Documentação do módulo Jogo da Memória |
| **schema.md** <img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="16"/> | Definição da estrutura de dados para salvar o histórico |
| **SECURITY.md** <img src="https://img.shields.io/badge/SECURITY-FFCC00?style=for-the-badge&logo=1password&logoColor=black" height="16"/> | Lógica do RNG e boas práticas para evitar previsibilidade |

---

## 📊 Persistência de Dados (`data/`)

<img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18"><br>
Diretório que contém os arquivos físicos de dados de ambos os jogos. Cada jogo mantém um par de arquivos independente: o `.txt` é a base de dados principal lida/escrita pelo módulo `history/`, enquanto o `.csv` espelha os mesmos dados em formato tabular para análise externa.

| Arquivo | Jogo | Formato |
| :--- | :--- | :--- |
| `historico.txt` | Jogo da Adivinhação | Base de dados principal |
| `historico.csv` | Jogo da Adivinhação | Exportação para análise externa |
| `historico_memoria.txt` | Jogo da Memória | Base de dados principal |
| `historico_memoria.csv` | Jogo da Memória | Exportação para análise externa |

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
O núcleo lógico do projeto. Contém dois jogos distintos com suas respectivas implementações:

| Arquivo | Responsabilidade |
| :--- | :--- |
| `jogo.c` / `jogo.h` | Sorteio de números, validação de palpites e regras de pontuação/dificuldade do Jogo da Adivinhação |
| `memorygame.c` / `memorygame.h` | Estrutura de dados do tabuleiro 4×4, embaralhamento (Fisher-Yates) e lógica de pares |
| `jogar_memoria.c` / `jogar_memoria.h` | Loop principal e fluxo de turnos do Jogo da Memória |

### Interface do Usuário (`ui/`)
<img src="https://img.shields.io/badge/-Módulo%20UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18"><br>
Isola toda a camada de apresentação, facilitando futuras mudanças visuais sem afetar a lógica do jogo:

| Arquivo | Responsabilidade |
| :--- | :--- |
| `menu.c` / `menu.h` | Exibição de textos e artes ASCII para a versão de console |
| `frontend.c` / `frontend.h` | Renderização e interação da versão gráfica com Raylib (janela 1200×800) |

### Gerência de Histórico (`history/`)
<img src="https://img.shields.io/badge/-Módulo%20History-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Responsável por salvar e carregar os dados do jogador. Faz a ponte entre as estruturas de memória do C e os arquivos salvos no disco no diretório `data/`.

### Utilidades (`utils/`)
<img src="https://img.shields.io/badge/-Módulo%20Utils-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Contém funções genéricas reutilizáveis por todos os módulos, como leitura segura de input, geração de números aleatórios sem viés e inicialização da semente de aleatoriedade.

### Análise Estatística (`static/`)
<img src="https://img.shields.io/badge/-Módulo%20Stats-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Módulo que processa o histórico de partidas para gerar métricas de desempenho, como o ranking de melhores jogadores e a média de tentativas por nível.

### Tipos Globais (`include/`)
<img src="https://img.shields.io/badge/-Tipos%20Globais-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Centraliza a definição de `structs`, `enums` e `typedefs` globais em `tipos.h`. Garante que todos os módulos utilizem as mesmas estruturas de dados de forma organizada.

---

## 🔗 Mapa de Dependências

```
main.c / main_raylib.c
    ├── ui/menu.h          (console)
    ├── ui/frontend.h      (raylib)
    ├── game/jogo.h
    ├── game/memorygame.h
    ├── game/jogar_memoria.h
    ├── history/historico.h
    ├── static/estatisticas.h
    └── utils/utils.h
            └── include/tipos.h  (compartilhado por todos)
```

> [!NOTE]
> Cada módulo expõe apenas sua interface via arquivo `.h`. O módulo `game/` não precisa saber como `history/` grava os arquivos — ele apenas consome a API definida no cabeçalho. Isso garante **encapsulamento** e facilita testes e manutenção independentes.

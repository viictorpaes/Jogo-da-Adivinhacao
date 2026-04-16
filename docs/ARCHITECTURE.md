<h1 align="center">Arquitetura do Projeto<br>
<img src="https://img.shields.io/badge/-Architecture-111827?style=flat-square&logo=instructure&logoColor=green" height="25"/></h1>

Visão geral — organização modular, responsabilidades e como os módulos interagem.

<pre>
Jogo-da-Adivinhacao/
├── .gitignore <img src="https://img.shields.io/badge/-.gitignore-111827?style=flat-square&logo=git&logoColor=F05032" height="18">
├── .clang-format <img src="https://img.shields.io/badge/-.clang--format-111827?style=flat-square&logo=llvm&logoColor=004488" height="18"/>
├── .prettierrc <img src="https://img.shields.io/badge/-Prettier-111827?style=flat-square&logo=prettier&logoColor=F7B93E" height="18"/>
├── Makefile <img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000" height="18">
├── protótipo.fig <img src="https://img.shields.io/badge/-Figma-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"/>
├── README.md <img src="https://img.shields.io/badge/-Markdown-111827?style=flat-square&logo=markdown&logoColor=white" height="18"/>
├── docs/ <img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=read-the-docs&logoColor=0078D4" height="18">
│   ├── API.md <img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="18"/>
│   ├── ARCHITECTURE.md <img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="18"/>
│   └── schema.md <img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="18">
├── img/ <img src="https://img.shields.io/badge/-Assets-111827?style=flat-square&logo=git-lfs&logoColor=white" height="18">
├── data/ <img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18">
│   └── historico.csv <img src="https://img.shields.io/badge/-CSV-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/>
│   └── historico.txt <img src="https://img.shields.io/badge/-TXT-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/>
└── src/ <img src="https://img.shields.io/badge/-<>src-111827?style=flat-square&logo=visualstudiocode&logoColor=007ACC" height="18"/>
    ├── game/ <img src="https://img.shields.io/badge/-Módulo-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── jogo.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── jogo.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── ui/ <img src="https://img.shields.io/badge/-UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18">
    │   ├── menu.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    │   └── menu.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=9C27B0" height="18"/>
    ├── ux/ <img src="https://img.shields.io/badge/-UX-111827?style=flat-square&logo=adobe-experience-manager&logoColor=FF0000" height="18">
    │   ├── acessibilidade.md <img src="https://img.shields.io/badge/-%E2%99%BF%20Acessibilidade-111827?style=flat-square" height="18">
    │   ├── jogar.md <img src="https://img.shields.io/badge/-%F0%9F%8E%AE%20Jogar-111827?style=flat-square" height="18">
    │   ├── jornadas.md <img src="https://img.shields.io/badge/-Jornadas-111827?style=flat-square&logo=googlemaps&logoColor=4285F4" height="18">
    │   └── personas.md <img src="https://img.shields.io/badge/-%F0%9F%91%A5%20Personas-111827?style=flat-square" height="18">
    ├── history/ <img src="https://img.shields.io/badge/-Módulo-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── historico.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── historico.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── utils/ <img src="https://img.shields.io/badge/-Util-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── utils.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── utils.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── static/ <img src="https://img.shields.io/badge/-Análise-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   ├── estatisticas.c <img src="https://img.shields.io/badge/-Source-111827?style=flat-square&logo=c&logoColor=4CAF50" height="18"/>
    │   └── estatisticas.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    ├── include/ <img src="https://img.shields.io/badge/-Tipos-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18">
    │   └── tipos.h <img src="https://img.shields.io/badge/-Header-111827?style=flat-square&logo=c&logoColor=00599C" height="18"/>
    └── main.c <img src="https://img.shields.io/badge/-Main-111827?style=flat-square&logo=c&logoColor=FF0000" height="18"/>
</pre>

# 🏗️ Detalhamento da Arquitetura do Projeto

Esta seção descreve a finalidade de cada componente na estrutura de diretórios do **Jogo da Adivinhação**, detalhando responsabilidades e padrões de qualidade adotados.

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
Gerencia o processo de build do projeto. Automatiza a compilação modular, lida com as dependências entre os arquivos fonte e facilita a geração do executável final via terminal.

## 🎨 Design e UX

### Protótipo de Interface
<img src="https://img.shields.io/badge/-Figma-111827?style=flat-square&logo=figma&logoColor=F24E1E" height="18"/><br>
Referência visual utilizada para planejar a interface baseada em texto. O arquivo `.fig` serviu de guia para o layout dos menus e o fluxo de telas apresentado ao usuário.

### Estratégia de Experiência (`ux/`)
<img src="https://img.shields.io/badge/-UX-111827?style=flat-square&logo=adobe-experience-manager&logoColor=FF0000" height="18"><br>
Contém a documentação de personas, jornadas de usuário e diretrizes de acessibilidade. Garante que o jogo seja inclusivo e que a curva de aprendizado para o jogador seja mínima. <br>
<img src="https://img.shields.io/badge/-%E2%99%BF%20Acessibilidade-111827?style=flat-square" height="18"> <img src="https://img.shields.io/badge/-%F0%9F%8E%AE%20Jogar-111827?style=flat-square" height="18"> <img src="https://img.shields.io/badge/-Jornadas-111827?style=flat-square&logo=googlemaps&logoColor=4285F4" height="18"> <img src="https://img.shields.io/badge/-%F0%9F%91%A5%20Personas-111827?style=flat-square" height="18">

## 📚 Documentação Técnica (`docs/`)

### Manuais e Esquemas
<img src="https://img.shields.io/badge/-Docs-111827?style=flat-square&logo=read-the-docs&logoColor=0078D4" height="18"><br>
Centraliza o conhecimento do projeto:
* **API.md**: Especificação das funções e contratos entre os módulos.<img src="https://img.shields.io/badge/-API-111827?style=flat-square&logo=markdown&logoColor=FFB13B" height="18"/>
* **ARCHITECTURE.md**: Visão macro do sistema e padrões de projeto.<img src="https://img.shields.io/badge/-Arch-111827?style=flat-square&logo=instructure&logoColor=4CAF50" height="18"/>
* **schema.md**: Definição da estrutura de dados para salvar o histórico.<img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="18">


## 📊 Persistência de Dados (`data/`)

### Armazenamento de Partidas
<img src="https://img.shields.io/badge/-Data-111827?style=flat-square&logo=databricks&logoColor=FF3621" height="18"><br>
Diretório que contém os arquivos físicos de dados. O `historico.txt` é a base de dados principal, enquanto o `historico.csv` permite que os dados sejam analisados em softwares externos.

## 💻 Módulo Príncipal (`src/`)

### Motor do Jogo (`game/`)
<img src="https://img.shields.io/badge/-Módulo-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
O núcleo lógico do projeto (`jogo.c`). Responsável pelo sorteio de números, validação de palpites e aplicação das regras de pontuação e dificuldade.

### Interface do Usuário (`ui/`)
<img src="https://img.shields.io/badge/-UI-111827?style=flat-square&logo=materialdesign&logoColor=757575" height="18"><br>
Gerencia toda a interação via terminal (`menu.c`). Isola a lógica de exibição de textos e artes ASCII, facilitando futuras mudanças visuais sem afetar a lógica do jogo.

### Gerência de Histórico (`history/`)
<img src="https://img.shields.io/badge/-Módulo-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Responsável por salvar e carregar os dados do jogador. Faz a ponte entre as estruturas de memória do C e os arquivos salvos no disco no diretório `data/`.

### Utilidades (`utils/`)
<img src="https://img.shields.io/badge/-Util-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Contém funções genéricas reutilizáveis por outros módulos, como tratamento de erros de input, geração de atrasos (delay) e manipulação de cores no terminal.

### Análise Estatística (`static/`)
<img src="https://img.shields.io/badge/-Análise-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Módulo que processa o histórico de partidas para gerar métricas de desempenho, como o ranking de melhores jogadores e a média de tentativas por nível.

### Tipos Globais (`include/`)
<img src="https://img.shields.io/badge/-Tipos-111827?style=flat-square&logo=c&logoColor=A8B9CC" height="18"><br>
Centraliza a definição de `structs`, `enums` e `typedefs` globais (`tipos.h`). Garante que todos os módulos utilizem as mesmas estruturas de dados de forma organizada.

### Ponto de Entrada (`main.c`)
<img src="https://img.shields.io/badge/-Main-111827?style=flat-square&logo=c&logoColor=FF0000" height="18"/><br>
O arquivo principal que orquestra a execução. Ele inicializa o sistema, carrega as configurações iniciais e invoca o loop principal do menu.
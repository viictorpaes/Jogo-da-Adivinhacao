<h1 align="center">Arquitetura do Projeto<br>
<img src="https://img.shields.io/badge/-Architecture-111827?style=flat-square&logo=instructure&logoColor=green"/></h1>

Visão geral — organização modular, responsabilidades e como os módulos interagem.

<pre>
Jogo-da-Adivinhacao/
├── .gitignore <img src="https://img.shields.io/badge/.gitignore-F05032?style=for-the-badge&logo=git&logoColor=orange&labelColor=black" height="18">
├── .clang-format <img src="https://img.shields.io/badge/.clang--format-004488?style=flat&logo=llvm&logoColor=white" alt=".clang-format" height="18"/>
├── .prettierrc <img src="https://img.shields.io/badge/Prettier-F7B93E?style=flat&logo=prettier&logoColor=black" alt="Prettier" height="18"/>
├── Makefile <img src="https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=probot&logoColor=red" height="18">
├── protótipo.fig <img src="https://img.shields.io/badge/Figma-F24E1E?style=flat-square&logo=figma&logoColor=black" height="18"/>
├── README.md <img src="https://img.shields.io/badge/Markdown-FFFFFF?style=for-the-badge&logo=markdown&logoColor=000000" height="18"/>
├── docs/ <img src="https://img.shields.io/badge/Documentação-Docs-blue?style=flat-square&logo=read-the-docs&logoColor=white" height="18">
│   ├── API.md <img src="https://img.shields.io/badge/API-Spec-orange?style=flat-square&logo=markdown" height="18"/>
│   ├── ARCHITECTURE.md <img src="https://img.shields.io/badge/Arch-System-111827?style=flat-square&logo=instructure&logoColor=green" height="18"/>
│   └── schema.md <img src="https://img.shields.io/badge/Schema-JSON-green?style=flat-square&logo=json" height="18">
├── img/ <img src="https://img.shields.io/badge/Assets-Img-green?style=flat-square&logo=git-lfs&logoColor=white" height="18">
├── data/ <img src="https://img.shields.io/badge/Data-Files-orange?style=flat-square&logo=databricks" height="18">
│   └── historico.csv <img src="https://img.shields.io/badge/Data-CSV-green?style=flat-square&logo=microsoft-excel&logoColor=white" height="18"/>
│   └── historico.txt <img src="https://img.shields.io/badge/Arquivo-TXT-grey?style=flat-square&logo=files&logoColor=white" height="18"/>
└── src/ <img src="https://img.shields.io/badge/%3C%2F%3E%20src-green?style=for-the-badge&logo=visualstudiocode&logoColor=white" height="18"/>
    ├── game/ <img src="https://img.shields.io/badge/Módulo-Jogo-blue?style=flat-square&logo=c&logoColor=white" height="18">
    │   ├── jogo.c <img src="https://img.shields.io/badge/C-Source-green?style=flat-square&logo=c&logoColor=white" height="18"/>
    │   └── jogo.h <img src="https://img.shields.io/badge/C-Header-blue?style=flat-square&logo=c&logoColor=white" height="18"/>
    ├── ui/ <img src="https://img.shields.io/badge/Módulo-UI-purple?style=flat-square&logo=materialdesign&logoColor=white" height="18">
    │   ├── menu.c <img src="https://img.shields.io/badge/C-Source-purple?style=flat-square&logo=c&logoColor=white" height="18"/>
    │   └── menu.h <img src="https://img.shields.io/badge/C-Header-purple?style=flat-square&logo=c&logoColor=white" height="18"/>
    ├── ux/ <img src="https://img.shields.io/badge/Design-UX-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="18">
    │   ├── acessibilidade.md <img src="https://img.shields.io/badge/Acessibilidade-rebeccapurple?style=flat-square&logo=appleaccess&logoColor=white" height="18">
    │   ├── jogar.md <img src="https://img.shields.io/badge/Jogar-rebeccapurple?style=flat-square&logo=gamepad&logoColor=white" height="18">
    │   ├── jornadas.md <img src="https://img.shields.io/badge/Jornadas-rebeccapurple?style=flat-square&logo=googlemaps&logoColor=white" height="18">
    │   └── personas.md <img src="https://img.shields.io/badge/Personas-rebeccapurple?style=flat-square&logo=groups&logoColor=white" height="18">
    ├── history/ <img src="https://img.shields.io/badge/Módulo-Histórico-blue?style=flat-square&logo=c&logoColor=white" height="18">
    │   ├── historico.c <img src="https://img.shields.io/badge/C-Source-green?style=flat-square&logo=c&logoColor=white" height="18"/>
    │   └── historico.h <img src="https://img.shields.io/badge/C-Header-blue?style=flat-square&logo=c&logoColor=white" height="18"/>
    ├── utils/ <img src="https://img.shields.io/badge/Módulo-Util-blue?style=flat-square&logo=c&logoColor=white" height="18">
    │   ├── utils.c <img src="https://img.shields.io/badge/C-Source-green?style=flat-square&logo=c&logoColor=white" height="18"/>
    │   └── utils.h <img src="https://img.shields.io/badge/C-Header-blue?style=flat-square&logo=c&logoColor=white" height="18"/>
    ├── static/ <img src="https://img.shields.io/badge/Módulo-Análise-blue?style=flat-square&logo=c&logoColor=white" height="18">
    │   ├── estatisticas.c <img src="https://img.shields.io/badge/C-Source-green?style=flat-square&logo=c&logoColor=white" height="18"/>
    │   └── estatisticas.h <img src="https://img.shields.io/badge/C-Header-blue?style=flat-square&logo=c&logoColor=white" height="18"/>
    ├── include/ <img src="https://img.shields.io/badge/Módulo-Tipos-blue?style=flat-square&logo=c&logoColor=white" height="18">
    │   └── tipos.h <img src="https://img.shields.io/badge/C-Header-blue?style=flat-square&logo=c&logoColor=white" height="18"/>
    └── main.c <img src="https://img.shields.io/badge/C-Main-red?style=flat-square&logo=c&logoColor=white" height="18"/>
</pre>

---

## 🏗️ Detalhes dos Módulos:

<h2 align="left">1. Interface do Usuário (`ui/`) <br>
<img src="https://img.shields.io/badge/Módulo-UI-purple?style=flat-square&logo=materialdesign&logoColor=white" height="18"></h2> 
Responsável pela camada de interação. O arquivo **`menu.c`** isola a navegação e as mensagens exibidas no terminal, permitindo alterar o visual do jogo sem impactar a lógica matemática.

<h2 align="left"> 2. Lógica do Jogo (`game/`) <br>
<img src="https://img.shields.io/badge/Módulo-Jogo-blue?style=flat-square&logo=c&logoColor=white" height="18"></h2> 
O motor principal. Aqui são processados os cálculos de sorteio, verificação de palpites e regras de pontuação.

<h2 align="left">3. Persistência de Dados (`data/` & `history/`) <br>
<img src="https://img.shields.io/badge/Data-Files-orange?style=flat-square&logo=databricks" height="18"> <img src="https://img.shields.io/badge/Módulo-Histórico-blue?style=flat-square&logo=c&logoColor=white" height="18"></h2> 
Os dados são armazenados de forma estruturada no arquivo **`historico.txt`**. O módulo `history/` fornece as funções necessárias para salvar e carregar esses estados, seguindo o padrão definido no `schema.md`.

<h2 align="left">4. Análise e Estatísticas (`static/`) <br>
<img src="https://img.shields.io/badge/Módulo-Análise-blue?style=flat-square&logo=c&logoColor=white" height="18"></h2> 
Módulo dedicado a processar os dados históricos para gerar relatórios de desempenho, como média de tentativas e taxa de sucesso do jogador.

<h2 align="left">5. Padronização e Qualidade</h2> 
**Compilação:** Gerenciada pelo `Makefile`.
**Formatação:** Automatizada via `.clang-format` e `.prettierrc` para manter a consistência entre diferentes contribuidores.
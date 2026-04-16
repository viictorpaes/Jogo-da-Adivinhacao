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
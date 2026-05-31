<h1 align="center">Guia de Contribuição<br>
<img src="https://img.shields.io/badge/-CONTRIBUTING-yellow?style=flat-square&logo=surveymonkey&logoColor=white" height="25"/></h1>

<p align="center">
  Tudo o que você precisa para montar o ambiente, entender o projeto e contribuir com código ou documentação.
</p>

## Índice

1. [Integrantes do Projeto](#-integrantes-do-projeto)
2. [Responsabilidades por Membro](#-responsabilidades-por-membro)
3. [Pré-requisitos](#-pré-requisitos)
4. [Configuração do Ambiente](#-configuração-do-ambiente)
5. [Compilação e Execução](#️-compilação-e-execução)
6. [Estrutura do Projeto](#-estrutura-do-projeto)
7. [Fluxo de Contribuição](#-fluxo-de-contribuição)
8. [Convenções de Código](#-convenções-de-código)
9. [Criando Issues](#-criando-issues)
10. [Como Adicionar um Novo Módulo](#-como-adicionar-um-novo-módulo)
11. [Rodando os Testes](#-rodando-os-testes)

---

## 👥 Integrantes do Projeto

<h3 align="center">👨🏻‍🏫 Docentes Responsáveis</h3>

| Professor | LinkedIn |
| :--- | :---: |
| Aêda Monalliza Cunha de Sousa | <a href="https://www.linkedin.com/in/aedasousa/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> |
| Guilherme Fernando Cacalvanti Pereira | <a href="https://www.linkedin.com/in/guilherme-pereira-11a32511a" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> |
| Lucas Rodolfo Celestino de Farias | <a href="https://www.linkedin.com/in/fariaslrc" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> |
| Renan Costa Alencar | <a href="https://www.linkedin.com/in/renancostaalencar" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> |
| Ricardo Macedo Baudel | <a href="https://www.linkedin.com/in/ricardo-baudel-700a98127/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> |

<h3 align="center">👨‍🎓 Equipe de Desenvolvimento</h3>

| Integrante | LinkedIn | GitHub |
| :--- | :---: | :---: |
| **Lucas Paguetti Pereira (Líder 👑)** | <a href="https://www.linkedin.com/in/lucas-paguetti-pereira" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/wqiluc" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| Eduardo de Souza Cavalcanti Junior | <a href="https://www.linkedin.com/in/eduardoscavalcantij/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/eduardo-scavalcanti" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| Felipe Franca Alves de Lima | <a href="https://www.linkedin.com/in/felipefrancaal/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/ffrancaal" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| Helamã Leone de Lima Procídio | <a href="https://www.linkedin.com/in/helam%C3%A3-procidio-428772367/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/procidiohelama-star" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| João Pedro Arruda Guimarães | <a href="https://www.linkedin.com/in/jo%C3%A3o-pedro-arruda-guimar%C3%A3es-157952287/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/Jp230603" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| Tiago Luiz Moreira de Vasconcelos | <a href="https://www.linkedin.com/in/tiagoluiz23/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/2006tiagoluiz" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |
| Victor José Paes e Silva | <a href="https://www.linkedin.com/in/viictorpaes/" target="_blank"><img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linkedin/linkedin-original.svg" width="14"/></a> | <a href="https://github.com/viictorpaes" target="_blank"><img src="https://img.shields.io/badge/GitHub-C0C0C0?style=for-the-badge&logo=github&logoColor=black" height="16"/></a> |

---

## 📋 Responsabilidades por Membro

| Integrante | Papel | Principais Contribuições |
| :--- | :--- | :--- |
| **Lucas Paguetti Pereira** | Co-líder | Criação do repositório, Makefile (Raylib), trilha sonora (`music/`), documentação e `docs/` |
| **Victor José Paes e Silva** | Co-líder | Criação do repositório, Makefile (Raylib), pair programming, documentação e `docs/` |
| **Eduardo de Souza Cavalcanti Junior** | Core | `tipos.h`, `jogo.c`, `menu.c`, `utils.c`, `memorygame.c`, `logica.c`, `precedencia.c`, `jogos_extras.c` |
| **Helamã Leone de Lima Procídio** | Frontend | Todas as telas Raylib (`frontend.c`), heurísticas visuais, renderização dos novos modos |
| **Felipe Franca Alves de Lima** | Dados | `historico.c`, `estatisticas.c`, funções recursivas, sistema de patentes, persistência multi-modo CSV/TXT |
| **João Pedro Arruda Guimarães** | Features | Testes de histórico, tematização Raylib, heurísticas de estratégia, modo VS, `Makefile` multiplataforma |
| **Tiago Luiz Moreira de Vasconcelos** | Features | Testes de histórico, tematização Raylib, heurísticas de estratégia, modo VS, revisão final e merge |

---

## 🛠️ Pré-requisitos

Antes de começar, certifique-se de ter instalado:

| Ferramenta | Versão mínima | Obrigatório |
| :--- | :---: | :---: |
| **GCC** | 4.8+ | Sim |
| **GNU Make** | 3.81+ | Sim |
| **Git** | 2.0+ | Sim |
| **Raylib** | 4.0+ | Apenas para `make raylib` |
| **clang-format** | 10+ | Recomendado (formatação) |

---

## 💻 Configuração do Ambiente

### <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS" height="18"/>

```bash
# 1. Instalar Homebrew (se ainda não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 2. Instalar GCC e Make
brew install gcc make

# 3. Instalar Raylib (opcional — versão gráfica)
brew install raylib

# 4. Instalar clang-format (opcional — formatação de código)
brew install clang-format

# 5. Clonar o repositório
git clone https://github.com/viictorpaes/Jogo-da-Adivinhacao.git
cd Jogo-da-Adivinhacao
```

### <img src="https://img.shields.io/badge/Ubuntu-E95420?style=flat-square&logo=ubuntu&logoColor=white" alt="Ubuntu" height="18"/>

```bash
# 1. Atualizar lista de pacotes
sudo apt-get update

# 2. Instalar GCC, Make e Git
sudo apt-get install -y gcc make git

# 3. Instalar Raylib (opcional — versão gráfica)
sudo apt-get install -y libraylib-dev

# 4. Instalar clang-format (opcional — formatação)
sudo apt-get install -y clang-format

# 5. Clonar o repositório
git clone https://github.com/viictorpaes/Jogo-da-Adivinhacao.git
cd Jogo-da-Adivinhacao
```

### <img src="https://img.shields.io/badge/windows%2010%2F11-2563EB?style=flat&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMjggMTI4Ij48cGF0aCBmaWxsPSIjMDBBREVGIiBkPSJNMTI2IDEuNjM3bC02NyA5LjgzNHY0OS44MzFsNjctLjUzNHpNMS42NDcgNjYuNzA5bC4wMDMgNDIuNDA0IDUwLjc5MSA2Ljk4My0uMDQtNDkuMDU3em01Ni44Mi42OGwuMDk0IDQ5LjQ2NSA2Ny4zNzYgOS41MDkuMDE2LTU4Ljg2M3pNMS42MSAxOS4yOTdsLjA0NyA0Mi4zODMgNTAuNzkxLS4yODktLjAyMy00OS4wMTZ6Ii8+PC9zdmc+" alt="Windows 10/11" height="18"/> <img src="https://img.shields.io/badge/MSYS2%20MinGW%2064--bit-black?style=flat&logo=gnubash&logoColor=white" alt="MSYS2 MinGW 64-bit" height="18"/> via MSYS2 MinGW 64-bit (recomendado)

> Baixe e instale o [MSYS2](https://www.msys2.org). Abra o terminal **MSYS2 MinGW 64-bit**.

```bash
# 1. Atualizar pacotes do MSYS2
pacman -Syu

# 2. Instalar GCC, Make e Git
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make git

# 3. Instalar Raylib (opcional — versão gráfica)
pacman -S mingw-w64-x86_64-raylib

# 4. Clonar o repositório
git clone https://github.com/viictorpaes/Jogo-da-Adivinhacao.git
cd Jogo-da-Adivinhacao
```

> [!TIP]
> No MSYS2, `mingw32-make` pode ser necessário no lugar de `make`. Caso ocorra erro, tente: `alias make=mingw32-make`.

<img src="https://img.shields.io/badge/windows%2010%2F11-2563EB?style=flat&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMjggMTI4Ij48cGF0aCBmaWxsPSIjMDBBREVGIiBkPSJNMTI2IDEuNjM3bC02NyA5LjgzNHY0OS44MzFsNjctLjUzNHpNMS42NDcgNjYuNzA5bC4wMDMgNDIuNDA0IDUwLjc5MSA2Ljk4My0uMDQtNDkuMDU3em01Ni44Mi42OGwuMDk0IDQ5LjQ2NSA2Ny4zNzYgOS41MDkuMDE2LTU4Ljg2M3pNMS42MSAxOS4yOTdsLjA0NyA0Mi4zODMgNTAuNzkxLS4yODktLjAyMy00OS4wMTZ6Ii8+PC9zdmc+" alt="Windows 10/11" height="18"/>Instalação manual (sem MSYS2)

Baixe os binários pré-compilados do Raylib em [raylib.com](https://www.raylib.com/index.html), extraia (ex.: `C:\raylib`) e compile passando o caminho:

```bash
make RAYLIB_DIR=C:/raylib raylib
```

---

## 🕹️ Compilação e Execução

Com o ambiente configurado, os comandos abaixo funcionam em **todos os sistemas operacionais**:

```bash
# Compilar e executar versão terminal
make run

# Compilar e executar versão gráfica (Raylib)
make raylib

# Compilar sem executar
make          # terminal
make build-raylib   # gráfico

# Compilar em modo debug (símbolos GDB/Valgrind)
make DEBUG=1 run
make DEBUG=1 raylib

# Remover binários gerados
make clean

# Formatar todo o código (requer clang-format)
make format
```

| Comando | Descrição |
| :--- | :--- |
| `make` | Compila versão terminal |
| `make run` | Compila e executa versão terminal |
| `make build-raylib` | Compila versão gráfica sem executar |
| `make raylib` | Compila e executa versão gráfica |
| `make clean` | Remove binários compilados |
| `make format` | Formata código com clang-format |
| `make DEBUG=1` | Compila com símbolos de debug |
| `make help` | Lista todos os alvos disponíveis |

---

## 📁 Estrutura do Projeto

```
Jogo-da-Adivinhacao/
├── Makefile                  # Sistema de build
├── .clang-format             # Regras de formatação C/C++
├── .prettierrc               # Regras de formatação Markdown/JSON
├── data/                     # Arquivos CSV e TXT de histórico (gerados em runtime)
├── docs/                     # Documentação técnica
│   ├── CONTRIBUTING.md       # Este arquivo
│   ├── ARCHITECTURE.md       # Visão da arquitetura
│   ├── API.md                # Contratos entre módulos
│   ├── GAMES.md              # Regras e detalhes dos 6 modos
│   └── CHANGELOG.md          # Plano de testes e histórico de mudanças
├── img/                      # Screenshots e assets visuais do README
└── src/
    ├── main.c                # Entry-point versão terminal
    ├── main_raylib.c         # Entry-point versão gráfica
    ├── include/tipos.h       # Structs, enums e typedefs globais
    ├── game/                 # Lógica dos 6 modos de jogo
    ├── ui/                   # Menus (terminal) e frontend (Raylib)
    ├── history/              # Leitura e escrita de histórico em CSV/TXT
    ├── static/               # Pontuação, heurísticas e estatísticas
    ├── utils/                # Funções utilitárias reutilizáveis
    ├── music/                # Trilha sonora (Raylib)
    └── ux/                   # Documentação de personas e jornadas
```

> Para a descrição completa de cada módulo, consulte [ARCHITECTURE.md](./ARCHITECTURE.md).

---

## 🔀 Fluxo de Contribuição

### 1. Faça um fork do repositório

Clique em **Fork** no GitHub e clone o seu fork localmente:

```bash
git clone https://github.com/SEU-USUARIO/Jogo-da-Adivinhacao.git
cd Jogo-da-Adivinhacao
```

### 2. Configure o repositório upstream

```bash
git remote add upstream https://github.com/viictorpaes/Jogo-da-Adivinhacao.git
```

### 3. Crie uma branch descritiva

Siga o padrão `tipo/descricao-curta`:

```bash
# Para nova funcionalidade
git checkout -b feat/modo-multiplayer-online

# Para correção de bug
git checkout -b fix/timer-zerando-ao-trocar-fase

# Para documentação
git checkout -b docs/atualizar-contributing
```

| Prefixo | Uso |
| :--- | :--- |
| `feat/` | Nova funcionalidade |
| `fix/` | Correção de bug |
| `docs/` | Documentação |
| `refactor/` | Refatoração sem mudança de comportamento |
| `test/` | Adição ou atualização de testes |

### 4. Implemente e formate o código

Antes de commitar, formate o código:

```bash
make format
```

### 5. Faça commits atômicos e descritivos

Siga o padrão [Conventional Commits](https://www.conventionalcommits.org/pt-br/):

```bash
# Bom
git commit -m "feat: adiciona modo torneio com chaveamento eliminatório"
git commit -m "fix: corrige timer não reiniciando ao passar de fase no VS"
git commit -m "docs: atualiza seção de Pair Programming no README"

# Ruim
git commit -m "update"
git commit -m "mudancas"
```

### 6. Sincronize com upstream antes de abrir PR

```bash
git fetch upstream
git rebase upstream/main
```

### 7. Abra um Pull Request

- Título claro e objetivo (ex.: `feat: modo torneio com chaveamento`)
- Descreva **o que** foi feito e **por quê**
- Referencia a issue relacionada com `Closes #123`
- Adicione screenshot ou screencast se a mudança for visual

---

## 📐 Convenções de Código

### Estilo C — `.clang-format`

O projeto usa o padrão **LLVM** via `.clang-format` na raiz. Sempre execute `make format` antes de commitar. As regras principais são:

- Indentação: **4 espaços** (sem tabs)
- Abertura de chave: **mesma linha** para `if/for/while`, **nova linha** para funções
- Comprimento máximo de linha: **120 caracteres**
- Ponteiros: alinhados à variável (`int *ptr`, não `int* ptr`)

```c
// Correto
void jogar_adivinhacao(ConfigJogo *cfg) 
{
    if (cfg->dificuldade == DIFICIL) 
    {
        iniciar_timer(cfg->timer);
    }
}

// Incorreto
void jogar_adivinhacao(ConfigJogo* cfg)
{
  if(cfg->dificuldade==DIFICIL)
  {
    iniciar_timer(cfg->timer); 
  }
}
```

### Nomenclatura

| Elemento | Convenção | Exemplo |
| :--- | :--- | :--- |
| Variáveis e funções | `snake_case` | `calcular_pontos()` |
| Constantes e macros | `UPPER_SNAKE_CASE` | `TIMER_ADIV_BONUS` |
| Structs e typedefs | `PascalCase` | `ConfigJogo`, `EstadoUI` |
| Arquivos `.c` / `.h` | `snake_case` | `jogar_memoria.c` |

### Módulos

- Todo módulo deve ter um `.h` com **include guard** e apenas a interface pública.
- Nunca incluir `raylib.h` fora dos módulos `ui/` e `music/`.
- Funções internas (não exportadas) devem ser declaradas como `static`.

---

## 🐛 Criando Issues

Use o [GitHub Issues](https://github.com/viictorpaes/Jogo-da-Adivinhacao/issues) para reportar bugs ou sugerir melhorias.

### Bug report

```
**Descrição do bug**
[O que acontece de errado]

**Como reproduzir**
1. Execute `make run`
2. Selecione modo Memória VS
3. ...

**Comportamento esperado**
[O que deveria acontecer]

**Ambiente**
- OS: macOS 14 / Ubuntu 22.04 / Windows 11
- GCC: 13.x
- Raylib: 4.5 (se aplicável)
```

### Sugestão de funcionalidade

```
**Funcionalidade desejada**
[Descreva a HU: Como [papel], quero [funcionalidade], para que [benefício]]

**Justificativa**
[Por que isso agrega valor ao projeto]

**Módulos envolvidos**
[ex.: src/game/memorygame.c, src/ui/frontend.c]
```

## 🧪 Rodando os Testes

O projeto usa testes manuais documentados em [docs/CHANGELOG.md](./CHANGELOG.md). Para executar:

```bash
# Compilar e executar a versão de teste
make run
```

Navegue pelos menus e valide os cenários descritos no CHANGELOG. Para cada caso de teste:

1. Execute o cenário descrito
2. Verifique o resultado esperado
3. Marque como `✅ Aprovado` ou `❌ Reprovado` no card do Trello

### Compilar em modo debug (recomendado durante testes)

```bash
make DEBUG=1 run
```

O modo debug ativa `-g -O0`, desabilitando otimizações e habilitando símbolos para uso com GDB:

```bash
# Depurar com GDB
gdb ./bin/jogo
(gdb) run
(gdb) backtrace
```

### Verificar vazamentos de memória com Valgrind (Linux/macOS)

```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/jogo
```

---

> Dúvidas? Abra uma [issue](https://github.com/viictorpaes/Jogo-da-Adivinhacao/issues) ou entre em contato com o líder técnico via [LinkedIn](https://www.linkedin.com/in/lucas-paguetti-pereira).

<h1 align="center">Frontend Gráfico com Raylib<br>
<img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="25"/></h1>

<p align="center">Instruções de compilação, uso e arquitetura da versão gráfica do projeto.</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-111827?style=flat-square&logo=c&logoColor=A8B9CC"/>
  <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white"/>
  <img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000"/>
  <img src="https://img.shields.io/badge/-1200×800-111827?style=flat-square&logo=visualstudiocode&logoColor=007ACC"/>
</p>

---

## 📁 Arquivos do Frontend

| Arquivo | Responsabilidade |
| :--- | :--- |
| `src/ui/frontend.h` | Header com estruturas (`EstadoUI`) e assinaturas de funções |
| `src/ui/frontend.c` | Implementação completa — renderização e entrada via Raylib |
| `src/main_raylib.c` | Ponto de entrada da versão gráfica |

---

## 🚀 Compilação

### Versão Console (Original)
```bash
make              # Compila a versão console
make run          # Compila e executa a versão console
make DEBUG=1      # Compila console com debug
```

### Versão Raylib (Gráfica)
```bash
make build-raylib  # Compila sem executar
make raylib        # Compila e executa
```

### Limpeza
```bash
make clean         # Remove todos os arquivos compilados
```

---

## 🛠️ Instalação do Raylib

<h3>
<img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/>
</h3>

```bash
brew install raylib
```

<h3>
<img src="https://img.shields.io/badge/Ubuntu%20%2F%20Debian-E95420?style=flat&logo=ubuntu&logoColor=white" alt="Ubuntu"/>
</h3>

```bash
sudo apt-get install libraylib-dev
```

<h3>
<img src="https://img.shields.io/badge/Windows-0078D4?style=flat&logo=windows&logoColor=white" alt="Windows"/> MSYS2 / MinGW
</h3>

```bash
pacman -S mingw-w64-x86_64-raylib
```

> [!NOTE]
> No Windows sem MSYS2, baixe os binários pré-compilados em [raylib.com](https://www.raylib.com/index.html) e adicione ao PATH.

---

## 🎮 Funcionalidades

### Menu Principal
- Escolha entre **Jogo da Adivinhação** ou **Jogo da Memória**
- Opção para sair da aplicação

### Jogo da Adivinhação
| Etapa | Detalhe |
| :--- | :--- |
| Dificuldade | Fácil (1–50 / 10 tent.), Médio (1–100 / 7 tent.), Difícil (1–200 / 5 tent.) |
| Palpite | Campo de texto — confirme com **Enter** |
| Feedback | O jogo informa se o número é **maior** ou **menor** |
| Resultado | Exibe vitória/derrota, número secreto e tentativas usadas |

### Jogo da Memória
| Etapa | Detalhe |
| :--- | :--- |
| Tabuleiro | 4×4 com 16 casas e 8 pares |
| Jogada | Clique em duas casas para revelar |
| Acerto | Casas permanecem reveladas; +10 pontos |
| Erro | Casas voltam a ficar ocultas |
| Fim | Exibe pontuação, pares, tentativas e eficiência |

---

## 🕹️ Controles

| Contexto | Controle | Ação |
| :--- | :---: | :--- |
| Adivinhação | Números / `Enter` | Digitar e confirmar palpite |
| Adivinhação | `ESC` | Voltar ao menu |
| Memória | Clique do mouse | Selecionar casa |
| Memória | `ESC` | Voltar ao menu |
| Menu | Clique do mouse | Selecionar opção |

---

## 🏗️ Arquitetura do Frontend

O frontend mantém um estado centralizado (`EstadoUI`) que controla:
- Estado atual da aplicação (`MENU`, `JOGO_ADIVINHACAO`, `JOGO_MEMORIA`, `RESULTADO`)
- Dados da partida em andamento
- Buffer de entrada do usuário

**Fluxo por frame:**
```
Loop principal
    ├── frontend_atualizar()  → processa entrada
    └── frontend_desenhar()   → renderiza a tela
```

> [!NOTE]
> A janela é definida como **1200×800 pixels**. Para alterar, modifique as constantes `SCREEN_WIDTH` e `SCREEN_HEIGHT` em `src/ui/frontend.h`.

---

## 🔧 Troubleshooting

| Problema | Solução |
| :--- | :--- |
| `raylib.h: No such file or directory` | Instale a biblioteca conforme seu sistema operacional |
| Programa não compila | Verifique a instalação do gcc/clang e do raylib |
| Janela não abre | Use `make raylib`; ambientes WSL/SSH sem display não suportam janelas gráficas |

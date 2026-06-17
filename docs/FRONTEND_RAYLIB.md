<h1 align="center">Frontend Gráfico com Raylib<br>
<img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white" height="25"/></h1>

<p align="center"><b>Instruções de compilação, uso e arquitetura da versão gráfica do projeto.</b></p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-111827?style=flat-square&logo=c&logoColor=A8B9CC"/>
  <img src="https://img.shields.io/badge/-Raylib-111827?style=flat-square&logo=raylib&logoColor=white"/>
  <img src="https://img.shields.io/badge/-Makefile-111827?style=flat-square&logo=probot&logoColor=A20000"/>
  <img src="https://img.shields.io/badge/-1200×800-111827?style=flat-square&logo=visualstudiocode&logoColor=007ACC"/>
</p>


## 📁 Arquivos do Frontend

| Arquivo | Responsabilidade |
| :--- | :--- |
| `src/ui/frontend.h` | Header com estruturas (`EstadoUI`) e assinaturas de funções |
| `src/ui/frontend.c` | Implementação completa — renderização e entrada via Raylib |
| `src/main/main_raylib.c` | Ponto de entrada da versão gráfica |

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

## 🛠️ Instalação do Raylib

<h3>
<img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" alt="macOS"/>
</h3>

```bash
brew install raylib
```

<h3>
<img src="https://img.shields.io/badge/Ubuntu-E95420?style=flat-square&logo=ubuntu&logoColor=white" alt="Ubuntu"/>
</h3>

```bash
sudo apt-get install libraylib-dev
```

<h3>
<img src="https://img.shields.io/badge/windows%2010%2F11-2563EB?style=flat&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMjggMTI4Ij48cGF0aCBmaWxsPSIjMDBBREVGIiBkPSJNMTI2IDEuNjM3bC02NyA5LjgzNHY0OS44MzFsNjctLjUzNHpNMS42NDcgNjYuNzA5bC4wMDMgNDIuNDA0IDUwLjc5MSA2Ljk4My0uMDQtNDkuMDU3em01Ni44Mi42OGwuMDk0IDQ5LjQ2NSA2Ny4zNzYgOS41MDkuMDE2LTU4Ljg2M3pNMS42MSAxOS4yOTdsLjA0NyA0Mi4zODMgNTAuNzkxLS4yODktLjAyMy00OS4wMTZ6Ii8+PC9zdmc+" alt="Windows 10/11" height="18"/> <img src="https://img.shields.io/badge/MSYS2%20MinGW%2064--bit-black?style=flat&logo=gnubash&logoColor=white" alt="MSYS2 MinGW 64-bit" height="18"/> MSYS2 / MinGW
</h3>

```bash
pacman -S mingw-w64-x86_64-raylib
```

> [!NOTE]
> No Windows sem MSYS2, baixe os binários pré-compilados em [raylib.com](https://www.raylib.com/index.html) e adicione ao PATH.


## 🎮 Funcionalidades

### Menu Principal
- Escolha entre os **6 modos de jogo** disponíveis
- Acesse Histórico, Estatísticas ou saia da aplicação

### 🔭 Missão: Adivinhação (Solo)
| Etapa | Detalhe |
| :--- | :--- |
| Dificuldade | Fácil (1–10 / 5 tent.), Médio (1–50 / 8 tent.), Difícil (1–100 / 10 tent.) |
| Palpite | Campo de texto — confirme com **Enter** |
| Feedback | "Maior" ou "Menor" com indicador de proximidade espacial |
| Timer | Regressivo de 15s por palpite; tentativa consumida ao esgotar |
| Resultado | Vitória/derrota com patente, pontuação e heurística de estratégia |

### ⚔️ Batalha de Sinais (Adivinhação VS — 2 Jogadores)
| Etapa | Detalhe |
| :--- | :--- |
| Turnos | Dois jogadores alternam palpites no mesmo dispositivo |
| Rodadas | Até 3 rodadas com placar acumulado |
| Resultado | Vencedor da melhor de 3 com histórico separado |

### 🧠 Jogo da Memória (Solo)
| Etapa | Detalhe |
| :--- | :--- |
| Tabuleiro | 4×4 com 16 casas e 8 pares |
| Jogada | Clique em duas casas para revelar |
| Timer | Regressivo de 30s base + bônus de 10s por par acertado |
| Acerto | Casas permanecem reveladas; +10 pontos |
| Fim | Exibe pontuação, pares, tentativas e eficiência |

### 🪐 1v1 Mapas Estelares (Memória VS — 2 Jogadores)
| Etapa | Detalhe |
| :--- | :--- |
| Turnos | Acerto mantém o turno; erro passa ao adversário |
| Timer | Independente por jogador |
| Resultado | Vencedor por maior pontuação com histórico separado |

### 🧮 Protocolo Lógico (Fórmulas V/F)
| Etapa | Detalhe |
| :--- | :--- |
| Questões | Fácil: 8, Médio: 10, Difícil: 12 |
| Timer | 30s / 20s / 15s por questão conforme dificuldade |
| Resposta | Avaliar V/F e classificar (Tautologia/Contradição/Contingência) |
| Patente | Sistema de rank progressivo por desempenho |

### 🔢 Hierarquia de Comandos (Precedência de Operadores)
| Etapa | Detalhe |
| :--- | :--- |
| Questões | Fácil: 8, Médio: 10, Difícil: 12 |
| Timer | 35s / 30s / 25s por questão conforme dificuldade |
| Resposta | Escolher a parentetização correta entre 4 opções embaralhadas |
| Patente | Sistema de rank progressivo por desempenho |

## 🕹️ Controles

| Contexto | Controle | Ação |
| :--- | :---: | :--- |
| Adivinhação / Lógica / Precedência | Números / `Enter` | Digitar e confirmar entrada |
| Adivinhação | `ESC` | Voltar ao menu |
| Memória | Clique do mouse | Selecionar casa |
| Memória | `ESC` | Voltar ao menu |
| Lógica / Precedência | `1` / `2` / `3` / `4` | Selecionar opção de resposta |
| Menu | Clique do mouse | Selecionar modo de jogo |


## 🏗️ Arquitetura do Frontend

O frontend mantém um estado centralizado (`EstadoUI`) que controla:
- Estado atual da aplicação (`MENU`, `JOGO_ADIVINHACAO`, `JOGO_BATALHA_SINAIS`, `JOGO_MEMORIA`, `JOGO_MEMORIA_VS`, `JOGO_LOGICA`, `JOGO_PRECEDENCIA`, `RESULTADO`, `HISTORICO`, `ESTATISTICAS` e estados auxiliares)
- Dados da partida em andamento (para todos os 6 modos)
- Buffer de entrada do usuário e cache de histórico

**Fluxo por frame:**
```
Loop principal
    ├── frontend_atualizar() → processa entrada
    └── frontend_desenhar()  → renderiza a tela
```

> [!NOTE]
> A janela é definida como **1200×800 pixels**. Para alterar, modifique as constantes `SCREEN_WIDTH` e `SCREEN_HEIGHT` em `src/ui/frontend.h`.


## 🔧 Troubleshooting

| Problema | Solução |
| :--- | :--- |
| `raylib.h: No such file or directory` | Instale a biblioteca conforme seu sistema operacional |
| Programa não compila | Verifique a instalação do gcc/clang e do raylib |
| Janela não abre | Use `make raylib`; ambientes WSL/SSH sem display não suportam janelas gráficas |


<h2 align="center">Telas 📱 <br></h2>

<table align="center" width="780">
  <tr><th align="center">🏠 Tela Inicial</th></tr>
  <tr><td align="center"><b>Menu principal do jogo — o jogador escolhe entre os 6 modos disponíveis ou acessa Histórico/Estatísticas.</b></td></tr>
  <tr><td align="center"><img src="../img/tela_inicial.png" width="750" alt="Tela Inicial"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">✏️ Salvar Nome</th></tr>
  <tr><td align="center"><b>Tela de cadastro do astronauta — o jogador insere seu nome antes de iniciar a partida para que o resultado seja salvo no ranking.</b></td></tr>
  <tr><td align="center"><img src="../img/salvar_nome.png" width="750" alt="Salvar Nome"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🔭 Operação Resgate — Patente</th></tr>
  <tr><td align="center"><b>Tela de patente da Missão Adivinhação — exibe o rank conquistado, pontuação e heurística de estratégia ao final da partida.</b></td></tr>
  <tr><td align="center"><img src="../img/operacao_resgate_patente.png" width="750" alt="Operação Resgate Patente"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">⚔️ Batalha de Sinais VS — Turno do Astronauta 1</th></tr>
  <tr><td align="center"><b>Modo 2 jogadores de adivinhação — turno do Astronauta 1; o placar lateral destaca "<-- SUA VEZ" e o timer conta regressivamente. Tentativas compartilhadas por rodada.</b></td></tr>
  <tr><td align="center"><img src="../img/batalha_sinais_vs_j1.png" width="750" alt="Batalha de Sinais VS — Turno J1"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">⚔️ Batalha de Sinais VS — Turno do Astronauta 2</th></tr>
  <tr><td align="center"><b>Turno do Astronauta 2 — feedback do palpite anterior exibido em vermelho; o placar lateral atualiza automaticamente o indicador de vez.</b></td></tr>
  <tr><td align="center"><img src="../img/batalha_sinais_vs_j2.png" width="750" alt="Batalha de Sinais VS — Turno J2"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🪐 Mapas Estelares — Solo</th></tr>
  <tr><td align="center"><b>Modo single-player de memória — encontre os pares de coordenadas estelares no grid 4×4. Quanto menos tentativas, maior a pontuação.</b></td></tr>
  <tr><td align="center"><img src="../img/mapas_estelares_solo.png" width="750" alt="Mapas Estelares Solo"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🧮 Protocolo Lógico</th></tr>
  <tr><td align="center"><b>Modo de fórmulas proposicionais — avalie V/F e classifique cada fórmula. Timer regressivo por questão; sistema de patentes progressivo.</b></td></tr>
  <tr><td align="center"><img src="../img/protocolo_logico.png" width="750" alt="Protocolo Lógico"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🧮 Protocolo Lógico — Patente</th></tr>
  <tr><td align="center"><b>Tela de patente do Protocolo Lógico — rank conquistado com base no percentual de acertos na sessão.</b></td></tr>
  <tr><td align="center"><img src="../img/protocolo_logico_patente.png" width="750" alt="Protocolo Lógico Patente"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🔢 Hierarquia de Comandos</th></tr>
  <tr><td align="center"><b>Modo de precedência de operadores — escolha a parentetização correta entre 4 opções embaralhadas, com timer regressivo por questão.</b></td></tr>
  <tr><td align="center"><img src="../img/hierarquia_cmds.png" width="750" alt="Hierarquia de Comandos"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">🔢 Hierarquia de Comandos — Patente</th></tr>
  <tr><td align="center"><b>Tela de patente da Hierarquia de Comandos — rank conquistado com base no desempenho.</b></td></tr>
  <tr><td align="center"><img src="../img/hierarquia_cmds_patente.png" width="750" alt="Hierarquia de Comandos Patente"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">📊 Estatísticas</th></tr>
  <tr><td align="center"><b>Painel de desempenho — exibe médias de tentativas, melhor e pior sessão, desvio padrão e dados calculados a partir do histórico de partidas.</b></td></tr>
  <tr><td align="center"><img src="../img/estatisticas.png" width="750" alt="Estatísticas"/></td></tr>
</table>

<br>

<table align="center" width="780">
  <tr><th align="center">📜 Histórico</th></tr>
  <tr><td align="center"><b>Registro completo de todas as sessões jogadas — mostra data, nome do jogador, dificuldade, tentativas utilizadas e resultado de cada partida.</b></td></tr>
  <tr><td align="center"><img src="../img/historico.png" width="750" alt="Histórico"/></td></tr>
</table>
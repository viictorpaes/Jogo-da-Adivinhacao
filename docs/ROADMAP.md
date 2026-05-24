<h1 align="center">RoadMap / Sprints & Tarefas por Membro <br>
<img src="https://img.shields.io/badge/-ROADMAP-111827?style=flat-square&logo=markdown&logoColor=green" height="23"/> </h1>

> <b>Registro das sprints do projeto, com as tarefas atribuídas a cada integrante da equipe.</b>

<h2 align="center">👥 Equipe <br>
<img src="https://img.shields.io/badge/-CONTRIBUTING-yellow?style=flat-square&logo=surveymonkey&logoColor=white" height="18"/></h2>

| Membro | Papel | Área de Atuação |
|--------|-------|-----------------|
| ![Lucas](https://img.shields.io/badge/Lucas_Paguetti-Líder-4B8BBE?style=flat-square&logo=github) | Co-líder de Projeto | Administração de atividades, gestão do repositório e liderança geral |
| ![Victor](https://img.shields.io/badge/Victor_Paes-Líder-4B8BBE?style=flat-square&logo=github) | Co-líder de Projeto | Administração de atividades, gestão do repositório e liderança geral |
| ![Eduardo](https://img.shields.io/badge/Eduardo-Capstone_1-2E8B57?style=flat-square&logo=c) | Desenvolvedor Core | Toda a lógica base do jogo no terminal — modularização, arquivos `.c` e `.h` |
| ![Helamã](https://img.shields.io/badge/Helamã-Frontend-9B59B6?style=flat-square&logo=raylib) | Desenvolvedor Frontend | Interface gráfica com Raylib — integrou o core de Eduardo na tela visual |
| ![Felipe](https://img.shields.io/badge/Felipe-Estatísticas-E67E22?style=flat-square&logo=databricks) | Desenvolvedor de Dados | Estatísticas, ranking, sessões, separação dos jogos em `data/` |
| ![João](https://img.shields.io/badge/João-Histórias_de_Usuário-E74C3C?style=flat-square&logo=rocket.chat) | Desenvolvedor de Features | Histórias de usuário, tematização astronauta e code reviews |
| ![Tiago](https://img.shields.io/badge/Tiago-Histórias_de_Usuário-E74C3C?style=flat-square&logo=rocket.chat) | Desenvolvedor de Features | Histórias de usuário, tematização astronauta e code reviews |

---

## Sprint 1 — Estrutura Base

**Objetivo:** Configurar o repositório, definir arquitetura e implementar o jogo de adivinhação no console.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Criar repositório e estrutura de diretórios | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Definir tipos globais (`tipos.h`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar lógica do jogo de adivinhação (`jogo.c`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar menu e UI do console (`menu.c`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar utilitários (`utils.c`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |

---

## Sprint 2 — Persistência e Histórico

**Objetivo:** Implementar salvamento de partidas em CSV/TXT e exibição do histórico.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Implementar módulo de histórico (`historico.c`) | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Criar schema de dados CSV | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Integrar salvamento no fluxo do jogo (`main.c`) | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Testar leitura e escrita de histórico | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ✅ Concluído |

---

## Sprint 3 — Estatísticas e Jogo da Memória

**Objetivo:** Implementar módulo de estatísticas/ranking e o Jogo da Memória.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Implementar cálculo de pontos e ranking (`estatisticas.c`) | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Implementar tabuleiro e lógica do Jogo da Memória (`memorygame.c`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar loop do Jogo da Memória no console (`jogar_memoria.c`) | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Integrar histórico do Jogo da Memória | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |

---

## Sprint 4 — Interface Gráfica (Raylib)

**Objetivo:** Criar versão gráfica completa com Raylib.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Configurar Makefile para Raylib | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Implementar telas base (menu, dificuldade, nome) no Raylib | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Implementar tela de adivinhação no Raylib | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Implementar tela do Jogo da Memória no Raylib | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Implementar telas de resultado e histórico no Raylib | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Tematização astronauta nas telas Raylib | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ✅ Concluído |

---

## Sprint 5 — Capstone 2: Estatísticas Analíticas

**Período:** até 26/05/2026  
**Objetivo:** Funções recursivas para estatísticas, heurísticas de estratégia e relatório analítico no histórico.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Implementar funções recursivas (soma, min, max, soma_quadrados) | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Implementar heurísticas textuais de estratégia | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ✅ Concluído |
| Exibir heurística nas telas de resultado (console + Raylib) | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Adicionar resumo estatístico na tela de histórico (Raylib) | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Exibir desvio padrão e min/max na tela de estatísticas | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |

---

## Sprint 5.5 — FDS Entrega 3 + Expansão de Modos

**Período:** mai/2026  
**Objetivo:** Implementar novos modos de jogo (Lógica, Precedência, Versus), sistema de patentes, trilha sonora e cumprir os requisitos da Entrega 3 de FDS (pair programming, issue tracker, screencasts).

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Implementar modo Protocolo Lógico (`logica.c`) | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar modo Precedência de Operadores (`precedencia.c`) | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Implementar modo Versus multiplayer local (Adivinhação VS + Memória VS) | ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) | ✅ Concluído |
| Implementar sistema de patentes progressivo | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Implementar `jogos_extras.c` para novos modos no console | ![Eduardo](https://img.shields.io/badge/Eduardo-core-2E8B57?style=flat-square) | ✅ Concluído |
| Adicionar trilha sonora temática em loop (`music/`) | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Persistência multi-modo: pares CSV+TXT por modo em `data/` | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ✅ Concluído |
| Expandir `frontend.c` para renderizar todos os novos modos | ![Helamã](https://img.shields.io/badge/Helamã-frontend-9B59B6?style=flat-square) | ✅ Concluído |
| Atualizar HUs para cobrir novos modos (28 HUs implementadas) | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ✅ Concluído |
| Pair programming documentado — relato no README | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Issue/bug tracker atualizado no GitHub (prints adicionados) | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Screencast 2 com ênfase nos novos modos | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | ✅ Concluído |
| Testes de sistema com os novos modos | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ✅ Concluído |

---

## Sprint 6 — Capstone 3: Polimento Final

**Período:** até 09/06/2026  
**Objetivo:** Refatoração, documentação final, testes com 100+ sessões.

| Tarefa | Responsável | Status |
|--------|-------------|--------|
| Remover comentários e código desnecessários | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | 🔄 Em progresso |
| Verificar e corrigir bugs remanescentes | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | 🔄 Em progresso |
| Atualizar README final | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | 🔄 Em progresso |
| Gerar 100+ sessões em `historico.txt` | ![Felipe](https://img.shields.io/badge/Felipe-dados-E67E22?style=flat-square) | ⏳ Pendente |
| Criar/revisar documentação em `docs/` | ![Lucas](https://img.shields.io/badge/Lucas-líder-4B8BBE?style=flat-square) ![Victor](https://img.shields.io/badge/Victor-líder-4B8BBE?style=flat-square) | 🔄 Em progresso |
| Revisão final de código e merge | ![João](https://img.shields.io/badge/João-features-E74C3C?style=flat-square) ![Tiago](https://img.shields.io/badge/Tiago-features-E74C3C?style=flat-square) | ⏳ Pendente |


> **Legenda:** <b>✅ Concluído | 🔄 Em progresso | ⏳ Pendente | ❌ Bloqueado</b>

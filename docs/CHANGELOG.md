<h1 align="center">Change Log / Plano de Testes
<br>
<img src="https://img.shields.io/badge/testes-20-111827?style=flat-square&logo=checkmarx&logoColor=white" height="22"/>
<img src="https://img.shields.io/badge/aprovados-19-brightgreen?style=flat-square&logo=checkmarx&logoColor=white" height="22"/>
<img src="https://img.shields.io/badge/pendentes-1-yellow?style=flat-square&logo=clockify&logoColor=white" height="22"/>
<img src="https://img.shields.io/badge/cobertura-95%25-blue?style=flat-square&logo=jest&logoColor=white" height="22"/>
</h1>

<p align="center"><b>Especificação dos casos de teste para validar os requisitos funcionais do projeto.</b></p>

---

## 1. Escopo

![Módulos](https://img.shields.io/badge/módulos-5-111827?style=flat-square&logo=c&logoColor=A8B9CC)

Cobre os módulos: **Jogo da Adivinhação** (console e Raylib), **Jogo da Memória** (console e Raylib), **Histórico** (CSV/TXT), **Estatísticas** (funções recursivas e heurísticas) e **Regressão**.

### Cobertura por Módulo

| Módulo | Casos de Teste | Aprovados | Pendentes | Status |
|--------|:--------------:|:---------:|:---------:|--------|
| Adivinhação | 5 | 5 | 0 | ![](https://img.shields.io/badge/100%25-brightgreen?style=flat-square) |
| Memória | 4 | 4 | 0 | ![](https://img.shields.io/badge/100%25-brightgreen?style=flat-square) |
| Histórico | 3 | 3 | 0 | ![](https://img.shields.io/badge/100%25-brightgreen?style=flat-square) |
| Estatísticas | 6 | 6 | 0 | ![](https://img.shields.io/badge/100%25-brightgreen?style=flat-square) |
| Regressão | 2 | 1 | 1 | ![](https://img.shields.io/badge/50%25-yellow?style=flat-square) |
| **Total** | **20** | **19** | **1** | ![](https://img.shields.io/badge/95%25-blue?style=flat-square) |

---

## 2. Casos de Teste — Jogo da Adivinhação

![Módulo](https://img.shields.io/badge/módulo-adivinhação-111827?style=flat-square&logo=c&logoColor=A8B9CC)
![Cobertura](https://img.shields.io/badge/cobertura-5%2F5-brightgreen?style=flat-square)

### CT-ADV-01: Geração de número secreto

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | O número gerado deve estar dentro do intervalo da dificuldade selecionada |
| **Pré-condição** | Dificuldade selecionada (Fácil/Médio/Difícil) |
| **Entrada** | Iniciar partida |
| **Resultado esperado** | Fácil: 1–50 \| Médio: 1–100 \| Difícil: 1–200 |

---

### CT-ADV-02: Feedback "Maior" / "Menor"

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Palpite abaixo do secreto retorna "Maior"; acima retorna "Menor" |
| **Entrada** | Palpite menor que secreto |
| **Resultado esperado** | Mensagem "O número secreto é MAIOR" |

---

### CT-ADV-03: Validação de entrada inválida

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-média-orange?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Entradas fora do intervalo ou não numéricas devem ser rejeitadas |
| **Entrada** | `-1`, `999`, `abc` (modo console) |
| **Resultado esperado** | Mensagem de erro, tentativa não contabilizada |

---

### CT-ADV-04: Derrota ao esgotar tentativas

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Ao usar todas as tentativas sem acertar, a partida termina com derrota |
| **Entrada** | Palpites errados até tentativas = max |
| **Resultado esperado** | Tela de derrota com número secreto revelado |

---

### CT-ADV-05: Vitória com pontuação correta

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Vitória na 1ª tentativa (Difícil) deve retornar 100 pts |
| **Entrada** | Palpite correto na tentativa 1, dificuldade Difícil |
| **Resultado esperado** | `calcular_pontos(DIFICIL, 1, true) == 100` |

---

## 3. Casos de Teste — Jogo da Memória

![Módulo](https://img.shields.io/badge/módulo-memória-111827?style=flat-square&logo=c&logoColor=A8B9CC)
![Cobertura](https://img.shields.io/badge/cobertura-4%2F4-brightgreen?style=flat-square)

### CT-MEM-01: Embaralhamento do tabuleiro

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Os 16 valores devem ter exatamente 8 pares (números 1–8, dois de cada) |
| **Entrada** | `inicializar_jogo_memoria()` |
| **Resultado esperado** | `numeros[i] ∈ {1..8}`, cada número aparece exatamente 2 vezes |

---

### CT-MEM-02: Par correto marcado como acertado

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Ao revelar duas casas com o mesmo número, elas devem ser marcadas |
| **Entrada** | `fazer_jogada(&jogo, pos1, pos2)` onde `numeros[pos1-1] == numeros[pos2-1]` |
| **Resultado esperado** | `acertadas[pos1-1] == true`, pontuação += 10 |

---

### CT-MEM-03: Par errado não incrementa pontuação

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-média-orange?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Par errado não altera pontuação, tentativas é incrementado |
| **Entrada** | `fazer_jogada` com casas de valores diferentes |
| **Resultado esperado** | Retorna `false`, `jogo.tentativas++`, `pontuacao` inalterada |

---

### CT-MEM-04: Término ao completar todos os pares

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | `jogo_memoria_finalizado` retorna true quando `pares_encontrados == 8` |
| **Entrada** | Completar todos os 8 pares |
| **Resultado esperado** | `jogo_memoria_finalizado(&jogo) == true` |

---

## 4. Casos de Teste — Histórico (Persistência)

![Módulo](https://img.shields.io/badge/módulo-histórico-111827?style=flat-square&logo=databricks&logoColor=FF3621)
![Cobertura](https://img.shields.io/badge/cobertura-3%2F3-brightgreen?style=flat-square)

### CT-HIST-01: Criar arquivos de histórico

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | `inicializar_historico()` cria CSV e TXT se não existirem |
| **Resultado esperado** | Arquivos criados com cabeçalho correto |

---

### CT-HIST-02: Salvar e recuperar partida de adivinhação

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Salvar um `RegistroPartida` e recuperá-lo com `carregar_historico` |
| **Resultado esperado** | Todos os campos iguais ao registro original |

---

### CT-HIST-03: Salvar e recuperar partida de memória

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Salvar um `RegistroMemoria` e recuperá-lo com `carregar_historico_memoria` |
| **Resultado esperado** | Todos os campos iguais ao registro original |

---

## 5. Casos de Teste — Estatísticas (Funções Recursivas)

![Módulo](https://img.shields.io/badge/módulo-estatísticas-111827?style=flat-square&logo=c&logoColor=A8B9CC)
![Cobertura](https://img.shields.io/badge/cobertura-6%2F6-brightgreen?style=flat-square)
![Capstone](https://img.shields.io/badge/Capstone-2-blueviolet?style=flat-square)

### CT-EST-01: soma_recursiva

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-recursão-purple?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Soma recursiva de um array deve igualar a soma iterativa |
| **Entrada** | `arr = {3, 1, 4, 1, 5}`, `n = 5` |
| **Resultado esperado** | `soma_recursiva(arr, 5) == 14` |

---

### CT-EST-02: minimo_recursivo

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-recursão-purple?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Entrada** | `arr = {7, 2, 9, 1, 5}`, `n = 5` |
| **Resultado esperado** | `minimo_recursivo(arr, 5) == 1` |

---

### CT-EST-03: maximo_recursivo

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-recursão-purple?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Entrada** | `arr = {7, 2, 9, 1, 5}`, `n = 5` |
| **Resultado esperado** | `maximo_recursivo(arr, 5) == 9` |

---

### CT-EST-04: soma_quadrados_recursiva (desvio padrão)

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-recursão-purple?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Soma dos quadrados das diferenças em relação à média |
| **Entrada** | `arr = {2, 4, 4, 4, 5, 5, 7, 9}`, média = 5 |
| **Resultado esperado** | `soma_quadrados == 32.0` |

---

### CT-EST-05: Heurística de adivinhação — vitória rápida

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-heurística-orange?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Entrada** | `tentativas=1, max=10, venceu=true` |
| **Resultado esperado** | Mensagem de parabéns por acerto na 1ª tentativa |

---

### CT-EST-06: Heurística de adivinhação — derrota

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Tipo](https://img.shields.io/badge/tipo-heurística-orange?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Entrada** | `venceu=false, tentativas=max` |
| **Resultado esperado** | Mensagem motivacional com dica de busca binária |

---

## 6. Testes de Regressão

![Módulo](https://img.shields.io/badge/módulo-regressão-111827?style=flat-square&logo=git&logoColor=F05032)
![Cobertura](https://img.shields.io/badge/cobertura-1%2F2-yellow?style=flat-square)

### CT-REG-01: 100 sessões consecutivas de adivinhação

![Status](https://img.shields.io/badge/status-pendente-yellow?style=flat-square)
![Capstone](https://img.shields.io/badge/Capstone-3-blueviolet?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | Após 100 partidas, o arquivo `historico.csv` deve ter 101 linhas (cabeçalho + 100) |
| **Observação** | Agendado para o Capstone 3 |

---

### CT-REG-02: Não duplicar registro ao reiniciar app

![Status](https://img.shields.io/badge/status-aprovado-brightgreen?style=flat-square)
![Prioridade](https://img.shields.io/badge/prioridade-alta-red?style=flat-square)

| Campo | Valor |
|-------|-------|
| **Descrição** | `inicializar_historico()` não deve sobrescrever dados existentes |

---

> **Legenda:** ![](https://img.shields.io/badge/aprovado-brightgreen?style=flat-square) Aprovado &nbsp;|&nbsp; ![](https://img.shields.io/badge/reprovado-red?style=flat-square) Reprovado &nbsp;|&nbsp; ![](https://img.shields.io/badge/pendente-yellow?style=flat-square) Pendente &nbsp;|&nbsp; ![](https://img.shields.io/badge/em%20análise-blue?style=flat-square) Em análise

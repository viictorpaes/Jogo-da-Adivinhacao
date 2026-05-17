<h1 align="center">Experiência: Jogar
<br>
<img src="https://img.shields.io/badge/🎮_Jogar-111827?style=flat-square&logo=gamepad2&logoColor=white" height="20"/>
<img src="https://img.shields.io/badge/UX-Gameplay-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="20"/>
</h1>

Documento de referência do fluxo de interação do jogador durante uma partida no **Missão Espacial: Adivinhação** — cobre telas, mensagens, estados esperados e sistema de feedback.

---

## Visão Geral

| Atributo | Detalhe |
| :--- | :--- |
| **Objetivo** | Adivinhar o número secreto gerado aleatoriamente dentro do intervalo da dificuldade |
| **Modos disponíveis** | Terminal (`make run`) e Visual Raylib (`make raylib`) |
| **Entrada do jogador** | Número inteiro dentro do intervalo definido pela patente escolhida |
| **Persistência** | Resultados salvos automaticamente em `data/historico.csv` e `data/historico.txt` |

---

## Fluxo Principal

```
Menu Principal
    └── "Missão: Adivinhação"
          └── Identificação do Astronauta (nome)
                └── Selecionar Patente Espacial (dificuldade)
                      └── Sistema gera número secreto
                            └── Loop de Tentativas
                                  ├── Astronauta insere palpite
                                  ├── Sistema valida entrada
                                  ├── Sistema responde: Maior / Menor / Acertou + Sinal Espacial
                                  ├── [Acerto] → Resumo (tentativas, pontuação) → Menu
                                  └── [Limite esgotado] → Revelar número → Resumo → Menu

Pós-partida:
    └── Resultado salvo automaticamente → pressionar ENTER → Menu Principal
```

---

## 🚀 Patentes Espaciais (Dificuldade)

A patente altera o intervalo de números possíveis e o número de tentativas, recompensando a precisão com pontuações maiores.

| Patente | Intervalo | Tentativas | Pontuação Máx. | Desafio |
| :--- | :---: | :---: | :---: | :--- |
| **Cientista** (Fácil) | `1 a 50` | 10 | 50 pts | 🟢 Baixo |
| **Piloto** (Médio) | `1 a 100` | 7 | 70 pts | 🟡 Moderado |
| **Buzz Lightyear** (Difícil) | `1 a 200` | 5 | 100 pts | 🔴 Alto |

> A pontuação é calculada como `base - (tentativas_usadas - 1) × step`, onde step é 5 (Fácil), 10 (Médio) ou 20 (Difícil). Derrota sempre resulta em 0 pontos.

---

## 📡 Sistema de Feedback por Sinal Espacial

O jogo usa um sistema de **proximidade por sinal** calculado como percentual da distância sobre o intervalo total (`distancia * 100 / range`):

| Feedback | Condição (% do intervalo) | Mensagem exibida |
| :--- | :---: | :--- |
| **Frequência muito próxima** 📡 | `< 5%` | "Você está quase lá!" |
| **Sinal detectado** 🔭 | `< 15%` | "Continue ajustando..." |
| **Interferência estática** 📟 | `< 40%` | "Sinal fraco." |
| **Sem sinal no espaço** 🛰️ | `≥ 40%` | "Muito longe!" |

> [!IMPORTANT]
> Além do sinal, o sistema sempre informa se o número secreto é **maior** ou **menor** que o palpite — combine as duas informações para uma estratégia de busca eficiente.

---

## Validação de Entradas

| Entrada | Comportamento do Sistema |
| :--- | :--- |
| Número dentro do intervalo | Prossegue normalmente |
| Número fora do intervalo | Exibe aviso e solicita nova entrada (sem consumir tentativa) |
| Caractere não numérico | Exibe erro e solicita nova entrada |
| Entrada vazia | Ignora e repete o prompt |

---

## Estados da Partida

| Estado | Condição de Entrada | Ação do Sistema |
| :--- | :--- | :--- |
| **Em andamento** | Tentativas restantes > 0 e ainda não acertou | Exibe prompt de palpite |
| **Vitória** | Palpite == número secreto | Exibe "MISSÃO CUMPRIDA", resumo e salva automaticamente |
| **Derrota** | Tentativas esgotadas sem acerto | Revela o número, exibe resumo e salva automaticamente |
| **Inválido** | Entrada fora do formato esperado | Rejeita entrada sem consumir tentativa |

---

## Exemplo de Sessão (Terminal)

```
=== Missão Espacial — Patente: Piloto (Médio) ===
Intervalo: 1 a 100 | Tentativas: 7

Tentativa 1/7 › Seu palpite: 50
🚨 TRANSMISSÃO: O número secreto é MAIOR! Aponte para cima! ^
📟 Interferência estática... Sinal fraco.
Tentativas restantes: 6

Tentativa 2/7 › Seu palpite: 75
🚨 TRANSMISSÃO: O número secreto é MENOR! Volte à órbita! v
📡 Frequência muito próxima! Você está quase lá!
Tentativas restantes: 5

Tentativa 3/7 › Seu palpite: 72
📡 Sinal estabelecido! Resgate a caminho!
✅ MISSÃO CUMPRIDA! Você encontrou o número secreto, Astronauta!

Resultado: 3 tentativas | Pontuação: 50 pts
Partida salva em: data/historico.txt e data/historico.csv
```

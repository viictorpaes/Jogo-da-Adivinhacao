<h1 align="center">Experiência: Jogar
<br>
<img src="https://img.shields.io/badge/🎮_Jogar-111827?style=flat-square&logo=gamepad2&logoColor=white" height="20"/>
<img src="https://img.shields.io/badge/UX-Gameplay-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="20"/>
</h1>

Documento de referência do fluxo de interação do jogador durante uma partida no **CesarNumber** — cobre telas, mensagens, estados esperados e sistema de feedback.

---

## Visão Geral

| Atributo | Detalhe |
| :--- | :--- |
| **Objetivo** | Adivinhar o número secreto gerado aleatoriamente dentro do intervalo da dificuldade |
| **Modos disponíveis** | Terminal (console) e Visual (Raylib) |
| **Entrada do jogador** | Número inteiro dentro do intervalo definido pela dificuldade escolhida |
| **Persistência** | Resultados salvos em `data/historico.csv` e `data/historico.txt` |

---

## Fluxo Principal

```
Menu Principal
    └── "Jogar"
          └── Selecionar Dificuldade
                └── Sistema gera número secreto
                      └── Loop de Tentativas
                            ├── Jogador insere palpite
                            ├── Sistema valida entrada
                            ├── Sistema responde: Maior / Menor / Acertou + Temperatura
                            ├── [Acerto] → Resumo (tentativas, pontuação) → Pós-partida
                            └── [Limite esgotado] → Revelar número → Resumo → Pós-partida

Pós-partida:
    ├── Jogar novamente
    ├── Voltar ao menu
    └── Salvar resultado no histórico
```

---

## 🎮🟢🟡🔴 Níveis de Dificuldade

A dificuldade altera o intervalo de números possíveis e o número de tentativas, recompensando a precisão com pontuações maiores.

| Nível | Intervalo | Tentativas | Pontuação Base | Desafio |
| :--- | :---: | :---: | :---: | :--- |
| **Fácil** | `1 a 50` | 20 | 1.000 pts | 🟢 Baixo |
| **Médio** | `1 a 100` | 10 | 2.000 pts | 🟡 Moderado |
| **Difícil** | `1 a 500` | 5 | 5.000 pts | 🔴 Alto |

---

## 🔥❄️ Sistema de Feedback Termodinâmico

O jogo usa um sistema de **proximidade por temperatura** para tornar a jogabilidade mais imersiva. O feedback é calculado pela diferença absoluta entre o palpite e o número secreto ($|palpite - secreto|$):

| Feedback | Condição (Distância) | Mensagem exibida |
| :--- | :---: | :--- |
| **Pegando Fogo!** 🔥🔥 | $\pm 1$ | Você está a apenas uma unidade do número! |
| **Quente!** 🔥 | $\leq 5$ | Você está muito perto, o acerto é iminente. |
| **Morno** 🌤️ | $\leq 15$ | Você está na vizinhança correta do número. |
| **Frio** ❄️ | $> 15$ | Você ainda está longe do objetivo. |

> [!IMPORTANT]
> Além da temperatura, o sistema sempre informa se o número secreto é **maior** ou **menor** que o palpite — combine as duas informações para uma estratégia de busca eficiente.

---

## Validação de Entradas

| Entrada | Comportamento do Sistema |
| :--- | :--- |
| Número dentro do intervalo | Prossegue normalmente |
| Número fora do intervalo | Exibe aviso e solicita nova entrada (sem consumir tentativa) |
| Caractere não numérico | Exibe erro descritivo e solicita nova entrada |
| Entrada vazia | Ignora e repete o prompt |

---

## Estados da Partida

| Estado | Condição de Entrada | Ação do Sistema |
| :--- | :--- | :--- |
| **Em andamento** | Tentativas restantes > 0 e ainda não acertou | Exibe prompt de palpite |
| **Vitória** | Palpite == número secreto | Exibe parabéns, resumo e opções pós-partida |
| **Derrota** | Tentativas esgotadas sem acerto | Revela o número, exibe resumo e opções |
| **Inválido** | Entrada fora do formato esperado | Rejeita entrada sem consumir tentativa |

---

## Exemplo de Sessão (Terminal)

```
=== CesarNumber — Dificuldade: Médio ===
Intervalo: 1 a 100 | Tentativas: 10

Tentativa 1/10 › Seu palpite: 50
→ Maior | Morno 🌤️  (distância: 22)

Tentativa 2/10 › Seu palpite: 75
→ Menor | Quente! 🔥 (distância: 3)

Tentativa 3/10 › Seu palpite: 72
→ Acertou! 🎉

Resultado: 3 tentativas | Pontuação: 1.700 pts
[1] Jogar novamente  [2] Menu  [3] Salvar resultado
```

<h1 align="center">Experiência: Jogar <br>
<img src="https://img.shields.io/badge/🎮 Jogar-rebeccapurple?style=flat-square&logo=gamepad&logoColor=white" height="18"></h1>

## Visão geral
- Objetivo: o jogador tenta adivinhar um número secreto gerado aleatoriamente dentro de um intervalo definido pela dificuldade.
- Escopo deste documento: fluxo de interação, telas/textos, estados esperados, mensagens de erro e exemplos de sessão.

## Fluxo principal (alto nível)
1. Tela inicial: jogador escolhe "Jogar" no menu principal.

2. Seleção de dificuldade: jogador escolhe entre Fácil, Médio ou Difícil.

3. Início da partida: o sistema gera um número secreto e exibe instruções (intervalo e número máximo de tentativas, se aplicável).

4. Loop de tentativas:
   - Jogador insere um palpite (inteiro).
   - Sistema valida a entrada (inteiro no intervalo).
   - Sistema responde: "Maior", "Menor" ou "Acertou".
   - Sistema registra tentativa e atualiza contadores (tentativas, erros acumulados).

5. Fim de partida:
   - Vitória: jogador acerta; exibir resumo (tentativas, pontuação, tempo/opcional).
   - Derrota: jogador atinge limite de tentativas (se houver); exibir resposta correta e resumo.
   
6. Pós-partida: opções: Jogar novamente, Voltar ao menu, Salvar resultado no histórico.


### 🎮🟢🟡🔴 Níveis de Dificuldade

A dificuldade selecionada altera o intervalo de números possíveis e restringe o número de tentativas, recompensando a precisão com pontuações maiores.

| Nível | Intervalo | Tentativas | Pontuação Base | Desafio |
| :--- | :---: | :---: | :---: | :--- |
| **Fácil** | `1 a 50` | 20 | 1000 | 🟢 Baixo |
| **Médio** | `1 a 100` | 10 | 2000 | 🟡 Moderado |
| **Difícil** | `1 a 500` | 5 | 5000 | 🔴 Alto |

### 🔥🧦❄️🌥️ Sistema de Feedback Termodinâmico

Para tornar a jogabilidade mais imersiva, o jogo utiliza um sistema de proximidade baseado em "temperaturas". O feedback é calculado pela diferença absoluta ($|palpite - secreto|$):

| Feedback | Condição (Distância) | Descrição |
| :--- | :--- | :--- |
| **Pegando Fogo!** 🔥🔥 | $\pm 1$ | Você está a apenas uma unidade do número! |
| **Quente!** 🔥 | $\leq 5$ | Você está muito perto, o acerto é iminente. |
| **Morno** 🌤️ | $\leq 15$ | Você está na vizinhança correta do número. |
| **Frio** ❄️ | $> 15$ | Você ainda está longe do objetivo. |

> [!IMPORTANT]
> Além da temperatura, o jogo continuará informando se o número secreto é **maior** ou **menor** que o palpite, auxiliando na estratégia de busca do jogador.
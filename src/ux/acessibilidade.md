<h1 align="center">Acessibilidade
<br>
<img src="https://img.shields.io/badge/♿_Acessibilidade-111827?style=flat-square&logo=appleaccess&logoColor=white" height="20"/>
<img src="https://img.shields.io/badge/UX-Design_Inclusivo-rebeccapurple?style=flat-square&logo=adobe-experience-manager&logoColor=white" height="20"/>
</h1>

Diretrizes de acessibilidade aplicadas ao **CesarNumber** para garantir que jogadores com diferentes necessidades possam interagir com o jogo de forma plena e autônoma.

---

## Princípios Adotados

| Princípio | Descrição |
| :--- | :--- |
| **Perceptível** | Informações transmitidas por mais de um canal (texto + símbolo + prefixo) |
| **Operável** | Toda interação possível exclusivamente via teclado |
| **Compreensível** | Mensagens em linguagem natural, sem jargões técnicos desnecessários |
| **Robusto** | Entradas inválidas tratadas com explicação clara, sem travamentos |

---

## Diretrizes por Categoria

### Legibilidade de Texto

<img src="https://img.shields.io/badge/Status-Implementado-22c55e?style=flat-square" height="17"/>

| Diretriz | Implementação |
| :--- | :--- |
| Mensagens completas e diretas | Evitar abreviações sem contexto nas saídas do terminal |
| Prefixos de tipo em mensagens | Usar `[INFO]`, `[ERRO]`, `[SUCESSO]` para diferenciar contextos |
| Evitar símbolos isolados | Símbolos sempre acompanhados de texto explicativo |

---

### Contraste e Não-Dependência de Cor

<img src="https://img.shields.io/badge/Status-Implementado-22c55e?style=flat-square" height="17"/>

| Diretriz | Implementação |
| :--- | :--- |
| Não depender apenas de cor para transmitir informação | Prefixos textuais como `[ERRO]` e `[OK]` complementam qualquer cor de terminal |
| Compatibilidade com terminais monocromáticos | O jogo funciona corretamente em terminais sem suporte a cores ANSI |

---

### Navegação por Teclado

<img src="https://img.shields.io/badge/Status-Implementado-22c55e?style=flat-square" height="17"/>

| Diretriz | Implementação |
| :--- | :--- |
| 100% das interações via teclado | Toda entrada é feita via digitação + `Enter`; sem dependência de mouse |
| Atalhos numéricos no menu | Opções selecionáveis por número (ex.: `[1] Jogar`, `[2] Histórico`) |
| Confirmação sempre explícita | Nenhuma ação irreversível ocorre sem prompt de confirmação |

---

### Compatibilidade com Leitores de Tela

<img src="https://img.shields.io/badge/Status-Parcial-f59e0b?style=flat-square" height="17"/>

| Diretriz | Implementação |
| :--- | :--- |
| Frases naturais e lineares | Evitar sequências de caracteres repetidos (`===`, `---`) sem contexto semântico |
| Sem arte ASCII complexa como único conteúdo | Menus e resultados expressos também em texto plano |
| Saída sequencial e previsível | Cada prompt aguarda resposta antes de exibir o próximo bloco |

> [!NOTE]
> A versão Raylib (gráfica) não possui suporte nativo a leitores de tela. Para acessibilidade plena, recomenda-se a **versão terminal** (`make run`).

---

### Gestão de Tempo

<img src="https://img.shields.io/badge/Status-Parcial_(varia_por_modo)-f59e0b?style=flat-square" height="17"/>

| Diretriz | Terminal | Raylib |
| :--- | :--- | :--- |
| Sem limite de tempo para responder | ✅ Aguarda indefinidamente em todos os modos | 🔸 Adivinhação e Memória têm timer de jogo; Lógica e Precedência têm timer por questão |
| Pausas naturais preservadas | ✅ O jogador controla o ritmo | 🔸 Timer corre continuamente — sem opção de pausa |
| Tentativas vs. tempo | ✅ Desafio baseado em quantidade de tentativas | 🔸 Desafio combinado: tentativas **e** tempo restante |

> [!NOTE]
> O timer no Raylib é parte intencional da mecânica de jogo, não uma barreira de acessibilidade — contribui para o bônus de pontuação. Jogadores que precisam de mais tempo sem penalização devem usar a **versão terminal** (`make run`), que não possui countdown em nenhum modo.

---

## Checklist de Conformidade

| Item | Terminal | Raylib |
| :--- | :---: | :---: |
| Interação 100% por teclado | ✅ | ✅ |
| Mensagens com prefixo de contexto | ✅ | 🔸 Parcial |
| Sem dependência exclusiva de cor | ✅ | ⬜ Não aplicado |
| Sem limite de tempo de resposta | ✅ | 🔸 Timer em Adivinhação, Memória, Lógica e Precedência |
| Entradas inválidas explicadas | ✅ | ✅ |
| Compatível com leitores de tela | 🔸 Parcial | ❌ Não suportado |

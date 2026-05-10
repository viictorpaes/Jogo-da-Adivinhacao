<h1 align="center">Schema de Dados<br>
<img src="https://img.shields.io/badge/-Schema-111827?style=flat-square&logo=json&logoColor=white" height="25"/></h1>

<p align="center">Definição da estrutura de dados utilizada para persistir o histórico de partidas.</p>

---

## 📄 Arquivo `data/historico.csv`
<img src="https://img.shields.io/badge/-CSV-111827?style=flat-square&logo=microsoft-excel&logoColor=217346" height="18"/><br>
Arquivo CSV simples com separador `,`. Cada linha representa uma partida encerrada.

### Colunas

| Campo | Tipo | Descrição | Exemplo |
| :--- | :---: | :--- | :--- |
| `data_iso` | `string` | Timestamp ISO 8601 | `2026-04-12T15:30:00Z` |
| `jogador` | `string` | Nome do jogador | `ana` |
| `pontuacao` | `int` | Pontuação obtida na partida | `2000` |
| `tentativas` | `int` | Número de tentativas feitas | `5` |
| `dificuldade` | `enum` | Nível selecionado: `facil`, `medio` ou `dificil` | `medio` |

### Exemplo de linha

```
2026-04-12T00:00:00Z,ana,2000,5,medio
```

---

## 🗃️ Arquivo `data/historico.txt`
<img src="https://img.shields.io/badge/-TXT-111827?style=flat-square&logo=files&logoColor=A85D00" height="18"/><br>
Base de dados principal utilizada pelo módulo `history/` para leitura e gravação em tempo de execução. O formato `.csv` é derivado deste arquivo para análise em ferramentas externas.

---

## ⚠️ Notas de Implementação

> [!IMPORTANT]
> Evitar vírgulas no nome do jogador, pois o separador do CSV é `,`. Se necessário, troque o separador para `;` ou implemente escape no módulo `history/historico.c`.

> [!NOTE]
> O campo `data_iso` segue o padrão **ISO 8601** com fuso UTC (`Z`). Use `strftime` com o formato `%Y-%m-%dT%H:%M:%SZ` para gerar timestamps compatíveis em C.

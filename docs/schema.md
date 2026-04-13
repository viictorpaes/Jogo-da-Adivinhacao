<h1 align="center">Schema do arquivo data/historico.csv <br>
<img src="https://img.shields.io/badge/schema-json-green?style=flat-square&logo=json" height="18"></h1>

<h2 align="left">Colunas (CSV): <br>
<img src="https://img.shields.io/badge/data-csv-green" height="18"></h2>

- `data_iso` — Timestamp ISO 8601 (ex.: 2026-04-12T15:30:00Z)
- `jogador` — Nome do jogador (string curta)
- `pontuacao` — Pontuação obtida na partida (inteiro)
- `tentativas` — Número de tentativas feitas (inteiro)
- `dificuldade` — Nível de dificuldade (`facil`, `medio`, `dificil`)

Exemplo:

```
2026-04-12T00:00:00Z,ana,2000,5,medio
```

## Notas:
- Arquivo CSV simples, separador `,`.
- Evitar vírgulas em nomes de jogador; se necessário, passe para outro separador ou escape.

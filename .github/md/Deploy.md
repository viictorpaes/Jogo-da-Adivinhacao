<h1 align="center">Deploy & CI/CD<br>
<img src="https://img.shields.io/badge/GitHub%20Actions-111827?style=flat-square&logo=githubactions&logoColor=2088FF" height="25"/>
<img src="https://img.shields.io/badge/GitHub%20Releases-111827?style=flat-square&logo=github&logoColor=white" height="25"/></h1>

<p align="center"><b>Pipeline automatizado de build e publicação de releases multiplataforma via GitHub Actions.</b></p>

---

## 🚀 Visão Geral

O deploy do projeto é 100% automatizado: ao criar e empurrar uma **tag `v*`** no repositório, o workflow `.github/workflows/release.yml` compila o binário da versão Raylib em três plataformas em paralelo e publica todos os artefatos em uma **GitHub Release** pública.

```
git tag v1.0.0
git push origin v1.0.0
        │
        ▼
  GitHub Actions
  ┌─────────────────────────────────────────┐
  │  build-macos  │  build-linux  │  build-windows  │
  └──────────────────┬──────────────────────┘
                     ▼
              release job
         (cria GitHub Release
          + anexa os 3 .zip)
```

---

## ⚡ Gatilho do Pipeline

| Evento | Comportamento |
| :--- | :--- |
| `push` em tag `v*` | Compila as 3 plataformas **e** publica a Release |
| `workflow_dispatch` | Compila as 3 plataformas, mas **não** publica Release (útil para testes de build) |

---

## 🏗️ Matriz de Jobs

### <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" height="18" alt="macOS"/> `build-macos` — `macos-latest`

| Etapa | Detalhe |
| :--- | :--- |
| **Checkout** | `actions/checkout@v4` |
| **Instalar Raylib** | `brew install raylib` |
| **Compilar** | `make build-raylib` |
| **Empacotar** | Copia `jogo_raylib` + `StarWarsMainTheme.mp3` → `jogo_raylib_macos.zip` |
| **Upload artefato** | `actions/upload-artifact@v4` → `jogo_raylib_macos` |

---

### <img src="https://img.shields.io/badge/Ubuntu%2022.04-E95420?style=flat-square&logo=ubuntu&logoColor=white" height="18" alt="Ubuntu 22.04"/> `build-linux` — `ubuntu-22.04`

| Etapa | Detalhe |
| :--- | :--- |
| **Checkout** | `actions/checkout@v4` |
| **Instalar dependências** | `gcc`, `make`, `libgl1-mesa-dev`, `libxi-dev`, `libxcursor-dev`, `libxinerama-dev`, `libxrandr-dev`, `libasound2-dev` |
| **Compilar Raylib 5.0 from source** | Clone `raysan5/raylib@5.0` → `make PLATFORM=PLATFORM_DESKTOP` → `sudo make install` |
| **Compilar jogo** | `make build-raylib RAYLIB_FLAGS="-I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lX11"` |
| **Empacotar** | Copia `jogo_raylib` + `StarWarsMainTheme.mp3` → `jogo_raylib_linux.zip` |
| **Upload artefato** | `actions/upload-artifact@v4` → `jogo_raylib_linux` |

> [!NOTE]
> O Ubuntu não disponibiliza o Raylib 5.x via `apt`, por isso o job compila a biblioteca do código-fonte diretamente. Isso garante compatibilidade total com a versão usada no projeto.

---

### <img src="https://img.shields.io/badge/Windows%2010%2F11-2563EB?style=flat&logo=windows&logoColor=white" height="18" alt="Windows"/> `build-windows` — `windows-latest` + MSYS2/MinGW64

| Etapa | Detalhe |
| :--- | :--- |
| **Checkout** | `actions/checkout@v4` |
| **Setup MSYS2** | `msys2/setup-msys2@v2` — sistema `MINGW64`, instala `mingw-w64-x86_64-gcc`, `mingw-w64-x86_64-make`, `mingw-w64-x86_64-raylib`, `zip` |
| **Compilar** | `mingw32-make build-raylib` (shell MSYS2) |
| **Empacotar** | Copia `jogo_raylib.exe` + `StarWarsMainTheme.mp3` + DLLs necessárias (`libgcc_s_seh-1.dll`, `libwinpthread-1.dll`, `libraylib.dll`) → `jogo_raylib_windows.zip` |
| **Upload artefato** | `actions/upload-artifact@v4` → `jogo_raylib_windows` |

> [!IMPORTANT]
> As DLLs do MinGW são incluídas no `.zip` para que o executável rode **sem precisar do MSYS2 instalado** na máquina do usuário final.

---

## 📦 Estrutura dos Artefatos

Cada `.zip` contém:

```
jogo_raylib_<plataforma>.zip
├── jogo_raylib          ← binário (Linux/macOS) ou jogo_raylib.exe (Windows)
├── src/
│   └── music/
│       └── StarWarsMainTheme.mp3   ← trilha sonora (caminho relativo obrigatório)
└── data/                           ← pasta vazia; o jogo cria os .csv/.txt aqui
```

> [!WARNING]
> Execute o binário **sempre de dentro da pasta extraída**. O caminho relativo `src/music/StarWarsMainTheme.mp3` é exigido pelo módulo `music/` em tempo de execução. Se o executável for movido sem a pasta, a trilha sonora não carregará.

---

## 🏷️ Job `release` — GitHub Release

O job `release` depende dos três jobs de build (`needs: [build-macos, build-linux, build-windows]`) e só é executado quando o `github.ref` começa com `refs/tags/`.

| Etapa | Detalhe |
| :--- | :--- |
| **Download artefatos** | `actions/download-artifact@v4` — baixa os 3 `.zip` gerados nos jobs anteriores |
| **Criar Release** | `softprops/action-gh-release@v2` — cria Release com nome `Jogo da Adivinhação <tag>` e anexa os 3 `.zip` |

A Release é publicada como **não-rascunho** e **não-pré-release** automaticamente.

---

## 🌐 Plataformas Suportadas

<p align="center">
<img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" height="22" alt="macOS"/>
<img src="https://img.shields.io/badge/Ubuntu%2022.04-E95420?style=flat-square&logo=ubuntu&logoColor=white" height="22" alt="Linux / Ubuntu 22.04"/>
<img src="https://img.shields.io/badge/Windows%2010%2F11-2563EB?style=flat&logo=windows&logoColor=white" height="22" alt="Windows 10/11"/>
</p>

| Plataforma | Runner | Arquivo | Executável |
| :--- | :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/macOS-white?style=flat&logo=apple&logoColor=black" height="16"/> macOS | `macos-latest` | `jogo_raylib_macos.zip` | `./jogo_raylib` |
| <img src="https://img.shields.io/badge/Ubuntu-E95420?style=flat-square&logo=ubuntu&logoColor=white" height="16"/> Linux (Ubuntu/Debian x64) | `ubuntu-22.04` | `jogo_raylib_linux.zip` | `./jogo_raylib` |
| <img src="https://img.shields.io/badge/Windows-2563EB?style=flat&logo=windows&logoColor=white" height="16"/> Windows 10/11 | `windows-latest` | `jogo_raylib_windows.zip` | `jogo_raylib.exe` |

---

## 🔖 Como Publicar uma Nova Release

```bash
# 1. Certifique-se de que o branch principal está atualizado
git checkout main
git pull

# 2. Crie e empurre a tag semântica
git tag v1.2.0
git push origin v1.2.0
```

O GitHub Actions dispara automaticamente o pipeline. Acompanhe em:
`https://github.com/viictorpaes/Jogo-da-Adivinhacao/actions`

---

## 🔗 Links Úteis

| Recurso | Link |
| :--- | :--- |
| Último release publicado | [![GitHub Release](https://img.shields.io/github/v/release/viictorpaes/Jogo-da-Adivinhacao?label=deploy&logo=github)](https://github.com/viictorpaes/Jogo-da-Adivinhacao/releases/latest) |
| Status do CI | [![Build & Release](https://github.com/viictorpaes/Jogo-da-Adivinhacao/actions/workflows/release.yml/badge.svg)](https://github.com/viictorpaes/Jogo-da-Adivinhacao/actions/workflows/release.yml) |
| Workflow fonte | [`.github/workflows/release.yml`](../workflows/release.yml) |

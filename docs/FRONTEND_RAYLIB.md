# Frontend com RayLib - Instruções de Compilação e Uso

## Descrição

Foi criado um frontend gráfico funcional para os jogos usando a biblioteca **RayLib**, uma biblioteca multiplataforma para gráficos, entrada e áudio.

### Arquivos Criados

- **`src/ui/frontend.h`** - Header com estruturas e funções do frontend
- **`src/ui/frontend.c`** - Implementação do frontend com RayLib
- **`src/main_raylib.c`** - Main simplificado que inicia o frontend

### Makefile Atualizado

O `Makefile` foi atualizado para suportar compilação de ambas as versões:

## Compilação

### 1. **Versão Console (Original)**
```bash
make              # Compila a versão console
make run          # Compila e executa a versão console
make DEBUG=1      # Compila console com debug
```

### 2. **Versão RayLib (Gráfica)**
```bash
make raylib       # Compila a versão RayLib
make run-raylib   # Compila e executa a versão RayLib
```

### 3. **Limpeza**
```bash
make clean        # Remove todos os arquivos compilados
```

## Requisitos para Compilar o RayLib

### Windows (MSYS2 / MinGW)
```bash
pacman -S mingw-w64-x86_64-raylib
```

### Ubuntu / Debian
```bash
sudo apt-get install libraylib-dev
# ou compilar do código-fonte:
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
```

### macOS
```bash
brew install raylib
```

## Funcionalidades do Frontend

### Menu Principal
- Escolha entre **Jogo da Adivinhação** ou **Jogo da Memória**
- Opção para sair

### Jogo da Adivinhação
1. Selecione a dificuldade:
   - **Fácil** (1-50, 10 tentativas)
   - **Médio** (1-100, 7 tentativas)
   - **Difícil** (1-200, 5 tentativas)

2. Jogue:
   - Digite seu palpite no campo de entrada
   - Pressione **Enter** para confirmar
   - Receba dica se o número é **maior** ou **menor**
   - O jogo termina quando você acerta ou esgota as tentativas

3. Resultado final mostra:
   - Se você venceu ou perdeu
   - O número secreto
   - Quantas tentativas usou

### Jogo da Memória
1. Tabuleiro 4x4 com 16 casas
2. Clique em duas casas para revelar os números
3. Se forem iguais, você ganha pontos e continuam reveladas
4. Se forem diferentes, voltam a ficar ocultas
5. Objetivo: encontrar todos os 8 pares

Estatísticas ao final:
- Pontuação total
- Número de pares encontrados
- Tentativas realizadas
- Eficiência (acertos/tentativa)

## Controles

### Jogo da Adivinhação
- **Números** - Digite seu palpite
- **Enter** - Confirmar palpite
- **ESC** - Voltar ao menu

### Jogo da Memória
- **Clique do Mouse** - Selecionar casa para revelar
- **ESC** - Voltar ao menu

### Menu
- **Clique do Mouse** - Selecionar opção

## Resolução da Janela

A janela é definida como **1200x800 pixels** (configurável em `frontend.h`).

## Estrutura do Código

O frontend mantém um estado centralizado (`EstadoUI`) que controla:
- Estado atual da aplicação (menu, jogo, resultado, etc.)
- Dados da partida (Jogo da Adivinhação)
- Dados do jogo da memória
- Entrada do usuário

O fluxo é simples:
1. **Atualizar** - Processar entrada do usuário
2. **Desenhar** - Renderizar a tela baseado no estado atual
3. **Loop** - Repetir até sair

## Troubleshooting

### Erro: "raylib.h: Arquivo ou diretório não encontrado"
- Instale a biblioteca raylib conforme o seu sistema operacional
- Verifique se os headers estão nos diretórios padrão do compilador

### Programa não compila
- Certifique-se que tem gcc/clang instalado
- Verifique a instalação do raylib

### Janela não abre
- Verifique se está usando `make run-raylib`
- Alguns ambientes WSL/SSH podem não suportar aplicações gráficas

## Desenvolvimento Futuro

Melhorias sugeridas:
- Adicionar sons e música com raylib
- Animações ao acertar/errar
- Diferentes temas de cores
- Salvar/carregar progresso
- Leaderboard visual
- Ícones e imagens customizadas
- Efeitos de partículas

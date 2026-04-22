# ==============================================================================
# 🛠️ MAKEFILE - PROJETO: JOGO DA ADIVINHAÇÃO
# Status: ⚠️ EM ANDAMENTO (Estrutura de build sendo preparada)
# ==============================================================================

# 1. Configurações do Compilador:
CC = gcc
# Flags de segurança e performance baseadas no padrão C11
CFLAGS = -std=c11 -Wall -Wextra -O2

# 2. Caminhos de Inclusão
# Indica ao compilador onde encontrar os arquivos de cabeçalho (.h)
# Isso permite usar #include "jogo.h" sem caminhos relativos complexos
INCLUDES = -I./src/game \
           -I./src/utils \
           -I./src/history \
           -I./src/static \
           -I./src/include

# 3. Lista de Arquivos Fontes (Em andamento)
# Conforme você criar os arquivos físicos nas pastas, o Make os encontrará aqui.
# DICA: Se um arquivo listado aqui não existir na pasta, o 'make' dará erro.
SRCS = src/main.c \
       src/game/jogo.c \
       src/utils/util.c \
       src/history/historico.c \
       src/static/estatisticas.c

# 4. Configurações de Saída
TARGET = jogo

# ------------------------------------------------------------------------------
# REGRAS DE AUTOMAÇÃO
# ------------------------------------------------------------------------------

# Regra padrão: Compila o executável principal
all: $(TARGET)

$(TARGET):
	@echo "🔨 Compilando o projeto com padrão C11..."
	# O comando abaixo une o compilador, as flags e os fontes para gerar o jogo
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(TARGET)
	@echo "✅ Compilação concluída com sucesso!"

# Regra de Limpeza: Remove o executável para uma compilação do zero
clean:
	@echo "🧹 Limpando arquivos binários..."
	rm -f $(TARGET)

# Regra de Execução: Compila e já inicia o jogo no terminal
run: all
	@echo "🕹️ Iniciando o jogo..."
	./$(TARGET)

# -----------------------------------------------------------------------------
# OBSERVAÇÃO: Este Makefile está sendo estruturado para a arquitetura modular do projeto.
# Para funcionar, os arquivos .c e .h listados em 'SRC' existem nas pastas.
# -----------------------------------------------------------------------------
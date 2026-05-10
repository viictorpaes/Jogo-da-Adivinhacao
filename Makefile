CC = gcc

DEBUG ?= 0
ifeq ($(DEBUG),1)
	CFLAGS = -std=c11 -Wall -Wextra -g -O0
else
	CFLAGS = -std=c11 -Wall -Wextra -O2
endif

INCLUDES = -I./src/game \
		 -I./src/utils \
		 -I./src/history \
		 -I./src/static \
		 -I./src/include \
		 -I./src/ui

SRCS = src/main.c \
	 src/game/jogo.c \
	 src/game/memorygame.c \
	 src/game/jogar_memoria.c \
	 src/utils/utils.c \
	 src/history/historico.c \
	 src/static/estatisticas.c \
	 src/ui/menu.c

SRCS_RAYLIB = src/main_raylib.c \
	 src/game/jogo.c \
	 src/game/memorygame.c \
	 src/game/jogar_memoria.c \
	 src/utils/utils.c \
	 src/history/historico.c \
	 src/static/estatisticas.c \
	 src/ui/frontend.c

TARGET = jogo
TARGET_RAYLIB = jogo_raylib

# Flags para raylib
RAYLIB_PREFIX := $(shell brew --prefix raylib 2>/dev/null)
ifneq ($(RAYLIB_PREFIX),)
	RAYLIB_FLAGS = -I$(RAYLIB_PREFIX)/include -L$(RAYLIB_PREFIX)/lib -lraylib -lm -lpthread
else
	RAYLIB_FLAGS = -lraylib -lm -lpthread
endif
ifeq ($(OS),Windows_NT)
	RAYLIB_FLAGS = -lraylib -lm -lwinmm -lgdi32 -lpthread
endif

.PHONY: all clean run build-raylib raylib run-raylib test format help

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(TARGET)

build-raylib: $(TARGET_RAYLIB)

$(TARGET_RAYLIB): $(SRCS_RAYLIB)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS_RAYLIB) $(INCLUDES) $(RAYLIB_FLAGS) -o $(TARGET_RAYLIB)

clean:
	rm -f $(TARGET) $(TARGET_RAYLIB) bin/* *.o

run: all
	@mkdir -p data
	./$(TARGET)

raylib: build-raylib
	@mkdir -p data
	./$(TARGET_RAYLIB)

run-raylib: raylib

test:
	@if [ -n "$(wildcard tests/*.c)" ]; then \
		gcc $(CFLAGS) $(INCLUDES) tests/*.c -o tests/run_tests && ./tests/run_tests; \
	else \
		echo "Nenhum teste encontrado"; \
	fi

format:
	@command -v clang-format >/dev/null 2>&1 || exit 0
	clang-format -i $(SRCS) $(SRCS_RAYLIB) src/include/*.h src/utils/*.h src/ui/*.c

help:
	@echo "=== EXECUÇÃO ==="
	@echo "make run             -> compilar e executar versão terminal (console)"
	@echo "make raylib          -> compilar e executar versão visual (RayLib)"
	@echo ""
	@echo "=== COMPILAÇÃO ==="
	@echo "make or make all     -> compilar versão terminal"
	@echo "make build-raylib    -> compilar versão visual sem executar"
	@echo "make DEBUG=1         -> compilar com debug"
	@echo ""
	@echo "=== UTILITÁRIOS ==="
	@echo "make test            -> rodar testes"
	@echo "make format          -> formatar código"
	@echo "make clean           -> limpar arquivos compilados"
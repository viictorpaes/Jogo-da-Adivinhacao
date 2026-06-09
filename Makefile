CC = gcc

DEBUG ?= 0
ifeq ($(DEBUG),1)
	CFLAGS = -std=c11 -Wall -Wextra -g -O0
else
	CFLAGS = -std=c11 -Wall -Wextra -O2
endif

INCLUDES = -I./src \
		 -I./src/game \
		 -I./src/utils \
		 -I./src/history \
		 -I./src/static \
		 -I./src/include \
		 -I./src/ui \
		 -I./src/music

SRCS = src/main/main.c \
	 src/game/jogo.c \
	 src/game/memorygame.c \
	 src/game/jogar_memoria.c \
	 src/game/jogos_extras.c \
	 src/game/logica.c \
	 src/game/precedencia.c \
	 src/utils/utils.c \
	 src/history/historico.c \
	 src/static/estatisticas.c \
	 src/ui/menu.c

SRCS_RAYLIB = src/main/main_raylib.c \
	 src/game/jogo.c \
	 src/game/memorygame.c \
	 src/game/jogar_memoria.c \
	 src/game/logica.c \
	 src/game/precedencia.c \
	 src/utils/utils.c \
	 src/history/historico.c \
	 src/static/estatisticas.c \
	 src/ui/frontend.c \
	 src/music/musica.c

ifeq ($(OS),Windows_NT)
	EXT = .exe
	MKDIR_DATA = if not exist data mkdir data
	RM_CMD = del /f /q
	RUN_PREFIX =
	# Windows: instale via MSYS2 com: pacman -S mingw-w64-x86_64-raylib
	# Ou defina RAYLIB_DIR para o caminho onde o raylib foi extraído manualmente:
	#   make RAYLIB_DIR=C:/raylib build-raylib
	RAYLIB_DIR ?=

	ifneq ($(RAYLIB_DIR),)
		RAYLIB_FLAGS = -I$(RAYLIB_DIR)/include -L$(RAYLIB_DIR)/lib \
			-lraylib -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32 -lpthread
	else
		RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32 -lpthread
	endif

else
	EXT =
	MKDIR_DATA = mkdir -p data
	RM_CMD = rm -f
	RUN_PREFIX = ./
	RAYLIB_PREFIX := $(shell brew --prefix raylib 2>/dev/null)

	ifneq ($(RAYLIB_PREFIX),)
		RAYLIB_FLAGS = -I$(RAYLIB_PREFIX)/include -L$(RAYLIB_PREFIX)/lib -lraylib -lm -lpthread

	else
		RAYLIB_FLAGS = -lraylib -lm -lpthread
	endif
	
endif

TARGET = jogo$(EXT)
TARGET_RAYLIB = jogo_raylib$(EXT)

.PHONY: all clean run build-raylib raylib run-raylib test format help

all:
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -lm -o $(TARGET)

build-raylib:
	$(CC) $(CFLAGS) $(SRCS_RAYLIB) $(INCLUDES) $(RAYLIB_FLAGS) -o $(TARGET_RAYLIB)

clean:
	-$(RM_CMD) $(TARGET) $(TARGET_RAYLIB)

run: all
	$(MKDIR_DATA)
	$(RUN_PREFIX)$(TARGET)

raylib: build-raylib
	$(MKDIR_DATA)
	$(RUN_PREFIX)$(TARGET_RAYLIB)

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
	@echo "make run                          -> compilar e executar versão terminal (console)"
	@echo "make raylib                       -> compilar e executar versão visual (RayLib)"
	@echo ""
	@echo "=== COMPILAÇÃO ==="
	@echo "make or make all                  -> compilar versão terminal"
	@echo "make build-raylib                 -> compilar versão visual sem executar"
	@echo "make DEBUG=1 ...                  -> compilar com debug"
	@echo "make RAYLIB_DIR=C:/raylib raylib  -> Windows sem MSYS2 (raylib manual)"
	@echo ""
	@echo "=== UTILITÁRIOS ==="
	@echo "make test            -> rodar testes"
	@echo "make format          -> formatar código"
	@echo "make clean           -> limpar arquivos compilados"
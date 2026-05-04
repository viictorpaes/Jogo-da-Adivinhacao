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

TARGET = jogo

.PHONY: all clean run test format help

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(TARGET)

clean:
	rm -f $(TARGET) bin/* *.o

run: all
	@mkdir -p data
	./$(TARGET)

test:
	@if [ -n "$(wildcard tests/*.c)" ]; then \
		gcc $(CFLAGS) $(INCLUDES) tests/*.c -o tests/run_tests && ./tests/run_tests; \
	else \
		echo "Nenhum teste encontrado"; \
	fi

format:
	@command -v clang-format >/dev/null 2>&1 || exit 0
	clang-format -i $(SRCS) src/include/*.h src/utils/*.h src/ui/*.c

help:
	@echo "make -> compilar"
	@echo "make DEBUG=1 -> compilar com debug"
	@echo "make run -> compilar e executar"
	@echo "make test -> rodar testes"
	@echo "make clean -> limpar"
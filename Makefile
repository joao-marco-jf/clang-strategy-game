# Nome do compilador
CXX = gcc

# Flags do compilador
CXXFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = src
INC_DIR = include
OUT_DIR = out
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(filter-out $(SRC_DIR)/main.c, $(SRCS)))

MAIN_OBJ = $(OUT_DIR)/main.o

# Arquivo executável
EXEC = $(BIN_DIR)/app

# Alvo padrão
all: $(EXEC)

# Compila o executável principal
$(EXEC): $(OBJS) $(MAIN_OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) $(MAIN_OBJ) -o $@

# Compila os objetos dos arquivos fonte
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OUT_DIR) $(BIN_DIR) ./saida.txt

.PHONY: all clean
# Nome do compilador
CXX = gcc

# Flags do compilador
CXXFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
OUT_DIR = out
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(filter-out $(SRC_DIR)/main.c, $(SRCS)))

MAIN_OBJ = $(OUT_DIR)/main.o

# Arquivo executável
EXEC = $(BIN_DIR)/main

# Arquivos fonte e objetos dos testes
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/**/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OUT_DIR)/%.o, $(TEST_SRCS))

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

# Compila os objetos dos arquivos de teste
$(OUT_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila e executa os testes
test: $(OBJS) $(TEST_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(TEST_OBJS) $(OBJS) -o $(BIN_DIR)/test -lcunit
	./$(BIN_DIR)/test

# Instala a biblioteca CUnit (supondo um sistema baseado em Debian)
install_cunit:
	sudo apt-get update && sudo apt-get install -y libcunit1 libcunit1-doc libcunit1-dev

# Limpeza
clean:
	rm -rf $(OUT_DIR) $(BIN_DIR)

.PHONY: all clean test install_cunit
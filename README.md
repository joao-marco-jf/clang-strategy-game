### README

# Meu Projeto de Aplicação C

Este projeto é uma aplicação desenvolvida em linguagem C. O código fonte está organizado em diferentes diretórios, e o processo de compilação é gerenciado pelo Makefile fornecido.

## Estrutura de Diretórios

- `src`: Contém os arquivos fonte (`.c`).
- `include`: Contém os arquivos de cabeçalho (`.h`).
- `out`: Diretório onde os arquivos objeto (`.o`) serão gerados.
- `bin`: Diretório onde o executável final será gerado.

## Requisitos

- Compilador GCC

## Compilação e Execução

### Alvo Padrão

Para compilar o projeto, basta rodar o comando:

```sh
make
```

Este comando irá gerar o executável principal `app` no diretório `bin`.

### Limpeza

Para limpar os arquivos gerados (arquivos objeto e o executável), use o comando:

```sh
make clean
```

Este comando remove os diretórios `out`, `bin` e o arquivo `saida.txt`.

## Descrição do Makefile

O Makefile incluído neste projeto automatiza o processo de compilação. Aqui está uma breve descrição das principais partes do Makefile:

- **Nome do compilador**
  ```makefile
  CXX = gcc
  ```

- **Flags do compilador**
  ```makefile
  CXXFLAGS = -Wall -Wextra -Iinclude
  ```

- **Diretórios**
  ```makefile
  SRC_DIR = src
  INC_DIR = include
  OUT_DIR = out
  BIN_DIR = bin
  ```

- **Arquivos fonte e objetos**
  ```makefile
  SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
  OBJS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(filter-out $(SRC_DIR)/main.c, $(SRCS)))
  MAIN_OBJ = $(OUT_DIR)/main.o
  ```

- **Arquivo executável**
  ```makefile
  EXEC = $(BIN_DIR)/app
  ```

- **Alvo padrão**
  ```makefile
  all: $(EXEC)
  ```

- **Compilação do executável principal**
  ```makefile
  $(EXEC): $(OBJS) $(MAIN_OBJ)
  	mkdir -p $(BIN_DIR)
  	$(CXX) $(OBJS) $(MAIN_OBJ) -o $@
  ```

- **Compilação dos objetos dos arquivos fonte**
  ```makefile
  $(OUT_DIR)/%.o: $(SRC_DIR)/%.c
  	mkdir -p $(OUT_DIR)
  	$(CXX) $(CXXFLAGS) -c $< -o $@
  ```

- **Limpeza**
  ```makefile
  clean:
  	rm -rf $(OUT_DIR) $(BIN_DIR) ./saida.txt
  ```

- **Phony Targets**
  ```makefile
  .PHONY: all clean
  ```

## Notas

- Certifique-se de ter o GCC instalado no seu sistema para compilar este projeto.
- O Makefile está configurado para gerar os arquivos objeto no diretório `out` e o executável no diretório `bin`.

## Autores

João Marcos Jensen Francisco e Cauã Rodrigues
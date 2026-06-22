# コンパイラとオプション
CC = gcc
CFLAGS = -Wall

# 出力先のフォルダ名を定義
BIN_DIR = bin
OBJ_DIR = obj

# 実行ファイル名
TARGET = $(BIN_DIR)/program.exe

SRCS = $(wildcard src/*.c)

# オブジェクトファイルのパス
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o,$(notdir $(SRCS)))

$(info src: $(SRCS))
$(info obj: $(OBJS))
.PHONY: all clean
all: $(TARGET)

# 1. リンク処理
$(TARGET): $(OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 2. コンパイル処理
$(OBJS): $(OBJ_DIR)/%.o: src/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
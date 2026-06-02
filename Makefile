# コンパイラとオプション
CC = gcc
CFLAGS = -Wall

# 出力先のフォルダ名を定義
BIN_DIR = bin
OBJ_DIR = obj
$(OBJ_DIR)/ui.o: CFLAGS += -finput-charset=cp932 -fexec-charset=cp932

# 実行ファイル名（binフォルダの中に作る）
TARGET = $(BIN_DIR)/program.exe

SRCS = $(wildcard src/*.c) # ソースファイル（現在のフォルダの .c をすべて取得）

# 【重要】オブジェクトファイル（objフォルダの中に .o を作るようにパスを変換）
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o,$(notdir $(SRCS)))

# 3. 【info】 変数の中に何が入ったか、Make実行時に画面に出力して確認する
$(info src: $(SRCS))
$(info obj: $(OBJS))
.PHONY: all clean
all: $(TARGET)

# 【1. リンク処理】
$(TARGET): $(OBJS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 【2. コンパイル処理】 静的パターンルール
$(OBJS): $(OBJ_DIR)/%.o: src/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ヘッダファイルの依存関係
#$(OBJS): src/%.h

# クリーンアップ（Windowsの rmdir コマンドでフォルダごと削除する）
clean:
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
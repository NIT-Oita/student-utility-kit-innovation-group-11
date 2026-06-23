#include <stdio.h>
#include "storage.h"

// 内部だけで使う関数（static）：タスク保存用のファイルを開く
static FILE *openTaskFile(const char *mode) {
    FILE *file = fopen("data/task.bin", mode);
    if (file != NULL) {
        return file;
    }
    file = fopen("../data/task.bin", mode);
    if (file != NULL) {
        return file;
    }
    return fopen("task.bin", mode);
}

// タスクとジャンルをファイルに保存する関数
void saveTasks(const Task tasks[], int task_count, char genres[][GENRE_LEN], int genre_count) {
    FILE *file = openTaskFile("wb"); // バイナリ書き込みモード("wb")で開く
    if (file == NULL) {
        perror("ファイルの保存に失敗しました。");
        return;
    }
    
    // 1. ジャンルの数を保存
    fwrite(&genre_count, sizeof(int), 1, file);
    
    // 2. ジャンルの配列を保存
    if (genre_count > 0) {
        fwrite(genres, sizeof(char) * GENRE_LEN, genre_count, file);
    }
    
    // 3. タスクの数を保存
    fwrite(&task_count, sizeof(int), 1, file);
    
    // 4. タスクの配列を保存
    if (task_count > 0) {
        fwrite(tasks, sizeof(Task), task_count, file);
    }
    
    fclose(file); // ファイルを閉じる
}

// ファイルからタスクとジャンルを読み込む関数
int loadTasks(Task tasks[], char genres[][GENRE_LEN], int *genre_count) {
    FILE *file = openTaskFile("rb"); // バイナリ読み込みモード("rb")で開く
    if (file == NULL) {
        // ファイルが無い場合は0件として返す
        *genre_count = 0;
        return 0;
    }
    
    int g_count = 0;
    // 1. ジャンルの数を読み込む
    if (fread(&g_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    
    // 異常な値がないかチェック（上限オーバーなど）
    if (g_count < 0 || g_count > MAX_GENRES) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    *genre_count = g_count;
    
    // 2. ジャンルの配列を読み込む
    if (g_count > 0) {
        int read_genres = fread(genres, sizeof(char) * GENRE_LEN, g_count, file);
        if (read_genres != g_count) {
            fclose(file);
            *genre_count = 0;
            return 0;
        }
    }
    
    int t_count = 0;
    // 3. タスクの数を読み込む
    if (fread(&t_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    // 異常な値がないかチェック
    if (t_count < 0 || t_count > MAX_TASKS) {
        fclose(file);
        return 0;
    }
    
    // 4. タスクの配列を読み込む
    if (t_count > 0) {
        int read_tasks = fread(tasks, sizeof(Task), t_count, file);
        if (read_tasks != t_count) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file); // 読み込み終わったら閉じる
    return t_count; // 読み込んだタスクの数を返す
}

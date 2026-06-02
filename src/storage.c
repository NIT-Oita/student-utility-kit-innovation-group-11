#include <stdio.h>
#include "storage.h"

// 保存用ファイルを最適な相対パスで開くヘルパー関数
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

// タスク・ジャンル保存関数
void saveTasks(const Task tasks[], int task_count, char genres[][GENRE_LEN], int genre_count) {
    FILE *file = openTaskFile("wb");
    if (file == NULL) {
        perror("ファイルが保存できませんでした。");
        return;
    }
    
    // 1. ジャンル数を書き込む
    fwrite(&genre_count, sizeof(int), 1, file);
    
    // 2. ジャンル配列を書き込む
    if (genre_count > 0) {
        fwrite(genres, sizeof(char) * GENRE_LEN, genre_count, file);
    }
    
    // 3. タスクの個数を書き込む
    fwrite(&task_count, sizeof(int), 1, file);
    
    // 4. タスク配列を書き込む
    if (task_count > 0) {
        fwrite(tasks, sizeof(Task), task_count, file);
    }
    
    fclose(file);
}

// タスク・ジャンル読込関数
int loadTasks(Task tasks[], char genres[][GENRE_LEN], int *genre_count) {
    FILE *file = openTaskFile("rb");
    if (file == NULL) {
        // ファイルが存在しない場合は0を返す (初期状態)
        *genre_count = 0;
        return 0;
    }
    
    int g_count = 0;
    // 1. ジャンル数を読み込む
    if (fread(&g_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    
    // 範囲チェック
    if (g_count < 0 || g_count > MAX_GENRES) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    
    *genre_count = g_count;
    
    // 2. ジャンル配列を読み込む
    if (g_count > 0) {
        int read_genres = fread(genres, sizeof(char) * GENRE_LEN, g_count, file);
        if (read_genres != g_count) {
            fclose(file);
            *genre_count = 0;
            return 0;
        }
    }
    
    int t_count = 0;
    // 3. タスクの個数を読み込む
    if (fread(&t_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    // 範囲チェック
    if (t_count < 0 || t_count > MAX_TASKS) {
        fclose(file);
        return 0;
    }
    
    // 4. タスク配列を読み込む
    if (t_count > 0) {
        int read_tasks = fread(tasks, sizeof(Task), t_count, file);
        if (read_tasks != t_count) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return t_count;
}

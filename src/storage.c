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

// タスク保存関数
void saveTasks(const Task tasks[], int count) {
    FILE *file = openTaskFile("wb");
    if (file == NULL) {
        perror("ファイルが保存できませんでした。");
        return;
    }
    
    // タスクの個数を書き込む
    fwrite(&count, sizeof(int), 1, file);
    
    // タスク配列を書き込む
    if (count > 0) {
        fwrite(tasks, sizeof(Task), count, file);
    }
    
    fclose(file);
}

// タスク読込関数
int loadTasks(Task tasks[]) {
    FILE *file = openTaskFile("rb");
    if (file == NULL) {
        // ファイルが存在しない場合は0を返す (初期状態)
        return 0;
    }
    
    int count = 0;
    // タスクの個数を読み込む
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    // 範囲チェック
    if (count < 0 || count > MAX_TASKS) {
        fclose(file);
        return 0;
    }
    
    // タスク配列を読み込む
    if (count > 0) {
        int read_count = fread(tasks, sizeof(Task), count, file);
        if (read_count != count) {
            // 読み込みエラーまたは不完全なデータの場合
            fclose(file);
            return read_count;
        }
    }
    
    fclose(file);
    return count;
}

#include <stdio.h>
#include <string.h>
#include "logic.h"

// タスク追加
void addTask(Task tasks[], int count, char title[], char deadline[]) {
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    strncpy(tasks[count].deadline, deadline, DEADLINE_LEN - 1);
    tasks[count].deadline[DEADLINE_LEN - 1] = '\0';
    
    tasks[count].completed = 0; // 未完了で初期化
}

// タスク完了
void completeTask(Task tasks[], int index) {
    tasks[index].completed = 1;
}

// タスク削除
void deleteTask(Task tasks[], int count, int index) {
    for (int i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
}

// タスク一覧表示
void showTasks(Task tasks[], int count) {
    if (count == 0) {
        printf("\n  現在、登録されているタスクはありません。\n");
        return;
    }
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i, tasks[i].title);
        printf("      期限: %s  /  状態: %s\n", tasks[i].deadline, tasks[i].completed ? "完了" : "未完了");
        if (i < count - 1) {
            printf("  ------------------------------------------------\n");
        }
    }
    printf("--------------------------------------------------\n");
}

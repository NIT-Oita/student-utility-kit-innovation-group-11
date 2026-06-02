#include <stdio.h>
#include <string.h>
#include "logic.h"

// タスク追加
void addTask(Task tasks[], int count, char title[], char deadline[], char genre[]) {
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    strncpy(tasks[count].deadline, deadline, DEADLINE_LEN - 1);
    tasks[count].deadline[DEADLINE_LEN - 1] = '\0';
    
    strncpy(tasks[count].genre, genre, GENRE_LEN - 1);
    tasks[count].genre[GENRE_LEN - 1] = '\0';
    
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

// タスク一覧表示（ジャンル別）
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count) {
    if (count == 0) {
        printf("\n  現在、登録されているタスクはありません。\n");
        // ジャンルが登録されている場合はジャンル一覧だけでも見せると親切
        if (genre_count > 0) {
            printf("\n--- 登録されているジャンル一覧 ---\n");
            for (int i = 0; i < genre_count; i++) {
                printf("  ・ %s\n", genres[i]);
            }
        }
        return;
    }
    
    // 各定義済みジャンルを表示
    for (int g = 0; g < genre_count; g++) {
        printf("\n================ [ %s ] ================\n", genres[g]);
        int has_tasks = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                printf("  [%d] %s\n", i, tasks[i].title);
                printf("      期限: %s  /  状態: %s\n", tasks[i].deadline, tasks[i].completed ? "完了" : "未完了");
                has_tasks = 1;
            }
        }
        if (!has_tasks) {
            printf("  (このジャンルのタスクはありません)\n");
        }
    }
    
    // 未分類ジャンルを表示
    int has_unclassified = 0;
    for (int i = 0; i < count; i++) {
        int belongs_to_genre = 0;
        for (int g = 0; g < genre_count; g++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                belongs_to_genre = 1;
                break;
            }
        }
        if (!belongs_to_genre) {
            if (!has_unclassified) {
                printf("\n================ [ 未分類 ] ================\n");
                has_unclassified = 1;
            }
            printf("  [%d] %s\n", i, tasks[i].title);
            printf("      期限: %s  /  状態: %s\n", tasks[i].deadline, tasks[i].completed ? "完了" : "未完了");
        }
    }
    printf("\n--------------------------------------------------\n");
}

#include <stdio.h>
#include <string.h>
#include "logic.h"

// タスク追加
void addTask(Task tasks[], int count, char title[], int year, int month, int day, char genre[]) {
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    tasks[count].year = year;
    tasks[count].month = month;
    tasks[count].day = day;

    strncpy(tasks[count].genre, genre, GENRE_LEN - 1);
    tasks[count].genre[GENRE_LEN - 1] = '\0';
    
    tasks[count].completed = 0; // 0で未完了
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
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count) {
    if (count == 0) {
        printf("\n  現在、登録されているタスクはありません。\n");
        if (genre_count > 0) {
            printf("\n--- 登録されているジャンル一覧 ---\n");
            for (int i = 0; i < genre_count; i++) {
                printf("  ・ %s\n", genres[i]);
            }
        }
        return;
    }
    printf("\n--------------------------------------------------\n");
    
    // ジャンルごとの表示
    for (int g = 0; g < genre_count; g++) {
        printf("\n================ [ %s ] ================\n", genres[g]);
        int has_tasks = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                printf("  [%d] %s\n", i, tasks[i].title);
                printf("      期限: %04d/%02d/%02d  /  状態: %s\n", tasks[i].year, tasks[i].month, tasks[i].day, tasks[i].completed ? "完了" : "未完了");
                has_tasks = 1;
            }
        }
        if (!has_tasks) {
            printf("  (このジャンルのタスクはありません)\n");
        }
    }
    
    // 未分類の表示
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
            printf("      期限: %04d/%02d/%02d  /  状態: %s\n", tasks[i].year, tasks[i].month, tasks[i].day, tasks[i].completed ? "完了" : "未完了");
        }
    }
    printf("\n--------------------------------------------------\n");
}

// タスクを日付順で並べ替える
void sortTask(Task tasks[],int count){
    for(int i =0;i < count -1;i++){
        for(int j = 0;j < count - i -1;j++){
            int swap_needed = 0;
            // 年を比較
            if(tasks[j].year < tasks[j + 1].year){
                swap_needed = 1;
            }else if(tasks[j].year == tasks[j + 1].year){
                // 月を比較
                if(tasks[j].month < tasks[j + 1].month){
                    swap_needed = 1;
                }else if(tasks[j].month == tasks[j + 1].month){
                    // 日を比較
                    if(tasks[j].day < tasks[j + 1].day){
                        swap_needed = 1;
                    }
                }
            }

            if(swap_needed == 1){
                Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
}

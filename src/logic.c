#include <stdio.h>
#include <string.h>
#include "logic.h"

// ユーザーが入力したバラバラのデータを受け取り、Task構造体にまとめて配列に保存する関数
void addTask(Task tasks[], int count, char title[], int year, int month, int day, char genre[]) {
    // 文字列がはみ出さないように安全にコピーし、必ず末尾に終端文字('\0')を入れる
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    // 年、月、日を保存
    tasks[count].year = year;
    tasks[count].month = month;
    tasks[count].day = day;

    // ジャンル名を安全にコピー
    strncpy(tasks[count].genre, genre, GENRE_LEN - 1);
    tasks[count].genre[GENRE_LEN - 1] = '\0';
    
    // 最初は未完了(0)とする
    tasks[count].completed = 0; 
}

// 指定したインデックスのタスクを「完了(1)」にする関数
void completeTask(Task tasks[], int index) {
    tasks[index].completed = 1;
}

// 指定したタスクを削除し、それより後ろのタスクを前へ詰める関数
void deleteTask(Task tasks[], int count, int index) {
    for (int i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1]; // 後ろのタスクを1つ前へコピー
    }
}

// タスクの一覧をジャンルごとにグループ分けして見やすく表示する関数
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count) {
    // タスクが1つもない場合の処理
    if (count == 0) {
        printf("\n  現在、登録されているタスクはありません。\n");
        // ジャンルだけが登録されている場合
        if (genre_count > 0) {
            printf("\n--- 登録されているジャンル一覧 ---\n");
            for (int i = 0; i < genre_count; i++) {
                printf("  ・ %s\n", genres[i]);
            }
        }
        return;
    }
    printf("\n--------------------------------------------------\n");
    
    // 1. ジャンルごとにタスクを探して表示する
    for (int g = 0; g < genre_count; g++) {
        printf("\n================ [ %s ] ================\n", genres[g]);
        int has_tasks = 0;
        for (int i = 0; i < count; i++) {
            // タスクのジャンルが現在見ているジャンルと一致するかチェック
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
    
    // 2. どのジャンルにも属していない（未分類）のタスクを表示する
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
                printf("\n================ [ 未分類 ] ================\\n");
                has_unclassified = 1;
            }
            printf("  [%d] %s\n", i, tasks[i].title);
            printf("      期限: %04d/%02d/%02d  /  状態: %s\n", tasks[i].year, tasks[i].month, tasks[i].day, tasks[i].completed ? "完了" : "未完了");
        }
    }
    printf("\n--------------------------------------------------\n");
}

// バブルソートを用いてタスクを期限が近い順に並べ替える関数
void sortTask(Task tasks[],int count){
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - i - 1; j++){
            int swap_needed = 0; // 入れ替えが必要かどうかのフラグ
            
            // 年を比較
            if(tasks[j].year < tasks[j + 1].year){
                swap_needed = 1;
            } else if(tasks[j].year == tasks[j + 1].year){
                // 月を比較
                if(tasks[j].month < tasks[j + 1].month){
                    swap_needed = 1;
                } else if(tasks[j].month == tasks[j + 1].month){
                    // 日を比較
                    if(tasks[j].day < tasks[j + 1].day){
                        swap_needed = 1;
                    }
                }
            }

            // 日付が逆転している場合は隣り合うタスクを交換
            if(swap_needed == 1){
                Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
}

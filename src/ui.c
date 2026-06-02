#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "logic.h"
#include "storage.h"
#include <time.h>

// 静的変数でタスク一覧を保持
static Task tasks[MAX_TASKS];
static int task_count = 0;
static int is_loaded = 0; // 読込フラグ

void mozi(){
    fflush(stdin);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void get_today(int *y, int *m, int *d) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    *y = t->tm_year + 1900;
    *m = t->tm_mon + 1;
    *d = t->tm_mday;
}

int is_past(int y, int m, int d, int ty, int tm, int td) {
    if (y < ty) return 1;
    if (y == ty && m < tm) return 1;
    if (y == ty && m == tm && d < td) return 1;
    return 0;
}

void start_screen(void) {
    printf("==================================================\n");
    printf("==                                              ==\n");
    printf("==            学生生活支援キット                ==\n");
    printf("==            - 課題管理 (TODO) -               ==\n");
    printf("==                                              ==\n");
    printf("==================================================\n");
    printf("\n");
    printf("  [Enter] キーを押すとメインメニューに進みます...\n");
    fflush(stdout);
    mozi();

}

void main_screen(void) {
    // 起動時に1度だけデータを読み込む
    if (!is_loaded) {
        task_count = loadTasks(tasks);
        is_loaded = 1;
    }

    int choice;
    while (1) {
        printf("\n==================================================\n");
        printf("==                  メインメニュー              ==\n");
        printf("==================================================\n");
        printf("  1. タスク一覧の表示\n");
        printf("  2. 新しいタスクの追加\n");
        printf("  3. タスクを完了にする\n");
        printf("  4. タスクの削除\n");
        printf("  5. 終了\n");
        printf("==================================================\n");
        printf("番号を入力してください (1-5): ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            // 文字などが入力された場合の無限ループを防ぐため、バッファをクリアする
            while (getchar() != '\n');
            printf("無効な入力です。1から5の数値を入力してください。\n");
            continue;
        }
        // scanfで残った改行文字を消費する
        while (getchar() != '\n');

        if (choice == 1) {
            printf("\n--- タスク一覧 ---\n");
            showTasks(tasks, task_count);
        } else if (choice == 2) {
            // タスク追加画面の呼び出し
            input_data();
        } else if (choice == 3) {
            printf("\n--- タスクを完了にする ---\n");
            if (task_count == 0) {
                printf("登録されているタスクがありません。\n");
            } else {
                showTasks(tasks, task_count);
                printf("完了にするタスクの番号を入力してください: ");
                int idx;
                fflush(stdout);
                if (scanf("%d", &idx) == 1) {
                    if (idx >= 0 && idx < task_count) {
                        completeTask(tasks, idx);
                        saveTasks(tasks, task_count);
                        printf("タスク「%s」を完了にしました。\n", tasks[idx].title);
                    } else {
                        printf("無効なタスク番号です。\n");
                    }
                }
                while (getchar() != '\n');
            }
        } else if (choice == 4) {
            printf("\n--- タスクの削除 ---\n");
            if (task_count == 0) {
                printf("登録されているタスクがありません。\n");
            } else {
                showTasks(tasks, task_count);
                printf("削除するタスクの番号を入力してください: ");
                int idx;
                fflush(stdout);
                if (scanf("%d", &idx) == 1) {
                    if (idx >= 0 && idx < task_count) {
                        char deleted_title[TITLE_LEN];
                        strncpy(deleted_title, tasks[idx].title, TITLE_LEN - 1);
                        deleted_title[TITLE_LEN - 1] = '\0';
                        
                        deleteTask(tasks, task_count, idx);
                        task_count--;
                        saveTasks(tasks, task_count);
                        printf("タスク「%s」を削除しました。\n", deleted_title);
                    } else {
                        printf("無効なタスク番号です。\n");
                    }
                }
                while (getchar() != '\n');
            }
        } else if (choice == 5) {
            printf("プログラムを終了します。ご利用ありがとうございました。\n");
            break;
        } else {
            printf("無効な選択です。1から5の数値を入力してください。\n");
        }
    }
}

void input_data(void) {
    char title[100];
    int year,month,day;
    int ty, tm, td;
    get_today(&ty, &tm, &td);

    if (task_count >= MAX_TASKS) {
        printf("これ以上タスクを追加できません（上限%d件）。\n", MAX_TASKS);
    }else if(task_count < MAX_TASKS){
        while(1){
        printf("\n==================================================\n");
        printf("==                タスクの追加                  ==\n");
        printf("==================================================\n");
        printf("追加するタスクのタイトルを入力してください:\n");
        printf("> ");
        fflush(stdout);

        // タイトル入力（安全に1行読み込む）
        if (fgets(title, sizeof(title), stdin) != NULL) {
            title[strcspn(title, "\n")] = '\0';
        
            if (title[0] == '\0') {
                printf("タイトルが空です。タスクの追加をキャンセルしました。\n");
            } else {
                printf("期限を入力してください（西暦）:\n");
                printf("> ");
                scanf_s("%d",&year);
                fflush(stdout);
                printf("\n期限を入力してください（月）:\n");
                printf("> ");
                scanf_s("%d",&month);
                fflush(stdout);
                printf("\n期限を入力してください（日）:\n");
                printf("> ");
                scanf_s("%d",&day);
                fflush(stdout);
                if (is_past(year, month, day, ty, tm, td)) {
                    printf("エラー: 過去の日付は指定できません\n");
                    mozi();
                    
                } else {
                    addTask(tasks, task_count, title, year,month,day);
                    task_count++;
                    saveTasks(tasks, task_count);
                    printf("\nタスク「%s」（期限: %d/%d/%d）を追加しました。\n", title, year,month,day);
                    break;
                }   
            }
        }
        }
    }
    
   
    // Enter待ち
    printf("Enterキーでメインメニューに戻る\n");
    mozi();
}

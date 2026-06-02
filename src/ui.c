#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "logic.h"
#include "storage.h"

// 静的変数でタスク一覧とジャンル一覧を保持
static Task tasks[MAX_TASKS];
static int task_count = 0;
static char genres[MAX_GENRES][GENRE_LEN];
static int genre_count = 0;
static int is_loaded = 0; // 読込フラグ

// 内部ヘルパー関数宣言
static void input_genre(void);

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

    // Enterキーの入力を待つ（入力バッファのクリアも兼ねる）
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main_screen(void) {
    // 起動時に1度だけデータを読み込む
    if (!is_loaded) {
        task_count = loadTasks(tasks, genres, &genre_count);
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
        printf("  5. 新しいジャンルの追加\n");
        printf("  6. 終了\n");
        printf("==================================================\n");
        printf("番号を入力してください (1-6): ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            // 文字などが入力された場合の無限ループを防ぐため、バッファをクリアする
            while (getchar() != '\n');
            printf("無効な入力です。1から6の数値を入力してください。\n");
            continue;
        }
        // scanfで残った改行文字を消費する
        while (getchar() != '\n');

        if (choice == 1) {
            printf("\n--- タスク一覧 ---\n");
            showTasks(tasks, task_count, genres, genre_count);
        } else if (choice == 2) {
            // タスク追加画面の呼び出し
            input_data();
        } else if (choice == 3) {
            printf("\n--- タスクを完了にする ---\n");
            if (task_count == 0) {
                printf("登録されているタスクがありません。\n");
            } else {
                showTasks(tasks, task_count, genres, genre_count);
                printf("完了にするタスクの番号を入力してください: ");
                int idx;
                fflush(stdout);
                if (scanf("%d", &idx) == 1) {
                    if (idx >= 0 && idx < task_count) {
                        completeTask(tasks, idx);
                        saveTasks(tasks, task_count, genres, genre_count);
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
                showTasks(tasks, task_count, genres, genre_count);
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
                        saveTasks(tasks, task_count, genres, genre_count);
                        printf("タスク「%s」を削除しました。\n", deleted_title);
                    } else {
                        printf("無効なタスク番号です。\n");
                    }
                }
                while (getchar() != '\n');
            }
        } else if (choice == 5) {
            // ジャンルの追加画面の呼び出し
            input_genre();
        } else if (choice == 6) {
            printf("プログラムを終了します。ご利用ありがとうございました。\n");
            break;
        } else {
            printf("無効な選択です。1から6の数値を入力してください。\n");
        }
    }
}

void input_data(void) {
    char title[100];
    char deadline[100];
    char genre[GENRE_LEN] = "未分類";

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
            printf("期限を入力してください (例: 2026-06-15, 明日まで):\n");
            printf("> ");
            fflush(stdout);
            
            // 期限入力
            if (fgets(deadline, sizeof(deadline), stdin) != NULL) {
                deadline[strcspn(deadline, "\n")] = '\0';
                
                if (deadline[0] == '\0') {
                    // 期限が空の場合は「なし」に設定する
                    strcpy(deadline, "なし");
                }
                
                // ジャンル選択 (ジャンルが登録されている場合のみ)
                if (genre_count > 0) {
                    printf("\n以下のジャンルから選択してください:\n");
                    for (int i = 0; i < genre_count; i++) {
                        printf("  %d: %s\n", i, genres[i]);
                    }
                    printf("  %d: 未分類 (または指定なし)\n", genre_count);
                    printf("番号を入力してください (デフォルト: 未分類):\n> ");
                    fflush(stdout);
                    
                    char choice_str[30];
                    if (fgets(choice_str, sizeof(choice_str), stdin) != NULL) {
                        int g_idx = -1;
                        if (sscanf(choice_str, "%d", &g_idx) == 1) {
                            if (g_idx >= 0 && g_idx < genre_count) {
                                strncpy(genre, genres[g_idx], GENRE_LEN - 1);
                                genre[GENRE_LEN - 1] = '\0';
                            }
                        }
                    }
                }
                
                if (task_count >= MAX_TASKS) {
                    printf("これ以上タスクを追加できません（上限%d件）。\n", MAX_TASKS);
                } else {
                    addTask(tasks, task_count, title, deadline, genre);
                    task_count++;
                    saveTasks(tasks, task_count, genres, genre_count);
                    printf("\nタスク「%s」（期限: %s, ジャンル: %s）を追加しました。\n", title, deadline, genre);
                }
            }
        }
    }
    
    printf("\n[Enter] キーを押すとメインメニューに戻ります...\n");
    fflush(stdout);
    
    // Enter待ち
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void input_genre(void) {
    char genre_name[100];
    printf("\n==================================================\n");
    printf("==              ジャンルの追加                  ==\n");
    printf("==================================================\n");
    printf("追加するジャンルの名前を入力してください:\n");
    printf("> ");
    fflush(stdout);

    if (fgets(genre_name, sizeof(genre_name), stdin) != NULL) {
        genre_name[strcspn(genre_name, "\n")] = '\0';
        
        if (genre_name[0] == '\0') {
            printf("ジャンル名が空です。追加をキャンセルしました。\n");
        } else if (genre_count >= MAX_GENRES) {
            printf("これ以上ジャンルを追加できません（上限%d件）。\n", MAX_GENRES);
        } else {
            // 重複チェック
            int exists = 0;
            for (int i = 0; i < genre_count; i++) {
                if (strcmp(genres[i], genre_name) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (exists) {
                printf("ジャンル「%s」は既に存在します。\n", genre_name);
            } else {
                strncpy(genres[genre_count], genre_name, GENRE_LEN - 1);
                genres[genre_count][GENRE_LEN - 1] = '\0';
                genre_count++;
                saveTasks(tasks, task_count, genres, genre_count);
                printf("\nジャンル「%s」を追加しました。\n", genre_name);
            }
        }
    }
    
    printf("\n[Enter] キーを押すとメインメニューに戻ります...\n");
    fflush(stdout);
    
    // Enter待ち
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

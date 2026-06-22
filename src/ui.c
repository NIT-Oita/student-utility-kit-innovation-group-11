#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "logic.h"
#include "storage.h"
#include <time.h>

// Enterキーの入力を待つ（バッファのゴミも捨てる）関数
void mozi(){
    fflush(stdin);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// 今日の日付を取得して変数に格納する関数
void get_today(int *y, int *m, int *d) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    *y = t->tm_year + 1900;
    *m = t->tm_mon + 1;
    *d = t->tm_mday;
}

// 入力された日付が今日より過去かどうかを判定する関数
int is_past(int y, int m, int d, int ty, int tm, int td) {
    if (y < ty) return 1;
    if (y == ty && m < tm) return 1;
    if (y == ty && m == tm && d < td) return 1;
    return 0; // 過去ではない場合は0を返す
}

// 静的変数でタスク一覧とジャンル一覧をプログラム全体で保持
static Task tasks[MAX_TASKS];
static int task_count = 0;
static char genres[MAX_GENRES][GENRE_LEN];
static int genre_count = 0;
static int is_loaded = 0; // 読み込みフラグ

// 内部使用関数宣言
static void input_genre(void);
void input_data(void);

// スタート画面（タイトル）を表示する関数
void start_screen(void) {
    printf("==================================================\n");
    printf("==                                              ==\n");
    printf("==            学生生活支援ツール                ==\n");
    printf("==            - 課題管理 (TODO) -               ==\n");
    printf("==                                              ==\n");
    printf("==================================================\n\n");
    printf("  [Enter] キーを押すとメインメニューに進みます...\n");
    
    // 出力バッファを強制的に吐き出し、画面にすぐに表示させる
    fflush(stdout);

    // Enterキーの入力を待つ（バッファに残っている改行や文字を読み捨てる処理）
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// メインメニューを表示し、ユーザーの操作を受け付ける関数
void main_screen(void) {
    // 起動時に1度だけデータを読み込む
    if (!is_loaded) {
        task_count = loadTasks(tasks, genres, &genre_count);
        is_loaded = 1;
    }

    int choice;
    // 終了が選ばれるまで無限ループ
    while (1) {
        printf("\n==================================================\n");
        printf("==                  メインメニュー              ==\n");
        printf("==================================================\n");
        printf("  1. タスク一覧を見る\n");
        printf("  2. 新しいタスクの追加\n");
        printf("  3. タスクを完了にする\n");
        printf("  4. タスクの削除\n");
        printf("  5. 新しいジャンルの追加\n");
        printf("  6. 終了\n");
        printf("==================================================\n");
        printf("番号を入力してください (1-6): ");
        fflush(stdout);

        // 数字が正しく入力されなかった場合の処理
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
            sortTask(tasks, task_count); // まず並べ替える
            showTasks(tasks, task_count, genres, genre_count); // そして表示する
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
                        completeTask(tasks, idx); // タスクを完了状態にする
                        saveTasks(tasks, task_count, genres, genre_count); // ファイルに保存する
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
                        char deleted_title[100];
                        strncpy(deleted_title, tasks[idx].title, sizeof(deleted_title) - 1);
                        deleted_title[sizeof(deleted_title) - 1] = '\0';
                        
                        deleteTask(tasks, task_count, idx); // タスクを削除する
                        task_count--; // タスク数を1減らす
                        saveTasks(tasks, task_count, genres, genre_count); // ファイルに保存する
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
            break; // whileループを抜けてプログラムを終了
        } else {
            printf("無効な選択です。1から6の数値を入力してください。\n");
        }
    }
}

// タスクを追加するための画面と入力を処理する関数
void input_data(void) {
    char title[100];
    int year, month, day;
    char genre[GENRE_LEN] = "未分類";
    
    // 今日の日付を取得しておく（過去かどうかの判定に使うため）
    int ty, tm, td;
    get_today(&ty, &tm, &td);

    // 上限件数チェック
    if (task_count >= MAX_TASKS) {
        printf("これ以上タスクを追加できません（上限%d件）。\n", MAX_TASKS);
    } else {
        printf("\n==================================================\n");
        printf("==                タスクの追加                  ==\n");
        printf("==================================================\n");
        printf("追加するタスクのタイトルを入力してください:\n> ");
        fflush(stdout);

        // タイトル入力：キーボード(stdin)から最大でtitleのサイズ分だけ安全に1行読み込む
        if (fgets(title, sizeof(title), stdin) != NULL) {
            // fgetsは改行文字(Enter)も読み込んでしまうため、改行文字を見つけて文字列の終わり('\0')に置き換える
            title[strcspn(title, "\n")] = '\0';
        
            if (title[0] == '\0') {
                printf("タイトルが空です。タスクの追加をキャンセルしました。\n");
            } else {
                printf("年を入力してください（例：2026）:\n> ");
                scanf_s("%d", &year);
                printf("\n月を入力してください（例：6）:\n> ");
                scanf_s("%d", &month);
                printf("\n日を入力してください（例：15）:\n> ");
                scanf_s("%d", &day);
                
                // 【重要】scanf_sで数値を入力した後に「Enterキー（改行）」が内部に残ってしまうため、
                // 次の文字入力がスキップされないように、改行文字が見つかるまで空読みして捨てる
                while (getchar() != '\n');
                
                // 入力された日付が今日より過去かどうかを判定
                if (is_past(year, month, day, ty, tm, td)) {
                    printf("エラー: 過去の日付は入力できません\n");
                    mozi(); // Enterキーが押されるまで待機する
                    return; // タスク追加を途中でやめてメインメニューに戻る
                }
                
                // ジャンル選択 (ジャンルが1つ以上登録されている場合のみ表示)
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
                        // 読み込んだ文字列の中から、整数(%d)を取り出してg_idxに格納する
                        if (sscanf(choice_str, "%d", &g_idx) == 1) {
                            if (g_idx >= 0 && g_idx < genre_count) {
                                // 指定されたジャンル名を安全にコピーする
                                strncpy(genre, genres[g_idx], GENRE_LEN - 1);
                                genre[GENRE_LEN - 1] = '\0';
                            }
                        }
                    }
                }
                
                // logic.c の addTask関数を呼んでタスクを配列に追加する
                addTask(tasks, task_count, title, year, month, day, genre);
                task_count++; // 追加したので件数を増やす
                
                // 並べ替えを実行
                sortTask(tasks, task_count);
                
                // storage.c の関数を呼んでファイルに保存する
                saveTasks(tasks, task_count, genres, genre_count);
                printf("\nタスク「%s」(期限: %04d/%02d/%02d, ジャンル: %s)を追加しました。\n", title, year, month, day, genre);
            }
        }
    }
    
    printf("\n[Enter] キーを押すとメインメニューに戻ります...\n");
    fflush(stdout);
    
    // Enter待ち（バッファのクリアも兼ねる）
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 新しいジャンルを追加するための画面と入力を処理する関数
static void input_genre(void) {
    char genre_name[100];
    printf("\n==================================================\n");
    printf("==              ジャンルの追加                  ==\n");
    printf("==================================================\n");
    printf("追加するジャンルの名前を入力してください:\n> ");
    fflush(stdout);

    if (fgets(genre_name, sizeof(genre_name), stdin) != NULL) {
        genre_name[strcspn(genre_name, "\n")] = '\0';
        
        if (genre_name[0] == '\0') {
            printf("ジャンル名が空です。追加をキャンセルしました。\n");
        } else if (genre_count >= MAX_GENRES) {
            printf("これ以上ジャンルを追加できません（上限%d件）。\n", MAX_GENRES);
        } else {
            // すでに同じ名前のジャンルが存在しないかの重複チェック
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
                // ジャンルを配列にコピーして追加
                strncpy(genres[genre_count], genre_name, GENRE_LEN - 1);
                genres[genre_count][GENRE_LEN - 1] = '\0';
                genre_count++;
                
                // ファイルに保存
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

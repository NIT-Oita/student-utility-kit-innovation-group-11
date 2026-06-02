#include <stdio.h>
#include <string.h>
#include "ui.h"

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
            printf("(タスク一覧を表示します)\n");
            // 他の人が実装するロジック（showTasksなど）を呼び出す場合はここに記述
        } else if (choice == 2) {
            // タスク追加画面の呼び出し
            input_data();
        } else if (choice == 3) {
            printf("\n--- タスクを完了にする ---\n");
            printf("完了にするタスクの番号を入力してください: ");
            int idx;
            fflush(stdout);
            if (scanf("%d", &idx) == 1) {
                printf("(タスク番号 %d を完了にします)\n", idx);
            }
            while (getchar() != '\n');
        } else if (choice == 4) {
            printf("\n--- タスクの削除 ---\n");
            printf("削除するタスクの番号を入力してください: ");
            int idx;
            fflush(stdout);
            if (scanf("%d", &idx) == 1) {
                printf("(タスク番号 %d を削除します)\n", idx);
            }
            while (getchar() != '\n');
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
    printf("\n==================================================\n");
    printf("==                タスクの追加                  ==\n");
    printf("==================================================\n");
    printf("追加するタスクのタイトルを入力してください:\n");
    printf("> ");
    fflush(stdout);

    // 文字列の入力（安全に1行読み込む）
    if (fgets(title, sizeof(title), stdin) != NULL) {
        // 末尾の改行文字を削除
        title[strcspn(title, "\n")] = '\0';
        
        if (title[0] == '\0') {
            printf("タイトルが空です。タスクの追加をキャンセルしました。\n");
        } else {
            printf("\nタスク「%s」を入力しました。\n", title);
            printf("(ロジック処理により保存されます)\n");
            // 他の人が実装するロジック（addTaskなど）を呼び出す場合はここに記述
        }
    }
    
    printf("\n[Enter] キーを押すとメインメニューに戻ります...\n");
    fflush(stdout);
    
    // Enter待ち
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

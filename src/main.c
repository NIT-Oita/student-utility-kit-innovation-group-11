#include <stdio.h>
#include "ui.h"

// メイン関数：プログラムの実行がここから始まります
int main(void) {
    // スタート画面（タイトル画面）を表示する
    start_screen();
    
    // メインメニューを表示し、ユーザーの操作を受け付ける
    main_screen();

    return 0; // プログラムを正常に終了する
}

#include <stdio.h>
#include <string.h>
#include "logic.h"

// タスク追加
void addTask(Task tasks[], int count, char title[],int year,int month,int day) {
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    tasks[count].year = year;
    tasks[count].month = month;
    tasks[count].day = day;
    
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
        printf("      期限: %d/%d/%d  /  状態: %s\n", tasks[i].year,tasks[i].month,tasks[i].day, tasks[i].completed ? "完了" : "未完了");
        if (i < count - 1) {
            printf("  ------------------------------------------------\n");
        }
    }
    printf("--------------------------------------------------\n");
}

//タスクを日付順で並べ替える
void sortTask(Task tasks[],int count){
    for(int i =0;i < count -1;i++){
        for(int j = 0;j < count - i -1;j++){
        int swap_needed = 0;
        /*0=並べ替え不要
          1=並べ替え必要*/  

            //年を比較
            if(tasks[j].year<tasks[j + 1].year){
                swap_needed = 1;
            }else if(tasks[j].year == tasks[j + 1].year){
                //年が同じなら月を比較
                if(tasks[j].month < tasks[j + 1].month){
                    swap_needed = 1;
                    }else if(tasks[j].month == tasks[j + 1].month){
                    //月が同じなら日を比較
                        if(tasks[j].day < tasks[j + 1].day){
                            swap_needed = 1;
                }
            }
        }

        //前のjの方が過去なら後ろのj+1と入れ替える
            if(swap_needed == 1){
            Task temp = tasks[j];//tempは空の箱
            tasks[j] = tasks[j+1];
            tasks[j+1] = temp;
            }
        }
    }
}

#include<stdio.h>
#include<string.h>
#include "logic.h"

/*completed 　完了か未完了か
int index タスクの番号
Task titleとタスクの番号をまとめた構造体*/

//タスク追加
void addTask(Task tasks[],int count,char title[]){
    strcpy(tasks[count].title,title); //asks[count].titleにtitleを保存
    tasks[count].completed = 0; //タスク未完了=0

//完了
void completeTask(Task tasks[],int index){
    tasks[index].completed = 1; //タスク完了=1
}

//タスク削除
void deleteTask(Task tasks[],int count,int index){
    for (int i = index;i < count -1;i++){
        tasks[i] = tasks[i + 1];
    }
}

//表示
void showTasks(Task tasks[],int count){
    for (int i=0;i < count;i++){
        printf("%d : %s",i,tasks[i].title);

        if(taska[i].completed == 1){
            printf("[完了]");
        }else{
            print("[未完了]");

        }

        printf("\n");
    }
}


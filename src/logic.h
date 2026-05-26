#ifndef LOGIC_H
#define LOGIC_H

#define MAX_TASKS 100
#define TITLE_LEN 50

typedef struct{
    char title[TITLE_LEN];
    int completed;
}Task;

//関数宣言
void addTask(Task tasks[], int count, char title[]);
void completeTask(Task tasks[], int index);
void deleteTask(Task tasks[], int count, int index);
void showTasks(Task tasks[], int count);

#endif
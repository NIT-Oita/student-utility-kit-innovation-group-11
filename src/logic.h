#ifndef LOGIC_H
#define LOGIC_H

#define MAX_TASKS 100
#define TITLE_LEN 50
#define DEADLINE_LEN 30

typedef struct{
    char title[TITLE_LEN];
    int year;
    int month;
    int day;
    int completed;
}Task;

//ŠÖ”éŒ¾
void addTask(Task tasks[], int count, char title[], int year,int month,int day);
void completeTask(Task tasks[], int index);
void deleteTask(Task tasks[], int count, int index);
void showTasks(Task tasks[], int count);
void sortTask(Task tasks[],int count);

#endif

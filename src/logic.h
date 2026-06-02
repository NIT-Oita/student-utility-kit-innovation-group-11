#ifndef LOGIC_H
#define LOGIC_H

#define MAX_TASKS 100
#define TITLE_LEN 50
#define DEADLINE_LEN 30
#define GENRE_LEN 30
#define MAX_GENRES 20

typedef struct{
    char title[TITLE_LEN];
    int year;
    int month;
    int day;
    char deadline[DEADLINE_LEN];
    char genre[GENRE_LEN];
    int completed;
}Task;

//�֐��錾
<<<<<<< HEAD
void addTask(Task tasks[], int count, char title[], int year,int month,int day);
=======
void addTask(Task tasks[], int count, char title[], char deadline[], char genre[]);
>>>>>>> feature2
void completeTask(Task tasks[], int index);
void deleteTask(Task tasks[], int count, int index);
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count);

#endif

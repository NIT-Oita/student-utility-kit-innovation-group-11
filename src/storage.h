#ifndef STORAGE_H
#define STORAGE_H

#include "logic.h"

// タスク・ジャンル保存関数
void saveTasks(const Task tasks[], int task_count, char genres[][GENRE_LEN], int genre_count);

// タスク・ジャンル読込関数
int loadTasks(Task tasks[], char genres[][GENRE_LEN], int *genre_count);

#endif

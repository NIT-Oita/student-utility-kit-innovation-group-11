#ifndef STORAGE_H
#define STORAGE_H

#include "logic.h"

// タスク保存関数
void saveTasks(const Task tasks[], int count);

// タスク読込関数
int loadTasks(Task tasks[]);

#endif

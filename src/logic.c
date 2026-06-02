#include <stdio.h>
#include <string.h>
#include "logic.h"

// �^�X�N�ǉ�
<<<<<<< HEAD
void addTask(Task tasks[], int count, char title[],int year,int month,int day) {
=======
void addTask(Task tasks[], int count, char title[], char deadline[], char genre[]) {
>>>>>>> feature2
    strncpy(tasks[count].title, title, TITLE_LEN - 1);
    tasks[count].title[TITLE_LEN - 1] = '\0';
    
    tasks[count].year = year;
    tasks[count].month = month;
    tasks[count].day = day;
    
    strncpy(tasks[count].genre, genre, GENRE_LEN - 1);
    tasks[count].genre[GENRE_LEN - 1] = '\0';
    
    tasks[count].completed = 0; // �������ŏ�����
}

// �^�X�N����
void completeTask(Task tasks[], int index) {
    tasks[index].completed = 1;
}

// �^�X�N�폜
void deleteTask(Task tasks[], int count, int index) {
    for (int i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
}

// �^�X�N�ꗗ�\���i�W�������ʁj
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count) {
    if (count == 0) {
        printf("\n  ���݁A�o�^����Ă���^�X�N�͂���܂���B\n");
        // �W���������o�^����Ă���ꍇ�̓W�������ꗗ�����ł�������Ɛe��
        if (genre_count > 0) {
            printf("\n--- �o�^����Ă���W�������ꗗ ---\n");
            for (int i = 0; i < genre_count; i++) {
                printf("  �E %s\n", genres[i]);
            }
        }
        return;
    }
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i, tasks[i].title);
        printf("      ����: %d/%d/%d  /  ���: %s\n", tasks[i].year,tasks[i].month,tasks[i].day, tasks[i].completed ? "����" : "������");
        if (i < count - 1) {
            printf("  ------------------------------------------------\n");
    
    // �e��`�ς݃W��������\��
    for (int g = 0; g < genre_count; g++) {
        printf("\n================ [ %s ] ================\n", genres[g]);
        int has_tasks = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                printf("  [%d] %s\n", i, tasks[i].title);
                printf("      ����: %s  /  ���: %s\n", tasks[i].deadline, tasks[i].completed ? "����" : "������");
                has_tasks = 1;
            }
        }
        if (!has_tasks) {
            printf("  (���̃W�������̃^�X�N�͂���܂���)\n");
        }
    }
    
    // �����ރW��������\��
    int has_unclassified = 0;
    for (int i = 0; i < count; i++) {
        int belongs_to_genre = 0;
        for (int g = 0; g < genre_count; g++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                belongs_to_genre = 1;
                break;
            }
        }
        if (!belongs_to_genre) {
            if (!has_unclassified) {
                printf("\n================ [ ������ ] ================\n");
                has_unclassified = 1;
            }
            printf("  [%d] %s\n", i, tasks[i].title);
            printf("      ����: %s  /  ���: %s\n", tasks[i].deadline, tasks[i].completed ? "����" : "������");
        }
    }
    printf("\n--------------------------------------------------\n");
}

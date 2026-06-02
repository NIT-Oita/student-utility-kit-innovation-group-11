#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "logic.h"
#include "storage.h"

// �ÓI�ϐ��Ń^�X�N�ꗗ�ƃW�������ꗗ��ێ�
static Task tasks[MAX_TASKS];
static int task_count = 0;
static char genres[MAX_GENRES][GENRE_LEN];
static int genre_count = 0;
static int is_loaded = 0; // �Ǎ��t���O

// �����w���p�[�֐��錾
static void input_genre(void);

void start_screen(void) {
    printf("==================================================\n");
    printf("==                                              ==\n");
    printf("==            �w�������x���L�b�g                ==\n");
    printf("==            - �ۑ�Ǘ� (TODO) -               ==\n");
    printf("==                                              ==\n");
    printf("==================================================\n");
    printf("\n");
    printf("  [Enter] �L�[�������ƃ��C�����j���[�ɐi�݂܂�...\n");
    fflush(stdout);

    // Enter�L�[�̓��͂�҂i���̓o�b�t�@�̃N���A�����˂�j
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main_screen(void) {
    // �N������1�x�����f�[�^��ǂݍ���
    // ?N??????1?x?????f?[?^???????
    if (!is_loaded) {
        task_count = loadTasks(tasks, genres, &genre_count);
        is_loaded = 1;
    }

    int choice;
    while (1) {
        printf("\n==================================================\n");
        printf("==                  ���C�����j���[              ==\n");
        printf("==================================================\n");
        printf("  1. �^�X�N�ꗗ�̕\��\n");
        printf("  2. �V�����^�X�N�̒ǉ�\n");
        printf("  3. �^�X�N�������ɂ���\n");
        printf("  4. �^�X�N�̍폜\n");
        printf("  5. �V�����W�������̒ǉ�\n");
        printf("  6. �I��\n");
        printf("==================================================\n");
        printf("�ԍ�����͂��Ă������� (1-6): ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            // �����Ȃǂ����͂��ꂽ�ꍇ�̖������[�v��h�����߁A�o�b�t�@���N���A����
            while (getchar() != '\n');
            printf("�����ȓ��͂ł��B1����6�̐��l����͂��Ă��������B\n");
            continue;
        }
        // scanf�Ŏc�������s�����������
        while (getchar() != '\n');

        if (choice == 1) {
            printf("\n--- �^�X�N�ꗗ ---\n");
            showTasks(tasks, task_count, genres, genre_count);
        } else if (choice == 2) {
            // �^�X�N�ǉ���ʂ̌Ăяo��
            input_data();
        } else if (choice == 3) {
            printf("\n--- �^�X�N�������ɂ��� ---\n");
            if (task_count == 0) {
                printf("�o�^����Ă���^�X�N������܂���B\n");
            } else {
                showTasks(tasks, task_count, genres, genre_count);
                printf("�����ɂ���^�X�N�̔ԍ�����͂��Ă�������: ");
                int idx;
                fflush(stdout);
                if (scanf("%d", &idx) == 1) {
                    if (idx >= 0 && idx < task_count) {
                        completeTask(tasks, idx);
                        saveTasks(tasks, task_count, genres, genre_count);
                        printf("�^�X�N�u%s�v�������ɂ��܂����B\n", tasks[idx].title);
                    } else {
                        printf("�����ȃ^�X�N�ԍ��ł��B\n");
                    }
                }
                while (getchar() != '\n');
            }
        } else if (choice == 4) {
            printf("\n--- �^�X�N�̍폜 ---\n");
            if (task_count == 0) {
                printf("�o�^����Ă���^�X�N������܂���B\n");
            } else {
                showTasks(tasks, task_count, genres, genre_count);
                printf("�폜����^�X�N�̔ԍ�����͂��Ă�������: ");
                int idx;
                fflush(stdout);
                if (scanf("%d", &idx) == 1) {
                    if (idx >= 0 && idx < task_count) {
                        char deleted_title[TITLE_LEN];
                        strncpy(deleted_title, tasks[idx].title, TITLE_LEN - 1);
                        deleted_title[TITLE_LEN - 1] = '\0';
                        
                        deleteTask(tasks, task_count, idx);
                        task_count--;
                        saveTasks(tasks, task_count, genres, genre_count);
                        printf("�^�X�N�u%s�v���폜���܂����B\n", deleted_title);
                    } else {
                        printf("�����ȃ^�X�N�ԍ��ł��B\n");
                    }
                }
                while (getchar() != '\n');
            }
        } else if (choice == 5) {
            // �W�������̒ǉ���ʂ̌Ăяo��
            input_genre();
        } else if (choice == 6) {
            printf("�v���O�������I�����܂��B�����p���肪�Ƃ��������܂����B\n");
            break;
        } else {
            printf("�����ȑI���ł��B1����6�̐��l����͂��Ă��������B\n");
        }
    }
}

void input_data(void) {
    char title[100];
<<<<<<< HEAD
    int year,month,day;
    if (task_count >= MAX_TASKS) {
<<<<<<< HEAD
        printf("����ȏ�^�X�N��ǉ��ł��܂���i���%d���j�B\n", MAX_TASKS);
    }else if(task_count < MAX_TASKS){
        printf("\n==================================================\n");
        printf("==                �^�X�N�̒ǉ�                  ==\n");
        printf("==================================================\n");
        printf("�ǉ�����^�X�N�̃^�C�g������͂��Ă�������:\n");
=======
        printf("??????^?X?N????????????i???%d???j?B\n", MAX_TASKS);
    }else if(task_count < MAX_TASKS){
        printf("\n==================================================\n");
        printf("==                ?^?X?N????                  ==\n");
        printf("==================================================\n");
        printf("???????^?X?N??^?C?g?????????????????:\n");
>>>>>>> ba350f2d1432345165ba4b21e53241b7b2ad4006
        printf("> ");
        fflush(stdout);
=======
    char deadline[100];
    char genre[GENRE_LEN] = "������";
>>>>>>> feature2

<<<<<<< HEAD
        // �^�C�g�����́i���S��1�s�ǂݍ��ށj
=======
        // ?^?C?g??????i???S??1?s??????j
>>>>>>> ba350f2d1432345165ba4b21e53241b7b2ad4006
        if (fgets(title, sizeof(title), stdin) != NULL) {
            title[strcspn(title, "\n")] = '\0';
        
            if (title[0] == '\0') {
<<<<<<< HEAD
                printf("�^�C�g������ł��B�^�X�N�̒ǉ����L�����Z�����܂����B\n");
            } else {
                printf("��������͂��Ă��������i����j:\n");
                printf("> ");
                scanf_s("%d",&year);
                printf("\n��������͂��Ă��������i���j:\n");
                printf("> ");
                scanf_s("%d",&month);
                fflush(stdout);
                printf("\n��������͂��Ă��������i���j:\n");
=======
                printf("?^?C?g?????????B?^?X?N???????L?????Z??????????B\n");
            } else {
                printf("????????????????????i????j:\n");
                printf("> ");
                scanf_s("%d",&year);
                printf("\n????????????????????i???j:\n");
                printf("> ");
                scanf_s("%d",&month);
                fflush(stdout);
                printf("\n????????????????????i???j:\n");
>>>>>>> ba350f2d1432345165ba4b21e53241b7b2ad4006
                printf("> ");
                scanf_s("%d",&day);
            
                addTask(tasks, task_count, title, year,month,day);
                task_count++;
                saveTasks(tasks, task_count);
<<<<<<< HEAD
                printf("\n�^�X�N�u%s�v�i����: %d/%d/%d�j��ǉ����܂����B\n", title, year,month,day);
            // ��������
            if (fgets(deadline, sizeof(deadline), stdin) != NULL) {
                deadline[strcspn(deadline, "\n")] = '\0';
                
                if (deadline[0] == '\0') {
                    // ��������̏ꍇ�́u�Ȃ��v�ɐݒ肷��
                    strcpy(deadline, "�Ȃ�");
                }
                
                // �W�������I�� (�W���������o�^����Ă���ꍇ�̂�)
                if (genre_count > 0) {
                    printf("\n�ȉ��̃W����������I�����Ă�������:\n");
                    for (int i = 0; i < genre_count; i++) {
                        printf("  %d: %s\n", i, genres[i]);
                    }
                    printf("  %d: ������ (�܂��͎w��Ȃ�)\n", genre_count);
                    printf("�ԍ�����͂��Ă������� (�f�t�H���g: ������):\n> ");
                    fflush(stdout);
                    
                    char choice_str[30];
                    if (fgets(choice_str, sizeof(choice_str), stdin) != NULL) {
                        int g_idx = -1;
                        if (sscanf(choice_str, "%d", &g_idx) == 1) {
                            if (g_idx >= 0 && g_idx < genre_count) {
                                strncpy(genre, genres[g_idx], GENRE_LEN - 1);
                                genre[GENRE_LEN - 1] = '\0';
                            }
                        }
                    }
                }
                
                if (task_count >= MAX_TASKS) {
                    printf("����ȏ�^�X�N��ǉ��ł��܂���i���%d���j�B\n", MAX_TASKS);
                } else {
                    addTask(tasks, task_count, title, deadline, genre);
                    task_count++;
                    saveTasks(tasks, task_count, genres, genre_count);
                    printf("\n�^�X�N�u%s�v�i����: %s, �W������: %s�j��ǉ����܂����B\n", title, deadline, genre);
                }
=======
                printf("\n?^?X?N?u%s?v?i????: %d/%d/%d?j????????????B\n", title, year,month,day);
>>>>>>> ba350f2d1432345165ba4b21e53241b7b2ad4006
            }
    }
}
    
<<<<<<< HEAD
    printf("\n[Enter] �L�[�������ƃ��C�����j���[�ɖ߂�܂�...\n");
    fflush(stdout);
    
    // Enter�҂�
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void input_genre(void) {
    char genre_name[100];
    printf("\n==================================================\n");
    printf("==              �W�������̒ǉ�                  ==\n");
    printf("==================================================\n");
    printf("�ǉ�����W�������̖��O����͂��Ă�������:\n");
    printf("> ");
    fflush(stdout);

    if (fgets(genre_name, sizeof(genre_name), stdin) != NULL) {
        genre_name[strcspn(genre_name, "\n")] = '\0';
        
        if (genre_name[0] == '\0') {
            printf("�W������������ł��B�ǉ����L�����Z�����܂����B\n");
        } else if (genre_count >= MAX_GENRES) {
            printf("����ȏ�W��������ǉ��ł��܂���i���%d���j�B\n", MAX_GENRES);
        } else {
            // �d���`�F�b�N
            int exists = 0;
            for (int i = 0; i < genre_count; i++) {
                if (strcmp(genres[i], genre_name) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (exists) {
                printf("�W�������u%s�v�͊��ɑ��݂��܂��B\n", genre_name);
            } else {
                strncpy(genres[genre_count], genre_name, GENRE_LEN - 1);
                genres[genre_count][GENRE_LEN - 1] = '\0';
                genre_count++;
                saveTasks(tasks, task_count, genres, genre_count);
                printf("\n�W�������u%s�v��ǉ����܂����B\n", genre_name);
            }
        }
    }
    
    printf("\n[Enter] �L�[�������ƃ��C�����j���[�ɖ߂�܂�...\n");
    fflush(stdout);
    
    // Enter�҂�
=======
    printf("\n[Enter] ?L?[??????????C?????j???[??????...\n");
    fflush(stdout);
    
    // Enter???
>>>>>>> ba350f2d1432345165ba4b21e53241b7b2ad4006
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

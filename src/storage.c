#include <stdio.h>
#include "storage.h"

// ????p?t?@?C??????K?????p?X??J???w???p?[???
static FILE *openTaskFile(const char *mode) {
    FILE *file = fopen("data/task.bin", mode);
    if (file != NULL) {
        return file;
    }
    file = fopen("../data/task.bin", mode);
    if (file != NULL) {
        return file;
    }
    return fopen("task.bin", mode);
}

// �^�X�N�E�W�������ۑ��֐�
void saveTasks(const Task tasks[], int task_count, char genres[][GENRE_LEN], int genre_count) {
    FILE *file = openTaskFile("wb");
    if (file == NULL) {
        perror("?t?@?C????????????????????B");
        return;
    }
    
    // 1. �W������������������
    fwrite(&genre_count, sizeof(int), 1, file);
    
    // 2. �W�������z�����������
    if (genre_count > 0) {
        fwrite(genres, sizeof(char) * GENRE_LEN, genre_count, file);
    }
    
    // 3. �^�X�N�̌�����������
    fwrite(&task_count, sizeof(int), 1, file);
    
    // 4. �^�X�N�z�����������
    if (task_count > 0) {
        fwrite(tasks, sizeof(Task), task_count, file);
    }
    
    fclose(file);
}

// �^�X�N�E�W�������Ǎ��֐�
int loadTasks(Task tasks[], char genres[][GENRE_LEN], int *genre_count) {
    FILE *file = openTaskFile("rb");
    if (file == NULL) {
        // �t�@�C�������݂��Ȃ��ꍇ��0��Ԃ� (�������)
        *genre_count = 0;
        return 0;
    }
    
    int g_count = 0;
    // 1. �W����������ǂݍ���
    if (fread(&g_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    
    // �͈̓`�F�b�N
    if (g_count < 0 || g_count > MAX_GENRES) {
        fclose(file);
        *genre_count = 0;
        return 0;
    }
    
    *genre_count = g_count;
    
    // 2. �W�������z���ǂݍ���
    if (g_count > 0) {
        int read_genres = fread(genres, sizeof(char) * GENRE_LEN, g_count, file);
        if (read_genres != g_count) {
            fclose(file);
            *genre_count = 0;
            return 0;
        }
    }
    
    int t_count = 0;
    // 3. �^�X�N�̌���ǂݍ���
    if (fread(&t_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    // �͈̓`�F�b�N
    if (t_count < 0 || t_count > MAX_TASKS) {
        fclose(file);
        return 0;
    }
    
    // 4. �^�X�N�z���ǂݍ���
    if (t_count > 0) {
        int read_tasks = fread(tasks, sizeof(Task), t_count, file);
        if (read_tasks != t_count) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return t_count;
}

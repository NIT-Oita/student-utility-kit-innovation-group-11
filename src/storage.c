#include<stdio.h>


char name[100];


//�ǂݎ�����^�X�N���t�@�C���ɕۑ�
void datamana(){
    FILE *task = fopen("task.bin", "wb");
    if (task == NULL) {
        perror("�t�@�C�����J���܂���ł���");
    }else{
        fwrite(name, sizeof(int), sizeof(name), task);
    }
}
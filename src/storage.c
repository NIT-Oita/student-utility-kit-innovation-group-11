#include<stdio.h>

extern char title[100];

void datamana(){
    FILE *task = fopen("../data/task.bin", "wb");
    if (task == NULL) {
        perror("ファイルが保存されませんでした。");
    }else{
        fwrite(title, sizeof(int), sizeof(title), task);
    }
}
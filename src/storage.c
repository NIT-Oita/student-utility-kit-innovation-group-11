#include<stdio.h>

char name[100];

int main(){
    printf("ファイルの名前を入力してください。");
    scanf_s("%c",name);
    return 0;
}

//読み取ったタスクをファイルに保存
void datamana(){
    FILE *task = fopen("task.bin", "wb");
    if (task == NULL) {
        perror("ファイルを開けませんでした");
    }else{
        fwrite(name, sizeof(int), sizeof(name), task);
    }
}
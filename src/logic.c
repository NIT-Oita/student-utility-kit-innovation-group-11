#include <stdio.h>
#include <string.h>
#include "logic.h"

// ï¿½^ï¿½Xï¿½Nï¿½Ç‰ï¿½
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
    
    tasks[count].completed = 0; // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Åï¿½ï¿½ï¿½ï¿½ï¿½
}

// ï¿½^ï¿½Xï¿½Nï¿½ï¿½ï¿½ï¿½
void completeTask(Task tasks[], int index) {
    tasks[index].completed = 1;
}

// ï¿½^ï¿½Xï¿½Nï¿½íœ
void deleteTask(Task tasks[], int count, int index) {
    for (int i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
}

// ï¿½^ï¿½Xï¿½Nï¿½ê——ï¿½\ï¿½ï¿½ï¿½iï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Êj
void showTasks(Task tasks[], int count, char genres[][GENRE_LEN], int genre_count) {
    if (count == 0) {
        printf("\n  ï¿½ï¿½ï¿½İAï¿½oï¿½^ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½^ï¿½Xï¿½Nï¿½Í‚ï¿½ï¿½ï¿½Ü‚ï¿½ï¿½ï¿½B\n");
        // ï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½oï¿½^ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½ê‡ï¿½ÍƒWï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ê——ï¿½ï¿½ï¿½ï¿½ï¿½Å‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æeï¿½ï¿½
        if (genre_count > 0) {
            printf("\n--- ï¿½oï¿½^ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ê—— ---\n");
            for (int i = 0; i < genre_count; i++) {
                printf("  ï¿½E %s\n", genres[i]);
            }
        }
        return;
    }
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i, tasks[i].title);
        printf("      ï¿½ï¿½ï¿½ï¿½: %d/%d/%d  /  ï¿½ï¿½ï¿½: %s\n", tasks[i].year,tasks[i].month,tasks[i].day, tasks[i].completed ? "ï¿½ï¿½ï¿½ï¿½" : "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½");
        if (i < count - 1) {
            printf("  ------------------------------------------------\n");
    
    // ï¿½eï¿½ï¿½`ï¿½Ï‚İƒWï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½\ï¿½ï¿½
    for (int g = 0; g < genre_count; g++) {
        printf("\n================ [ %s ] ================\n", genres[g]);
        int has_tasks = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(tasks[i].genre, genres[g]) == 0) {
                printf("  [%d] %s\n", i, tasks[i].title);
                printf("      ï¿½ï¿½ï¿½ï¿½: %s  /  ï¿½ï¿½ï¿½: %s\n", tasks[i].deadline, tasks[i].completed ? "ï¿½ï¿½ï¿½ï¿½" : "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½");
                has_tasks = 1;
            }
        }
        if (!has_tasks) {
            printf("  (ï¿½ï¿½ï¿½ÌƒWï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ìƒ^ï¿½Xï¿½Nï¿½Í‚ï¿½ï¿½ï¿½Ü‚ï¿½ï¿½ï¿½)\n");
        }
    }
    
    // ï¿½ï¿½ï¿½ï¿½ï¿½ŞƒWï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½\ï¿½ï¿½
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
                printf("\n================ [ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ] ================\n");
                has_unclassified = 1;
            }
            printf("  [%d] %s\n", i, tasks[i].title);
            printf("      ï¿½ï¿½ï¿½ï¿½: %s  /  ï¿½ï¿½ï¿½: %s\n", tasks[i].deadline, tasks[i].completed ? "ï¿½ï¿½ï¿½ï¿½" : "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½");
        }
    }
    printf("\n--------------------------------------------------\n");
}

//ƒ^ƒXƒN‚ğ“ú•t‡‚Å•À‚×‘Ö‚¦‚é
void sortTask(Task tasks[],int count){
    for(int i =0;i < count -1;i++){
        for(int j = 0;j < count - i -1;j++){
        int swap_needed = 0;
        /*0=•À‚×‘Ö‚¦•s—v
          1=•À‚×‘Ö‚¦•K—v*/  

            //”N‚ğ”äŠr
            if(tasks[j].year<tasks[j + 1].year){
                swap_needed = 1;
            }else if(tasks[j].year == tasks[j + 1].year){
                //”N‚ª“¯‚¶‚È‚çŒ‚ğ”äŠr
                if(tasks[j].month < tasks[j + 1].month){
                    swap_needed = 1;
                    }else if(tasks[j].month == tasks[j + 1].month){
                    //Œ‚ª“¯‚¶‚È‚ç“ú‚ğ”äŠr
                        if(tasks[j].day < tasks[j + 1].day){
                            swap_needed = 1;
                }
            }
        }

        //‘O‚Ìj‚Ì•û‚ª‰ß‹‚È‚çŒã‚ë‚Ìj+1‚Æ“ü‚ê‘Ö‚¦‚é
            if(swap_needed == 1){
            Task temp = tasks[j];//temp‚Í‹ó‚Ì” 
            tasks[j] = tasks[j+1];
            tasks[j+1] = temp;
            }
        }
    }
}

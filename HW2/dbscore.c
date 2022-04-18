#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "student.h"
/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int dbscore(int argc, char* argv[])
{
    int fd, i=0, j, n=0, tempid, arrayid[MAX], tempscore, arrayscore[MAX];
    char arrayname[MAX][100], tempname[100];
    struct student record;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }
    
    while (read(fd, &record, sizeof(record)) > 0) {
        lseek(fd, (long)record.id - START_ID * sizeof(record), SEEK_SET);
        if (record.id != 0 && record.name[0]!='$') {
            arrayid[i] = record.id;
            memcpy(arrayname[i],record.name,sizeof(int)*100);
            arrayscore[i] = record.score;
            n++;
            i++;
        }
    }
    
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            if(arrayscore[i] > arrayscore[j]) {
                tempid = arrayid[i];
                memcpy(tempname, arrayname[i], sizeof(arrayname[i]));
                tempscore = arrayscore[i];
                arrayid[i] = arrayid[j];
                memcpy(arrayname[i], arrayname[j], sizeof(arrayname[j]));
                arrayscore[i] = arrayscore[j];
                arrayid[j] = tempid;
                memcpy(arrayname[j],tempname,sizeof(tempname));
                arrayscore[j] = tempscore;
            }
            if(arrayscore[i] == arrayscore[j]){
                if(arrayid[i] < arrayid[j]) {
                    tempid = arrayid[i];
                    memcpy(tempname, arrayname[i], sizeof(arrayname[i]));
                    tempscore = arrayscore[i];
                    arrayid[i] = arrayid[j];
                    memcpy(arrayname[i], arrayname[j], sizeof(arrayname[j]));
                    arrayscore[i] = arrayscore[j];
                    arrayid[j] = tempid;
                    memcpy(arrayname[j],tempname,sizeof(tempname));
                    arrayscore[j] = tempscore;
                }
            }
        }
    }
    printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
    for(i=n-1;i>=0;i--){
        printf("%-9d   %-10s   %-9d", arrayid[i], arrayname[i], arrayscore[i]);
        printf("\n");
    }
    
    
    close(fd);
}

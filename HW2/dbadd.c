#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

void dbadd(int argc, char *argv[])
{
    int fd;
    struct student rec;
    struct flock lock;
    
    if(argc < 2){
        fprintf(stderr,"사용법:%s file\n",argv[0]);
        exit(1);
    }
    if((fd = open(argv[1],O_RDWR))==-1){
        perror(argv[1]);
        exit(2);
    }
    printf("%-9s %-8s %-4s\n","학번","이름","점수");
    if(scanf("%d %s %d", &rec.id, &rec.name,&rec.score)==3){
        lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
        if(((read(fd, (char*)&rec, sizeof(rec)) > 0) && (rec.id != 0))){
            printf("중복\n");
            close(fd);
            return;
        }
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = START_ID*sizeof(rec);
        lock.l_len = sizeof(rec);
        
        if (fcntl(fd, F_SETLKW, &lock) == -1) { /* 쓰기 잠금 */
            perror(argv[1]);
            exit(3);
        }
        lseek(fd,(rec.id-START_ID)*sizeof(rec),SEEK_SET);
        write(fd, (char*)&rec,sizeof(rec));
        
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
    }
    close(fd);
    
}

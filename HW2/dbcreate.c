#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학생 정보를 입력받아 데이터베이스 파일에 저장한다. */
int dbcreate(int argc, char *argv[])
{
        int fd;
        struct student rec;
        struct flock lock;

        if (argc < 2) {
                fprintf(stderr, "사용법 : %s file\n", argv[0]);
                exit(1);
        }

        if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1) {
                perror(argv[1]);
                exit(2);
        }

        printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
        while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) {

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = (rec.id - START_ID) * sizeof(rec);
                lock.l_len = sizeof(rec);

                if(fcntl(fd, F_SETLKW, &lock) == -1){
        
                        perror(argv[1]);
                        exit(3);
                }

                lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
                write(fd, &rec, sizeof(rec));

                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);

        }
        printf("record size= %d\n", sizeof(rec));
        close(fd);
}

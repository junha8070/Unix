#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int dblist(int argc, char* argv[])
{
        int fd, id;
        char c;
        struct student record;
        if (argc < 2) {
                fprintf(stderr, "사용법 : %s file\n", argv[0]);
                exit(1);
        }
        if ((fd = open(argv[1], O_RDONLY)) == -1) {
                perror(argv[1]);
                exit(2);
        }
        printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
        while (read(fd, &record, sizeof(record)) > 0) {
                lseek(fd, (long)record.id - START_ID * sizeof(record), SEEK_SET);
                if (record.id != 0 && record.name[0]!='$') {
                        printf("%-9d   %-10s   %-9d", record.id, record.name, record.score);
                        printf("\n");
                }

        }

        close(fd);
}

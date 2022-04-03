#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
/* 학번을 입력받아 해당 학생 레코드를 수정한다. */
int dbdelete(int argc, char* argv[])
{
    int fd, id;
    char c;
    struct student record;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do
    {
        printf("학번 입력: ");
        if (scanf("%d", &id) == 1) {
            lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
            if ((read(fd, &record, sizeof(record)) > 0) && (record.id != 0))
            {
                
                record.name[0] = '$';
                lseek(fd, (long)-sizeof(record), SEEK_CUR);
                write(fd, (char*)&record, sizeof(record));
                
                printf("삭제되었습니다.\n");
            }
            else printf("레코드 %d 없음\n", record.id);
        }
        else printf("입력오류\n");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');
    close(fd);
}

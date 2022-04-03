#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char* argv[]) {
        char func;
        
        do{
                printf("무슨 기능을 선택할가요(c/q/u/l/a/d/e)?");
                scanf("%c", &func);
                if (func == 'c') {
                        printf("\n<생성 기능 수행>\n");
                        dbcreate(argc, argv);
                }
                else if (func == 'q') {
                        printf("\n<질의 기능 수행>");
                        dbquery(argc, argv);
                }
                else if (func == 'u') {
                        printf("\n<수정 기능 수행>\n");
                        dbupdate(argc, argv);
                }
                else if (func == 'l') {
                        printf("\n<전체 출력 기능 수행>\n");
                        dblist(argc, argv);
                }
                else if (func == 'a') {
                        printf("\n<추가 기능 수행>\n");
                        dbadd(argc, argv);
                }
                else if (func == 'd') {
                        printf("\n<삭제 기능 수행>\n");
                        dbdelete(argc, argv);
                }
                else if (func == 'e') {
                        printf("종료합니다.\n");
                        exit(0);
                }
        } while (func != 'e');
}

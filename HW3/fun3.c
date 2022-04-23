#include <sys/types.h>
#include <unistd.h>
void fun3(char *arg[], int argi, int *fg){
        int pid, status;
        if((pid=fork())==-1)
                perror("fork failed");
        else if(pid!=0){
                (*fg)++;
                printf("[%d] %d\n",*fg, pid);
        }
        else{
                arg[argi-1]=(char *)0;
                execvp(arg[0], &arg[0]);
        }
}

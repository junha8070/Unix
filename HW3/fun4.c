#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXARG 7
void fun4(char *arg[],int argi){
        int r3=0, r4=0;
        int f3, f4, t;
        int pid, status;
        int fd3, fd4;
        char *carg[MAXARG];
        int i; char *p;
        for(i=0; i<argi; i++){
                if(p=strchr(arg[i],'<')){
                        r3=i;
                        f3=i+1;
                        t=i;
                }
                if(p=strchr(arg[i],'>')){
                        r4=i;
                        f4=i+1;
                        t=i;
                }
        }
        if((pid=fork())==-1)
                perror("fork failed");
        else if(pid !=0)
                pid=wait(&status);
        else{
                if(r3){
                        fd3=open(arg[f3], O_RDONLY);
                        dup2(fd3,0);
                        close(fd3);
                }
                if(r4){
                        fd4=open(arg[f4], O_CREAT|O_TRUNC|O_WRONLY, 0600);
                        dup2(fd4,1);
                        close(fd4);
                }
                if(r3 && r4)
                        t=r3;
                int j;
                for(j=0; j<t; j++)
                        carg[j]=arg[j];
                carg[j]=(char *)0;
                execvp(carg[0], &carg[0]);
        }
}

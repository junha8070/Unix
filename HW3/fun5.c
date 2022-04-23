#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAXARG 7
void fun5(char *arg[], int argi){
        char *carg[MAXARG];
        char *s;
        char *p;
        int t=0;
        int pid, status;
        int r3=0, r4=0;
        int f3, f4;
        int fd3, fd4;
        int i,j;
        for(i=0; i<argi; i++){
                if(p=strchr(arg[i], '<')){
                        r3=i;
                        f3=i+1;
                }
                if(p=strchr(arg[i],'>')){
                        r4=i;
                        f4=i+1;
                }
        }

        for(i=0; i<argi; i++){
                if(p=strchr(arg[i],'(')){
                        s=arg[i];
                        int j;
                        for(j=0; j<strlen(arg[i])-1; j++)
                                s[j]=s[j+1];
                        s[j]='\0';
                }
                if(p=strchr(arg[i],')')){
                        s=strtok(arg[i],")");
                        arg[i]=s;
                        for(j=t; j<=i; j++)
                                carg[j-t]=arg[j];
                        carg[j-t]=(char *)0;
                        if((pid=fork())==-1)
                                perror("fork failed");
                        else if(pid!=0)
                                pid=wait(&status);
                        else{
                                if(r3){
                                        fd3=open(arg[f3], O_RDONLY);
                                        dup2(fd3, 0);
                                        close(fd3);
                                }
                                if(r4){
                                        fd4=open(arg[f4], O_WRONLY|O_APPEND);
                                        dup2(fd4, 1);
                                        close(fd4);
                                }
                                execvp(carg[0], &carg[0]);
                        }
                }
                if(p=strchr(arg[i],';')){
                        s=strtok(arg[i],";");
                        arg[i]=s;
                        for(j=t; j<=i; j++)
                                carg[j-t]=arg[j];
                        carg[j-t]=(char *)0;
                        t=i+1;
                        if((pid=fork())==-1)
                                perror("fork failed");
                        else if(pid!=0)
                                pid=wait(&status);
                        else{
                                if(r3){
                                        fd3=open(arg[f3], O_RDONLY);
                                        dup2(fd3, 0);
                                        close(fd3);
                                }
                                if(r4){
                                        fd4=open(arg[f4], O_CREAT|O_TRUNC|O_WRONLY, 0600);
                                        dup2(fd4, 1);
                                        close(fd4);
                                }
                                execvp(carg[0],&carg[0]);
                        }
                }
        }
}

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXARG 7
void fun2(char *arg[], int argi){
        char *carg[MAXARG];
        char *s;
        int t=0, loc, r=1;
        int pid, status;
        char *p;
        int i;
        for(i=0; i<argi; i++){
                if(p=strchr(arg[i], '(')){
                        s=arg[i];
                        int j;
                        for(j=0; j<strlen(arg[i])-1; j++)
                                s[j]=s[j+1];
                        s[j]='\0';
                }
                if(p=strchr(arg[i], ')')){
                        s=strtok(arg[i], ")");
                        arg[i]=s;
                }
                if(p=strchr(arg[i], ';')){
                        s=strtok(arg[i], ";");
                        arg[i]=s;
                        int j;
                        for(j=t; j<=i; j++)
                                carg[j-t]=arg[j];
                        carg[j-t]=(char *)0;
                        t=i+1;
                if((pid=fork())==-1)
                        perror("fork failed");
                        else if(pid!=0)
                                pid=wait(&status);
                        else
                                execvp(carg[0], &carg[0]);
                }
        }
                if((pid=fork())==-1)
                        perror("fork failed");
                else if(pid!=0)
                        pid=wait(&status);
                else
                        execvp(arg[t], &arg[t]);
}

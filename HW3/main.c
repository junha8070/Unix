#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "fun.h"
#define MAXARG 7

int main()
{
    char buf[256];
    char *arg[MAXARG];
    char *s;
    char *save;
    int fg=0;
    int argi;
    int r1, r2, r3, r4, r5;
    int f3, f4, t;
    static const char delim[] = " \t\n";
    int pid, status;
    while(1){
        r1=0; r2=0; r3=0; r4=0; r5=0;
        printf("myshell& ");
        gets(buf);
        argi=0;
        s=strtok_r(buf, delim, &save);
        while(s){
            arg[argi++]=s;
            s=strtok_r(NULL, delim, &save);
        }
        arg[argi]=(char *)0;
        if(!strcmp(arg[0], "quit"))
            break;
        
        int i;
        for(i=0; i<argi; i++){
            if(strchr(arg[i],'(')){
                r1=1;
            }
            
            if(strchr(arg[i],';')){
                r2=1;
            }
            
            if(strchr(arg[i],'<')){
                r3=1;
            }
            
            if(strchr(arg[i],'>')){
                r4=1;
            }
            
            if(strchr(arg[i],'&'))
                r5=1;
        }
        
        
        if(!r1&&r2){
            fun1(arg,argi);
        }
        else if(r1&&r2&&!r3&&!r4){
            fun2(arg,argi);
        }
        else if(r5){
            fun3(arg,argi,&fg);
        }
        else if(!r1&&!r2&&(r3||r4)){
            fun4(arg,argi);
        }
        else if((r1&&r2&&r3)||(r1&&r2&&r4)){
            fun5(arg,argi);
        }
        else{
            if((pid=fork())==-1)
                perror("fork failed");
            else if(pid!=0)
                pid=wait(&status);
            else
                execvp(arg[0],&arg[0]);
        }
    }
    exit(0);
}

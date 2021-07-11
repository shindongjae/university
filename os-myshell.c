#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>

int check(char* tmp);

void description();

int main() {
    int i=0;
    int start=0;
    pid_t pid, d_pid; int status;
    char cmd[50] = "";

    char* history[100];
    for (i = 0;i < 100;i++) {//할당
        history[i] = malloc(sizeof(char) * 50);
        memset(history[i], 0, sizeof(history[i])); //history배열 할당후 초기화
    }

    int position = 0;
    
    while (1) {
        bool background = false;
        printf("12161459_shell$ ");
        fgets(cmd, sizeof(cmd), stdin);
        
        int length = strlen(cmd); //문자열뒤 개행문자 제거
        cmd[length - 1] = '\0';
        if (cmd[length - 2] == '&') {//백그라운드실행후 &는 토큰에 저장하지않음.
            background = true;
            cmd[length - 2] = '\0';
        }


	start=position;//입력받은 명령어의 시작위치

        char* token = strtok(cmd, " ");
        while (token != NULL) {   //문자열 history에 저장.
            for (i = 0;i < strlen(token);i++) {
                history[position][i] = token[i];
            }
            history[position][strlen(token)] = '\0';
            position++;

            token = strtok(NULL, " ");
        }

       
        int state = check(history[position-1]);//quit, history, help인경우 123

        if(state==1)//quit
        {
            printf("myshell developed by shindongjae(12161459)");
            for (i = 0;i < 100;i++)
                free(history[i]);
            return 0;
        }

        else if (state == 2)//history
        {
            if(position<10)
                for (i = 0;i < position;i++)
                    printf("%s ", history[i]);
            else
                for (i = position-10;i < position;i++)
                    printf("%s ", history[i]);
            printf("\n");
        }

        else if (state == 3)//help
        {
            description();
        }
	
	else//cat, ls, background, not background
	{
	    if(strcmp(history[start],"cat")==0&&position>start)//cat이라면
	    {
	    	pid=fork();
		if(pid>0)
		{
		    printf("parent process\n");	
if(!background) //background가 아닌경우에만 대기
		    	d_pid=wait(&status);    	    
		}
		else if(pid==0)//child
		{
		    printf("child process\n");
		    execl("/bin/cat","cat",history[start+1],NULL);
	 	    exit(-1);
		}
		else
		    {
			perror("write error\n");
			exit(-11);
		    }
	    }
	
	    else if(strcmp(history[start],"ls")==0)//ls -l이라면
	    {   
		if(position>start && strcmp(history[start+1],"-l")==0)//"ls -l"
		{    	
	    	    pid=fork();
		    if(pid>0)
		    {
		        printf("parent process\n");
if(!background) //background가 아닌경우에만 대기
		    	    d_pid=wait(&status);    	    

		    }
		    else if(pid==0)//child
		    {
		        printf("child process\n");
		        execl("/bin/ls","ls","-l",NULL);
	 	        exit(-1);
		    }
		    else
		    {
			perror("write error\n");
			exit(-11);
		    }
		}
	    }	
	}
    }
 }


/*//other.c
#include <stdio.h>
#include <string.h>


int check(char* tmp) {
    if (strcmp(tmp, "quit") == 0)
        return 1;
    if (strcmp(tmp, "history") == 0)
        return 2;
    if (strcmp(tmp, "help") == 0)
        return 3;
    return 0;
}




void description() {
    printf("Description\n");
    printf("my shell is a simple C Shell, a shell with C-like syntax \n\n");
    printf("built in command\n");
    printf("1.quit\n");
    printf("2.history\n");
    printf("3.help\n\n");
    printf("\n");
    printf("cat : print file\n");
    printf("ls -l : directory list\n");
    printf("\n");	
}


*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_LEN 1024

int main(){
    char line[BUFFER_LEN];  //get command line
    char* argv[100];        //user command
    char* path= "/bin/";    //set path at bin
    char progpath[20];      //full file path
    int argc;               //arg count

    while(1){

        printf("> ");                    //print shell prompt
        fflush(stdout);
        if(!fgets(line, BUFFER_LEN, stdin)){  //get command and put it in line
            break;                                //if user hits CTRL+D break
        }
        size_t length = strlen(line);
        if (line[length - 1] == '\n')
            line[length - 1] = '\0';

        if(strcmp(line, "exit")==0){            //check if command is exit
            break;
        }

        char *token;                  //split command into separate strings
        token = strtok(line," ");
        int i=0;
        while(token!=NULL){
            argv[i]=token;
            token = strtok(NULL," ");
            i++;
        }
        argv[i]=NULL;                     //set last value to NULL for execvp

        argc=i;                           //get arg count
        for(i=0; i<argc; i++){
            printf("%s\n", argv[i]);      //print command/args
        }
        strcpy(progpath, path);           //copy /bin/ to file path
        strcat(progpath, argv[0]);            //add program to path

        for(i=0; i<strlen(progpath); i++){    //delete newline
            if(progpath[i]=='\n'){
                progpath[i]='\0';
            }
        }
        int pid = fork();              //fork child

        if(pid==0){               //Child
            execvp(progpath,argv);
            fprintf(stderr, "Child process could not do execvp\n");

        }else{                    //Parent
            wait(NULL);
            printf("Child exited\n");
        }

    }
}

//#define MAXCOM 1000
//#define MAXLIST 100
//
//#define clear() printf("\033[H\033[J")
//
//void init_shell() {
//    clear();
//    printf("\n İşletim Sistemleri SHELL \n ");
//    sleep(1);
//    clear();
//}
//
//void printDir() {
//    char cwd[1024];
//    getcwd(cwd, sizeof(cwd));
//    printf("\nDizin: %s", cwd);
//}
//
//int takeInput(char* str)
//{
//    char* buf;
//    buf = readline("\n>>> ");
//    if (strlen(buf) != 0) {
//        add_history(buf);
//        strcpy(str, buf);
//        return 0;
//    } else {
//        return 1;
//    }
//}
//
//int main() {
//    char inputString[MAXCOM], *parsedArgs[MAXLIST];
//    char* parsedArgsPiped[MAXLIST];
//    int execFlag = 0;
//    init_shell();
//
//    // while(true) {
//    printDir();
//
//    return 0;
//}
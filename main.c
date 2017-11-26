#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_LEN 1024

void testit() {
    int fp,stdo;
    int fw=open("CMakeLists.txt", O_CREAT|O_WRONLY|O_APPEND,0644);


    dup2(fw,1); // stdout -&gt; fw
    printf("Bu Printf dosyaya yazilacak\n");
    fflush(stdout);

    dup2(stdo,1); // stdout u geri alıyoruz
    printf("Bu Printf yazilmayacak ve Ekranda gozukecek\n");

    close(fp);
}

int main() {
    char line[BUFFER_LEN];
    char *argv[100];
    int argc;

    while (1) {
        printf("> ");   // prompt kısmı
        fflush(stdout);

        if(!fgets(line, BUFFER_LEN, stdin)) {  // Kullanıcıdan komutu alır ve line a koyar
            break;                                // CTRL+D ye basılırsa durduracak
        }

        size_t length = strlen(line);
        if (line[length - 1] == '\n')
            line[length - 1] = '\0';

        if(strcmp(line, "quit")==0) {            // komutun "quit" olup olmadıgını kontrol eder
            break;
        }

        char *token;                  // komutu ayrı ayrı stringlere bölmek için
        token = strtok(line," ");

        int i=0, kucuktur, buyuktur;

        while(token!=NULL){
            argv[i]=token;
            token = strtok(NULL," ");

//            if(strcmp(argv[i],"<") == 0) // kelime kontrolü yapan bu döngü içerisinde "<" veya ">"  rastladıgı anda gerekli yere '1' atar. GEREKSİZ ŞUAN
//                kucuktur = 1;
//            else if(strcmp(argv[i], ">") == 0)
//                buyuktur = 1;

            i++;
        }
        argv[i]=NULL;                     // execvp fonks için son değer NULL yapılır

        argc=i;

        int pid = fork();

        if (pid == 0) {
            int fd0,fd1,i,in=0,out=0;
            char input[64],output[64];

            // '<' veya '>' ile karsilastiginde argv[i] degiskenimize NULL atar böylece bunu komut olarak okumaz ve bir sonraki degiskene gecer

            for(i=0;argv[i]!='\0';i++)
            {
                if(strcmp(argv[i],"<")==0) {
                    argv[i]=NULL;
                    printf("'<' simgesiyle karsilasti ve if sorgusuna girdi! argv[i+1] = %s. \n", argv[i+1]);
                    strcpy(input,argv[i+1]);
                    in=2;
                }

                if(strcmp(argv[i],">")==0)
                {
                    argv[i]=NULL;
                    strcpy(output,argv[i+1]);
                    out=2;
                }
            }

            printf("'<' veya '>' ugramadan geldi. | in = %d\n", in);

            // kullanıcı girdisinde '>' char ına rastlarsak
            if(in)
            {
                printf("BURALAR ŞENLENECEK in");
                // fd0 yani file descriptor - internetten arastirilmali
                int fd0;
                if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
                    perror("Input dosyası acilamadi!");
                    exit(0);
                }
                // dup2() fd0'ın önceki dosya girdisinin içeriğini kopyalar
                dup2(fd0, 0);

                close(fd0); // gerekli
            }

            // kullanıcı girdisinde '>' char ına rastlarsak
            if (out)
            {
                printf("BURALAR ŞENLENECEK in");
                int fd1 ;
                if ((fd1 = creat(output , 0644)) < 0) {
                    perror("Output dosyasi acilamadi!");
                    exit(0);
                }

                dup2(fd1, STDOUT_FILENO);
                close(fd1); // gerekli
            }

            execvp(*argv, argv);
            perror("execvp");
            _exit(1);
        }

        else {
            wait(NULL);
            printf("\nCocuktan cikti\n");
        }
    }
}

//    char line[BUFFER_LEN];  //get command line
//    char* argv[100];        //user command
//    char* path= "/bin/";    //set path at bin
//    char progpath[20];      //full file path
//    int argc;               //arg count
//    char input[64],output[64];
//    int fd0,fd1;
//    int in = 0, out = 0;
//
//    while(1){
//
//        printf("> ");                    // prompt
//        fflush(stdout);
//        if(!fgets(line, BUFFER_LEN, stdin)) {  // Kullanıcıdan komutu alır ve line a koyar
//            break;                                // CTRL+D ye basılırsa durduracak
//        }
//        size_t length = strlen(line);
//        if (line[length - 1] == '\n')
//            line[length - 1] = '\0';
//
//        if(strcmp(line, "quit")==0) {            // komutun "quit" olup olmadıgını kontrol eder
//            break;
//        }
//
//        char *token;                  //split command into separate strings
//        token = strtok(line," ");
//
//        int i=0, kucuktur, buyuktur;
//
//        while(token!=NULL){
//            argv[i]=token;
//            token = strtok(NULL," ");
//
////            if(strcmp(argv[i],"<") == 0) // kelime kontrolü yapan bu döngü içerisinde "<" veya ">"  rastladıgı anda gerekli yere '1' atar.
////                kucuktur = 1;
////            else if(strcmp(argv[i], ">") == 0)
////                buyuktur = 1;
//
//            i++;
//        }
//        argv[i]=NULL;                     //set last value to NULL for execvp
//
//        argc=i;                           //get arg count
//        for(int i=0; i<argc; i++) {
//            printf("%s\n", argv[i]);      //print command/args
//        }
//        strcpy(progpath, path);           //copy /bin/ to file path    ORNEK: progpath = /bin/  OLDU ARTIK
//        strcat(progpath, argv[0]);            //add program to path ORNEK: cat < test1 girildiginde progpath = progpath + 'cat' kelimesi olur
//                                            // progpath = "/bin/cat" oldu.
//
//        for(int i=0; i < strlen(progpath); i++) {    //delete newline
//            if(progpath[i]=='\n') {
//                progpath[i]='\0';
//            }
//        }
//
//        int pid = fork();              //fork child
//
//        if(pid==0){               //Child
//            // function for redirection ( '<' , '>' )
//
//            // finds where '<' or '>' occurs and make that argv[i] = NULL , to ensure that command wont't read that
//
//            for(int i=0; argv[i]!='\0'; i++) {
//                if(strcmp(argv[i],"<")==0) {
//                    argv[i]=NULL;
//                    strcpy(input,argv[i+1]);
//                    printf("QQQQQQQQQQQQQQQQQQ input: %s\n", input);
//                    in=2;
//                }
//
//                if(strcmp(argv[i],">")==0) {
//                    argv[i]=NULL;
//                    strcpy(output,argv[i+1]);
//                    out=2;
//                }
//            }
//
//            //if '<' char was found in string inputted by user
//            if(in)
//            {
//                printf("< TESPIT EDILDI \n");
//                if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
//                    perror("Couldn't open input file");
//                    exit(0);
//                }
//                // dup2() copies content of fdo in input of preceeding file
//                dup2(fd0, 0); // STDIN_FILENO here can be replaced by 0
//
//                close(fd0); // necessary
//            }
//
//            //if '>' char was found in string inputted by user
//            if (out)
//            {
//                if ((fd1 = creat(output , 0644)) < 0) {
//                    perror("Couldn't open the output file");
//                    exit(0);
//                }
//
//                dup2(fd1, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
//                close(fd1);
//            }
//
//            execvp(progpath,argv);
//            perror("execvp");
//            _exit(1);
//
//            // another syntax
//            /*      if (!(execvp(*argv, argv) >= 0)) {     // execute the command
//                    printf("*** ERROR: exec failed\n");
//                    exit(1);
//             */
//
//
//        }else{                    //Parent
//            wait(NULL);
//            printf("Child exited\n");
//        }
//
//    }
//}

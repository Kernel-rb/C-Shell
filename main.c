#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LSH_RL_BUFSIZE 1024 // max number of characters in a line
#define LSH_TOK_BUFSIZE 64 // max number of tokens (words) in a line
#define LSH_TOK_DELIM " \t\r\n\a" // delimiters for tokens ( space, tab, newline, alert)

#define ANSI_COLOR_RED  "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

int lsh_num_builtins(void);
void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);
int lsh_launch(char **args);
int lsh_cd(char **args);
int lsh_mkdir(char **args);
int lsh_cat(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "mkdir",
    "cat",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_mkdir,
    &lsh_cat,
    &lsh_help,
    &lsh_exit
};

void sigint_handler(int sig) {
    printf(ANSI_COLOR_RED "\nCtrl+C pressed. Exiting shell.\n" ANSI_COLOR_RESET);
    exit(EXIT_SUCCESS);
}

void sigterm_handler(int sig) {
    printf(ANSI_COLOR_RED "\nSIGTERM received. Exiting shell.\n" ANSI_COLOR_RESET);
    exit(EXIT_SUCCESS);
}

int main(int argc , char **argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    lsh_loop();
    return EXIT_SUCCESS;
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf( ANSI_COLOR_CYAN ">" ANSI_COLOR_RESET);
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    }while(status);
}

char *lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer){
        fprintf(stderr, ANSI_COLOR_RED "lsh: allocation error\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }

    while(1){
        c = getchar();
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else{
            buffer[position] = c;
        }
        position++;

        if(position >= bufsize){
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer){
                fprintf(stderr, ANSI_COLOR_RED "lsh: allocation error\n" ANSI_COLOR_RESET);
                exit(EXIT_FAILURE);
            }
        }
    }
}

char  **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, ANSI_COLOR_RED "lsh: allocation error\n" ANSI_COLOR_RESET);
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM); // strtok is a function that splits a string into tokens
    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, ANSI_COLOR_RED "lsh: allocation error\n" ANSI_COLOR_RESET);
                exit(EXIT_FAILURE);
            }
        }   
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args){
    pid_t pid, wpid;
    int status;
    
    pid = fork();
    if(pid == 0 ){ 
        if(execvp(args[0], args) == -1){ // execvp is a function that executes a file
            perror(ANSI_COLOR_RED "lsh" ANSI_COLOR_RESET); // perror is a function that prints a system error message
        }
        exit(EXIT_FAILURE);
    }else if(pid < 0){
        perror(ANSI_COLOR_RED "Error forking " ANSI_COLOR_RESET); 
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED); // waitpid is a function that waits for a child process to change state
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, ANSI_COLOR_RED "lsh: expected argument to \"cd\"\n" ANSI_COLOR_RESET);
    }else{
        if(chdir(args[1]) != 0){
            perror(ANSI_COLOR_RED "lsh" ANSI_COLOR_RESET);
        }
    }
    return 1;
}

int lsh_mkdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, ANSI_COLOR_RED "lsh: expected argument to \"mkdir\"\n" ANSI_COLOR_RESET);
    }else{
        if(mkdir(args[1], 0777) != 0){
            perror(ANSI_COLOR_RED "lsh" ANSI_COLOR_RESET);
        }
    }
    return 1;
}

int lsh_cat(char **args){
    if(args[1] == NULL){
        fprintf(stderr, ANSI_COLOR_RED "lsh: expected argument to \"cat\"\n" ANSI_COLOR_RESET);
    }else{
        FILE *file;
        char c;
        file = fopen(args[1], "r");
        if(file){
            while((c = getc(file)) != EOF){
                putchar(c);
            }
            fclose(file);
        }else{
            perror(ANSI_COLOR_RED "lsh" ANSI_COLOR_RESET);
        }
    }
    return 1;
}

int lsh_help(char **args){
    int i;
    printf(ANSI_COLOR_YELLOW "kernel's Shell\n" ANSI_COLOR_RESET);
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for(i = 0; i < lsh_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args){
    return 0;
}

int lsh_execute(char **args){
    int i;

    if(args[0] == NULL){
        return 1;
    }

    for(i = 0; i < lsh_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

int lsh_num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char *);
}

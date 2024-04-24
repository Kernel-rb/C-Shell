#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
#include <histedit.h>

// colors :
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"


int main(int argc , char** argv){
  // TODO: ASCII ART FOR Lipsy 
  puts(ANSI_COLOR_CYAN "===== Lispy v0.0.0.1 =====" ANSI_COLOR_RESET);
  puts(ANSI_COLOR_CYAN "===== Press CTRL + C or type 'exit' to quit =====" ANSI_COLOR_RESET);

  while(1){ 
    // TODO : fix mli knwrk 3la effacer tytms7 ta dak Lipsy 
    printf(ANSI_COLOR_YELLOW "Lipsy> " ANSI_COLOR_RESET);
    char *input = readline("");
    add_history(input);
    if(strcmp(input , "exit") == 0){
      exit(0);
    }
    printf("u write :  %s \n", input);
    free(input);
  };
  return 0 ;
}

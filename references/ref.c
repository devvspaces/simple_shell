#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 20

int main() {
    char input[1000];
    char *commands[50][MAX_ARGS];
    int cmd_count = 0;

    while (1) {
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';

        // Parse input into individual commands and arguments
        char *token = strtok(input, " ");
        while (token != NULL) {
            if (strcmp(token, "&&") == 0) {
                commands[cmd_count][0] = NULL; // Mark end of previous command
                cmd_count++;
            } else if (strcmp(token, "||") == 0) {
                commands[cmd_count][0] = NULL; // Mark end of previous command
                cmd_count++;
            } else {
                commands[cmd_count][0] = token;
                int arg_count = 1;
                while ((token = strtok(NULL, " ")) != NULL && arg_count < MAX_ARGS) {
                    commands[cmd_count][arg_count] = token;
                    arg_count++;
                }
                commands[cmd_count][arg_count] = NULL; // Mark end of arguments
            }
            token = strtok(NULL, " ");
        }
        commands[cmd_count][0] = NULL; // Mark end of final command

        // Execute commands
        int status;
        //pid_t pid;
        int i = 0;
      //   while (commands[i][0] != NULL) {
      //       pid = fork();
      //       if (pid == 0) {
      //           // Child process
      //           execvp(commands[i][0], commands[i]);
      //           perror("execvp error");
      //           exit(1);
      //       } else if (pid < 0) {
      //           perror("fork error");
      //           exit(1);
      //       } else {
      //           // Parent process
      //           wait(&status);
      //           if (WIFEXITED(status)) {
      //               int exit_status = WEXITSTATUS(status);
      //               if (strcmp(commands[i+1][0], "&&") == 0 && exit_status != 0) {
      //                   break; // Skip next command if previous command failed
      //               } else if (strcmp(commands[i+1][0], "||") == 0 && exit_status == 0) {
      //                   break; // Skip next command if previous command succeeded
      //               }
      //           }
      //           i++;
      //       }
      //   }
        cmd_count = 0;
    }

    return 0;
}

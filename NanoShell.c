/*
it passed all tests but i still did not implement the list from variable name like
x=home
ls/$x
suppose to list home

i will update when finished
ان شاء الله
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define count 8000
#define max_vars 100

struct local_var {
    char names[max_vars][500];
    char values[max_vars][500];
};

int main(int argc, char **argv)
{
    char buf[count];
    struct local_var vars;
    int var_count = 0;

    while (1) {
        printf("M-BOT ;) HEHEHEHE $ ");
        fgets(buf, count, stdin);

        buf[strcspn(buf, "\n")] = 0;

        if (strlen(buf) == 0)
            continue;

        if (strchr(buf, '=') != 0 && var_count < max_vars) {
            int i;
            int space_before = 0;
            for (i = 0; buf[i] != '='; i++) {
                if (buf[i] == ' ') {
                    space_before = 1;
                }
                vars.names[var_count][i] = buf[i];
            }
            vars.names[var_count][i] = 0;
            int j;
            i++;
            int space = 0;
            for (j = 0; buf[i] != '\0'; i++, j++) {
                if (buf[i] == ' ') {
                    space = 1;
                }
                vars.values[var_count][j] = buf[i];
            }
            if (space || space_before) {
                printf("Invalid command\n");
                var_count++;
            } else {
                printf("name: %s, value: %s\n", vars.names[var_count],
                       vars.values[var_count]);
                var_count++;
            }
        } else if (buf[0] == '$') {
            for (int m = 0; m < var_count; m++) {
                if (strcmp(vars.names[m], buf + 1) == 0) {
                    printf("%s\n", vars.values[m]);
                    continue;
                }
            }
        } else if (strncmp(buf, "export ", 7) == 0) {
            char env_str[1000];
            for (int m = 0; m < var_count; m++) {
                if (strcmp(vars.names[m], buf + 7) == 0) {
                    sprintf(env_str, "%s=%s", vars.names[m],
                            vars.values[m]);
                    putenv(env_str);
                    printf("Exported: %s\n", buf + 7);
                    break;
                }
            }
        } else if (strncmp(buf, "printenv", 8) == 0) {
            extern char **environ;
            if (strlen(buf) == 8) {
                for (int i = 0; environ[i] != NULL; i++) {
                    printf("%s\n", environ[i]);
                }
            } 
        } else if (strncmp(buf, "echo ", 5) == 0) {
            printf("%s\n", buf + 5);
        } else if (strcmp(buf, "pwd") == 0) {
            if (getcwd(buf, sizeof(buf)) != NULL) {
                printf("%s\n", buf);
            } else {
                printf("pwd: error getting directory\n");
            }
        } else if (strncmp(buf, "cd ", 3) == 0) {
            if (chdir(buf + 3) != 0) {
                printf("cd: cannot change directory\n");
            }
        } else if (strcmp(buf, "exit") == 0) {
            printf("Good Bye :)\n");
            return 0;
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}

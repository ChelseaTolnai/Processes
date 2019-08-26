// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as 
// `execl()`, `execle()`, `execv()`, and others. Why do you think there 
// are so many variants of the same basic call?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    fork();
    
    // EXECL
    // execl(const char *path, const char *arg, ...);
    // Good if you want a specific known argument or know how many args there will be
    
    // const char *arg[] = {"/bin/ls", NULL};
    // execl("/bin/ls", arg[0], arg[1], NULL);



    // EXECLP
    // execlp(const char *file, const char *arg, ...);
    // Good if using file instead of path



    // EXECLE
    // execle (const char *path, const char *arg, ..., char * const envp[]);
    // Good for specifying the environment of the executed program 

    // const char *arg[] = {"/bin/ls", NULL};
    // char *const envp[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};
    // execle("/bin/ls", arg[0], arg[1], NULL, envp);



    // EXECV
    // execv(const char *path, char *const argv[]);
    // Good if you want to use all arguments or don't specifically know how many arguments there may be

    char *const argv[] = {"/bin/ls", NULL};
    // execv("/bin/ls", argv);
    execv(argv[0], argv);



    // EXECVP
    // execvp(const char *file, char *const argv[]);
    // Good if using file instead of path



    // EXECLP
    // execvpe(const char *file, char *const argv[], char *const envp[]);
    // Good if using file instead of path and setting environment



    return 0;
}


// RETURNS
// ex4.c   main
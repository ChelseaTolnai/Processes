// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory 
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor 
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    // Writes to text.txt file "Hello, C!"
    FILE *fp;
    fp = fopen("text.txt", "r+");
    fprintf(fp, "%s", "Hello, C!");
    fclose(fp);
    
    // Forks and reads file "Hello, C!"
    // Happens twice because of fork.
    int rc = fork();
    fp = fopen("text.txt","r");
    printf("AFTER FORK: \n");
    while(1) {
        char c = fgetc(fp);
        if( feof(fp) ) { 
            break ;
        }
        printf("%c", c);
    }
    printf("\n");
    fclose(fp);

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        fp = fopen("text.txt","r");
        printf("CHILD READ: \n");
        while(1) {
            char c = fgetc(fp);
            if( feof(fp) ) { 
                break ;
            }
            printf("%c", c);
        }
        printf("\n");
        fclose(fp);

        fp = fopen("text.txt", "r+");
        fprintf(fp, "%s", "Hello, C! From Child");
        fclose(fp);

        fp = fopen("text.txt","r");
        printf("CHILD READ AFTER WRITE: \n");
        while(1) {
            char c = fgetc(fp);
            if( feof(fp) ) { 
                break ;
            }
            printf("%c", c);
        }
        printf("\n");
        fclose(fp);
    } else {
        fp = fopen("text.txt","r");
        printf("PARENT READ: \n");
        while(1) {
            char c = fgetc(fp);
            if( feof(fp) ) { 
                break ;
            }
            printf("%c", c);
        }
        printf("\n");
        fclose(fp);

        fp = fopen("text.txt", "r+");
        fprintf(fp, "%s", "Hello, C! From Parent");
        fclose(fp);

        fp = fopen("text.txt","r");
        printf("PARENT READ AFTER WRITE: \n");
        while(1) {
            char c = fgetc(fp);
            if( feof(fp) ) { 
                break ;
            }
            printf("%c", c);
        }
        printf("\n");
        fclose(fp);
    }
    return 0;
}


// RETURNS TWO DIFFERENT OPTIONS BASED ON WHAT PROCESS OCCURS FIRST
// Both reads file twice first due to fork
// Then Both read original file.
// Then Both write in the file.
// ==>  If parent first it writes "Hello, C! From Parent"
//      Then Child writes "Hello, C! From Childt" (remaining 't' because parent's string length greater)
// ==>  If child first it writes "Hello, C! From Child"
//      Then Child writes "Hello, C! From Parent" 
// Then Both read the newly written file after both child and parent finish writing

// PARENT FIRST
// AFTER FORK: 
// AFTER FORK: 
// Hello, C!
// Hello, C!
// PARENT READ: 
// CHILD READ: 
// Hello, C!
// Hello, C!
// CHILD READ AFTER WRITE: 
// PARENT READ AFTER WRITE: 
// Hello, C! From Childt
// Hello, C! From Childt

// CHILD FIRST
// AFTER FORK: 
// AFTER FORK: 
// Hello, C!
// Hello, C!
// CHILD READ: 
// PARENT READ: 
// Hello, C!
// Hello, C!
// PARENT READ AFTER WRITE: 
// CHILD READ AFTER WRITE: 
// Hello, C! From Parent
// Hello, C! From Parent


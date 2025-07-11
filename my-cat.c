//Project 1: Warmup to C and Unix programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    FILE *fptr;
    char *part =NULL;
    size_t len =0;
    ssize_t line;

    // Check if the file can be oppened

    if (argc == 1){
        return 0;
    }

    for (int i = 1; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-cat: cannot open file %s\n", argv[1]);
            exit(1);
        }
        else{
            //Loop through file lines and print them
            while ((line = getline(&part, &len, fptr)) != -1){
                printf("%s", part);
            }
            fclose(fptr);
            free(part);
        }
    }
    return 0;
}
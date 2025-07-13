//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//still needs expections, details, comments
int main (int argc, char *argv[]) {

    FILE *fptr;
    char *part =NULL;
    size_t len =0;
    ssize_t line;

    // Check if the file can be oppened

    if (argc == 1){
        return 0;
    }

    char *word = argv[1];

    for (int i = 2; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-grep: cannot open file %s\n", argv[i]);
            exit(1);
        }
        else{
            //Loop through file lines and print lines if word is found
            while ((line = getline(&part, &len, fptr)) != -1){
                if(strstr(part,word)!=NULL){
                    printf("%s", part);
                }
            }
            fclose(fptr);
            free(part);
        }
    }
    return 0;
}
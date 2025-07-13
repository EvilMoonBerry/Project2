//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//still needs expections, details, comments

//loops through words in line and prints 4 byte version to user. 
//tabs? writing to file? is the format correct
int zipWord(char * s)
{
    int i = 0;
    //char newLine = []
    while(i<strlen(s)){
        int j = 1;
        while(s[i]==s[i+j]){
            j++;
        }
        if(s[i]== ' '){
            printf(" ");
        }else{
            printf("%d%c",j,s[i]);
        }
        i+=j;
    }
    return 0;
}

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
                zipWord(part);
            }
            fclose(fptr);
            free(part);
        }
    }
    return 0;
}
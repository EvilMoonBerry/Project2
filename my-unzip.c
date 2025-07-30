//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int unzipWord(char *s)
{

    int i = 0;
    char character;
    
    while(i<strlen(s)){
        int x = 0;
        // Parse number and charachter combination
        while(isdigit(s[i])){
            x = x *10+(s[i]-'0');
            i++;
        }

        character = s[i];
        //Print the charachter x times for user to see
        for(int j = 0; j < x; j++){
            printf("%c",character);
        }

        i++;
    }
    return 0;
}

int main (int argc, char *argv[]) {

    FILE *fptr;
    char *part =NULL;
    size_t len =0;
    ssize_t line;
    
    //Error if user does not give enough arguments
    if (argc == 1){
        printf("my-unzip: file1 [file2 ...]");
        exit(1);
    }
    //Loop through input files
    for (int i = 1; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[1]);
            exit(1);
        }
        else{
            //Loop through file lines
            while ((line = getline(&part, &len, fptr)) != -1){
                unzipWord(part);
            }
            fclose(fptr);
        }
    }
    free(part);

    return 0;
}
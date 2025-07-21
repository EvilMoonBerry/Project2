//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//still needs expections, details, comments, 


// write in file in a new format
int unzipWord(char *s)
{

    int i = 0;
    
    while(i<strlen(s)){
        int j = 1;
        while(s[i]==s[i+j]){
            j++;
        }
        
        for(int x=0;x<=j;++x){
            printf("%c",s[i]);
        }
        //}

        i+=j;
    }
    return 0;
}

int main (int argc, char *argv[]) {

    FILE *fptr;
    char *part =NULL;
    size_t len =0;
    ssize_t line;
    

    if (argc == 1){
        printf("my-unzip: file1 [file2 ...]");
        exit(1);
    }

    for (int i = 1; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[1]);
            exit(1);
        }
        else{
            //Loop through file lines
            printf(argv[i]);
            while ((line = getline(&part, &len, fptr)) != -1){
                unzipWord(part);
            }
            fclose(fptr);
        }
    }
    free(part);

    return 0;
}
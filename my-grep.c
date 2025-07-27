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
    //FILE *input_fp =NULL;
    char *inputfiles;
    char *inputfile = NULL;
    size_t input_len = 0;
    char *token;
    int found =0;
    char *copy_part;

    // Check if the file can be oppened

    if (argc == 1){
        fprintf(stderr, "my-grep: searchterm [file ...]");
        exit(1);
    }

    char *word = argv[1];

    if(argc == 2){
        ssize_t partsread = getline(&inputfile, &input_len, stdin);
            if (partsread == -1) {
                fprintf(stderr, "Failed to read filename\n");
                exit(1);
            }
        inputfile[strcspn(inputfile, "\n")] = '\0';

//https://opensource.com/article/22/4/parsing-data-strtok-c 
//https://cboard.cprogramming.com/c-programming/138566-string-search-strstr.html 
        inputfiles = strtok(inputfile," ");
            
        while (inputfiles){
             fptr = fopen(inputfiles, "r");
            if (fptr == NULL) {
                fprintf(stderr, "my-grep: cannot open file %s\n", inputfiles);
                exit(1);
            }
            else{
                //fix this like in the other part of the code. Now this finds other words that contain the searched word in the word
                //Loop through file lines and print lines if word is found
                while ((line = getline(&part, &len, fptr)) != -1){
                    if(strstr(part,word)!=NULL){
                        printf("%s", part);
                    }
                }
            }
            inputfiles=strtok(NULL," ");
        }
    }

    for (int i = 2; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-grep: cannot open file %s\n", argv[i]);
            exit(1);
        }
        else{
            //Loop through file lines and print lines if word is found
            while ((line = getline(&part, &len, fptr)) != -1){
                //https://stackoverflow.com/questions/14020380/strcpy-vs-strdup 
                copy_part = strdup(part);
                token = strtok(copy_part, " ,.!?;:(){}[]+\"\"\n\t\r");
                found = 0;
                while(token !=NULL){
                    if(strcmp(token,word)==0){
                        found = 1;
                        break;
                    }
                    token=strtok(NULL," ,.!?;:(){}[]+\"\"\n\t\r");
                }
                if(found){
                    printf("%s",part);
                }
            }
        }
        fclose(fptr);
    }
    free(part);
    return 0;
}
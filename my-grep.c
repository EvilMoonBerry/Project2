//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {

    FILE *fptr;
    char *part =NULL;
    size_t len =0;
    ssize_t line;
    char *inputfile = NULL;
    size_t input_len = 0;
    char *token;
    int found =0;
    char *copy_part;
   
    //Error if user does not give enough arguments
    if (argc == 1){
        fprintf(stderr, "my-grep: searchterm [file ...]");
        exit(1);
    }

    //Word that is looked for
    char *word = argv[1];

    //Error If user tries to search " "
    if (strlen(word)==0){
        fprintf(stderr, "my-grep: searchterm cannot be empty");
        exit(1);
    }

    //If user gives only word to search ask for files where the word is searched 
    if(argc == 2){
        ssize_t partsread = getline(&inputfile, &input_len, stdin);
        if (partsread == -1) {
            fprintf(stderr, "Failed to read filename\n");
            exit(1);
        }

        //Strip users’ input of newline
        inputfile[strcspn(inputfile, "\n")] = '\0';
        char * start = inputfile;

        // if user gives more than one file name separate them and loop through all file names
        while (*start != '\0') {

            while(*start ==' ')start++;
            if(*start =='\0'){
                break;
            }
            char *end =start;
            while (*end != ' ' && *end !='\0') end++;

            char saved = *end;
            *end = '\0';

            printf("Reading file: [%s]\n", start);

            fptr = fopen(start, "r");
            if (fptr == NULL) {
                fprintf(stderr, "my-grep: cannot open file %s\n", start);
                exit(1);
            }
            //Loop through file lines and print lines if word is found
            while ((line = getline(&part, &len, fptr)) != -1){
            //https://stackoverflow.com/questions/14020380/strcpy-vs-strdup 
            copy_part = strdup(part);
            if(!copy_part){
                fprintf(stderr, "memory allocation failed copy_part\n");
                exit(1);
            }
            //Divide a line from file to words and compare them to the searched word. If match print that line and repeat
            //https://opensource.com/article/22/4/parsing-data-strtok-c 
            token = strtok(copy_part, " ,.!?;:(){}[]+\"\"\n\t\r");
            found = 0;
            while(token !=NULL){
                if(strcmp(token,word)==0){
                    found = 1;
                    break;
                }
                token=strtok(NULL, " ,.!?;:(){}[]+\"\"\n\t\r");
            }
            if(found){
                printf("%s",part);
            }
            free(copy_part);
        
            }
            fclose(fptr);
            *end =saved;
            start = end;
    }
    }else{

        for (int i = 2; i< argc;i++){
            fptr = fopen(argv[i], "r");
            if (fptr == NULL) {
                fprintf(stderr, "my-grep: cannot open file %s\n", argv[i]);
                exit(1);
            }
            //Loop through file lines and print lines if word is found
            while ((line = getline(&part, &len, fptr)) != -1){
                //https://stackoverflow.com/questions/14020380/strcpy-vs-strdup 
                copy_part = strdup(part);
                //Divide a line from file to words and compare them to the searched word. If match print that line and repeat
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
                free(copy_part);
            }
            fclose(fptr);
            }
    }
    free(part);
    free(inputfile);
    return 0;
}

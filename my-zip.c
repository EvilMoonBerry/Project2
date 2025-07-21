//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//still needs expections, details, comments, 


// write in file in a new format
int zipWord(char *s, FILE *fp)
{
    
    int i = 0;
    
    while(i<strlen(s)){
        int j = 1;
        while(s[i]==s[i+j]){
            j++;
        }
        /*if(s[i]== ' '){
            fwrite(" ",1,1,fp);
        }// this does not seem to work. Do I need this?
        else if ((s[i]== '\t')) {
            fwrite("\t",1,1,fp);
        }
        else if ((s[i]== '\n')) {
            fwrite("\n",1,1,fp);
        }
        else{*/
            //printf("%d%c",j,s[i]);
            int test = snprintf(NULL,0,"%d%c",j,s[i]);
            char *ziptext = malloc(test +1);
            if(!ziptext){
                fprintf(stderr, "error: malloc fail");
                exit(1);
            }
            sprintf(ziptext,"%d%c",j,s[i]);
            fwrite(ziptext,1,strlen(ziptext),fp);
            free(ziptext);
        //}

        i+=j;
    }
    return 0;
}

int main (int argc, char *argv[]) {

    FILE *fptr;
    FILE *output_fp =NULL;
    char *part =NULL;
    size_t len =0;
    ssize_t line;
    char *zipfile = NULL;
    size_t input_len = 0;

    if (argc == 1){
        printf("my-zip: file1 [file2 ...]");
        exit(1);
    }

    if (!isatty(fileno(stdout))){
        output_fp = stdout;
    } else{
        
    // Check if the file can be oppened
        ssize_t partsread = getline(&zipfile, &input_len, stdin);
            if (partsread == -1) {
                fprintf(stderr, "Failed to read filename\n");
                exit(1);
            }
        zipfile[strcspn(zipfile, "\n")] = '\0';

        output_fp = fopen(zipfile,"w");

        if(!output_fp){
            fprintf(stderr, "my-zip: cannot open file %s\n", zipfile);
            exit(1);
        }
    }

    for (int i = 1; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-zip: cannot open file %s\n", argv[1]);
            exit(1);
        }
        else{
            //Loop through file lines
            printf(argv[i]);
            while ((line = getline(&part, &len, fptr)) != -1){
                zipWord(part,output_fp);
            }
            fclose(fptr);
        }
    }
    free(part);

    return 0;
}
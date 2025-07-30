//Project 2: Unix Utilities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// write in file in a new format
int zipWord(char *s, FILE *fp)
{
    
    int i = 0;
    
    while(i<strlen(s)){
        int j = 1;

        //How many times the charachter repeats consecutively
        while(s[i]==s[i+j]){
            j++;
        }
            int test = snprintf(NULL,0,"%d%c",j,s[i]);
            //Memory allocation
            char *ziptext = malloc(test +1);
            if(!ziptext){
                fprintf(stderr, "error: malloc fail");
                exit(1);
            }
            //Formatting and writing it to file
            sprintf(ziptext,"%d%c",j,s[i]);
            fwrite(ziptext,1,strlen(ziptext),fp);
            free(ziptext);
        }

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

    if (argc < 2){
        printf("my-zip: file1 [file2 ...]");
        exit(1);
    }

    //if outputfile has been given use stdout
    if (!isatty(fileno(stdout))){  //https://www.man7.org/linux/man-pages/man3/isatty.3.html //https://man7.org/linux/man-pages/man3/fileno.3.html 
        output_fp = stdout;
    } 
    //If user does not give outputfile ask for it
    else{
    // Check if the file can be oppened
        ssize_t partsread = getline(&zipfile, &input_len, stdin);
            if (partsread == -1) {
                fprintf(stderr, "Failed to read filename\n");
                exit(1);
            }
        //Strip users’ input of newline
        zipfile[strcspn(zipfile, "\n")] = '\0';
        //Error if file can not be opened
        output_fp = fopen(zipfile,"w");
        if(!output_fp){
            fprintf(stderr, "my-zip: cannot open file %s\n", zipfile);
            exit(1);
        }
    }

     // Check if the input file can be oppened
    for (int i = 1; i< argc;i++){
        fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            fprintf(stderr, "my-zip: cannot open file %s\n", argv[1]);
            exit(1);
        }
        else{
            //Loop through file lines
            while ((line = getline(&part, &len, fptr)) != -1){
                zipWord(part,output_fp);
            }
            fclose(fptr);
        }
    }
    free(part);

    return 0;
}
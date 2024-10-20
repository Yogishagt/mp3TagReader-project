#include<stdio.h>
#include "view.h"
#include "edit.h"
#include<stdlib.h>

int main(int argc, char *argv[]){
    char *mode=argv[1];
    if(argc<3){
        printf("------------------------------------------------------------------------------\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE\n");
        printf("To view please pass like : ./a.out -v mp3filename\n");
        printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("To get help pass like : ./a.out --help\n");
        printf("------------------------------------------------------------------------------\n");
        return 0;
    }
    // check for CLA [-v]
    if(!strcmp(mode,"--help")){
        helpMenu();
    }
    else if(!strcmp(mode,"-v")){
        // declaring the structure 
        Details detail;
        // storing the  filename in the structure
        strcpy(detail.filename,argv[2]);

        if(readAndValidation(argc,argv,&detail) ==1){
            // call the function
            mp3View(&detail);
        }
        else{
            printf("INFO: Error in reading file\n");
            return 0;
        }
        // closing the file
        fclose(detail.file);
    }
    // check for CLA[-e]
    if(!strcmp(mode,"-e")){
        if(argc <= 4 ){
            printf("------------------------------------------------------------------------------\n");
            printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE\n");
            printf("To view please pass like : ./a.out -v mp3filename\n");
            printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
            printf("To get help pass like : ./a.out --help\n");
            printf("------------------------------------------------------------------------------\n");
            return 0;
        }
        // declaring the structure 
        Detail detail;
        Details detailEdit;
        // storing the  filename in the structure
        strcpy(detail.filename,argv[4]);
        
        strcpy(detailEdit.filename,argv[4]);

        strcpy(detail.editMode,argv[2]);

        if(readAndValidation(argc,argv,&detailEdit) ==1){
            // call the function
            
            mp3Edit(&detail,argv[3]);
        }
        else{
            printf("INFO: Error in reading file\n");
            return 0;
        }
    }
}



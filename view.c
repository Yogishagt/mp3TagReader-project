#include "view.h"

void dispayMp3(Details *detail){
    printf("---------------SELECTED VIEW DETAILS----------------\n");
    printf("------------------------------------------------------------\n");
    printf("        MP3 TAG READER AND EDITOR FOR IB3V2\n");
    printf("------------------------------------------------------------\n");
    printf("TITLE           :   %.30s\n", strtok(detail->title, "-"));
    printf("ARTIST          :   %-.30s\n",strtok(detail->artist, "-"));
    printf("ALBUM           :   %-.30s\n",strtok(detail->album, "-"));
    printf("YEAR            :   %-.4s\n",detail->year);
    printf("MUSIC           :   %-.30s\n",strtok(detail->music, "-"));
    printf("COMMENT         :   %-.30s\n",strtok(detail->comment, "-"));
    printf("-------------------------------------------------------------\n");
    printf("---------------DETAILS DISPLAYED SUCCESSFULLY----------------\n");
}

int readAndValidation(int argc,char *argv[],Details *detail){
    // open mp3 file -> fopen (read mode)
    detail->file=fopen(detail->filename,"r");
    if(detail->file==NULL){
        printf("INFO: Error oprning file\n");
        return 0;
    }
    fseek(detail->file,0,SEEK_SET);
    // check ID3
    char ID3[5];
    fread(ID3,sizeof(char),3,detail->file);
    // printf("id -> %s\n",ID3);
    if(argc<=2){
        printf("INFO: Insuffcient  arguments\n");
        printf("INFO: Error: no filename provided\n");
    }
    else if(strstr(ID3,"ID3")){
        // check version (03 00)
        char version[2];
        fread(version,1,2,detail->file);
        if(version[0]==3 &&  version[1]==0){
            // check for extention (.mp3)
            if(strstr(detail->filename,".mp3")){
                return 1;
            }
            else{
                printf("INFO: File is not a mp3 file!\n");
                return  0;
            }
        }
        else{
            printf("INFO: Version not matched!\n");
            return 0;
        } 
    }
    else{
        printf("INFO: ID3 tag not found\n");
        return 0;
    }
}

void  checkTag(Details *detail){

    // reading the tag  from the file
    fread(detail->tag,1,4,detail->file);

    // terminating the tring with null  character
    detail->tag[4]='\0';
}

void readSize(Details *detail){
    // reading the size of the tag
    fread(&detail ->size,sizeof(detail ->size),1,detail->file);
    detail ->size=bswap_32(detail ->size);

    // skip 1 byte for null character and 2 byte for flag
    fseek(detail->file,3,SEEK_CUR);
}

int mp3View(Details *detail){
    // skip header 
    fseek(detail->file,10,SEEK_SET);
    
    // function call
    checkTag(detail);

    if(!strcmp(detail->tag,"TIT2")){
        //function call
        readSize(detail);
        // reading title 
        fread(detail->title, 1,detail ->size-1,detail->file);
        // function call
        checkTag(detail);

        if(!strcmp(detail->tag,"TPE1")){
            // function call
            readSize(detail);

            // reading  artist name
            fread(detail->artist,1,detail ->size-1,detail->file);

            // function call
            checkTag(detail);
            
            if(!strcmp(detail->tag,"TALB")){
                // function call
                readSize(detail);

                // reading the album name
                fread(detail->album,1,detail ->size-1,detail->file);

                // function call
                checkTag(detail);
                
                if(!strcmp(detail->tag,"TYER")){
                    // function call
                    readSize(detail);

                    // reading the year
                    fread(detail->year,1,detail ->size-1,detail->file);

                    // function call
                    checkTag(detail);
                    

                    if(!strcmp(detail->tag,"TCON")){
                        // function call
                        readSize(detail);

                        // reading the commant
                        fread(detail->music,1,detail ->size-1,detail->file);

                        // function call
                        checkTag(detail);
                        
                        if(!strcmp(detail->tag,"COMM")){
                            // function call
                            readSize(detail);

                            // reading the comment
                            fread(detail->comment,1,detail ->size-8,detail->file);

                            //calling the display function
                            dispayMp3(detail);

                        }
                        else{
                            printf("INFO: Error COMM tag not found!\n");
                            return  0;
                        }
                    }
                    else{
                        printf("INFO: Error TCON tag not found!\n");
                        return 0;
                    }
                }
                else{
                    printf("INFO: Error TYER tag not found!\n");
                    return 0;
                }
            }
            else{
                printf("INFO: Error TALB tag not found!\n");
                return 0;
            }
        }
        else{
            printf("INF: Error TPE1 tag not found!\n");
            return 0;
        }

    }
    else{
        printf("INFO: Error TIT2 tag not found!\n");
        return 1;
    }
    return 0;
}

void helpMenu(){
    printf("------------------------------HELP MENU------------------------------\n");
    printf("1. -v -> to view the mp3 file contects\n");
    printf("2. -e -> to edit the mp3 file contects\n");
    printf("         2.1. -t -> edit song title\n");
    printf("         2.2. -a -> edit artist name\n");
    printf("         2.3. -A -> edit albun name\n");
    printf("         2.4. -y -> edit year\n");
    printf("         2.5. -m -> edit content\n");
    printf("         2.1. -c -> edit comment\n");
}
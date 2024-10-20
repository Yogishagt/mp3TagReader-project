#include "edit.h"
void copy_data(int i,Detail *detail){
    char ch;
    while(i){
        fread(&ch,sizeof(ch),1,detail->file);
        fwrite(&ch,sizeof(ch),1,detail->dup_file);
        i--;
    }
}
void copy_remaining(Detail *detail){
    char ch;
    while((fread(&ch,1,1,detail->file)) > 0){
        fwrite(&ch,1,1,detail->dup_file);
    }
}

void copy_back(Detail * detail){
    // copying data form duplicate file source file
    //closeing the  source file
    fclose(detail->file);

    // opening the  file in write to cpoy back
    detail->file=fopen(detail->filename,"w");
    if(detail->file==NULL){
        printf("INFO: Error in oprning file\n");
        return;
    }

    char ch;
    fseek(detail->file,0,SEEK_SET);
    fseek(detail->dup_file,0,SEEK_SET);
    while((fread(&ch,1,1,detail->dup_file)) > 0){
        fwrite(&ch,1,1,detail->file);
    }
    fclose(detail->dup_file);
    fclose(detail->file);
}

void copy_tagDetail(int  i,Detail *detail){
    // read size
    fread(&detail ->size,sizeof(detail ->size),1,detail->file);
    detail ->size=bswap_32(detail ->size);
    fseek(detail->file,-4,SEEK_CUR);
    copy_data((i+detail->size+4-1),detail);
}

void readSize_andCopy(int i, Detail *detail){
    // moving file stream 7  bytes back
    fseek(detail->file,-7,SEEK_CUR);

    // read size
    fread(&detail ->size,sizeof(detail ->size),1,detail->file);
    // swaping  the size for  little to big
    detail ->size=bswap_32(detail ->size);
    fseek(detail->file,3,SEEK_CUR);
    // function call
    copy_data((i+detail->size+4-1),detail);
}

void edit(char *newvalue,char *title, Detail *detail){
    // read size
    uint32_t size=strlen(newvalue);
    size +=1;
    size=bswap_32(size);

    // reading the size of previous title 
    fread(&detail ->size,sizeof(detail ->size),1,detail->file);
    // swaping  the size to  little endien
    detail ->size=bswap_32(detail ->size);

    fwrite(&size,sizeof(size),1,detail->dup_file);

    // cpoying the flag and null (3 byte)
    // function calling
    copy_data(3,detail);

    // writing the new  title 
    fwrite(newvalue, 1,strlen(newvalue),detail->dup_file);

    fseek(detail->file,detail->size-1,SEEK_CUR);

    // calling the function
    copy_remaining(detail);

    //calling function
    copy_back(detail);

    // calling function 
    display(newvalue,"TITLE",detail);
}

void display(char *change,char *title, Detail * detail){
    printf("------------------------SELECTED EDIT DETAILS---------------------------------\n\n");
    printf("-----------SELECTED EDIT OPTION-----------\n\n");
    printf("-----------CHANGE THE %s--------------\n\n",title);
    printf("%s : %s\n",title,change);
    printf("\n-----------%s CHANGED SUCCESSFYLLY---------------------------------------\n",title);
}

int mp3Edit(Detail *detail,char *newvalue){
    // opening the  file in write and read mode
    detail->dup_file=fopen("dup_new.mp3","w+");
    if(detail->file==NULL){
        printf("INFO: Error in oprning file\n");
        return 0;
    }
    // opening the  file in write and read mode
    detail->file=fopen(detail->filename,"r");
    if(detail->file==NULL){
        printf("INFO: Error oprning file\n");
        return 0;
    }

    //coping the 10 bytes header and 4 bytes tag
    // function calling
    copy_data(14,detail);
   
        
    if(!strcmp(detail->editMode,"-t")){
        //function call
        edit(newvalue,"TITLE",detail);
    }
    else if(!strcmp(detail-> editMode,"-a")){

        // function call
        copy_tagDetail(7,detail);

        //function call
        edit(newvalue,"ARTIST",detail);
    }
    else if(!strcmp(detail-> editMode,"-A")){
        // function call
        copy_tagDetail((7+7),detail); // 7 for size of  artist and flag's

        //function call 
        readSize_andCopy(0,detail);

        //function call
        edit(newvalue,"ALBUM",detail); 
    }
    else if(!strcmp(detail-> editMode,"-y")){
        // function call
        copy_tagDetail((7+7),detail); // 7 for size of  artist and flag's

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(0,detail);

        //function call
        edit(newvalue,"YEAR",detail); 
    }
    else if(!strcmp(detail-> editMode,"-m")){
        // function call
        copy_tagDetail((7+7),detail); // 7 for size of  artist and flag's

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(0,detail);

        //function call
        edit(newvalue,"MUSIC",detail);        
    }
    else if(!strcmp(detail-> editMode,"-c")){
        // function call
        copy_tagDetail((7+7),detail); // 7 for size of  artist and flag's

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(7,detail);

        //function call 
        readSize_andCopy(0,detail);

        //function call
        edit(newvalue,"COMMENT",detail); 
    }
    else{
        printf("INFO: Invalid Command Line  Argument\n");
        return 0;
    }      
    return 0;
}


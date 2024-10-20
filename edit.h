#include<stdio.h>
#include <stdint.h>
#include<string.h>
#include <stdlib.h>
#include <byteswap.h>

typedef struct Detail{
    FILE *file;
    FILE *dup_file;
    uint32_t size;
    char filename[50];
    char editMode[4];
} Detail;

/*to edit the mp3 file details*/
int mp3Edit(Detail *detail,char *newvalue);

/*to edit  the mp3 file details*/
void edit(char *newvalue,char *title, Detail *detail);

/*copy the i number of  bytes from file to the duplicate file*/
void copy_data(int i,Detail *detail);

/*to copy the remaining  data from the file to the duplicate file*/
void copy_remaining(Detail *detail);

/*to display the edit detail*/
void display(char *change,char *title, Detail * detail);

/*to copy back  the data from duplicate file to the original file*/
void copy_back(Detail * detail);

/*to read size of detail and copy detail*/
void readSize_andCopy(int i, Detail *detail);
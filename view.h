#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include <byteswap.h>

typedef struct Details{
    char title[50];
    char artist[50];
    char album[50];
    char year[50];
    char music[50];
    char comment[50];
    char tag[5];
    uint32_t size;
    FILE *file;
    char filename[50];
    char editMode[4];
} Details;

/*to Read and validate view args from argv*/
int readAndValidation(int argc,char *argv[],Details *detail);

/*to check tag*/
void  checkTag(Details *detail);

/*to read the size of tag*/
void readSize(Details *detail);

/*to  get the details of the song from the file*/
int mp3View(Details *detail);

/*to display  the details of the song*/
void dispayMp3(Details *detail);

void helpMenu();
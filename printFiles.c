/* Name:        Yousuf Rajput
 *
 * FileName:    printFiles.c
 *
 * Description: This file contains the function to make the 
 *              tree that has the directoires and files
 *
 * Date:        November 26, 2018
 *
 * ID:          cs30ffh
 *
 * Sources: write up, di, stackOF
 */


#include "pa4.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pa4Strings.h"
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define  TIME_FORMAT "%b %e %H:%M "



/* Prototype:   void printFiles(const struct fileInfo *fi, int showHidden,
 *              int showLongFmt,int indent)
 *
 * Description: 
 *
 * Paramters:   fi - the name of file of root of tree
 *              showHidden - if we want to show the hidden files
 *              showLongFmt - if we want to show the files in long format 
 *              indent - if we want to indent the files
 *
 * Return:      returns void
 *  
 */


void printFiles(const struct fileInfo *fi, int showHidden,
        int showLongFmt,int indent){

    char space[BUFSIZ] = "";
    

    for(int i = 0;i < indent;++i){
        //space = space + " ";  
        strcat(space," ");
    }

    //check if a file is hidden
    if(showHidden || !isHidden(fi->filename)){

        //check if we want to print the long format 
        if(showLongFmt){

            //print all members requried by the long format
            printPermissions(fi->mode);
            printf(STR_PWNAME,getpwuid(fi->uid)->pw_name);
            printf(STR_GNAME,getgrgid(fi->gid)->gr_name);
            printf(STR_SIZE,fi->size);
            
            //print the time format 
            struct tm *timeStruct = localtime(&(fi->time));
            char buffer[MAXLEN];
            strftime(buffer,MAXLEN, TIME_FORMAT,timeStruct);
            printf("%s" , buffer);
        }

        //print the name of the file
        printf("%s%s\n",space,fi->filename); 

    }

    //check if the file is a directory
    if(fi->isDir){

        //loop through children of the file
        for(int i = 0; i < fi->childrenSize; i++){
            
            printFiles(fi->children[i],showHidden,showLongFmt,indent + 1);       
        }

    }

}


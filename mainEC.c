/* Name:        Yousuf Rajput
 *
 * FileName:    main.c
 *
 * Description: This file contains the main for the 
 *              program. We do error checking and check for
 *              the input of the flags 
 *
 * Date:        November 28, 2018
 *
 * ID:          cs30ffh
 *
 *
 */


#include "pa4.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pa4Strings.h"
#include <dirent.h>
#include <getopt.h>
#define NEG_ONE -1
#define NULL_CHAR '\0'


/* Prototype:   int main(int argc, char *argv[])
 *
 * Description: This main does a wide variety of error checking. This is to 
 *              assure that the arguments that are passed in are appropriate.
 *              For example, we want to make sure that the file passed in 
 *              exists and is not null. Also, we take care of passing in flags
 *              and making sure that the correct arguments for them are passed
 *              in as well.
 *
 * Paramters:  argc - number of arguments 
 *             argv - the arguments passed in
 *
 * Return:      int
 *  
 */
//struct fileInfo *buildFileTree(const char *filename,SortBy sortby, int rev);

int main(int argc, char *argv[]){
    //struct fileInfo *fileTree = buildFileTree(argv[1],NAME,1);
    //fileTree->isDir = 1;
    //printPermissions(0007);


    int option;
    char *fileName = NULL;

    int hiddenCheck = 0,countCheck = 0, longCheck = 0,revCheck = 0,timeCheck = 0;

    //loop through flags set 
    while((option = getopt(argc,argv,FLAGS)) != NEG_ONE){

        //carry out 
        switch(option){
            case FLAG_SHOWHIDDEN:
                hiddenCheck = 1; 
                break;

            case FLAG_COUNT:
                countCheck = 1;
                break;

            case FLAG_LONGFMT:
                longCheck  = 1;
                break;

            case FLAG_REVERSE:
                revCheck = 1;
                break;

            case FLAG_TIME:
                timeCheck = 1;
                break;

            case FLAG_HELP:
                fprintf(stderr,STR_USAGE,argv[0]);
                return EXIT_SUCCESS;
                //break;

            case FLAG_UNKNOWN:
                fprintf(stderr,STR_USAGE,argv[0]);
                return EXIT_FAILURE;
        }       


    }


    //checking for extraneuos args
    if(optind < argc){
        fprintf(stderr,STR_EXTRA_ARG,fileName);
        fprintf(stderr,STR_USAGE,argv[0]);
        return EXIT_FAILURE;
    }

    //check existence of a file
    if(fileName){
        if(access(fileName,F_OK) == -1){
            fprintf(stderr,ERR_DNE,fileName);
            return EXIT_FAILURE;
        }
    }

    else{
        fileName = STR_THIS;    
    }

    SortBy sortC =  (timeCheck == 1) ? TIME:NAME; 
    struct fileInfo *file = NULL;
    for(int i = 0; fileName != NULL_CHAR;i++){
        if(access(fileName,R_OK) == 0){
            file = buildFileTree(fileName,sortC,revCheck);  
        }
        fileName++;
    }
    //check if file is true
    if(file){
        //qsort if rev passed
        if(revCheck){
            //sort by name 
            if(sortC == NAME){
                qsort(file->children,file->childrenSize,
                    sizeof(struct fileInfo *),nameCompareRev);
            }

            //sort by the time
            if(sortC == TIME){
                qsort(file->children,file->childrenSize,
                    sizeof(struct fileInfo *),timeCompareRev);
            }
        }

        //check if sort will not be reversed
        else{

            //sort by name
            if(sortC == NAME){
                qsort(file->children,file->childrenSize,    
                    sizeof(struct fileInfo *),nameCompare);
            }

            //sort by the time
            if(sortC == TIME){
                qsort(file->children,file->childrenSize,
                    sizeof(struct fileInfo *),timeCompare);
            }
        }
        //check if we need count of files
        if(countCheck){
            fprintf(stdout,STR_COUNT,fileName,getFileCount(file));   

        }

        //loop thorugh tree and print files
        for(int i = 0; i < file->childrenSize; i++){

            printFiles(file->children[i],hiddenCheck,longCheck,0);       
        }
        
        //free and return upon success
        freeFileTree(file);
        return EXIT_SUCCESS;


    }


    //call to buildFileTree
    //fprintf(stdout, "revcheck is %d\n", revCheck);
    struct fileInfo *tree = buildFileTree(fileName,sortC,revCheck);

    //check to see if buildFileTree returns null
    if(!tree){
        return EXIT_FAILURE;    
    }

    //if -c is entered
    if(countCheck == 1){
        fprintf(stdout,STR_COUNT,fileName,getFileCount(tree));   
    }

    //call printFiles
    printFiles(tree,hiddenCheck,longCheck,0);

    //free the tree
    freeFileTree(tree);
}


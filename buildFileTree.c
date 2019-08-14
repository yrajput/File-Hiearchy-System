/* Name:        Yousuf Rajput
 *
 * FileName:    buildFileTree.c
 *
 * Description: This file contains the function to make the 
 *              tree that has the directoires and files
 *
 * Date:        November 26, 2018
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


/* Prototype:   struct fileInfo *buildFileTree(const char *filename,
 *                              SortBy sortby, int rev)
 *
 * Description: This function builds the tree of the directories and the files
 *              and then returns the pointer to the struct fileInfo. This
 *              function is called recursively to build the tree in
 *              pre-traversal order. We then order the directories in
 *              alphabetical order. 
 *
 * Paramters:   fileName - the name of file of root of tree
 *              sortby - sorted by name vs time
 *              rev - whether it needs to be in reverse order
 *
 * Return:      pointer to the root of the tree, filename
 *  
 */
struct fileInfo *buildFileTree(const char *filename,SortBy sortby, int rev){

    //dynamically allocate memory for one struct fileInfo
    struct fileInfo *tree = calloc(1,sizeof(struct fileInfo));
    //printf("%s\n",filename);

    //if alloc fails, print error
    if(!tree){
        perror(__func__);   
        return NULL;
    }

    //call getFileInfo to initialize members
    getFileInfo(tree,filename);

    //check if file is a directory
    DIR *currentFile = opendir(filename);

    //chck to see that the directory was opened
    if(!currentFile){
        return tree;    
    }

    //set isDir to be true
    tree->isDir = TRUE;

    //while loop for reading next sunfile using readdir
    struct dirent *subFile;
    while((subFile = readdir(currentFile)) != NULL){

        //if . or .., then skip the file
        if(strcmp(subFile->d_name,STR_THIS)!=0 && strcmp(subFile->d_name,STR_UP) != 0){

            //concatenate directory with the subfile name
            char buffer[MAXLEN];
            sprintf(buffer,FILE_CONCAT_FORMAT,tree->filename,subFile->d_name);

            //compare children size and children capacity to check for more room
            if(tree->childrenSize >= tree->childrenCapacity){

                //alloc space for children if it ran out
                struct fileInfo **temp= realloc(tree->children,
                        (tree->childrenCapacity+CHILDREN_INCREMENT)*sizeof(struct fileInfo *));

                //if realloc fails, free tree and return
                if(!temp){
                    if(!(tree->children)){
                        perror(__func__);
                        free(tree->children);

                    }
                    closedir(currentFile);
                    free(tree);
                    return NULL;
                }
                //increase capacity of children after realloc succeeds
                tree->children = temp;
                tree->childrenCapacity += CHILDREN_INCREMENT;

            }

            //call buildFileTree with new string
            tree->children[tree->childrenSize] = buildFileTree(buffer,sortby,rev);
            if(!tree->children[tree->childrenSize]){
                return NULL;    
            }

            //increment children size
            tree->childrenSize++;
        }
    }
    //close the directory
    closedir(currentFile);

    //check if sort will be reversed
    if(rev){
        //sort by name 
        if(sortby == NAME){
            qsort(tree->children,tree->childrenSize,sizeof(struct fileInfo *),nameCompareRev);
            return tree;
        }

        //sort by the time
        if(sortby == TIME){
            qsort(tree->children,tree->childrenSize,sizeof(struct fileInfo *),timeCompareRev);
            return tree;
        }
    }

    //check if sort will not be reversed
    else{

        //sort by name
        if(sortby == NAME){
            qsort(tree->children,tree->childrenSize,sizeof(struct fileInfo *),nameCompare);
            return tree;
        }

        //sort by the time
        if(sortby == TIME){
            qsort(tree->children,tree->childrenSize,sizeof(struct fileInfo *),timeCompare);
            return tree;
        }
    }

    //return the final tree with directories and the files
    return tree;











}




/* Name:        Yousuf Rajput
 *
 * FileName:    freeFileTree.c
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


/* Prototype:   void freeFileTree(struct fileInfo *fi)
 *
 * Description: This function builds the tree of the directories and the files
 *              and then returns the pointer to the struct fileInfo. This
 *              function is called recursively to build the tree in
 *              pre-traversal order. We then order the directories in
 *              alphabetical order. 
 *
 * Paramters:   fi - the root of the tree we want to free
 *             
 *
 * Return:      void
 *  
 */


void freeFileTree(struct fileInfo *fi){

    //loop thorugh the children of the directory
    for(int i = fi->childrenSize - 1; i >= 0; i--){

        //check if there exists children
        if(fi->children != NULL){
            return freeFileTree(fi->children[i]);    
        }


    }

    //free node
    free(fi);

    //reutrn upon completion of freeing
    return;
}


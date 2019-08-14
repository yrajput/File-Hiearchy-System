/* Name:        Yousuf Rajput
 *
 * FileName:    printPermissions.c
 *
 * Description: This file contains the function that prints out 
 *              the permissions of the mode passed in of the file
 *
 * Date:        November 26,2018
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


/* Prototype:   void printPermission(mode_t mode) 
 *
 * Description: This function is passed in the mode, which is used to 
 *              determine the permissions of the file, whether we can 
 *              read, write, or execute. We use the contants from stat 
 *              and then set teh correct permisison accordingly using the 
 *              provided constants in pa4.h
 *
 * Paramters:  mode - mode of permission 
 *
 * Return:     void
 *
 */
void printPermissions(const mode_t mode){


    //alloc space for the string that depicts permission
    char *string = (char *)malloc(sizeof(char));;

    //check if the mode indicates it is a directory
    if(S_ISDIR(mode))
        strcpy(string,D_PERMISSION);
    
    else
        strcpy(string,NO_PERMISSION);
    

    //user read permission check
    if(mode & S_IRUSR)
        strcat(string,R_PERMISSION);

    

    else
        strcat(string,NO_PERMISSION);
    

    //user write permission check
    if(mode & S_IWUSR)
        strcat(string,W_PERMISSION);

    

    else
        strcat(string,NO_PERMISSION);

    


    //user execute permission check
    if(mode & S_IXUSR)
        strcat(string,X_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //group read permission check
    if(mode & S_IRGRP)
        strcat(string,R_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //group write permission check
    if(mode & S_IWGRP)
        strcat(string,W_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //group exec permission check
    if(mode & S_IXGRP)
        strcat(string,X_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //other read permission check
    if(mode & S_IROTH)
        strcat(string,R_PERMISSION);

    

    else
        strcat(string,NO_PERMISSION);
    

    //other write permission check
    if(mode & S_IWOTH)
        strcat(string,W_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //other exec permission check
    if(mode & S_IXOTH)
        strcat(string,X_PERMISSION);
    

    else
        strcat(string,NO_PERMISSION);
    

    //print the string with all the permissions
    printf("%s ",string);

}

/* Name:        Yousuf Rajput
 *
 * FileName:    testnameComapre.c
 *
 * Description: This file contains the function that tests the nameCompare
 *              method using unit tests 
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
#include "test.h" 



/* Prototype:   void testnameCompare()
 *
 * Description: This function contains the unit tests to test the nameCompare
 *              method. We pass in a varity of inputs to test the behavior and
 *              output of the function.
 *
 * Paramters:  none
 *
 * Return:     void
 *
 */

void testnameCompare(){
    
    //make structs for comparisons 
    struct fileInfo *testName = calloc(1,sizeof(struct fileInfo));
    struct fileInfo *testName2 = calloc(1,sizeof(struct fileInfo));

    //use string copy to test same files  
    strcpy(testName->filename,"example/file/tester");
    strcpy(testName2->filename,"example/file/tester");

    int returnVal = nameCompare(&testName,&testName2);
    TEST(returnVal == 0);
    
    //test names as less than 
    strcpy(testName->filename,"example/file/");
    strcpy(testName2->filename,"example/file/tester");

    returnVal = nameCompare(&testName,&testName2);
    TEST(returnVal == -1);
    
    //test strings of greater than 
    strcpy(testName->filename,"example/file/directory/tester");
    strcpy(testName2->filename,"example/file/current/tester");

    returnVal = nameCompare(&testName,&testName2);
    TEST(returnVal == 1);

    //test strings of greater than 
    strcpy(testName->filename,"example/file/directory/tester/compare");
    strcpy(testName2->filename,"example/file/current/tester/now");

    returnVal = nameCompare(&testName,&testName2);
    TEST(returnVal == 1);


    //test names as less than 
    strcpy(testName->filename,"example/file/compare");
    strcpy(testName2->filename,"example/file/tester/test");

    returnVal = nameCompare(&testName,&testName2);
    TEST(returnVal == -1);



    //free the alloc structs
    free(testName);
    free(testName2);


    

    
    
}


int main(void){
  fprintf(stderr,"Running tests for nameCompare...\n");
  testnameCompare();
  fprintf(stderr,"Done running tests!\n");

  return 0;

  
    
}

/* Name: Yousuf Rajput
 *
 * FileName: testttimeCompare.c
 *
 * Description: this file contians the unit test for comparing the times
 *              for the timeInfo struct
 *
 * Date: November 24, 2018
 *
 * ID: cs30ffh
 *
 */


#include <string.h>
#include <stdlib.h>
#include "pa4.h"
#include "test.h"
#include "pa4Strings.h"




/* Prototype:   void testtimeCompare()
 *
 * Description: This function contains the unit tests to test the timeCompare
 *              method. We pass in a varity of inputs to test the behavior and
 *              output of the function.
 *
 * int timeCompare(const void *p1,const void *p2)
 *
 * Paramters:  none
 *
 * Return:     void
 *
 */


void testtimeCompare(){
    
    //create two structs and realloc for comparisons
    struct fileInfo *testTime = calloc(1,sizeof(struct fileInfo));
    struct fileInfo *testTime2 = calloc(1,sizeof(struct fileInfo));

    //test larger numbers 
    testTime->time = 6;
    testTime2->time = 5;
    int returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == 1);

    printf("%d\n",returnVal);


    //test same numbers 
    testTime->time = 34;
    testTime2->time = 34;
    returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == 0);

    printf("%d\n",returnVal);

    //test same numbers
    testTime->time = 12398;
    testTime2->time = 12398;
    returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == 0);

    printf("%d\n",returnVal);



    //test less than numbers
    testTime->time = 1;
    testTime2->time = 2;
    returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == -1);

    printf("%d\n",returnVal);

    //test less than numbers
    testTime->time = 0;
    testTime2->time = 9;
    returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == -1);

    printf("%d\n",returnVal);


    //test less than numbers
    testTime->time = 1;
    testTime2->time = 2;

    returnVal = timeCompare(&testTime,&testTime2);
    TEST(returnVal == -1);

   

}



int main(void){
  fprintf(stderr,"Running tests for timeCompare...\n");
  testtimeCompare();
  fprintf(stderr,"Done running tests!\n");

  return 0;

  
    
}

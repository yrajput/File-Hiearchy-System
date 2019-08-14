/*
 * Filename: timeCompareRev.s
 * Author: Yousuf Rajput
 * Userid: cs30ffh
 * Description: Compares the times of struct timeInfo 
 *
 * Date: November 24, 2018
 * Sources of Help: write up, class, piaza, online
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global timeCompareRev

/*
 * Function name: timeCompare()
 *
 * Function prototype: int timeCompareRev (const void * p1, const void * p2); 
 *
 * Description:        This function is responsible for sorting the two times
 *                     in struct timeInfo. It will be used with the C library
 *                     function qsort(), which sorts the passed in array. The 
 *                     comparison is done in reverse order
 *
 * Parameters: 
 *                     p1/p1 - two void pointers that will be compared
 *                     that should be treated as pointers to address to 
 *                     struct timeInfo
 *
 * Side Effects:       None.
 *
 * Error Conditions:   None.
 *
 * Return Value:       -1 if larger
 *                     0 if the same
 *                     1 if smaller
 *
 * Registers Used: r0-r3
 */
timeCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}

    add fp, sp, FP_OFFSET

    sub sp, sp, PARAM_SPACE

    str r0, [fp, P1_OFFSET]

    str r1, [fp, P2_OFFSET]

if:

    ldr r0, [fp, P1_OFFSET]
    ldr r0,[r0]
    ldr r1,=offset_time          @ load the time offset
    ldr r1, [r1]     @ get 1st time into r0
    ldr r1,[r0,r1]



    ldr r2, [fp, P2_OFFSET]
    ldr r2,[r2]
    ldr r3,=offset_time          @ load the time offset
    ldr r3, [r3]                 @ get 2nd time into r1
    ldr r3,[r2,r3]
   

    @ strcmp returned value < 0, first < second
    cmp r1, r3
    bge else_if

    @ return 1
    mov r0, 1
    b end_if

else_if:
    @ compare two times
    ldr r0, [fp, P1_OFFSET]
    ldr r0,[r0]
    ldr r1,=offset_time          @ load the time offset
    ldr r1, [r1]     @ get 1st time into r0
    ldr r1,[r0,r1]

    ldr r3, [fp, P2_OFFSET]
    ldr r3,[r3]
    ldr r2,=offset_time          @ load the time offset
    ldr r2, [r2]                 @ get 2nd time into r1
    ldr r2,[r3,r2]

    cmp r1, r2

    bgt else

    @ return 0
    mov r0, 0
    b end_if

else:
    @ Else, equal, so return -1
    mov r0, -1

end_if:
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}

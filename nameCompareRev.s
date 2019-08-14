/*
 * Filename: nameCompareRev.s
 * Author: TODO
 * Userid: TODO
 * Description: defines the nameCompare funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: TODO
 * Sources of Help: TODO
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global nameCompareRev

/*
 * Function name: nameCompareRev()
 *
 * Function prototype: int nameCompare (const void * p1, const void * p2); 
 *
 * Description:        This function is responsible for sorting the two names
 *                     in struct timeInfo. It will be used with the C library
 *                     function qsort(), which sorts the passed in array. They
 *                     will be sorted in alphabetical order. This function will
 *                     be sorted in the reverse order.
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

nameCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}

    @ Translation #1: Assembly to Machine Instruction: ADD
    add fp, sp, FP_OFFSET
   
    sub sp, sp, PARAM_SPACE

    @ Translation #2: Assembly to Machine Instruction: STR
    str r0, [fp, P1_OFFSET]
  
    str r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names

    @ Translation #3: Assembly to Machine Instruction: LDR
    ldr r0, [fp, P1_OFFSET]
  
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value < 0, first > second
    cmp r0, 0
    ble else_if
   
    @ return -1
    mov r0, -1
    b end_if

else_if:
    @ Call strcmp on two names
    ldr r0, [fp, P1_OFFSET]
    ldr r0, [r0]                 @ get 1st name into r0
    ldr r1, [fp, P2_OFFSET]
    ldr r1, [r1]                 @ get 2nd name into r1
    bl strcmp

    @ strcmp returned value > 0, first < second
    cmp r0, 0

    bge else
  
    @ return 1
    mov r0, 1
    b end_if

else:
    @ Else, equal, so return 0
    mov r0, 0

end_if:
      sub sp, fp, FP_OFFSET
   
    @ Restore caller's registers
    pop {fp, pc}

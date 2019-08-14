/*
 * Filename: getFileCount.s
 * Author: Yousuf Rajput
 * Userid: cs30ffh
 * Description: Gets the number of files 
 * Date: November 24, 2018
 * Sources of Help: write up, class, piaza, online
 */

.syntax unified

.equ PARAM, -32
.equ I_INDEX, -20
.equ CHILDRENCOUNT,-16
.equ COUNT,-8
.equ FP_OFFSET,4
.equ MEM_SPACE,32
.equ NULL,'\0'
.equ MUL_FAC,4

.text
.align 2
.global getFileCount

/*
 * Function name: getFileCount()
 *
 * Function prototype: int getFileCount(const struct fileInfo *fi)
 *
 * Description:        This function is responsible for sorting the two times
 *                     in struct timeInfo. It will be used with the C library
 *                     function qsort(), which sorts the passed in array. 
 *
 * Parameters: 
 *                     fi - the root of the tree we want to get the count of
 *
 * Side Effects:       None.
 *
 * Error Conditions:   None.
 *
 * Return Value:       int - count of the nodes in the tree
 *
 * Registers Used: r0-r3
 */


getFileCount:
  @ Save caller's registers on the stack
    push    {fp, lr}

    add     fp, sp, FP_OFFSET

    sub     sp,sp,MEM_SPACE

    str     r0,[fp,PARAM]               @ store the parameter on stack

    mov     r1,1                        @int count = 1
    str     r1,[fp,COUNT]               @store count on stack

    ldr     r0,[fp,PARAM]               @ load the parameter
    ldr     r1,=offset_children         @ load the offset
    ldr     r1,[r1]                     @ deref the offset
    ldr     r1,[r0,r1]                  @ load the value 

    cmp     r1,NULL                     @ if fi->children != null
    beq     end                         @ skip if not met

    ldr     r0,[fp,PARAM]               @ load the param
    ldr     r2,=offset_childrenSize     @ load childrenSize offset
    ldr     r2,[r2]                     @ deref the offset
    ldr     r2,[r0,r2]                  @ load the value

    sub     r2,r2,1                     @ childrenSize - 1
    str     r2,[fp,I_INDEX]             @ i = childrenSize - 1

    cmp     r2,0                        @ i >= 0
    blt     end                         @ skip if not met

  for:

    ldr     r1,[fp,I_INDEX]             @ laod the index
    cmp     r1,0                        @ i >= 0
    blt     end                         @ skip loop if not met
  
    ldr     r1,[fp,PARAM]               @ load the param
    ldr     r0,=offset_children         @ load offset of children
    ldr     r0,[r0]                     @ deref the offset
    ldr     r0,[r1,r0]                  @ fi -> children

    ldr     r2,[fp,I_INDEX]             @ laod i index

    mov     r3,MUL_FAC
    mul     r2,r2,r3
    ldr     r3,[r0,r2]                  @ fi->children[i]
    mov     r0,r3

    bl      getFileCount                @ recursive call

    ldr     r3,[fp,COUNT]               @ load the count
    add     r0,r0,r3                    @ count += getFileCount
    str     r0,[fp,COUNT]               @ store count val back on stack
    
    ldr     r1,[fp,I_INDEX]
    sub     r1,r1,1                     @ i--
    str     r1,[fp,I_INDEX]               @ store updated index on stack

    b       for
    
  end:

    ldr r0,[fp,COUNT]

    add sp,sp,MEM_SPACE
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}


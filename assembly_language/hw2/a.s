@BEGIN
	.text
	.align	2   @align 4 byte
	.global	main
	
main:
	stmfd sp!, {fp,lr}
	ldr r4,[r1,#4]
	ldr r5,[r1,#8]
	ldr r6,[r1,#12]
	stmfd sp!, {r4-r6}
	
	@ r4-r8 can use
	mov r7, #0	@intA
	mov r8, #0	@intB
	mov r10, #10
	
GETA:
	ldrb r0,[r4],#1
	cmp r0,#0
	subne r0, r0, #48
	mulne r7, r10, r7
	addne r7, r7, r0
	bne GETA
	
	mov r10, #10
GETB:
	ldrb r0,[r5],#1
	cmp r0,#0
	subne r0, r0, #48
	mulne r8, r10, r8
	addne r8, r8, r0
	bne GETB

GETFIN:
	adr r1, JUMPTABLE
	ldrb r0,[r6]
	sub r0, r0, #48
	cmp r0, #8
	ldrle pc, [r1, r0, lsl #2]
	
	b EXIT
	
JUMPTABLE:
	.word ADD0
	.word SUB1
	.word BITREV2
	.word DIV3
	.word MAX4
	.word EXP5
	.word GCD6
	.word LONGMUX7
	.word LCM8

ADD0:
	mov r1, r7
	mov r2, r8
	add r3,r1,r2
	ldr r0,=ADD0_S
	bl printf
	b EXIT

SUB1:
	mov r1, r7
	mov r2, r8
	sub r3,r1,r2
	ldr r0,=SUB1_S
	bl printf
	b EXIT

BITREV2:
	mov r1, r7
	mov r2, r8
	mov r3, #0
	mov r4, #31
BITREV2LOOP:
	mov r0, r7, lsl r4
	mov r3, r3, lsl #1
	add r3, r3, r0, lsr #31
	sub r4, r4, #1
	cmp r4, #0
	bge BITREV2LOOP
	ldr r0,=BITREV2_S
	bl printf
	b EXIT

DIV3:
	mov r1, r7
	mov r2, r8
	mov r3, #0
	mov r4, r1
IV3LOOP:
	sub r4, r4, r2
	cmp r4 ,#0
	addge r3, r3, #1
	bge IV3LOOP
	ldr r0,=DIV3_S
	bl printf
	b EXIT

MAX4:
	mov r1, r7
	mov r2, r8
	cmp r1, r2
	movge r3, r1
	movlt r3, r2
	ldr r0,=MAX4_S
	bl printf
	b EXIT

EXP5:
	mov r1, r7
	mov r2, r8
	mov r3, #1
	mov r4, r2
EXP5LOOP:
	cmp r4, #0
	mulgt r3, r1, r3
	subgt r4, #1
	bgt EXP5LOOP
	ldr r0,=EXP5_S
	bl printf
	b EXIT
	
GCD6:
	bl GCD
	@ldmfd sp!,{r3}
	mov r3, r6
	mov r1, r7
	mov r2, r8
	ldr r0,=GCD6_S
	bl printf
	b EXIT
	
LONGMUX7:
	mov r1, r7
	mov r2, r8
	mov r4, r2
LONGMUX7LOOP:
	cmp r4, #0
LONGMUX7FIN:
	ldr r0,=GCD6_S
	bl printf
	b EXIT

LCM8:
	bl GCD
	@ldmfd sp!,{r3}
	mov r3, r6
	mov r1, r7
	mov r2, r8
	mov r4, r1
	mov r5, r2
	mov r6, #0
	mov r7, #0
LCM8LOOP1:
	cmp r4, #0
	beq LCM8LOOP2
	sub r4, r4, r3
	add r6, r6, #1
	b LCM8LOOP1
LCM8LOOP2:
	cmp r5, #0
	beq LCM8FIN
	sub r5, r5, r3
	add r7, r7, #1
	b LCM8LOOP2
LCM8FIN:
	mul r3, r6, r3
	mul r3, r7, r3
	ldr r0,=LCM8_S
	bl printf
	b EXIT

@ find gcd with r7 and r8, return with r3 push in stack
GCD:
	mov r1, r7
	mov r2, r8
	mov r4, r1
	mov r5, r2
	cmp r4, r5
	movlt r6, r4
	movlt r4, r5
	movlt r5, r6
	mov r3, r5
GCDLOOP:
	cmp r5, #0
	movne r3, r5
	beq GCDFIN
	sub r4, r4, r5
	cmp r4, r5
	movlt r6, r4
	movlt r4, r5
	movlt r5, r6
	b GCDLOOP
GCDFIN:
	mov r6, r4
	bx lr
	
	
ADD0_S:
	.asciz	"Function 0: addition of %d and %d is %d.\n"
	.align
SUB1_S:
	.asciz	"Function 1: subtraction of %d and %d is %d.\n"
	.align
BITREV2_S:
	.asciz	"Function 2: Bit-reverse of 0x%08x and 0x%08x(ignored) is 0x%08x.\n"
	.align
DIV3_S:
	.asciz	"Function 3: division of %d and %d is %d.\n"
	.align
MAX4_S:
	.asciz	"Function 4: maximum of %d and %d is %d.\n"
	.align
EXP5_S:
	.asciz	"Function 5: exponent of %d and %d is %d.\n"
	.align
GCD6_S:
	.asciz	"Function 6: greatest common divisor of %d and %d is %d.\n"
	.align
LONGMUX7_S_1:
	.asciz	"Function 7: Long-multiplication of %d and %d is %d"
	.align
LONGMUX7_S_2:
	.asciz	"%d.\n"
	.align
LCM8_S:
	.asciz	"Function 8: least common multiply of %d and %d is %d.\n"
	.align
WRONG_OPER_S:
	.asciz	"the oper must be 0~9\n"
	.align
EXIT:
	ldmfd sp!, {r4-r6}
	ldmfd sp!,{fp,lr}
	bx lr

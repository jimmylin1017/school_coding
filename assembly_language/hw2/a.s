@BEGIN
	.text
	.align	2   @align 4 byte
	.global	main
	
main:
	stmfd sp!, {fp,lr}
	ldr v1,[a2,#8] @arithm
	ldr v2,[a2,#12] @intA
	ldr v3,[a2,#16] @intB
	stmfd sp!, {v1-v3}
	
	@ v1-v5 can use
	mov v4, #0 @store intA
	mov v5, #0 @store intB
	mov v7, #10
	
GETA:
	ldrb a1,[v1],#1
	cmp a1,#0
	subne a1, a1, #48
	mulne v4, v7, v4
	addne v4, v4, a1
	bne GETA
	
	mov v7, #10
GETB:
	ldrb a1,[v2],#1
	cmp a1,#0
	subne a1, a1, #48
	mulne v5, v7, v5
	addne v5, v5, a1
	bne GETB

GETFIN:
	adr a2, JUMPTABLE
	ldrb a1,[v3]
	sub a1, a1, #48
	cmp a1, #8
	ldrle pc, [a2, a1, lsl #2]
	
	ldr a1, =ERROR_S
	bl printf
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
	mov a2, v4
	mov a3, v5
	add a4,a2,a3
	ldr a1,=ADD0_S
	bl printf
	b EXIT

SUB1:
	mov a2,v4
	mov a3,v5
	sub a4,a2,a3
	ldr a1,=SUB1_S
	bl printf
	b EXIT

BITREV2:
	mov a2,v4
	mov a3,v5
	mov a4,#0
	mov v1,#31 @counter: shift 31 times
BITREV2LOOP:
	mov a1,a2,lsl v1 @a1 = a2 left shift v1 to get 
	mov a4,a4,lsl #1 @shift a4 bit left 1
	add a4,a4,a1,lsr #31 @shift right to get first bit add to a4
	sub v1,v1,#1
	cmp v1,#0
	bge BITREV2LOOP
	ldr a1,=BITREV2_S
	bl printf
	b EXIT

DIV3:
	mov a2,v4
	mov a3,v5
	mov a4,#0
	mov v1,a2
IV3LOOP:
	sub v1,v1,a3
	cmp v1,#0
	addge a4,a4,#1
	bge IV3LOOP
	ldr a1,=DIV3_S
	bl printf
	b EXIT

MAX4:
	mov a2,v4
	mov a3,v5
	cmp a2,a3
	movge a4,a2 @a2 >= a3, a4 = a2
	movlt a4,a3 @a2 < a3, a4 = a3
	ldr a1,=MAX4_S
	bl printf
	b EXIT

EXP5:
	mov a2,v4
	mov a3,v5
	mov a4,#1
	mov v1,a3 @v1 is counter fot multiple
EXP5LOOP:
	cmp v1,#0
	mulgt a4,a2,a4 @v1 > 0 then a4 = a2 * a4
	subgt v1,#1
	bgt EXP5LOOP
	ldr a1,=EXP5_S
	bl printf
	b EXIT
	
GCD6:
	bl GCD @return value is v3 and arguement is v4, v5
	mov a4,v3 @store return value in a4
	mov a2,v4
	mov a3,v5
	ldr a1,=GCD6_S
	bl printf
	b EXIT
	
LONGMUX7:
	mov a2, v4
	mov a3, v5
	ldr a1,=LONGMUX7_S_1
	bl printf
	umull a2, a3, v4, v5 @a2,a3 = v4 * v5 undigned
	ldr a1,=LONGMUX7_S_2
	bl printf
	b EXIT

LCM8:
	bl GCD @return value is v3 and arguement is v4, v5
	mov a4, v3 @store return value in a4
	mov a2, v4
	mov a3, v5
	mov v1, a2 @for minus to get p (a2 = a4 * p)
	mov v2, a3 @for minus to get q (a3 = a4 * q)
	mov v3, #0 @value p (a2 = a4 * p)
	mov v4, #0 @value q (a3 = a4 * q)
LCM8LOOP1:
	cmp v1, #0
	beq LCM8LOOP2
	sub v1, v1, a4
	add v3, v3, #1
	b LCM8LOOP1
LCM8LOOP2:
	cmp v2, #0
	beq LCM8FIN
	sub v2, v2, a4
	add v4, v4, #1
	b LCM8LOOP2
LCM8FIN:
	mul a4, v3, a4 @a4 = p * q * a4 to get LCM
	mul a4, v4, a4
	ldr a1,=LCM8_S
	bl printf
	b EXIT

@ find gcd with v4 and v5, return with a4 push in stack
GCD:
	mov a2, v4
	mov a3, v5
	mov v1, a2
	mov v2, a3
	cmp v1, v2
	movlt v3, v1
	movlt v1, v2
	movlt v2, v3
	mov a4, v2
GCDLOOP:
	cmp v2, #0
	movne a4, v2
	beq GCDFIN
	sub v1, v1, v2
	cmp v1, v2
	movlt v3, v1
	movlt v1, v2
	movlt v2, v3
	b GCDLOOP
GCDFIN:
	mov v3, v1
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
	.asciz	"Function 7: Long-multiplication of %d and %d is "
	.align
LONGMUX7_S_2:
	.asciz	"%lld.\n"
	.align
LCM8_S:
	.asciz	"Function 8: least common multiply of %d and %d is %d.\n"
	.align
ERROR_S:
	.asciz	"the operation must be 0~9\n"
	.align
EXIT:
	ldmfd sp!, {v1-v3}
	ldmfd sp!,{fp,lr}
	bx lr

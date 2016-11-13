@this is comment

@the information that tells arm-none-eabi-as what arch. to assemble to 
	.cpu arm926ej-s
	.fpu softvfp

@this is code section
@note, we must have the main function for the simulator's linker script
	.text
	.align	2   @align 4 byte
	.global	main
main:

	@prologue
	stmfd sp!, {fp,lr}
	
	@code body
	@arithm intA intB intp
	ldr r5,[r1,#4]!
	ldr r6,[r1,#4]!
	ldr r7,[r1,#4]!
	
	mov r1, #0
	mov r2, #0
	mov r10, #10
	
	ldrb r8,[r5],#1
	ldrb r9,[r6],#1
		
GETA:
	cmp r8,#0
	beq GETB
	sub r8, r8, #48
	mul r11, r1, r10
	add r1, r11, r8
	ldrb r8,[r5],#1
	b GETA

GETB:
	cmp r9,#0
	beq GETFIN
	sub r9, r9, #48
	mul r12, r2, r10
	add r2, r12, r9
	ldrb r9,[r6],#1
	b GETB
	
GETFIN:
	adr r0, JUMPTABLE
	ldrb r4,[r7]
	sub r4,r4,#48
	cmp r4,#8
	ldrle pc, [r0, r4, lsl #2]
	
	b EXIT
	
JUMPTABLE:
	B ADD0
	B SUB1
	B BITREV2
	B DIV3
	B MAX4
	B EXP5
	B GCD6
	B LONGMUX7
	B LCM8
	
ADD0:
	add r3,r1,r2
	ldr r0,=ADD0_S
	bl printf
	B EXIT

SUB1:
	

BITREV2:
	

DIV3:
	

MAX4:
	

EXP5:
	

GCD6:
	

LONGMUX7:
	

LCM8:
	

ADD0_S:
	.asciz	"Function 0: addition of %d and %d is %d.\n"
SUB1_S:
	.asciz	"Function 1: subtraction of %d and %d is %d.\n"
BITREV2_S:
	.asciz	"Function 2: Bit-reverse of %d and %d is %d.\n"
DIV3_S:
	.asciz	"Function 3: division of %d and %d is %d.\n"
MAX4_S:
	.asciz	"Function 4: maximum of %d and %d is %d.\n"
EXP5_S_PRE:
	.asciz	"Function 5: exponent of %d and %d"
GCD6_S:
	.asciz	"Function 6: greatest common divisor of %d and %d is %d.\n"
LONGMUX7_S:
	.asciz	"Function 7: Long-multiplication of %d and %d is %d.\n"
LCM8_S:
	.asciz	"Function 8: least common multiply of %d and %d is %d.\n"
WRONG_OPER_S:
	.asciz	"the oper must be 0~9\n"
EXIT:
	ldmfd sp!,{fp,lr}
	bx lr
	
	.end

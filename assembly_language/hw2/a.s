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
	ldr r5,[r1,#4]
	ldr r6,[r1,#8]
	ldr r7,[r1,#12]
	
	@ldrb r0,[r7]
	@bl putchar
	
	mov r11, #0
	mov r10, #10		
GETA:
	ldrb r8,[r5],#1
	cmp r8,#0
	@beq GETB
	subne r8, r8, #48
	mulne r11, r10, r11
	addne r11, r11, r8
	bne GETA
	
	@mov r1, r11
	@ldr r0, =ADD0_S
	@bl printf
	@b EXIT
	
	mov r10, #10
	mov r12, #0
GETB:
	ldrb r9,[r6],#1
	cmp r9,#0
	@ble GETFIN
	subne r9, r9, #48
	mulne r12, r10, r12
	addne r12, r12, r9
	bne GETB
	
	ldrb r0,[r7]
	bl putchar
	
	@b ADD0
	
	mov r1, r11
	mov r2, r12
	ldr r0, =ADD0_S
	bl printf
	@b EXIT
	
GETFIN:
	adr r4, JUMPTABLE
	ldrb r0,[r7]
	bl putchar
	sub r0, r0, #48
	cmp r0, #8
	ldr pc, [r4, r0, lsl #2]
	
	b EXIT
	
JUMPTABLE:
	b ADD0
	b SUB1
	b BITREV2
	b DIV3
	b MAX4
	b EXP5
	b GCD6
	b LONGMUX7
	b LCM8
	
ADD0:
	mov r1, r11
	mov r2, r12
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

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
	stmfd sp!, {r0,r1,fp,lr}
	add	fp, sp, #4
	ldr r5,[r1,#4]
	
	@code body
	ldr	r0, =string0
	bl printf
loop:
	ldrb r0,[r5],#1
	cmp r0,#' '
	cmpne r0,#'1'
	cmpne r0,#'2'
	cmpne r0,#'3'
	cmpne r0,#'4'
	cmpne r0,#'5'
	cmpne r0,#'6'
	cmpne r0,#'7'
	cmpne r0,#'8'
	cmpne r0,#'9'
	cmpne r0,#'0'
	beq endcheck
	cmp r0,#'A'
	bge labA
	bl putchar
	b endcheck
labA:
	cmp r0,#'Z'
	ble labZ
	bl putchar
	b endcheck
labZ:
	add r0,r0,#32
	bl putchar
endcheck:
	cmp r0,#0
	bne loop
	
	@epilogue
	sub	sp, fp, #4
	ldmfd sp!, {r0,r1,fp,lr}
	bx lr
	
string0:
	.ascii	"The string output: \0"
	
	.end

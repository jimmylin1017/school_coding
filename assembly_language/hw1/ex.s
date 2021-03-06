@ Hello, arm-gcc
@ Hello, CodeSourcery:0x66778899
@ Hello, CodeSourcery:0x44331122
@ Hello, CodeSourcery:0x34333231

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
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4

    @code body
	ldr	r0, =string1
	bl printf
	
	ldr	r0, =string0
	ldr r1, Label1
	bl printf
	ldr	r0, =string0
	ldr r1, Label1 + 4
	bl printf
	ldr	r0, =string0
	ldr r1, Label1 + 8
	bl printf
	
	mov r0, #1
	bl fun

	mov	r0, #0
	
	@epilogue
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr

@another function
fun:
    add r0, r0, #1    
    bx lr

@data section

Label1:
    .word   0x66778899	@0x66778899
    .short  0x1122	@0x44331122
	.short  0x4433
    .align 2
    .byte   0x31, 0x32, 0x33, 0x34	@0x34333231

string0:
	.ascii	"Hello, CodeSourcery:0x%X\n\0"
string1:
	.asciz "Hello, arm-gcc\n"
    
    .end


	.text
	.align 2   @align 4 byte
	.global	main

main:

	stmfd sp!,{fp,lr}
	mov r5,#0
	adr r0,string
	bl printf
	ldr r7,=0xe92d4800 @ e92d4800: push {fp, lr}
	ldr r8,=0xe8bd4800 @ e8bd4800: pop {fp, lr}

FINDMAIN:

	ldr r6,[r5],#4
	cmp r6,r7
	bne FINDMAIN

GETINST:

	@ get Cond
	mov r2,#0
	add r2,r2,r6, lsr #28
	cmp r2,#0x0
	ldreq r2,=CONDEQ
	cmp r2,#0x1
	ldreq r2,=CONDNE
	cmp r2,#0xe
	ldreq r2,=CONDAL
	
	@ check Data Processing PSR Transfer
	mov r4,#0
	add r4,r4,r6, lsr #25
	and r4,r4,#0x7
	cmp r4,#0x1
	ldrne r3,=OPCODEXXX
	bne PRINT
	
	@ get Opcode
	mov r3,#0
	add r3,r3,r6, lsr #21
	and r3,r3,#0xf
	cmp r3,#0x0
	ldreq r3,=OPCODEAND
	cmp r3,#0x2
	ldreq r3,=OPCODESUB
	cmp r3,#0x4
	ldreq r3,=OPCODEADD
	cmp r3,#0xa
	ldreq r3,=OPCODECMP
	cmp r3,#0xd
	ldreq r3,=OPCODEMOV
	
PRINT:

	adr r0,string0
	sub r1,r5,#4
	bl printf
	ldr r6,[r5],#4
	cmp r6, r8
	bne GETINST	
	
	adr r0,string0
	sub r1,r5,#4
	ldr r2,=CONDAL
	ldr r3,=OPCODEXXX
	bl printf
	
	ldmfd sp!,{fp,lr}
	bx lr

	
string:
	.ascii "PC\tCond\tOpcode\n"
	.align
	
string0:
	.ascii "%d\t%s\t%s\n"
	.align

CONDEQ:
	.ascii "EQ\0"
CONDNE:
	.ascii "NE\0"
CONDAL:
	.ascii "AL\0"
	
OPCODEAND:
	.ascii "AND\0"
OPCODEADD:
	.ascii "ADD\0"
OPCODESUB:
	.ascii "SUB\0"
OPCODECMP:
	.ascii "CMP\0"
OPCODEMOV:
	.ascii "MOV\0"
OPCODEXXX:
	.ascii "xxx\0"

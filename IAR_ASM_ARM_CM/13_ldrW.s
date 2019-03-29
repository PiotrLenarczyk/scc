;	ldrW macro definition; loads any 4B value into register

thumb
main
;CM0+ compatible:
//ldrW	macro reg, imm_0, imm_1, imm_2, imm_3
//		ldr reg, =imm
//	endm
	movs r0, #0x11
	mov r0, r8
	movs r0, #0x22
	mov r0, r9
	movs r0, #0x33
	mov r0, r10
	movs r0, #0x44
	movs r0, r0, LSL #0x0
	

	
	;mov r0, #0x11
;at lest CM3 compatible:
//	;ldrW r0, #0x11223344
//	mov r0, #0x11223344 & 0x000000FF
//	orr r0, r0, #0x11223344 & 0x0000FF00
//	orr r0, r0, #0x11223344 & 0x00FF0000
//	orr r0, r0, #0x11223344 & 0xFF000000
//
//	
//ldrW	macro reg, imm
//	
//	mov reg, #imm & 0x000000FF
//	orr reg, reg, #imm & 0x0000FF00
//	orr reg, reg, #imm & 0x00FF0000
//	orr reg, reg, #imm & 0xFF000000
//		endm
//
//	ldrW r1, 0x11223344
//	ldr r2, =0x11223344

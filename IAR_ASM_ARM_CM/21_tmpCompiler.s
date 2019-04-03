thumb
memAddr	equ	0x20000080
main:
	ldr r0, =0xFFFFFFFF
	movs r1, #0x1
	adds r2, r1, r0
	ldr r3, =memAddr
	str	r2, [r3]
	
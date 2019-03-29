thumb
memAddr	equ	0x20000100
main:
	movs r0, #0x11
	movs r1, #0x1
	adds	r0, r1, #0x1
	
	ldr r3, =memAddr
	str	r0, [r3]
	str r0, [r3+#4]
thumb
ldrW macro reg, immed
      movs  reg, #((immed >> 0x0) & 0xFF)
      adds	reg, #((immed >> 0x8) & 0xFF)
      adds 	reg, #((immed >> 0x10) & 0xFF)
      adds 	reg, #((immed >> 0x18) & 0xFF)
	endm
memAddr	equ	0x20000100
main:
	  movs  r0, #((0x11223344 >> 0x0) & 0xFF)
      adds	r0, #((0x11223344 >> 0x8) & 0xFF)
      adds 	r0, #((0x11223344 >> 0x10) & 0xFF)
      adds 	r0, #((0x11223344 >> 0x18) & 0xFF)
	movs r0, #0x11
	movs r1, #0x1
	
	ldr r3, =memAddr
	str	r0, [r3]
	str r0, [r7]
	
	ldr r4, [r4]
	
;THUMB
main:
		;movs		r0, #0xFFFFFFFF
		movs		r1, #0x000000FF
		;movs		r2, #0x0000FF00
		;movs		r3, #0x00FF0000
		;movs		r4, #0xFF000000
		;movs		r5, #0xFE000000
		;movs		r6, #0x11223344; illegal immediate
		
		ldr		r7, =0x11223344 ;any immediate value


		movs r2, #0x33
		ldr r3, =0x20000100
		str r2, [r3]
		adds r3, #0x4
		str r2, [r3]
		
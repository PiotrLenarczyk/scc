THUMB
main:
		movs		r0,#0x18
		ldr		r1, =0x20026
		;swi		0x123456 ; return control to higher level debugger
		

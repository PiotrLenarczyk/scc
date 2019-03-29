THUMB
main:
		movs		R0, #5
	ldr		r1, =0x20000000
		str		r0, [r1]
		
//		mov r0, #0x18
//		ldr r1, =0x20026
;		swi 0x123456 ;number out of range

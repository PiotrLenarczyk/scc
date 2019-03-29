		;ADRL	is only ARM instruction
	thumb
	
ENTRY
main
		blx		func
		b Array
func
		nop
		ldr		r0, =main
		ldr		r1, =Array
		mov		pc, lr
Array
		mov		r0, r0

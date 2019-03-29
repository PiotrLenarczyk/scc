thumb
ENTRY
main:
		bl		func1
		bl		func2
		
func1
		ldr		r0, =0x2A ;mov r0, #42
		ldr		r1, =0x55555555	;ldr r1, [PC, #offset to literal pool 1]
		ldr		r2, =0xFFFFFFFF ;ldr r2, #0
		mov		pc, lr
;LTORG ;literal pool1 contains 0x55555555
func2
		ldr		r3, =0x55555555 ;ldr r3, [PC, #offset toliteral pool 1
		mov		pc, lr	
	
	data
Array1	dcd 4200
	ltorg
		;space	4200		;4200B will be reset to 0x0from here

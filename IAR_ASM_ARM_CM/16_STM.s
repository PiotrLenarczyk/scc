thumb
main:
spAddr	equ	0x20000100
	movs	r1, #0xAA
	movs	r2, #0xBB
	
	ldr 	r7, =spAddr
	stmia	r7!, {r1-r2} ;store on stack, inc addr after each store
	ldr		r7, =spAddr + 0x10
	stm	r7!, {r1-r2}		;stmia	
	;thumb not avaiable
		;stmib		r7!, {r1-r2}	 ;inc addr before each store
		;stmda	r7!, {r1-r2}		;decrement addr after each store
		;stmdb	r7!, {r1-r2}		;decrement addr before each store
		;stmfd	r7!, {r1-r2}		;fully descending stack
		;stmed	r7!, {r1-r2}		;empty descending stack
		;stmfa	r7!, {r1-r2}		;fully ascending stack
	ldr		r7, =spAddr + 0x20
	stmea	r7!, {r1-r2}		;empty ascending stack
	
	
	push {r1-r2}
	pop {r3-r4}
	
	
	
	
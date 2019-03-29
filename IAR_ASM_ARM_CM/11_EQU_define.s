CODE16
N		EQU 0x01 ;#define N 0x0		
ENTRY
main
		;		mov		r1, #N
		movs		r1, #N
		movs		r2, #0x3
		ldr		r3, =jumpTable
		
		mov pc, r3
		ldr		r3, =jumpTable+0x4
		mov pc, r3
		b endMain
		;LDR		pc, [r3,r0,LSL#2]
		data
jumpTable
		DCD		doAdd
		DCD		doSub
		ltorg
doAdd	adds		r0, r1, r2
		mov		pc, lr
doSub	subs		r0, r1, r2
		mov		pc, lr
		;???????????
endMain

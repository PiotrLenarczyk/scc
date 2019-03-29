;		AREA	thumbSub,CODE,READONLY




CODE32	;ARM instructions address |= 0x1
main:
		movs		r1, #0x11
		ldr		r0, =start+1 ; jump address must be or'ed with 0x1
		;bx		r0; enable switching instructions type (ARM/THUMB)
		movs r1, #0x0
CODE16	;THUMB instructions address &=0xFFFFFFFE
start
		movs		r1, #0xFF
		

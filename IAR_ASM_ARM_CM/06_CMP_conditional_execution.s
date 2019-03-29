		;N-NEGATIVE
		;Z-ZERO
		;C-CARRY
		;v-oVERFLOW
		;CMP,	CMN, TST, TEQ only updates flags
thumb
main
		movs		r1, #0xFF
		movs		r1, #0x1 ;adding 0x1 updates Z&C flags; 0x2 updates C flag
		;add		r1, r1, r8 ;r0=r1+r8; don't update flags
		add		r1, r1, r8 ;r0=r1+r8; update flags
		;addcss	r0,		r1, r8 ;if C flag set then r0=r1+r8 and update flags
		;CMP		r0, r1 ;update flags based on r0-r1
		

thumb
ENTRY
main:
		movs		r0, #0xF
		movs		r1, #0x3
gcd
		cmp		r0, r1
		subs	r0, r0, r1
		subs	r1, r1, r0
		bne		gcd
		
		
		

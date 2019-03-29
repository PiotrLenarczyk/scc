
movImm	macro regDst, imm
		movs	regDst, #imm
	endm

thumb
main
	movs	r1, #0x11
	movImm 	r2, 0x22


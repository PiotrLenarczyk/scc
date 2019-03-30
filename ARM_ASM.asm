;====
;FOO
;====

;====


	.text
	.globl	main
	.globl	_exit
ENTRY:
main:
	bl	_main
	.text
	.globl	_main
_0x0:
	movs	r7,r6 ;#0xFFFFFFF8;(#-8)
	add	r3,r7
	movs	r6,r6 ;#0xAAAA;(#43690)
	mov	r4,r6
	movs	r4,r6 ;#0xBBBB;(#48059)
	orr	r4,r4
	str	r4,[r3,#0x0]
	orrs	r3,r4,ERROR_NULL_REG

	add	r3,#0xFFFFFFFF
	orrs	r1,r3,ERROR_NULL_REG
_0x1:
	lw	lr,[r7,#0xFFFFFFFC]
	orrs	sp,r7,ERROR_NULL_REG
	lw	r7,[sp,#0x0]
	movs	sp,r6 ;#0x4;(#4)
	add	sp,sp
	j	lr
_main:
	movs	sp,r6 ;#0xFFFFFFF0;(#-16)
	add	sp,sp
	str	r7,[sp,#0xC]
	movs	sp,r6 ;#0xC;(#12)
	add	r7,sp
	str	lr,[r7,#0xFFFFFFFC]
	j	_0x0

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

				;movs	r6,#0xFFFFFFF8 (-8)
	movs	r7,r6
	adds	r3,r7

				;movs	r6,#0xAAAABBBB (-1431651397)
	movs	r6,r6
	movs	r4,r6
	str	r4,[r3,#0x0]
	orrs	r3,r4

				;movs	r6,#0xFFFFFFFF (-1)
	movs	r6,r6
	adds	r3,r6
	orrs	r1,r3
_0x1:
	lw	lr,[r7,#0xFFFFFFFC]
	orrs	sp,r7
	lw	r7,[sp,#0x0]
	b	lr
_main:
	str	r7,[sp,#0xC]

				;movs	r6,#0xC (12)
	movs	sp,r6
	adds	r7,sp
	str	lr,[r7,#0xFFFFFFFC]
	j	_0x0

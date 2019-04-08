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
	adds	r3,r7,r6

				;movs	r6,#0xAAAABBBB (-1431651397)
	movs	r4,r4,r6

			
				;movs	r6,#0x0 (0)
	adds	r6,r3,r6
	str	r4,[r6]

				;movs	r6,#0x0 (0)
	orrs	r3,r4,r6

				;movs	r6,#0xFFFFFFFF (-1)
	movs	r3,r3,r6

				;movs	r6,#0x0 (0)
	orrs	r1,r3,r6
_0x1:
	lw	lr,[r7,#0xFFFFFFFC]

				;movs	r6,#0x0 (0)
	orrs	sp,r7,r6
	lw	r7,[sp,#0x0]

				;movs	r6,#0x4 (4)
	adds	sp,sp,r6
	b	lr
_main:

				;movs	r6,#0xFFFFFFF0 (-16)
	adds	sp,sp,r6

			
				;movs	r6,#0xC (12)
	adds	r6,sp,r6
	str	r7,[r6]

				;movs	r6,#0xC (12)
	adds	r7,sp,r6

			
				;movs	r6,#0xFFFFFFFC (-4)
	adds	r6,r7,r6
	str	lr,[r6]
	j	_0x0

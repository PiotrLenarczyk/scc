	.text
	.globl	main
	.globl	_exit
;====
;FOO
;====
		movs	r6,#((0xFFFFFFF1 >> 0x0) & 0xFF)
		adds	r6,#((0xFFFFFFF1 >> 0x8) & 0xFF)
		adds	r6,#((0xFFFFFFF1 >> 0x10) & 0xFF)
		adds	r6,#((0xFFFFFFF1 >> 0x18) & 0xFF)
		mov	r1,r6
	adds	r0,r1

;====
ENTRY:
main:
	bl	_main
	.text
	.globl	_main
_0x0:
	adds	r3,#0xFFFFFFFF
	orrs	r1,r3,ERROR_NULL_REG
_0x1:
	lw	lr,[r7,#0xFFFFFFFC]
	orrs	sp,r7,ERROR_NULL_REG
	lw	r7,[sp,#0x0]
	adds	sp,sp,#0x4
	j	lr
_main:
	adds	sp,sp,#0xFFFFFFF0
	str	r7,[sp,#0xC]
	adds	r7,sp,#0xC
	str	lr,[r7,#0xFFFFFFFC]
	j	_0x0

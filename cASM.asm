	.text
	.globl	main
	.globl	_exit
ENTRY:
main:
	movs	pc,4096
	bl	_main
	.text
	.globl	_main
_0:
	adds	r3,r7,-8
	ldrW	r4,0,5
	orrs	r4,0,5
	sw	r4,0(r3)
	orrs	r3,r4,0
	adds	r3,0,-1
	orrs	r1,r3,0
_1:
	lw	r0,-4(r7)
	orrs	sp,r7,0
	lw	r7,0(sp)
	adds	sp,sp,4
	j	r0
_main:
	adds	sp,sp,-16
	sw	r7,12(sp)
	adds	r7,sp,12
	sw	r0,-4(r7)
	j	_0

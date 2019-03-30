	.text
	.globl	main
	.globl	_exit
	.globl	_print_int
	.globl	_print_string
main:
	ldrW	$gp,0x1000
	jal	_main
_exit:
	ori	$v0,$0,0xA
	syscall
_print_int:
	ori	$v0,$0,0x1
	syscall
	jr	$ra
_print_string:
	ori	$v0,$0,0x4
	syscall
	jr	$ra
	.text
	.globl	_main
_0x0:
	addi	$t0,$fp,0xFFFFFFF8
	ldrW	$t1,0xAAAA
	ori	$t1,$t1,0xBBBB
	sw	$t1,0x0($t0)
	or	$t0,$t1,$0
	addi	$t0,$0,0xFFFFFFFF
	or	$v0,$t0,$0
_0x1:
	lw	$ra,0xFFFFFFFC($fp)
	or	$sp,$fp,$0
	lw	$fp,0x0($sp)
	addi	$sp,$sp,0x4
	jr	$ra
_main:
	addi	$sp,$sp,0xFFFFFFF0
	sw	$fp,0xC($sp)
	addi	$fp,$sp,0xC
	sw	$ra,0xFFFFFFFC($fp)
	j	_0x0

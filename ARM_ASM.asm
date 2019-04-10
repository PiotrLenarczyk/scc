THUMB
ENTRY:
main:

				;movs	r6,#0x20000200 (536871424)
	mov	r7,r6

				;movs	r6,#0x20000400 (536871936)
	mov	sp,r6
	bl	_main
_0x0:

				;movs	r6,#0xFFFFFFF8 (-8)

	adds	r6,r7,r6
	mov	r3,r6

				;movs	r6,#0xAAAABBBB (-1431651397)
	mov	r4,r6

			
				;movs	r6,#0x0 (0)

	adds	r6,r6,r3
	str	r4,[r6]
	mov	r3,r4

				;movs	r6,#0xFFFFFFFF (-1)
	mov	r3,r6
	mov	r0,r3
_0x1:

				;movs	r6,#0xFFFFFFFC (-4)

	adds	r6,r7
	ldr	r6,[r6]
	mov	lr,r6
	mov	sp,r7

				;movs	r6,#0x0 (0)

	adds	r6,sp
	ldr	r6,[r6]
	mov	r7,r6

				;movs	r6,#0x4 (4)

	adds	sp,r6,sp
	mov	pc,lr
_main:

				;movs	r6,#0xFFFFFFF0 (-16)

	adds	sp,r6,sp

			
				;movs	r6,#0xC (12)

	adds	r6,r6,sp
	str	r7,[r6]

				;movs	r6,#0xC (12)

	adds	r7,r6,sp

			
				;movs	r6,#0xFFFFFFFC (-4)

	adds	r6,r6,r7
	str	lr,[r6]
	b	_0x0

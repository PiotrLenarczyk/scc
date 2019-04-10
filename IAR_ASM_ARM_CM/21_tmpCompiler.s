THUMB
ENTRY:
main:

				ldr R6, =0x20000200 ;(536871424)
	mov	r7,r6

				ldr R6, =0x20000400 ;(536871936)
	mov	sp,r6
	bl	_main
	b _main
_0x0:

				ldr R6, =0xFFFFFFF8 ;(-8)

	adds	r6,r7,r6
	mov	r3,r6

				ldr R6, =0xAAAABBBB ;(-1431651397)
	mov	r4,r6

			
				ldr R6, =0x0 ;(0)

	adds	r6,r6,r3
	str	r4,[r6]
	mov	r3,r4

				ldr R6, =0xFFFFFFFF ;(-1)
	mov	r3,r6
	mov	r0,r3
_0x1:

				ldr R6, =0xFFFFFFFC ;(-4)

	add	r6,r7
	ldr	r6,[r6]
	mov	lr,r6
	mov	sp,r7

				ldr R6, =0x0 ;(0)

	add	r6,sp
	ldr	r6,[r6]
	mov	r7,r6

				ldr R6, =0x4 ;(4)

	add	sp,r6,sp
	mov	pc,lr
_main:

				ldr R6, =0xFFFFFFF0 ;(-16)

	add	sp,r6,sp

			
				ldr R6, =0xC ;(12)

	add	r6,r6,sp
	str	r7,[r6]

				ldr R6, =0xC ;(12)
	add		r6,sp
	mov	r7,r6

			
				ldr R6, =0xFFFFFFFC ;(-4)

	adds	r6,r6,r7

		mov r0, r8
			mov r8, r0
			movs r0, #0x0
			add r0, lr
	str	r0,[r6]
			mov r0, r8
	b	_0x0

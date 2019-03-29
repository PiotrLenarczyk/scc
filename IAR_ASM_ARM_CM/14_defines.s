//==========================================
num	set	0x11223344	;number in memory

definedNum equ 4 ;#define



main:    
	ldr r0, =num
	ldr r1, =num
	ldr r2, =num
	ldr r3, tab
	ldr r4, tab+definedNum
	ldr r5, tab+8
	
	movs r0, #0x4
	movs r1, #0x5
	bl jumpFunc
jumpFunc:
	adr r3, jumpTab
	movs r4, #0x0
	mov	pc, r3
	
loop:
	B loop
//==========================================
doAdd	add r0, r0, r1
		mov pc,lr
doSub	subs r0, r0, r1
		mov pc, lr
	data
tab	dcd	0x11223344	;declared array on 4B type
	dcd	0x55667788
str1	dc8	"text samples!",0
jumpTab dcd doAdd
//		dcd doSub
		ltorg

//==========================================

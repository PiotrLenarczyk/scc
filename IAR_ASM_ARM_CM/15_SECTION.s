thumb
main:
	ldr r7, =consts
	ldr r0, [r7]
	adds r7, #0x4
	ldr r1, [r7]
	B endMain	;othercase consts will be executed as instructions!!!
	movs r1, #0x0	;this instruction should not be executed	
	DATA
consts	dcd	0xAABBCCDD
		dcd 0x55667788
endMain:
//
//;MYxxxxx RELOCABLE SECTION
//	section MYDATA:DATA(2)
//	DATA
//myConsts	dcd	0x12345678
//			dcd	0x98765443
//	
//	section MYCODE:CODE(2)
//	movs r3, #0xAF
//	ldr r6, =myConsts
//	ldr r2, [r6]
//	
	

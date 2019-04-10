THUMB				;program	for procedures with return
				bl		main
				
procedureWithRet:
				movs		r1, #0xA
				mov		pc, lr
				
someInstructions:
				movs		r1, #0
				
main:
				bl		procedureWithRet
				adds		r1, r1, #0x1

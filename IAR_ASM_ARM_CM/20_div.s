thumb
main:
;CM0 DIVISION codereview: unsigned integer division arm cortex m0
;input: R0=divisor, R1=dividend; resultR0=R1/R0
;output: R0=quotient, R1=reminder
;	div by 0: R0,R1 unchanged; C flag set
	movs r1, #0x7
	movs r0, #0x3
		movs r2, #0xFF
divu:
	cmp	r1, #0x0
	beq	zero_dividend
	
	cmp r0, #0x0
	beq	div_by_zero
	
	;push {r2, lr}	;save bx lr
		push {r2}
	movs r2, #0x0	;r2=quotient=repeated substraction counter
sub_loop:			;do{
	adds r2, #0x1	;quotient+=1 (init is 0x0; so single pass loop is 0x1)
	subs r1, r1, r0		;dividend-=divisor; sets flag
	;cmp r0, r1
	bhs sub_loop	;}while(1); while divisor was unsigned lower, than old value of dividend



;endwhile	;removes single cmp instruction from while loop
	;case, that there where too many substractions 
	add r1, r0			;remainder, undo overflow
	subs r0,r2, #0x1	;quotient undo overflow, and setting of C flag
;	cmp r0, r0			;clear C flag
	movs r2, #0x0
	msr apsr, r2
	;pop {r2, pc}
		pop {r2}
		b endDiv
	
	
;====
div_by_zero:
	subs r0, #0x1	;set the C flag; restore R0 in next label
	
zero_dividend:	;CMP cleared the flag
	movs	r0, #0x0 ;movs does not affect C flag
	;bx	lr
	b endDiv
	
endDiv:
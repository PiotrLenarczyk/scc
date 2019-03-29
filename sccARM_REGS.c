#define NULL_ADDR	NULL_ADDR
#define T0	R3	//first temporary reg
#define	A0	R1	//first argument reg
#define	GP 	PC
#define	FP 	R7
#define	V0	R1
#define	RA	LR
	enum {
		NULL_ADDR, 
		R0, R1, R2, R3, R4, R5, R6, R7, 
		SP, LR, PC, APSR		//SP = MSP
	};
	char	*regname[32] = {
		"0", 	
		"r0", 	"r1", 	"r2", 	"r3", 	"r4", 	"r5", 	"r6",	"r7",
		"sp", 	"lr", 	"pc", 	"apsr", 
	};
//=====================================================
//{r0-r2}	-	GPR's
//{r3-r5}	-	temporary GPR's
//{r6-r7}	-	spare
//{r8-12}	-	immediate stuff handling via stacking regs to higher regs
//=====================================================
//=====================================================
//MACROS:	
//	ldrW	rDst, 	rSrc, immed	//load 4B immediate; rSrc 0x0
//	ldrHi2B	rDst, 	rSrc, immed	//load higher 2B immediate; rSrc 0x0
//	ldrLo2B	rDst,	rSrc, immed	//load lower 2B immediate;	rSrc 0x0
//	ldr1stB	rDst,	rSrc, immed	//load first lowest byte
//	ldr2ndB	rDst,	rSrc, immed	//load second byte
//	ldr3rdB	rDst,	rSrc, immed //load third byte
//	ldr4thB rDst, 	rSrc, immed //load fouth byte
//=====================================================	


void
printReg(register int r)
{	register char *s = regname[r];

	//printChar('$');
	while (*s) 
	{	printChar(*s);
		++s;
	};
};






















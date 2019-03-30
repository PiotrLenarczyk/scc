	enum {
		ZERO,	AT,	V0,	V1,	A0,	A1,	A2,	A3,
		T0,	T1,	T2,	T3,	T4,	T5,	T6,	T7,
		S0,	S1,	S2,	S3,	S4,	S5,	S6,	S7,
		T8,	T9,	K0,	K1,	GP,	SP,	FP,	RA
	};


	char	*regname[32] = {
		"0",	"at",	"v0",	"v1",	"a0",	"a1",	"a2",	"a3",
		"t0",	"t1",	"t2",	"t3",	"t4",	"t5",	"t6",	"t7",
		"s0",	"s1",	"s2",	"s3",	"s4",	"s5",	"s6",	"s7",
		"t8",	"t9",	"k0",	"k1",	"gp",	"sp",	"fp",	"ra"
	};

	void
	printReg(register int r)
	{	register char *s = regname[r];

		printChar('$');
		while (*s) 
		{	printChar(*s);
			++s;
		};
	};

	void
	printImmediate(register int r)
	{	printf("0x%X", r);
	};
	
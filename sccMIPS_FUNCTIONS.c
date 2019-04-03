
#define	TOS	(T0 + (sp-1))
#define	NOS	(T0 + (sp-2))
#define	TMP	(T0 + sp)

	//immediate value
	void
	mips_immed(register int rt,
	register int rs,
	register int immed)
	{	print_rt(rt);
		printComma();
		print_rs(rs);
		printComma();
		printImmediate10(immed);
		printNewLine();
	};
	
	//address offset
	void
	mips_offset(register int rt,
	register int rs,
	register int immed)
	{	print_rt(rt);
		printComma();
		print_rs(rs);
		printComma();
		printChar('_');
		printNumber10(immed);
		printNewLine();
	};

	//Rdest, Roperand1, Roperand2
	void
	mips_3reg(register int rd,
	register int rs,
	register int rt)
	{	print_rt(rd);
		printComma();
		print_rs(rs);
		printComma();
		print_rs(rt);
		printNewLine();
	};

	//left shift
	void
	mips_ls(register int rt,
	register int immed,
	register int rs)
	{	print_rt(rt);
		printComma();
		printImmediate10(immed);
		printChar('(');
		print_rs(rs);
		printChar(')');
		printNewLine();
	};

	//load unsigned immediate
	void
	mips_lui(register int rt,
	register int immed)
	{	printOperand("lui");
		print_rs(rt);
		printComma();
		printImmediate10(immed);
		printNewLine();
	};

	//immediate addtion
	void
	mips_addi(register int rt,
	register int rs,
	register int immed)
	{	printOperand("addi");
		mips_immed(rt, rs, immed);
	};

	//immediate OR
	void
	mips_ori(register int rt,
	register int rs,
	register int immed)
	{	printOperand("ori");
		mips_immed(rt, rs, immed);
	};

	//immediate XOR
	void
	mips_xori(register int rt,
	register int rs,
	register int immed)
	{	printOperand("xori");
		mips_immed(rt, rs, immed);
	};

	//branch on equal
	void
	mips_beq(register int rt,
	register int rs,
	register int immed)
	{	printOperand("beq");
		mips_offset(rt, rs, immed);
	};

	//branch on not equal`
	void
	mips_bne(register int rt,
	register int rs,
	register int immed)
	{	printOperand("bne");
		mips_offset(rt, rs, immed);
	};

	//jump for address stored in register
	void
	mips_jr(register int r)
	{	printOperand("jr");
		printReg(r);
		printNewLine();
	};

	//allocate nuninitialized memory`
	void
	mips_space(register int n)
	{	printStr("\t.space\t");
		printNumber10(n);
		printNewLine();
	};

	//unsigned OR
	void
	mips_or(register int rd,
	register int rs,
	register int rt)
	{	printOperand("or");
		mips_3reg(rd, rs, rt);
	};

	//unsigned XOR
	void
	mips_xor(register int rd,
	register int rs,
	register int rt)
	{	printOperand("xor");
		mips_3reg(rd, rs, rt);
	};

	//unsigned AND
	void
	mips_and(register int rd,
	register int rs,
	register int rt)
	{	printOperand("and");
		mips_3reg(rd, rs, rt);
	};

	//unsigned addition
	void
	mips_addu(register int rd,
	register int rs,
	register int rt)
	{	printOperand("addu");
		mips_3reg(rd, rs, rt);
	}

	//unsigned substraction
	void
	mips_subu(register int rd,
	register int rs,
	register int rt)
	{	printOperand("subu");
		mips_3reg(rd, rs, rt);
	};

	//set value if one reg is less than other reg
	void
	mips_slt(register int rd,
	register int rs,
	register int rt)
	{	printOperand("slt");
		mips_3reg(rd, rs, rt);
	};

	//set value if one reg is less than other reg
	void
	mips_sltu(register int rd,
	register int rs,
	register int rt)
	{	printOperand("sltu");
		mips_3reg(rd, rs, rt);
	};

	//shift left logical value
	void
	mips_sllv(register int rd,
	register int rs,
	register int rt)
	{
		printOperand("sllv");
		mips_3reg(rd, rs, rt);
	}

	//shift right arithmetic
	void
	mips_srav(register int rd,
	register int rs,
	register int rt)
	{	printOperand("srav");
		mips_3reg(rd, rs, rt);
	};

	//store 4B word
	void
	mips_sw(register int rt,
	register int immed,
	register int rs)
	{	printOperand("sw");
		mips_ls(rt, immed, rs);
	};

	//store 2B halfword
	void
	mips_sh(register int rt,
	register int immed,
	register int rs)
	{	printOperand("sh");
		mips_ls(rt, immed, rs);
	};

	//store 1B byte
	void
	mips_sb(register int rt,
	register int immed,
	register int rs)
	{	printOperand("sb");
		mips_ls(rt, immed, rs);
	};

	//load 4B word
	void
	mips_lw(register int rt,
	register int immed,
	register int rs)
	{	printOperand("lw");
		mips_ls(rt, immed, rs);
	};

	//load 2B halfword
	void
	mips_lh(register int rt,
	register int immed,
	register int rs)
	{	printOperand("lh");
		mips_ls(rt, immed, rs);
	};

	//load 1B byte
	void
	mips_lb(register int rt,
	register int immed,
	register int rs)
	{	printOperand("lb");
		mips_ls(rt, immed, rs);
	};

	//text section
	void
	mips_text(void)
	{	printStr("\t.text\n");
	};

	//data section
	void
	mips_data(int n)
	{	printStr("\t.data\t");
		printNumber10(n);
		printChar('\n');
	};

	//jump label
	void
	mips_j(register char *s)
	{	printOperand("j");
		while (*s)
		{	printChar(*s);
			++s;
		}
		printNewLine();
	};

	//jump _label
	void
	mips_j_(register int n)
	{	printOperand("j");
		printChar('_');
		printNumber10(n);
		printNewLine();
	};

	//jump and link _label
	void
	mips_jal_(register char *s)
	{	printOperand("jal");
		printChar('_');
		while (*s)
		{	printChar(*s);
			++s;
		};
		printNewLine();
	};

	//assembler specific syscall
	void
	mips_syscall(void)
	{	printStr("\tsyscall\n");
	};

	//global variable attribute
	void
	mips_globl(register char *s)
	{	printStr("\t.globl\t");
		while (*s)
		{	printChar(*s);
			++s;
		};
		printNewLine();
	};

	//global attribute for _variable
	void
	mips_globl_(register char *s)
	{	printStr("\t.globl\t_");
		while (*s)
		{	printChar(*s);
			++s;
		};
		printNewLine();
	};

	//label:
	void
	mips_label(register char *s)
	{	while (*s) 
		{	printChar(*s);
			++s;
		}
		printStr(":\n");
	}

	//_numLabel:
	void
	mips_label_(register int n)
	{	printChar('_');
		printNumber10(n);
		printStr(":\n");
	};

	//_prelabel
	void
	mips_prelabel(register char *s)
	{
		printChar('_');
		while (*s) {
			printChar(*s);
			++s;
		}
		printStr(":\n");
	}

	//push number on stack`
	void
	pushnum(register int n)
	{	incSp();
		/* Try to optimize immediate handling...
		   ori immediate doesn't sign extend,
		   addi immediate does
		*/
		if ((n & 0xffff8000) == 0xffff8000) {
			mips_addi(TOS, 0, n);
		} else if ((n & 0xffff0000) == 0) {
			mips_ori(TOS, 0, n);
		} else if ((n & 0x0000ffff) == 0) {
			mips_lui(TOS, ((n >> 16) & 0xffff));
		} else {
			mips_lui(TOS, ((n >> 16) & 0xffff));
			mips_ori(TOS, TOS, (n & 0xffff));
		};
		objsize[sp-1] = 0;
	};

	//
	void
	pushgpoff(register int off)
	{	incSp();
		mips_addi(TOS, GP, off);
		objsize[sp-1] = 0;
	};
	
	
	void
	pushfpoff(register int off)
	{	incSp();
		mips_addi(TOS, FP, off);
		objsize[sp-1] = 0;
	};
	
	//push data up
	void
	pushdup(void)
	{	incSp();
		mips_or(TOS, NOS, 0);
		objsize[sp-1] = objsize[sp-2];
	};

	//push argument
	void
	pusharg(register int argno)
	{	incSp();
		mips_or(TOS, (A0 + argno), 0);
		objsize[sp-1] = 0;
	};

	//variable value
	void
	lval(register int size)
	{	objsize[sp-1] = size;
	};

	//load top of stack
	void
	loadtos(void)
	{	/* Need both TOS loaded from memory? */
		switch (objsize[sp-1]) 
		{	case 0:	return;
			case 1: mips_lb(TOS, 0, TOS); break;
			case 2: mips_lh(TOS, 0, TOS); break;
			case 4: mips_lw(TOS, 0, TOS); break;
			default:
				error("cannot load %d-byte object",
					  objsize[sp-1]);
		};
		objsize[sp-1] = 0;
	};

	//load next on stack, top of stack
	void
	loadnostos(void)
	{	/* Need either NOS or TOS loaded from memory? */
		decSp();
		loadtos();
		incSp();
		loadtos();
	};

	//load next on stack
	void
	loadnos(void)
	{	/* Need NOS loaded from memory? */
		decSp();
		loadtos();
		incSp();
	};

	//set argument
	void
	setarg(register int argno)
	{	loadtos();
		mips_or((A0 + argno), TOS, 0);
		decSp();
	};

	//push operand
	void
	pushop(register int op)
	{	switch (op) 
		{	case NEG:
				loadtos();
				mips_subu(TOS, 0, TOS);
				break;
			case '!':
				loadtos();
				mips_sltu(TOS, 0, TOS);
				break;
			case '~':
				loadtos();
				mips_xori(TOS, TOS, -1);
				break;
			case MULBY4:
				loadtos();
				mips_addu(TOS, TOS, TOS);
				mips_addu(TOS, TOS, TOS);
				break;
			case MULBY2:
				loadtos();
				mips_addu(TOS, TOS, TOS);
				break;
			case AFP:
				loadtos();
				mips_addu(TOS, TOS, FP);
				break;
			case ASP:
				loadtos();
				mips_addu(TOS, TOS, SP);
				break;
			case AGP:
				loadtos();
				mips_addu(TOS, TOS, GP);
				break;
			case RETVAL:
				loadtos();
				mips_or(V0, TOS, 0);
				decSp();
				break;
			case '+':
				loadnostos();
				mips_addu(NOS, NOS, TOS);
				decSp();
				break;
			case '-':
				loadnostos();
				mips_subu(NOS, NOS, TOS);
				decSp();
				break;
			case SL:
				loadnostos();
				mips_sllv(NOS, NOS, TOS);
				decSp();
				break;
			case SR:
				loadnostos();
				mips_srav(NOS, NOS, TOS);
				decSp();
				break;
			case LE:
				loadnostos();
				mips_slt(TMP, TOS, NOS);	/* GT */
				mips_slt(NOS, NOS, TOS);	/* LT */
				mips_or(TMP, NOS, TMP);		/* NE */
				mips_xori(TMP, TMP, 1);		/* EQ */
				mips_or(NOS, NOS, TMP);
				decSp();
				break;
			case '<':
				loadnostos();
				mips_slt(NOS, NOS, TOS);
				decSp();
				break;
			case GE:
				loadnostos();
				mips_slt(TMP, NOS, TOS);	/* LT */
				mips_slt(NOS, TOS, NOS);	/* GT */
				mips_or(TMP, NOS, TMP);		/* NE */
				mips_xori(TMP, TMP, 1);		/* EQ */
				mips_or(NOS, NOS, TMP);
				decSp();
				break;
			case '>':
				loadnostos();
				mips_slt(NOS, TOS, NOS);
				decSp();
				break;
			case EQ:
				loadnostos();
				mips_xor(NOS, NOS, TOS);	/* NE */
				mips_sltu(NOS, 0, NOS);
				mips_xori(TMP, TMP, 1);
				decSp();
				break;
			case NE:
				loadnostos();
				mips_xor(NOS, NOS, TOS);	/* NE */
				mips_sltu(NOS, 0, NOS);
				decSp();
				break;
			case '&':
				loadnostos();
				mips_and(NOS, NOS, TOS);
				decSp();
				break;
			case '^':
				loadnostos();
				mips_xor(NOS, NOS, TOS);
				decSp();
				break;
			case '|':
				loadnostos();
				mips_or(NOS, NOS, TOS);
				decSp();
				break;
			default:
				error("cannot yet handle op (%c)", op);
		};
	};

	//store 4B/2B/1B
	void
	store(register int prop)
	{	/* Store TOS into NOS */
		loadtos();
		switch (objsize[sp-2]) 
		{	case 0: error("lvalue required");
			case 1: mips_sb(TOS, 0, NOS); break;
			case 2: mips_sh(TOS, 0, NOS); break;
			case 4: mips_sw(TOS, 0, NOS); break;
			default:
				error("cannot store %d-byte object",
					  objsize[sp-2]);
		};

		if (prop) 
		{	/* Just in case we have x=(y=z)...
			   Strictly speaking, x=(y=z) sets x=((typeof(y))z),
			   but I don't think we have to be that precise here
			*/
			mips_or(NOS, TOS, 0);
			decSp();
			objsize[sp-1] = 0;
		} else 
		{	decSp();
			decSp();
		};
	};

	//jump _label
	void
	jump(register int a)
	{	/* Compiler-generated labels are nearby...
		   so use a branch instead
		*/
		mips_j_(a);
	};

	//jump on false
	void
	jumpf(register int a)
	{	loadtos();
		mips_beq(TOS, 0, a);
		decSp();
	};

	//jump on true
	void
	jumpt(register int a)
	{	loadtos();
		mips_bne(TOS, 0, a);
		decSp();
	};

	//label
	void
	label(register int a)
	{
		mips_label_(a);
	};

	//goto implementation
	void
	ghoto(register char *s)
	{	mips_j(s);
	};

	//
	void
	target(register char *s)
	{	mips_prelabel(s);
	};

	//MIPS startup
	void
	startup(void)
	{	mips_text();
		mips_globl("main");
		mips_globl_("exit");
		mips_globl_("print_int");
		mips_globl_("print_string");
		mips_label("main");
		mips_lui(GP, ((DATABASE >> 16) & 0xffff));
		mips_jal_("main");
		mips_label("_exit");
		mips_ori(V0, 0, 10);
		mips_syscall();
		mips_label("_print_int");
		mips_ori(V0, 0, 1);
		mips_syscall();
		mips_jr(RA);
		mips_label("_print_string");
		mips_ori(V0, 0, 4);
		mips_syscall();
		mips_jr(RA);
	}

	//call function
	void
	call(register int mysym)
	{	register char *n = nameString(symtab[mysym].ipos);
		register int i;
		/* We're not a leaf procedure.... */
		isleaf = 0;

		/* Save registers */
		if (sp > 0) 
		{	mips_addi(SP, SP, -4*(TOS-T0+1));
			for (i=T0; i<=TOS; ++i) 
			{	mips_sw(i, -4*(i-T0), SP);
			};
		};

		/* Call the function */
		mips_jal_(n);

		/* Restore registers */
		if (sp > 0) 
		{	for (i=T0; i<=TOS; ++i) 
			{	mips_lw(i, -4*(i-T0), SP);
			};
			mips_addi(SP, SP, 4*(TOS-T0+1));
		};

		/* Copy the return value to someplace useful */
		incSp();
		mips_or(TOS, V0, 0);
		objsize[sp-1] = 0;
	};


	//function begin
	void
	funcbegin(register int mysym)
	{	register char *n = nameString(symtab[mysym].ipos);

		fpoffset = -4;
		highwater = 0;
		beginlab = labelNum++;
		endlab = labelNum++;

		/* For now, functions always return an int */
		symtab[mysym].type = FUNC;
		symtab[mysym].base = -4;
		symtab[mysym].size = 4;
		symtab[mysym].dim = 1;

		++scope;

		/* So far, we could be a leaf procedure.... */
		isleaf = 1;

		mips_text();
		mips_globl_(n);
		label(beginlab);
	};


	//function end
	void
	funcend(register int mysym)
	{	register char *n = nameString(symtab[mysym].ipos);

		/* For now, functions always return an int */
		symtab[mysym].type = FUNC;
		symtab[mysym].base = -4;
		symtab[mysym].size = 4;
		symtab[mysym].dim = 1;

		/* Now the common end return code...
		   but special-case leaf procedures
		*/
		if ((isleaf == 0) || (highwater != 0)) 
		{	/* Not a leaf; do full stack frame...
			   Stack looks like:
			   [old fp] [ret addr] [locals]
			   we do this here because that's when we know
			   how much space we need for locals...
			*/
			/* Add space for fp and return address */
			highwater += 8;	

			label(endlab);
			mips_lw(RA, -4, FP);		/* ra = fp[-4] */
			mips_or(SP, FP, 0);		/* sp = fp */
			mips_lw(FP, 0, SP);		/* fp = old fp */
			mips_addi(SP, SP, 4);		/* sp = old sp */
			mips_jr(RA);			/* return */
			mips_prelabel(n);
			mips_addi(SP, SP, -highwater);	/* sp -= highwater */
			mips_sw(FP, highwater-4, SP);	/* sp[highwater-4] = fp */
			mips_addi(FP, SP, highwater-4);	/* fp = &(sp[highwater-4]) */
			mips_sw(RA, -4, FP);		/* fp[-4] = ra */
		} else 
		{	/* A leaf without locals... */
			label(endlab);
			mips_jr(RA);			/* return */
			mips_prelabel(n);
		}

		jump(beginlab);

		--scope;
	};

	//variable definition
	void
	def(register int mysym)
	{	register char *n = nameString(symtab[mysym].ipos);
		register int asize;
		/* Objects always are 4-byte word alligned... */
		asize = (((symtab[mysym].size * symtab[mysym].dim) + 3) & ~3);

		symtab[mysym].type = VAR;
		if ((symtab[mysym].scope = scope) == 0) 
		{	/* Offset from $gp */
			symtab[mysym].base = gpoffset;
			gpoffset += asize;

			mips_data(DATABASE + symtab[mysym].base);
			mips_globl(n);
			mips_label(n);
			mips_space(asize);
		} else 
		{	/* Offset from $fp */
			fpoffset -= asize;
			symtab[mysym].base = fpoffset;

			if (highwater < -fpoffset) 
			{	highwater = -fpoffset;
			};
		};
	};

	//define string variable
	int
	defstr(register int spos)
	{	register int num;
		register int asize;

		mips_data(DATABASE + gpoffset);

		asize = 0;
		while (input[++spos] != '"') 
		{	if (++asize > 1) 
			{	if ((asize & 7) == 1) 
				{	printNewLine();
					printStr("\t.byte\t");
				} else 
				{	printStr(", ");
				};
			} else 
			{	printStr("\t.byte\t");
			};
			if (input[spos] == '\\') 
			{	switch (input[++spos]) 
				{	case 't':	printf("%3d", '\t'); break;
					case 'n':	printf("%3d", '\n'); break;
					case 'r':	printf("%3d", '\r'); break;
					case 'b':	printf("%3d", '\b'); break;
					case '0':	case '1':	case '2':
					case '3':	case '4':	case '5':
					case '6':	case '7':
						num = (input[spos] - '0');
						while ((input[spos+1] >= '0') &&
							   (input[spos+1] <= '7')) {
							num *= 8;
							num += (input[++spos] - '0');
						}
						printf("%3d", num);
						break;
					default:
						printf("%3d", input[spos]);
				};
			} else 
			{	printf("%3d", input[spos]);
			};
		};

		++asize;
		printf("\n"
			   "\t.byte\t0\n"
			   "\n"
			   "\t.text\n");

		/* Make size a multiple of 4 bytes for allignment... */
		asize = ((asize + 3) & ~3);
		gpoffset += asize;
		return(DATABASE + gpoffset - asize);
	};
	
		
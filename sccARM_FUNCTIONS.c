
#define	TOS	( T0 + ( sp-1 ) )
#define	NOS	( T0 + ( sp-2 ) )
#define	TMP	( T0 + sp )

void 
printImmedShifted( register int rTarget,
register int immed4B, 
register int bitLeftShift)
{	printSharp();
	printStr( "((" );
	printNumber( immed4B );
	printStr( " >> " );
	printNumber( bitLeftShift );
	printStr( ") & 0xFF)" );
};

void arm_loadImmed( register int rTarget,
register int immed )
{	printTab();
	printOperand(  "movs"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( rTarget, immed, 0x0 ); 
	printNewLine();
	printTab();
	printOperand(  "adds"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( rTarget, immed, 0x8 ); 
	printNewLine();
	printTab();
	printOperand(  "adds"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( rTarget, immed, 0x10 ); 
	printNewLine();
	printTab();
	printOperand(  "adds"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( rTarget, immed, 0x18 ); 
	printNewLine();
	printTab();
	printOperand(  "mov"  );
	print_rt( rTarget );
	printComma();
	print_rt( R6 );
};

//void operandImmediate( "adds", "r0, "r1", "#-15" )
void
foo()
{	
	register int rTarget = 0x2;
	register int rs = 0x1;
	register int immed = -15;
	char inOperand[] = "adds";
	arm_loadImmed( rTarget, immed );
	
	
	
	printNewLine();
	printTab();
	printStr( inOperand );
	printTab();
	print_rt( rs );
	printComma();
	printReg( rTarget );
	printNewLine();
};

		//immediate value
		void
		arm_immed( register int rt,
		register int rs,
		register int immed ) 
		{	print_rt( rt );
			printComma();
			if (rs)
			{	print_rs( rs );
				printComma();
			};
			printImmediate( immed );
			printNewLine();
		};

//address offset
void
arm_offset( register int rt,
register int rs,
register int immed )
{	print_rt( rt );
	printComma();
	print_rs( rs );
	printComma();
	printChar( '_' );
	printNumber( immed );
	printNewLine();
};

//Rdest, Roperand1, Roperand2
void
arm_3reg( register int rd,
register int rs,
register int rt )
{	print_rt( rd );
	printComma();
	print_rs( rs );
	printComma();
	print_rs( rt );
	printNewLine();
};

//load register-relative immediate offset
void
arm_ls( register int rt,
register int immed,
register int rs )
{	print_rt( rt );
	printComma();
	printChar( '[' );
	print_rs( rs );
	printComma();
	printImmediate( immed );
	printChar( ']' );
	printNewLine();
};

		//lui - load reg upper 2B with immediate ?
		void
		arm_movs( register int rt,
		register int immed )
		{	printOperand(  "movs"  );
			print_rs( rt );
			printComma();
			printImmediate( immed );
			printNewLine();
		};

//immediate OR
void
arm_ori( register int rt,
register int rs,
register int immed )
{	printOperand(  "ldrW"  );
	arm_immed( rt, rs, immed );
	printOperand(  "orrs"  );
	arm_immed( rt, rs, immed );
};

		//immediate addtion
		void
		arm_adds( register int rt,
		register int rs,
		register int immed )
		{	printOperand(  "adds"  );
			arm_immed( rt, rs, immed );
		};

//immediate XOR
void
arm_xori( register int rt,
register int rs,
register int immed )
{	printOperand(  "xori"  );
	arm_immed( rt, rs, immed );
};

		//branch on equal
		void
		arm_beq( register int rt,
		register int rs,
		register int immed )
		{	printOperand(  "beq"  );
			arm_offset( rt, rs, immed );
		};

		//branch on not equal`
		void
		arm_bne( register int rt,
		register int rs,
		register int immed )
		{	printOperand(  "bne"  );
			arm_offset( rt, rs, immed );
		};

		//jump for address stored in register
		void
		arm_jr( register int r )
		{	printOperand(  "j"  );
			printReg( r );
			printNewLine();
		};

//allocate nuninitialized memory
void
arm_space( register int n )
{	printStr(  "\t.space\t"  );
	printNumber( n );
	printNewLine();
};

		//unsigned OR
		void
		arm_or( register int rd,
		register int rs,
		register int rt )
		{	printOperand(  "orrs"  );
			arm_3reg( rd, rs, rt );
		};

//unsigned XOR
void
arm_xor( register int rd,
register int rs,
register int rt )
{	printOperand(  "xor"  );
	arm_3reg( rd, rs, rt );
};

//unsigned AND
void
arm_and( register int rd,
register int rs,
register int rt )
{	printOperand(  "and"  );
	arm_3reg( rd, rs, rt );
};

//unsigned addition
void
arm_addu( register int rd,
register int rs,
register int rt )
{	printOperand(  "addu"  );
	arm_3reg( rd, rs, rt );
}

//unsigned substraction
void
arm_subu( register int rd,
register int rs,
register int rt )
{	printOperand(  "subu"  );
	arm_3reg( rd, rs, rt );
};

//set value if one reg is less than other reg
void
arm_slt( register int rd,
register int rs,
register int rt )
{	printOperand(  "slt"  );
	arm_3reg( rd, rs, rt );
};

//set value if one reg is less than other reg
void
arm_sltu( register int rd,
register int rs,
register int rt )
{	printOperand(  "sltu"  );
	arm_3reg( rd, rs, rt );
};

//shift left logical value
void
arm_sllv( register int rd,
register int rs,
register int rt )
{
	printOperand(  "sllv"  );
	arm_3reg( rd, rs, rt );
}

//shift right arithmetic
void
arm_srav( register int rd,
register int rs,
register int rt )
{	printOperand(  "srav"  );
	arm_3reg( rd, rs, rt );
};

//store 4B word
void
arm_sw( register int rt,
register int immed, 
register int rs )
{	printOperand(  "str"  );
	arm_ls( rt, immed, rs );
};

//store 2B halfword
void
arm_sh( register int rt,
register int immed,
register int rs )
{	printOperand(  "sh"  );
	arm_ls( rt, immed, rs );
};

//store 1B byte
void
arm_sb( register int rt,
register int immed,
register int rs )
{	printOperand(  "sb"  );
	arm_ls( rt, immed, rs );
};

//load 4B word
void
arm_lw( register int rt,
register int immed,
register int rs )
{	printOperand(  "lw"  );
	arm_ls( rt, immed, rs );
};

//load 2B halfword
void
arm_lh( register int rt,
register int immed,
register int rs )
{	printOperand(  "lh"  );
	arm_ls( rt, immed, rs );
};

//load 1B byte
void
arm_lb( register int rt,
register int immed,
register int rs )
{	printOperand(  "lb"  );
	arm_ls( rt, immed, rs );
};

//text section
void
arm_text( void )
{	printStr(  "\t.text\n"  );
};

//data section
void
arm_data( int n )
{	printStr(  "\t.data\t"  );
	printNumber( n );
	printChar( '\n' );
};

//jump label
void
arm_j( register char *s )
{	printOperand(  "j"  );
	while ( *s )
	{	printChar( *s );
		++s;
	}
	printNewLine();
};

//jump _label
void
arm_j_( register int n )
{	printOperand(  "j"  );
	printChar( '_' );
	printNumber( n );
	printNewLine();
};

		//jump and link _label
		void
		arm_bl_( register char *s )
		{	printOperand(  "bl"  );
			printChar( '_' );
			while ( *s )
			{	printChar( *s );
				++s;
			};
			printNewLine();
		};

//assembler specific syscall
void
arm_syscall( void )
{	printStr(  "\tsyscall\n"  );
};

//global variable attribute
void
arm_globl( register char *s )
{	printStr(  "\t.globl\t"  );
	while ( *s )
	{	printChar( *s );
		++s;
	};
	printNewLine();
};

//global attribute for _variable
void
arm_globl_( register char *s )
{	printStr(  "\t.globl\t_"  );
	while ( *s )
	{	printChar( *s );
		++s;
	};
	printNewLine();
};

//label:
void
arm_label( register char *s )
{	while ( *s ) 
	{	printChar( *s );
		++s;
	}
	printStr(  ":\n"  );
}

//_numLabel:
void
arm_label_( register int n )
{	printChar( '_' );
	printNumber( n );
	printStr(  ":\n"  );
};

//_prelabel
void
arm_prelabel( register char *s )
{
	printChar( '_' );
	while ( *s ) {
		printChar( *s );
		++s;
	}
	printStr(  ":\n"  );
}

//push number on stack
void
pushnum( register int n )
{	incSp();
	/* Try to optimize immediate handling...
	   ori immediate doesn't sign extend,
	   addi immediate does
	*/
	if ( ( n & 0xffff8000 ) == 0xffff8000 ) 
	{	arm_adds(  TOS, 0, n  );
	} else if ( ( n & 0xffff0000 ) == 0 ) 
	{	arm_ori( TOS, 0, n );
	} else if ( ( n & 0x0000ffff ) == 0 ) 
	{	arm_movs( TOS, ( ( n >> 16 ) & 0xffff ) );
	} else 
	{	arm_movs( TOS, ( ( n >> 16 ) & 0xffff ) );
		arm_ori( TOS, TOS, ( n & 0xffff ) );
	};
	objsize[sp-1] = 0;
};

//
void
pushgpoff( register int off )
{	incSp();
	arm_adds( TOS, GP, off );
	objsize[sp-1] = 0;
};


void
pushfpoff( register int off )
{	incSp();
	arm_adds( TOS, FP, off );
	objsize[sp-1] = 0;
};

//push data up
void
pushdup( void )
{	incSp();
	arm_or( TOS, NOS, 0 );
	objsize[sp-1] = objsize[sp-2];
};

//push argument
void
pusharg( register int argno )
{	incSp();
	arm_or( TOS, ( A0 + argno ), 0 );
	objsize[sp-1] = 0;
};

//variable value
void
lval( register int size )
{	objsize[sp-1] = size;
};

//load top of stack
void
loadtos( void )
{	/* Need both TOS loaded from memory? */
	switch ( objsize[sp-1] ) 
	{	case 0:	return;
		case 1: arm_lb( TOS, 0, TOS ); break;
		case 2: arm_lh( TOS, 0, TOS ); break;
		case 4: arm_lw( TOS, 0, TOS ); break;
		default:
			error(  "cannot load %d-byte object",
				  objsize[sp-1] );
	};
	objsize[sp-1] = 0;
};

//load next on stack, top of stack
void
loadnostos( void )
{	/* Need either NOS or TOS loaded from memory? */
	decSp();
	loadtos();
	incSp();
	loadtos();
};

//load next on stack
void
loadnos( void )
{	/* Need NOS loaded from memory? */
	decSp();
	loadtos();
	incSp();
};

//set argument
void
setarg( register int argno )
{	loadtos();
	arm_or( ( A0 + argno ), TOS, 0 );
	decSp();
};

//push operand
void
pushop( register int op )
{	switch ( op ) 
	{	case NEG:
			loadtos();
			arm_subu( TOS, 0, TOS );
			break;
		case '!':
			loadtos();
			arm_sltu( TOS, 0, TOS );
			break;
		case '~':
			loadtos();
			arm_xori( TOS, TOS, -1 );
			break;
		case MULBY4:
			loadtos();
			arm_addu( TOS, TOS, TOS );
			arm_addu( TOS, TOS, TOS );
			break;
		case MULBY2:
			loadtos();
			arm_addu( TOS, TOS, TOS );
			break;
		case AFP:
			loadtos();
			arm_addu( TOS, TOS, FP );
			break;
		case ASP:
			loadtos();
			arm_addu( TOS, TOS, SP );
			break;
		case AGP:
			loadtos();
			arm_addu( TOS, TOS, GP );
			break;
		case RETVAL:
			loadtos();
			arm_or( V0, TOS, 0 );
			decSp();
			break;
		case '+':
			loadnostos();
			arm_addu( NOS, NOS, TOS );
			decSp();
			break;
		case '-':
			loadnostos();
			arm_subu( NOS, NOS, TOS );
			decSp();
			break;
		case SL:
			loadnostos();
			arm_sllv( NOS, NOS, TOS );
			decSp();
			break;
		case SR:
			loadnostos();
			arm_srav( NOS, NOS, TOS );
			decSp();
			break;
		case LE:
			loadnostos();
			arm_slt( TMP, TOS, NOS );	/* GT */
			arm_slt( NOS, NOS, TOS );	/* LT */
			arm_or( TMP, NOS, TMP );		/* NE */
			arm_xori( TMP, TMP, 1 );		/* EQ */
			arm_or( NOS, NOS, TMP );
			decSp();
			break;
		case '<':
			loadnostos();
			arm_slt( NOS, NOS, TOS );
			decSp();
			break;
		case GE:
			loadnostos();
			arm_slt( TMP, NOS, TOS );	/* LT */
			arm_slt( NOS, TOS, NOS );	/* GT */
			arm_or( TMP, NOS, TMP );		/* NE */
			arm_xori( TMP, TMP, 1 );		/* EQ */
			arm_or( NOS, NOS, TMP );
			decSp();
			break;
		case '>':
			loadnostos();
			arm_slt( NOS, TOS, NOS );
			decSp();
			break;
		case EQ:
			loadnostos();
			arm_xor( NOS, NOS, TOS );	/* NE */
			arm_sltu( NOS, 0, NOS );
			arm_xori( TMP, TMP, 1 );
			decSp();
			break;
		case NE:
			loadnostos();
			arm_xor( NOS, NOS, TOS );	/* NE */
			arm_sltu( NOS, 0, NOS );
			decSp();
			break;
		case '&':
			loadnostos();
			arm_and( NOS, NOS, TOS );
			decSp();
			break;
		case '^':
			loadnostos();
			arm_xor( NOS, NOS, TOS );
			decSp();
			break;
		case '|':
			loadnostos();
			arm_or( NOS, NOS, TOS );
			decSp();
			break;
		default:
			error(  "cannot yet handle op ( %c )", op );
	};
};

//store 4B/2B/1B
void
store( register int prop )
{	/* Store TOS into NOS */
	loadtos();
	switch ( objsize[sp-2] ) 
	{	case 0: error(  "lvalue required"  );
		case 1: arm_sb( TOS, 0, NOS ); break;
		case 2: arm_sh( TOS, 0, NOS ); break;
		case 4: arm_sw( TOS, 0, NOS ); break;
		default:
			error(  "cannot store %d-byte object",
				  objsize[sp-2] );
	};

	if ( prop ) 
	{	/* Just in case we have x=( y=z )...
		   Strictly speaking, x=( y=z ) sets x=( ( typeof( y ) )z ),
		   but I don't think we have to be that precise here
		*/
		arm_or( NOS, TOS, 0 );
		decSp();
		objsize[sp-1] = 0;
	} else 
	{	decSp();
		decSp();
	};
};

//jump _label
void
jump( register int a )
{	/* Compiler-generated labels are nearby...
	   so use a branch instead
	*/
	arm_j_( a );
};

//jump on false
void
jumpf( register int a )
{	loadtos();
	arm_beq( TOS, 0, a );
	decSp();
};

//jump on true
void
jumpt( register int a )
{	loadtos();
	arm_bne( TOS, 0, a );
	decSp();
};

//label
void
label( register int a )
{
	arm_label_( a );
};

//goto implementation
void 
ghoto( register char *s )
{	arm_j( s );
};

//
void
target( register char *s )
{	arm_prelabel( s );
};

//arm startup
void
startup( void )
{	arm_text();
	arm_globl(  "main"  );
	arm_globl_(  "exit"  );
	printStr(  ";====\n"  );
	printStr(  ";FOO\n"  );
	printStr(  ";====\n"  );
	foo(); 
	printStr(  "\n;====\n"  );
	arm_label(  "ENTRY"  );
	arm_label(  "main"  );
	arm_bl_(  "main"  );
}

//call function
void
call( register int mysym )
{	register char *n = nameString( symtab[mysym].ipos );
	register int i;
	/* We're not a leaf procedure.... */
	isleaf = 0;

	/* Save registers */
	if ( sp > 0 ) 
	{	arm_adds( SP, SP, -4*( TOS-T0+1 ) );
		for ( i=T0; i<=TOS; ++i ) 
		{	arm_sw( i, -4*( i-T0 ), SP );
		};
	};

	/* Call the function */
	arm_bl_( n );

	/* Restore registers */
	if ( sp > 0 ) 
	{	for ( i=T0; i<=TOS; ++i ) 
		{	arm_lw( i, -4*( i-T0 ), SP );
		};
		arm_adds( SP, SP, 4*( TOS-T0+1 ) );
	};

	/* Copy the return value to someplace useful */
	incSp();
	arm_or( TOS, V0, 0 );
	objsize[sp-1] = 0;
};


//function begin
void
funcbegin( register int mysym )
{	register char *n = nameString( symtab[mysym].ipos );

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

	arm_text();
	arm_globl_( n );
	label( beginlab );
};


//function end
void
funcend( register int mysym )
{	register char *n = nameString( symtab[mysym].ipos );

	/* For now, functions always return an int */
	symtab[mysym].type = FUNC;
	symtab[mysym].base = -4;
	symtab[mysym].size = 4;
	symtab[mysym].dim = 1;

	/* Now the common end return code...
	   but special-case leaf procedures
	*/
	if ( ( isleaf == 0 ) || ( highwater != 0 ) ) 
	{	/* Not a leaf; do full stack frame...
		   Stack looks like:
		   [old fp] [ret addr] [locals]
		   we do this here because that's when we know
		   how much space we need for locals...
		*/
		/* Add space for fp and return address */
		highwater += 8;	

		label( endlab );
		arm_lw( RA, -4, FP );		/* ra = fp[-4] */
		arm_or( SP, FP, 0 );		/* sp = fp */
		arm_lw( FP, 0, SP );		/* fp = old fp */
		arm_adds( SP, SP, 4 );		/* sp = old sp */
		arm_jr( RA );			/* return */
		arm_prelabel( n );
		arm_adds( SP, SP, -highwater );	/* sp -= highwater */
		arm_sw( FP, highwater-4, SP );	/* sp[highwater-4] = fp */
		arm_adds( FP, SP, highwater-4 );	/* fp = &( sp[highwater-4] ) */
		arm_sw( RA, -4, FP );		/* fp[-4] = ra */
	} else 
	{	/* A leaf without locals... */
		label( endlab );
		arm_jr( RA );			/* return */
		arm_prelabel( n );
	}

	jump( beginlab );

	--scope;
};

//variable definition
void
def( register int mysym )
{	register char *n = nameString( symtab[mysym].ipos );
	register int asize;
	/* Objects always are 4-byte word alligned... */
	asize = ( ( ( symtab[mysym].size * symtab[mysym].dim ) + 3 ) & ~3 );

	symtab[mysym].type = VAR;
	if ( ( symtab[mysym].scope = scope ) == 0 ) 
	{	/* Offset from $gp */
		symtab[mysym].base = gpoffset;
		gpoffset += asize;

		arm_data( DATABASE + symtab[mysym].base );
		arm_globl( n );
		arm_label( n );
		arm_space( asize );
	} else 
	{	/* Offset from $fp */
		fpoffset -= asize;
		symtab[mysym].base = fpoffset;

		if ( highwater < -fpoffset ) 
		{	highwater = -fpoffset;
		};
	};
};

//define string variable
int
defstr( register int spos )
{	register int num;
	register int asize;

	arm_data( DATABASE + gpoffset );

	asize = 0;
	while ( input[++spos] != '"' ) 
	{	if ( ++asize > 1 ) 
		{	if ( ( asize & 7 ) == 1 ) 
			{	printNewLine();
				printStr(  "\t.byte\t"  );
			} else 
			{	printStr(  ", "  );
			};
		} else 
		{	printStr(  "\t.byte\t"  );
		};
		if ( input[spos] == '\\' ) 
		{	switch ( input[++spos] ) 
			{	case 't':	printf(  "%3d", '\t' ); break;
				case 'n':	printf(  "%3d", '\n' ); break;
				case 'r':	printf(  "%3d", '\r' ); break;
				case 'b':	printf(  "%3d", '\b' ); break;
				case '0':	case '1':	case '2':
				case '3':	case '4':	case '5':
				case '6':	case '7':
					num = ( input[spos] - '0' );
					while ( ( input[spos+1] >= '0' ) &&
						   ( input[spos+1] <= '7' ) ) {
						num *= 8;
						num += ( input[++spos] - '0' );
					}
					printf(  "%3d", num );
					break;
				default:
					printf(  "%3d", input[spos] );
			};
		} else 
		{	printf(  "%3d", input[spos] );
		};
	};

	++asize;
	printf(  "\n"
		   "\t.byte\t0\n"
		   "\n"
		   "\t.text\n"  );

	/* Make size a multiple of 4 bytes for allignment... */
	asize = ( ( asize + 3 ) & ~3 );
	gpoffset += asize;
	return( DATABASE + gpoffset - asize );
};



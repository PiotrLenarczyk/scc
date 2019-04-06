#pragma once
#include "sccARM_REGS.c"
#define	TOS	( T0 + ( sp-1 ) )	//Top of stack
#define	NOS	( T0 + ( sp-2 ) )	//next on stack
#define	TMP	( T0 + sp )			//temporary

void 
printImmedShifted(int immed4B, 
int bitLeftShift)
{	printSharp();
	printStr( "((" );
	printNumber( immed4B );
	printStr( " >> " ); 
	printNumber( bitLeftShift );
	printStr( ") & 0xFF)" );
};

void arm_loadImmed( int immed )
{
/*
	printTab();printTab();printTab();
	printOperand(  "mov"  );	//push R7 to temporary reg - it will be restored at function end
	print_rt( R8 );
	printComma();
	print_rs( R7 );	

	printNewLine();
	printTab();printTab();printTab();
	printOperand(  "movs"  );
	print_rs( R7 );
	printComma();  
	printImmedShifted( immed, 0x0 ); 
	
	printNewLine();
	printTab();printTab();printTab();
	printOperand(  "movs"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( immed, 0x8 ); 
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "lsls" );
	print_rs( R6 );
	printComma();
	printImmediate( 0x8 );
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "orrs" );
	print_rt( R7 );
	printComma();
	print_rs( R6 );

	printNewLine();
	printTab();printTab();printTab();
	printOperand(  "movs"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( immed, 0x10 ); 
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "lsls" );
	print_rs( R6 );
	printComma();
	printImmediate( 0x10 );
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "orrs" );
	print_rt( R7 );
	printComma();
	print_rs( R6 );

	printNewLine();
	printTab();printTab();printTab();
	printOperand(  "movs"  );
	print_rs( R6 );
	printComma();
	printImmedShifted( immed, 0x18 );
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "lsls" );
	print_rs( R6 );
	printComma();
	printImmediate( 0x18 );
	printNewLine();
	printTab();printTab();printTab();
	printOperand( "orrs" );
	print_rt( R6 ); 
	printComma();
	print_rs( R7 );
	
	printNewLine();
	printTab();printTab();printTab();
	printOperand(  "mov"  );	//push R7 to temporary reg - it will be restored at function end
	print_rt( R7 );
	printComma();
	print_rs( R8 );	
//*/ 
	printNewLine();
	printTab();printTab();printTab();
	printOperand(  ";movs"  );
	print_rt( R6 );
	printStr( ",#" );
	printNumber( immed );
	printStr( " (" );
	printNumber10( immed );
	printChar( ')' );
};

void arm_addsImmed(  int rTarget, 
int immed )
{	arm_loadImmed( immed );	
	// if (immed >= 0)
	// {	printStr(",#");  
		// printNumber( immed );
	// }else
	// {	printStr(",#");
		// printNumber10( immed );
	// };
	
	printNewLine();
	printOperand( "adds" );
	print_rt( rTarget );
	printComma();
	print_rs( R6 ); 
};

void operandImmediate(char* inOperand, 
int rt,
int rs,
int immed)  
{	
	// if( rt == rs )
		// return;
	if ( rs )
	{	arm_loadImmed( immed );
		printNewLine();
		printTab();
		//printStr( inOperand );
		printf("%s",inOperand);
		printTab();
		print_rt( rt );
		printComma();
		print_rs( rs );
		printComma();
		print_rs( R6 );
		printNewLine();
		return;
	};
	if (( rs == 0x0 ) || (immed > 0xFF))
	{	rs = R6;
		arm_loadImmed( rs, immed );
		printNewLine();
		printTab();
		// printStr( inOperand );
		printf("%s",inOperand);
		printTab();
		print_rt( rt );
		printComma();
		print_rs( rs );
		printComma();
		print_rs(R6);
		printNewLine();
		return;
	};
	printNewLine();
	printTab();
	// printStr( inOperand );
	printf("%s",inOperand);
	printTab();
	print_rt( rt );
	printComma();
	printImmediate( immed );
	printNewLine();
};

//void operandImmediate( "adds", "r0, "r1", "#-15" )
void
foo()
{	
	int rTarget = 0x2;
	int rs = 0x1;
	int immed = -15;
	char inOperand[] = "adds";
};


		// //immediate value
		// void
		// arm_immed( int rt,
		// int rs,
		// int immed ) 
		// {	print_rt( rt );
			// printComma();
			// if (rs)
			// {	print_rs( rs );
				// printComma();
			// };
			// printImmediate( immed );
			// printNewLine();
		// };

//address offset
void
arm_offset( int rt,
int rs,
int immed )
{	print_rt( rt );
	printComma();
	print_rs( rs );
	printComma();
	printChar( '_' );
	printNumber( immed );
	printNewLine();
};

//Rdest, Rsource, Rtemporary
void
arm_2reg( int rd,
int rs )
{	print_rt( rd );
	printComma();
	print_rs( rs );
	printNewLine();
};

//Rdest, Rsource, Rtemporary
void
arm_3reg( int rd,
int rs,
int rt )
{	print_rt( rd );
	printComma();
	print_rs( rs );
	printComma();
	print_rs( rt );
	printNewLine();
};

//load register-relative immediate offset
void
arm_ls( int rt,
int immed,
int rs )
{	
	print_rt( rt );	//??	
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
		arm_movs( int rt,
		int immed )
		{	operandImmediate( "movs", rt, 0, immed );
		};

//immediate OR
void
arm_orImmed( int rt,
int rs,
int immed )
{	operandImmediate( "orrs", rt, rs, immed );
};

		//immediate addtion
		void
		arm_adds( int rt,
		int rs,
		int immed )
		{	operandImmediate( "adds", rt, rs, immed );
		};

//immediate XOR
void
arm_xori( int rt,
int rs,
int immed )
{	operandImmediate( "eors", rt, rs, immed );
};

		//branch on equal
		void
		arm_beq( int rt,
		int rs,
		int immed )
		{	operandImmediate( "beq", rt, rs, immed );
		};

		//branch on not equal`
		void
		arm_bne( int rt,
		int rs,
		int immed )
		{	operandImmediate(  "bne", rt, rs, immed );
		};

		//jump for address stored in register
		void
		arm_b( int r )
		{	printOperand(  "b"  );
			printReg( r );
			printNewLine();
		};

//allocate uninitialized memory
void
arm_space( int n )
{	printStr(  "\t.space\t"  );
	printNumber( n );
	printNewLine();
};

		//unsigned OR
		void
		arm_or( int rd,
		int rs,
		int rt )
		{	printOperand( "orrs" );
			arm_2reg( rd, rs );
		};

//unsigned XOR
void
arm_xor( int rd,
int rs,
int rt )
{	printOperand(  "xor"  );
	arm_3reg( rd, rs, rt );
};

//unsigned AND
void
arm_and( int rd,
int rs,
int rt )
{	printOperand(  "and"  );
	arm_3reg( rd, rs, rt );
};

//unsigned substraction
void
arm_subu( int rd,
int rs,
int rt )
{	printOperand(  "subu"  );
	arm_3reg( rd, rs, rt );
};

//set value if one reg is less than other reg
void
arm_slt( int rd,
int rs,
int rt )
{	printOperand(  "slt"  );
	arm_3reg( rd, rs, rt );
};

//set on less than; if(rs<rt)
void
arm_sltu( int rd,
int rs,
int rt )
{	printOperand(  "sltu"  );
	arm_3reg( rd, rs, rt );
};

//shift left logical variable
void
arm_sllv( int rd,
int rs,
int rt )
{
	printOperand(  "sllv"  );
	arm_3reg( rd, rs, rt );
}

//shift right arithmetic variable
void
arm_srav( int rd,
int rs,
int rt )
{	printOperand(  "srav"  );
	arm_3reg( rd, rs, rt );
};

//store 4B word
void
arm_sw( int rt,
int immed, 
int rs )
{	printNewLine();
	// printOperand(  "str"  );	//??
	//arm_ls( rt, immed, rs );
	printTab(); printTab(); printTab();
	arm_adds( R6, rs, immed );
	printOperand( "str" );
	print_rt( rt );
	printComma();
	printChar( '[' );
	print_rs( R6 );
	printChar( ']' );
	printNewLine();
};

//store 2B halfword
void
arm_sh( int rt,
int immed,
int rs )
{	printOperand(  "STOREHALFWORD"  );
	arm_ls( rt, immed, rs );
};

//store 1B byte
void
arm_sb( int rt,
int immed,
int rs )
{	printOperand(  "STOREBYTE"  );
	arm_ls( rt, immed, rs );
};

//load 4B word
void
arm_ldr( int rt,
int immed,
int rs )
{	printOperand(  "lw"  );
	arm_ls( rt, immed, rs );
};

//load 2B halfword
void
arm_lh( int rt,
int immed,
int rs )
{	printOperand(  "lh"  );
	arm_ls( rt, immed, rs );
};

//load 1B byte
void
arm_lb( int rt,
int immed,
int rs )
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
arm_j( char *s )
{	printOperand(  "j"  );
	while ( *s )
	{	printChar( *s );
		++s;
	}
	printNewLine();
};

//jump _label
void
arm_j_( int n )
{	printOperand(  "j"  );
	printChar( '_' );
	printNumber( n );
	printNewLine();
};

		//jump and link _label
		void
		arm_bl_( char *s )
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
arm_globl( char *s )
{	printStr(  "\t.globl\t"  );
	while ( *s )
	{	printChar( *s );
		++s;
	};
	printNewLine();
};

//global attribute for _variable
void
arm_globl_( char *s )
{	printStr(  "\t.globl\t_"  );
	while ( *s )
	{	printChar( *s );
		++s;
	};
	printNewLine();
};

//label: print label procedure body
void
arm_label( char *s )
{	while ( *s ) 
	{	printChar( *s );
		++s;
	}
	printStr(  ":\n"  );
}

//_numLabel: print label name=number
void
arm_label_( int n )
{	printChar( '_' );
	printNumber( n );
	printStr(  ":\n"  );
};

//_prelabel	print label procedure body
void
arm_prelabel( char *s )
{
	printChar( '_' );
	while ( *s ) {
		printChar( *s );
		++s;
	}
	printStr(  ":\n"  );
}

//==========================================================
//===========	CODE GENERATOR	============================
//==========================================================
//push number on stack
void 
pushnum( int n )
{	incSp();
	if ( ( n & 0xffff8000 ) == 0xffff8000 ) 
	{	operandImmediate( "adds", TOS, 0, n  );
		//arm_adds(  TOS, 0, n  );
	} 
	else if ( ( n & 0xffff0000 ) == 0 ) 
	{	operandImmediate( "orrs", TOS, 0, n );
		//arm_orImmed( TOS, 0, n );
	} else if ( ( n & 0x0000ffff ) == 0 ) 
	{	operandImmediate( "movs", TOS, 0, n );
		//arm_movs( TOS, ( ( n >> 16 ) & 0xffff ) );
	} 
	else 
	{	operandImmediate( "orrs", TOS, 0, n );	//?? 
		//arm_movs( TOS, ( ( n >> 16 ) & 0xffff ) );
		//arm_orImmed( TOS, TOS, ( n & 0xffff ) );
	};
	
	objsize[sp-1] = 0;
};

//GP - global data address reg value
void
pushgpoff( int off )
{	incSp();
	arm_adds( TOS, GP, off );
	objsize[sp-1] = 0;
};

//stack frame pointer
void
pushfpoff( int off )
{	incSp();
	// operandImmediate( "orrs", TOS, FP, off );
	arm_orImmed( TOS, FP, off );	//????
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
pusharg( int argno )
{	incSp();
	arm_or( TOS, ( A0 + argno ), 0 );
	objsize[sp-1] = 0;
};

//pointer
void
lval( int size )
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
		case 4: arm_ldr( TOS, 0, TOS ); break;
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
setarg( int argno )
{	loadtos();
	arm_or( ( A0 + argno ), TOS, 0 );
	decSp();
};

//push operand
void
pushop( int op )
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
			arm_adds( TOS, TOS, TOS );
			arm_adds( TOS, TOS, TOS );
			break;
		case MULBY2:
			loadtos();
			arm_adds( TOS, TOS, TOS );
			break;
		case AFP:
			loadtos();
			arm_adds( TOS, TOS, FP );
			break;
		case ASP:
			loadtos();
			arm_adds( TOS, TOS, SP );
			break;
		case AGP:
			loadtos();
			arm_adds( TOS, TOS, GP );
			break;
		case RETVAL:
			loadtos();
			arm_or( V0, TOS, 0 );
			decSp();
			break;
		case '+':
			loadnostos();
			arm_adds( NOS, NOS, TOS );
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
store( int prop )
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
jump( int a )
{	/* Compiler-generated labels are nearby...
	   so use a branch instead
	*/
	arm_j_( a );
};

//jump on false
void
jumpf( int a )
{	loadtos();
	arm_beq( TOS, 0, a );
	decSp();
};

//jump on nonzero ("true")
void
jumpt( int a )
{	loadtos();
	arm_bne( TOS, 0, a );
	decSp();
};

//label handler
void
label( int a )
{
	arm_label_( a );
};

//goto handler
void 
ghoto( char *s )
{	arm_j( s );
};

//
void
target( char *s )
{	arm_prelabel( s );
};

//arm startup
void
startup( void )
{	
	printStr(  ";====\n"  );
	printStr(  ";FOO\n"  );
	printStr(  ";====\n"  );
	foo(); 
	printStr(  "\n;====\n\n\n"  );
	arm_text();
	arm_globl(  "main"  );
	arm_globl_(  "exit"  );
	arm_label(  "ENTRY"  );
	arm_label(  "main"  );
	arm_bl_(  "main"  );
}

//call function by branch and link return address
void
call( int mysym )
{	char *n = nameString( symtab[mysym].ipos );
	int i;
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
		{	arm_ldr( i, -4*( i-T0 ), SP );
		};
		arm_adds( SP, SP, 4*( TOS-T0+1 ) );
	};

	/* Copy the return value to someplace useful */
	incSp();
	arm_or( TOS, V0, 0 );
	objsize[sp-1] = 0;
};


//function begin INT return; int foo(void) / int foo(args)
void
funcbegin( int mysym )
{	char *n = nameString( symtab[mysym].ipos );

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
funcend( int mysym )
{	char *n = nameString( symtab[mysym].ipos );

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
		arm_ldr( RA, -4, FP );		/* ra = fp[-4] */
		arm_or( SP, FP, 0 );		/* sp = fp */
		arm_ldr( FP, 0, SP );		/* fp = old fp */
		arm_adds( SP, SP, 4 );		/* sp = old sp */
		arm_b( RA );			/* return */
		arm_prelabel( n );
		arm_adds( SP, SP, -highwater );	/* sp -= highwater */
		arm_sw( FP, highwater-4, SP );	/* sp[highwater-4] = fp */
		arm_adds( FP, SP, highwater-4 );	/* fp = &( sp[highwater-4] ) */
		arm_sw( RA, -4, FP );		/* fp[-4] = ra */
	} else 
	{	/* A leaf without locals... */
		label( endlab );
		arm_b( RA );			/* return */
		arm_prelabel( n );
	}

	jump( beginlab );

	--scope;
};

//memory definition
void
def( int mysym )
{	char *n = nameString( symtab[mysym].ipos );
	int asize;
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

//string memory definition
int
defstr( int spos )
{	int num;
	int asize;

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



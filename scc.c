/*https://www.quora.com/How-do-I-make-a-compiler-for-C-from-scratch-Are-there-any-tutorial-or-source-from-which-I-can-learn*/
/*[Henry Dietz; University of Kentucky]*/
/*	mucky.c

	MIPS uCompiler from KentuckY.
*/
/*
	TRIVIAL C -> TARGET_ASM -> Assembler -> Linker -> Machine code
	COMPILER:	TOKENIZER(lexical analyzer) -> SYMBOL TABLE
											-> PARSER (syntax analyzer) -> CODE GENERATOR
*/ 
#if (defined _WIN32) && (defined _MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

/*target lists*/
#if defined MIPS
	#undef MIPS
	#define MIPS						0x10
	#define COMPILER_TARGET				MIPS
	#define	COMPILER_TARGET_CHOOSEN		0x1
#elif defined ARM	//Cortex M0 / M0+
	#define	ARM_CM0
	#define COMPILER_TARGET				ARM_CM0
	#define	COMPILER_TARGET_CHOOSEN		0x1
#endif

/*default compiler MIPS target*/
#ifndef COMPILER_TARGET_CHOOSEN		
	#define COMPILER_TARGET				MIPS
#endif


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int					haveinput = 0;

char				*prelab = "L";
int					callerreg, calleereg;
int					scope = 0;
int					labelNum = 0;		/* next compiler-generated label */
int					lexsym;

int					beginlab, endlab;	/* for function begin/end code */
int					gpoffset, fpoffset;	/* for globals/locals */
int					isleaf;				/* is this a leaf procedure? */
int					linestart = 0;		/* start of current line */

#define	DATABASE	0x10000000

#define	INT			'a'
#define	IF			'b'
#define	ELSE		'c'
#define	WHILE		'd'
#define	RETURN		'e'
#define	FUNC		'f'
#define	WORD		'g'
#define	NUM			'h'
#define	DO			'i'
#define	VAR			'j'
#define	AFP			'k'
#define	ASP			'l'
#define	AGP			'm'
#define	SHORT		'n'
#define	CHAR		'o'
#define RETVAL		'p'
#define	MULBY4		'q'
#define	MULBY2		'r'
#define	STRING		's'
#define	FOR			't'
#define	GOTO		'u'
#define	TARGET		'v'

#define	EQ			'A' /**/
#define	NE			'B' /**/
#define	GE			'C' /**/
#define	LE			'D'	/**/
#define	SL			'E'	/**/
#define	PP			'F'	/**/
#define	MM			'G' /**/
#define	OE			'H'	/**/
#define	XE			'I'	/**/
#define	AE			'J'	/**/
#define	PE			'K'	/**/
#define	ME			'L'	/**/
#define	TE			'M'	/**/
#define	DE			'N'	/**/
#define	RE			'O'	/**/
#define	OO			'P'	/**/
#define	AA			'Q'	/**/
#define	NEG			'R'	/**/
#define	SR			'S'	/**/
#define	MYEOF		'Z'	/**/

#define	MAXINPUT	(1024*1024)
char				input[MAXINPUT];
int					eof;
int					ipos;

char				*myname;	/* name of this command */

int					nextToken;	/* next token */
int					lexnum;		/* lexical number value */
int					lexstr;		/* lexical string ipos */
int					lineno = 1;	/* current line number */

#define				STACKSIZE	64
int					objsize[STACKSIZE];
int					sp = 0;		/*stack pointer*/

int					highwater = 0;

#define	sym	struct _sym
sym {
	int	ipos;
	int	type;
	int	scope;
	int	base;
	int	size;
	int	dim;
} symtab[513];		/* symbol table */
int	symsp = 0;

void	expr(void);
void	decl(void);


int
isNameChar(register int t)
{	return(((t >= '0') && (t <= '9')) ||
	       ((t >= 'A') && (t <= 'Z')) ||
	       ((t >= 'a') && (t <= 'z')) ||
	       (t == '_'));
};

char *
nameString(register int ipos)
{	static char name[256];
	register int i = 0;

	while (isNameChar(name[i] = input[ipos+i])) ++i;
	name[i] = 0;
	return(&(name[0]));
};

int warn(fmt, a, b, c)
char *fmt;
int a, b, c;
{	fprintf(stderr, "#line %d: ", lineno);
	fprintf(stderr, fmt, a, b, c);
	fprintf(stderr, "\n");
	return 0;
};

int error(fmt, a, b, c)
char *fmt;
int a, b, c;
{	warn(fmt, a, b, c);
	fprintf(stderr,
"#compilation terminated on this error\n"
"</PRE>\n"
"<P>\n"
		);
	exit(0);
	return 0;
};


/*	Code generation stuff
*/

void
incSp(void)	/*increment stack pointer*/
{	++sp;
};

void
decSp(void) /*decrement stack pointer*/
{	--sp;
};

void
printStr(char* str)
{	printf( "%s", str );
};
// #define	printStr(s)	print(s, (sizeof(s)-1))
#define	printOperand(s)		{ printTab(); printStr(s); printTab(); }

void
printChar(register int c)
{	putchar(c);
};

void
printTab(void)
{	printChar('\t');
};

void
printComma(void)
{	printChar(',');
};

void
printSharp(void)
{	printChar('#');
};

void
printNewLine(void)
{	printChar('\n');
};

void
print(register char *s,
register int len)
{	while (--len >= 0) 
	{	printChar(*s);
		++s;
	};
};

//#if 	(COMPILER_TARGET == MIPS)
#if defined MIPS
	#include "sccMIPS_REGS.c"
//#elif 	(COMPILER_TARGET == ARM_CM0)
#elif defined	ARM_CM0
	#include "sccARM_REGS.c"
#endif

void
print_rt(register int r)	/*print temporary register*/
{	printReg(r);
};

void
print_rs(register int r)	/*print source register*/
{	printReg(r);
};

void
print_rd(register int r)	/*print destination register*/
{	printReg(r);
};

void printImmediate(register int r);	/*target specific*/

void
printNumber(register int n)
{	printf("0x%X", n);
};

void
printNumber10(register int n)
{	printf("%d", n);
};

//	INSTRUCITON SET API
//#if (COMPILER_TARGET == MIPS)
#if defined MIPS
	#include "sccMIPS_FUNCTIONS.c"
//#elif (COMPILER_TARGET == ARM_CM0)
#elif defined ARM_CM0
	#include "sccARM_FUNCTIONS.c"
#endif	//TARGET == MIPS

//==================================================================
//=======	TOKENIZER(lexical analyzer - LEXER)	==================
//==================================================================
/*	Lexicals...
*/

int
prefixis(register char *p)
{	register int i = 0;

	for (;;) 
	{	register int t = p[i];
		if (t == 0) 
		{	ipos += i;
			return(1);
		};
		if (t != input[ipos + i]) 
		{	return(0);
		};
		++i;
	};
};

int
nameis(register char *p)
{	register int i = 0;

	for (;;) 
	{	register int t = p[i];

		if (!isNameChar(t)) 
		{	if (!isNameChar(input[ipos + i])) 
			{	ipos += i;
				return(1);
			} else 
			{	return(0);
			};
		};
		if (t != input[ipos + i]) 
		{	return(0);
		};
		++i;
	};
};

//update token
int
lexhelp(void)
{	register int base = 10;

again:
	/* Recognize all the non-name stuff */
	switch (input[ipos]) 
	{	/* Handle whitespace, etc. */
		case '\n':
#ifdef		NOTNOW
			printf("#line\t%d:\t", lineno);
			while (linestart <= ipos) 
			{	putchar(input[linestart]);
				++linestart;
			};
#endif
			++lineno;
			/* Fall through... */
		case ' ':	case '\t':	case '\r':
			++ipos;
			goto again;
		case '\000':
			return(MYEOF);

		/* Handling of punctuation... */
		case '=':	case '!':
		case '<':	case '>':
		case '+':	case '-':	case '~':
		case '*':	case '/':	case '%':
		case '|':	case '&':
			if (prefixis("==")) return(EQ);
			if (prefixis("!=")) return(NE);
			if (prefixis(">=")) return(GE);
			if (prefixis("<=")) return(LE);
			if (prefixis("<<")) return(SL);
			if (prefixis("++")) return(PP);
			if (prefixis("--")) return(MM);
			if (prefixis("|=")) return(OE);
			if (prefixis("^=")) return(XE);
			if (prefixis("&=")) return(AE);
			if (prefixis("+=")) return(PE);
			if (prefixis("-=")) return(ME);
			if (prefixis("*=")) return(TE);
			if (prefixis("/=")) return(DE);
			if (prefixis("%=")) return(RE);
			if (prefixis("||")) return(OO);
			if (prefixis("&&")) return(AA);
			/* Fall through... */
		case ',':	case '?':	case ':':
		case '{':	case '}':	case '^':
		case '[':	case ']':
		case '(':	case ')':
		case ';':
			return(input[ipos++]);

		/* Handling of numbers... */
		case '0':
			base = 8;
			switch (input[++ipos]) {
			case 'b': base = 2; ++ipos; break;
			case 'x': base = 16; ++ipos; break;
			}
		case '1':	case '2':	case '3':
		case '4':	case '5':	case '6':
		case '7':	case '8':	case '9':
			lexnum = 0;
			for (;;) 
			{	register int t = input[ipos];

				if ((t >= '0') && (t <= '9')) 
				{	t -= '0';
				} else if (((t |= ('a'-'A')) >= 'a') &&
					   (t <= 'f')) 
				{
				t -= ('a' - 10);
				} else 
				{	return(NUM);
				};

				if (t >= base) 
				{	error("invalid digit");
				};

				lexnum = (lexnum * base) + t;
				++ipos;
			}
		case '\'':				//character
			++ipos;
			lexnum = input[ipos++];
			if (input[ipos++] != '\'') 
			{	error("ill-formed character constant");
			};
			return(NUM);
		case '"':				//string
			lexstr = ipos;
			do 
			{	++ipos;
				if (input[ipos] == 0) 
				{	error("string ends in end of input");
				}
			} while (	(input[ipos] != '"') ||
						(input[ipos-1] == '\\')
					);
			++ipos;
			return(STRING);
		default:
			if (!isNameChar(input[ipos])) 
			{	error("illegal character 0x%02x (%c)",
					  input[ipos],
					  input[ipos]);
				++ipos;
				goto again;
			};
	};

	/* Must be a name... */
	if (nameis("int")) return(INT);
	if (nameis("short")) return(SHORT);
	if (nameis("char")) return(CHAR);
	if (nameis("if")) return(IF);
	if (nameis("else")) return(ELSE);
	if (nameis("while")) return(WHILE);
	if (nameis("do")) return(DO);
	if (nameis("return")) return(RETURN);
	if (nameis("for")) return(FOR);
	if (nameis("goto")) return(GOTO);

	/* Find it in the symbol table */
	for (lexsym=(symsp-1); lexsym>=0; --lexsym) 
	{	if (nameis(&(input[symtab[lexsym].ipos]))) 
		{	return(symtab[lexsym].type);
		}
	}

	/* Make a new symbol table entry */
	symtab[lexsym = (symsp++)].ipos = ipos;
	nameis(&(input[ipos]));
	return(symtab[lexsym].type = ((input[ipos] == ':') ?
				      TARGET :
				      WORD));
};

//next token
int
lex(void)
{	nextToken = lexhelp();
	return(nextToken);
};

int
match(register int t)
{	if (nextToken == t) 
	{	lex();
		return(1);
	};
	return(0);
};

int
assume(register int t)
{	if (!match(t)) 
	{	warn("missing %c assumed", t);
		return(0);
	};
	return(1);
};


/*	Parsing...
*/
//================================================================
//==================	PARSER(syntax analyzer)	================
//================================================================
void
memaddr(register int mysym)
{	/* Base address */
	if (symtab[mysym].scope != 0) 
	{	pushfpoff(symtab[mysym].base);
	} else 
	{	pushgpoff(symtab[mysym].base);
	};

	lex();
	if (match('[')) 
	{	/* subscripted */
		expr();		/* Index value */
		assume(']');

		/* Multiply by element size */
		switch (symtab[mysym].size) 
		{	case 2:	pushop(MULBY2); break;
			case 1: break;
			default:
				pushop(MULBY4);
		};

		pushop('+');	/* Add to base address */
	};

	lval(symtab[mysym].size);
};

void
unary(void)
{	register int mysym;
	register int args = 0;

	switch (nextToken) 
	{	case PP:
			lex();
			unary();
			pushdup();
			pushnum(1);
			pushop('+');
			store(1);
			break;
		case MM:
			lex();
			unary();
			pushdup();
			pushnum(-1);
			pushop('+');
			store(1);
			break;
		case '(':
			lex();
			expr();
			assume(')');
			break;
		case '-':
			lex();
			unary();
			pushop(NEG);
			break;
		case '!':
			lex();
			unary();
			pushop('!');
			break;
		case '~':
			lex();
			unary();
			pushop('~');
			break;
		case VAR:
			memaddr(lexsym);
			break;
		case WORD:
			symtab[lexsym].type = FUNC;
			symtab[lexsym].base = 0;
			/* Fall through... */
		case FUNC:
			/* Function call */
			mysym = lexsym;
			lex();
			if (!match('(')) 
			{	error("undefined variable %s",
					  nameString(symtab[mysym].ipos));
			}
			args = 0;
			while (!match(')')) 
			{	expr();
				setarg(args++);
				match(',');
			}
			call(mysym);
			break;
		case NUM:
			pushnum(lexnum);
			lex();
			break;
		case STRING:
			pushnum(defstr(lexstr));
			lex();
			break;
		default:
			error("malformed expression");
	};

	/* Suffix operation */
	switch (nextToken) 
	{	case PP:
			lex();
			pushdup();
			loadnos();
			pushdup();
			pushnum(1);
			pushop('+');
			store(0);
			break;
		case MM:
			lex();
			pushdup();
			loadnos();
			pushdup();
			pushnum(1);
			pushop('+');
			store(0);
			break;
	};
};

//multiply; divide; modulo;
void
mul(void)
{	register int t;

	unary();
	for (;;) 
	{	switch (nextToken) 
		{	case '*':
			case '/':
			case '%':
				t = nextToken;
				lex();
				unary();
				pushop(t);
			default:
				return;
		};
	};
};

//addition; substraction
void
add(void)
{	register int t;

	mul();
	for (;;) 
	{	switch (nextToken) 
		{	case '+':
			case '-':
				t = nextToken;
				lex();
				mul();
				pushop(t);
			default:
				return;
		};
	};
};

//shift left; shift right;
void
slsr(void)
{	register int t;

	add();
	for (;;) 
	{	switch (nextToken) 
		{	case SL:
			case SR:
				t = nextToken;
				lex();
				add();
				pushop(t);
			default:
				return;
		};
	};
};

//lessEqual; lessThan; greatEqual; greatThan;
void
leltgegt(void)
{	register int t;

	slsr();
	for (;;) 
	{	switch (nextToken) 
		{	case LE:
			case '<':
			case GE:
			case '>':
				t = nextToken;
				lex();
				slsr();
				pushop(t);
			default:
				return;
		};
	};
};

//equal; notEqual
void
eqne(void)
{	register int t;

	leltgegt();
	for (;;) 
	{	switch (nextToken) 
		{	case EQ:
			case NE:
				t = nextToken;
				lex();
				leltgegt();
				pushop(t);
			default:
				return;
		};
	};
};

void
and(void)
{	eqne();
	while (match('&')) 
	{	eqne();
		pushop('&');
	};
};

void
xor(void)
{	and();
	while (match('^')) 
	{	and();
		pushop('^');
	};
};

void
or(void)
{	xor();
	while (match('|')) 
	{	xor();
		pushop('|');
	};
};

//logical andand	&&
void
andand(void)
{	register int lab;

	or();
	if (match(AA)) 
	{	lab = labelNum;
		labelNum += 3;

		do 
		{	jumpf(lab);
			++labelNum;
			or();
		} while (match(AA));

		jumpt(lab+1);
		label(lab);
		pushnum(0);
		decSp();
		jump(lab+2);
		label(lab+1);
		pushnum(1);
		label(lab+2);
	};
};

//logical oror	||
void
oror(void)
{	register int lab;

	andand();
	if (match(OO)) 
	{	lab = labelNum;
		labelNum += 3;

		do 
		{	jumpt(lab);
			++labelNum;
			andand();
		} while (match(OO));

		jumpf(lab+1);
		label(lab);
		pushnum(1);
		decSp();
		jump(lab+2);
		label(lab+1);
		pushnum(0);
		label(lab+2);
	};
};

void
cond(void)
{	register int lab;

	oror();
	if (match('?')) 
	{	lab = labelNum;
		labelNum += 2;

		jumpf(lab);
		expr();
		decSp();
		jump(lab+1);
		assume(':');
		label(lab);
		cond();
		label(lab+1);
	};
};

//======================	ASSIGMENTS	==========================
void
assign(void)
{	register int t;

	cond();
	switch (nextToken) 
	{	case '=':
			lex();
			assign();
			store(1);
			break;
		case OE:			// |=
			lex();
			pushdup();
			assign();
			pushop('|');
			store(1);
			break;
		case XE:			//^=
			lex();
			pushdup();
			assign();
			pushop('^');
			store(1);
			break;
		case AE:			//&=
			lex();
			pushdup();
			assign();
			pushop('&');
			store(1);
			break;
		case PE:			//+=
			lex();
			pushdup();
			assign();
			pushop('+');
			store(1);
			break;
		case ME:			//-=
			lex();
			pushdup();
			assign();
			pushop('-');
			store(1);
			break;
		case TE:			//*=
			lex();
			pushdup();
			assign();
			pushop('*');
			store(1);
			break;
		case DE:			// /=
			lex();
			pushdup();
			assign();
			pushop('/');
			store(1);
			break;
		case RE:			//%=
			lex();
			pushdup();
			assign();
			pushop('%');
			store(1);
			break;
	};
};

//===================	EXPRESSIONS	======================
//f.e. if ((A>B),(C!=D)
void
expr(void)
{	assign();
	while (match(',')) 
	{	decSp();
		assign();
	};
};

//newSymbol
int
newsym(void)
{	/* Create a new symbol table entry */
	register int mysym;

	switch (nextToken) 
	{	case WORD:
			mysym = lexsym;
			break;
		case VAR:
		case FUNC:
			if (scope == symtab[lexsym].scope) 
			{	warn("redefinition of identifier");
			};
			symtab[mysym = (symsp++)].ipos = symtab[lexsym].ipos;
			break;
		default:
			error("ill-formed declaration of %s",
				  nameString(symtab[mysym].ipos));
	};
	lex();
	symtab[mysym].scope = scope;
	return(mysym);
}

//===================	STATEMENTS	======================
//f.e. if (expression) then statement
void
stat(void)
{	register int scopesymsp, scopeoffset;
	register int lab;
	register int mysym;

	switch (nextToken) 
	{	case '{':					//procedure
			lex();
			scopesymsp = symsp;
			scopeoffset = fpoffset;

			decl();
			while (!match('}')) {
				stat();
			}

			symsp = scopesymsp;
			fpoffset = scopeoffset;
			break;
		case IF:					//if (expressiong) statement
			lex();
			expr();
			lab = labelNum;
			labelNum += 2;
			jumpf(lab);
			stat();
			if (nextToken == ELSE) 
			{	lex();
				jump(lab+1);
				label(lab);
				stat();
				label(lab+1);
			} else 
			{	label(lab);
			};
			break;
		case FOR:					//for(variable==expression1;/*TO*/ expression2; optionalExpression3) statement
			lex();
			assume('(');
			lab = labelNum;
			labelNum += 4;
			if (!match(';')) 
			{	expr();
				decSp();
				match(';');
			};
			label(lab);
			if (!match(';')) 
			{	expr();
				jumpf(lab+1);
				match(';');
			};
			jump(lab+2);
			label(lab+3);
			if (!match(')')) 
			{	expr();
				decSp();
				match(')');
			};
			jump(lab);
			label(lab+2);
			stat();
			jump(lab+3);
			label(lab+1);
			break;
		case WHILE:				//while(expression) statement
			lex();
			lab = labelNum;
			labelNum += 2;
			label(lab);
			expr();
			jumpf(lab+1);
			stat();
			jump(lab);
			label(lab+1);
			break;
		case DO:				//do statement while(expression)	-> at least single pass
			lex();
			lab = (labelNum++);
			label(lab);
			stat();
			if (match(WHILE)) 
			{	error("do missing while");
			};
			expr();
			assume(';');
			jumpt(lab);
			break;
		case RETURN:
			lex();
			if (nextToken != ';') 
			{	expr();
				pushop(RETVAL);
			}
			match(';');
			break;
		case GOTO:				//goto label
			lex();
			ghoto(nameString(symtab[newsym()].ipos));
			--symsp;
			break;
		case TARGET:
			target(nameString(symtab[symsp-1].ipos));
			--symsp;
			lex();
			assume(':');
			break;
		case ';':
			lex();
			break;
		default:
			expr();
			assume(';');
			decSp();
			break;
	};
};

int
ctype(void)
{	switch (nextToken) 
	{	case INT:	lex(); return(4);
		case SHORT:	lex(); return(2);
		case CHAR:	lex(); return(1);
		case WORD:	
			if (scope == 0) 
			{	warn("missing int keyword assumed");
				return(4);
			};
	};
	return(0);
};

//============================================================
//===================	DECLARATION	==========================
//============================================================
void
decl(void)
{	register int scopeoffset;
	register int mysym, argsym;
	register int size, args;

	while ((size = ctype()) != 0) 
	{
moredecls:
		mysym = newsym();
		symtab[mysym].size = size;

		switch (nextToken) 
		{
			case '[':
				lex();
				symtab[mysym].type = VAR;
				if (nextToken != NUM) {
					error("non-constant dim for %s",
						  nameString(symtab[mysym].ipos));
				}
				symtab[mysym].dim = lexnum;
				def(mysym);
				lex();
				assume(']');
				if (match(',')) goto moredecls;
				assume(';');
				break;
			case ';':
				symtab[mysym].dim = 1;
				def(mysym);
				lex();
				break;
			case ',':
				symtab[mysym].dim = 1;
				def(mysym);
				lex();
				goto moredecls;
			case '(':
				if (scope != 0) 
				{	error("nested definition of function %s",
						  nameString(symtab[mysym].ipos));
				}
				lex();

				funcbegin(mysym);

				args = 0;
				while ((size = ctype()) != 0) 
				{	argsym = newsym();
					symtab[argsym].type = VAR;
					symtab[argsym].size = 4;
					symtab[argsym].dim = 1;
					def(argsym);

					/* Copy arg from register to local */
					pushnum(symtab[argsym].base);
					pushop(AFP);
					lval(4);
					pusharg(args++);
					store(0);

					if (match('[')) 
					{	error("array arguments currently not supported");
					};
					match(',');
				};
				if (!match(')')) 
				{	warn("missing ) in function argument declaration");
				};
				stat();
				funcend(mysym);

				break;
			default:
				error("declaration missing ; or argument list");
		};
	};
};


int
main(int argc, char **argv)
{	int c;
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	puts("scc hello");
	
	eof = 0;
	if ( argc == 0x2 )
	{	pFile = fopen ( argv[argc - 1], "r" );
		if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
		// obtain file size:
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);

		// copy the file into the buffer:
		result = fread (input,1,lSize,pFile);
		if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
		eof = lSize;
	} else
	{	while ((c = getchar()) != EOF) input[eof++] = c;
	};

	input[eof] = 0;
	ipos = 0;
	nextToken = lex();
	startup();
	decl();
	return 0;
}

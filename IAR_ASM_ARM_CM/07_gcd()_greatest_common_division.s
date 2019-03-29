		;int		gcd(int a, int b)
		;{		while(a != b)
		;		{ 	if (a > b) 	a = a - b;
		;		else 		b = b - a;
		;		};
		;		return a;
		;};
		;
		
thumb
ENTRY
		movs		r0, #15
		movs		r1, #3
gcd
		cmp		r0, r1
		beq		endgcd
		blt		less
		subs		r0, r0, r1
		b		gcd
less
		subs		r1, r1, r0
		b		gcd
endgcd
		

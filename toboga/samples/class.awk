#!/usr/bin/awk -f

function ovinhos( n, k ) {
	if( k == 0 ) return 1;
	if( n == k ) return 1;
	if ( (n,k) in Mem ) return Mem[n, k];
	return Mem[n, k] = ovinhos( n - 1, k ) + ovinhos( n - 1, k - 1 );
}

function b2( n,		i, j ) {
	delete V;
	V[0] = V[1] = 1;
	for( j = 2; j <= n ; j++) {
		for( i = 0 ;  ; ) {
			
		}
	}
}

BEGIN {
	funcName = ARGV[1]
	n = ARGV[2]
	k = ARGV[3]
	if (funcName == "ovinhos") {
		print n " ovinhos pode ser repartidos entre " k " de " ovinhos(n, k) " maneiras."
	}    
	ARGV[1] = ARGV[2] = ARGV[3] = ""
}  
	




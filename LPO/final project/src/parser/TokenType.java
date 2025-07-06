package parser;


public enum TokenType { 
	// symbols
	ASSIGN, MINUS, PLUS, TIMES, NOT, AND, EQ, STMT_SEP, PAIR_OP, OPEN_PAR, CLOSE_PAR,
	OPEN_BLOCK, CLOSE_BLOCK,//new tokens
	OPEN_VEC, CLOSE_VEC,
	// keywords
	PRINT, VAR, BOOL, IF, ELSE, FST, SND,
	FOR_EACH, IN, //new tokens
	// non singleton categories
	SKIP, IDENT, NUM,   
	// end-of-file
	EOF, 	
}

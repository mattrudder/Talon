%{
%}

%union {
	std::string* ident;
	std::string* string;
	int token;
}

%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token> TASSIGN TLPAREN TRPAREN TLBRACE TRBRACE TDOT TCOMMA TSEMICOLON

%type <ident> ident

%start material

%%

material : stmts
		 ;

stmts : stmt
	  | stmts stmts
	  ;

stmt : ident TSEMICOLON
	 ;

ident : TIDENTIFIER { $$ = $1; }
	  ;
%%
grammar TalonMaterial;

options {
	language = C;
	output=AST;
	ASTLabelType=pANTLR3_BASE_TREE;
}

tokens {
	Module;
	ObjectBlock;
	PropertyAssignment;
}

module
	:	(materialStatement)+
		-> ^(Module materialStatement*)
	;

materialStatement
	:	Material Identifier objectBlock
		-> ^(Material Identifier objectBlock)
	;
	
objectBlock
	:	lc='{'
			(propertyDeclaration)*
		'}'
		-> ^(ObjectBlock[$lc] propertyDeclaration*)
	;

propertyDeclaration
	:	Identifier ':' propertyValue ';'
		-> ^(PropertyAssignment Identifier propertyValue)
	;

propertyValue
	:	StringLiteral
	;

Material
	:	'material'
	;

Identifier
	:	(Letter) (Letter | Digit)*
	;

StringLiteral
	:	'"' str=StringGuts { SETTEXT($str.text); } '"'
	;

fragment
StringGuts
	:	(EscapeSequence | ~('\\'|'"'))*;

fragment
EscapeSequence
	:	'\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
	|	UnicodeEscape
	;

fragment
UnicodeEscape
	:	'\\' 'u' HexDigit HexDigit HexDigit HexDigit
	;

fragment
HexLiteral
	:	'0' ('x'|'X') HexDigit+
	;

fragment
DecimalLiteral
	:	('0' | '1'..'9' '0'..'9'*)
	;

fragment
FloatingPointLiteral
	:	('0'..'9')+ '.' ('0'..'9')* Exponent?
	|	'.' ('0'..'9')+ Exponent?
	|	('0'..'9')+ (Exponent)
	;

fragment
HexDigit
	:	('0'..'9'|'a'..'f'|'A'..'F')
	;

fragment
CharacterLiteral
	:	'\'' ( EscapeSequence | ~('\''|'\\') ) '\''
	;

Comment
	:	'//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	|	'/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
	;
Whitespace
	:	(' ' | '\t' | '\n' | '\r' | '\f')+ { $channel = HIDDEN; }
	;

fragment
Letter
	:	'A'..'Z'
	|	'a'..'z'
	|	'_'
	|	'-'
	;

fragment
Digit
	:	'0'..'9'
	;

fragment
Exponent
	:	('e'|'E') ('+'|'-')? (Digit)+
	;


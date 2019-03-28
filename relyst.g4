grammar relyst;

compileUnit
    :   definitionList? EOF
    ;

definition
	:	namespaceDefinition
	|	structDefinition
	;

definitionList 
	:	(definition ';'*)+
	;

nameScoped
	:	(ID '.')* ID
	;

namespaceDefinition
	:	'namespace' nameScoped '{' definitionList? '}'
	;

structDefinition
	:	('compnt' | 'component' | 'struct') name=ID ':' typeList ';'
	;

type
	:	nameScoped
	;

typeList
	:	(type ',')* type
	;

ID			  :	([a-zA-Z] | '_') ([a-zA-Z0-9] | '_')*;
BLOCK_COMMENT :	'/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT  : '//' ~[\r\n]* -> channel(HIDDEN);
WHITE_SPACE   : [ \t\r\n] -> channel(HIDDEN);
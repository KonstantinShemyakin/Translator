%{
enum T_Lex { None, Declare, TypeDef, Comma, Semicolon, DeclComma, DeclSemicolon, ExprSemicolon, StmtSemicolon, 
             BegBlock, EndBlock, BegFunc, EndFunc, 
             StructBeg, StructEnd, EnumBeg, EnumEnd, EnumComma, 
             ParamBeg, ParamEnd, ParamComma, ListBeg, ListEnd, ListComma 
           };

%}

%token CONSTANT               768 // 0300
%token STRING_LITERAL        1280 // 0500
%token INC_OP                 278 // 0116
%token DEC_OP                 279 // 0117
%token LEFT_OP                286 // 011E
%token RIGHT_OP               287 // 011F
%token LE_OP                  283 // 011B
%token GE_OP                  285 // 011D
%token EQ_OP                  280 // 0118
%token NE_OP                  281 // 0119
%token AND_OP                 274 // 0112
%token OR_OP                  273 // 0111
%token MUL_ASSIGN             264 // 0108
%token DIV_ASSIGN             265 // 0109
%token MOD_ASSIGN             266 // 010A
%token ADD_ASSIGN             262 // 0106
%token SUB_ASSIGN             263 // 0107
%token LEFT_ASSIGN            288 // 0120
%token RIGHT_ASSIGN           289 // 0121
%token AND_ASSIGN             267 // 010B
%token XOR_ASSIGN             269 // 010D
%token OR_ASSIGN              268 // 010C
%token ELLIPSIS               564 // 0234
%token PTR_OP                 563 // 0233
%token TYPEDEF               1825 // 0721
%token EXTERN                1820 // 071C
%token STATIC                1817 // 0719
%token AUTO                  1818 // 071A
%token REGISTER              1821 // 071D
%token CHAR                  1819 // 071B
%token SHORT                 1810 // 0712
%token INT                   1811 // 0713
%token LONG                  1812 // 0714
%token SIGNED                1822 // 071E
%token UNSIGNED              1827 // 0723
%token FLOAT                 1813 // 0715
%token DOUBLE                1814 // 0716
%token CONST                 1816 // 0718
%token VOLATILE              1828 // 0724
%token VOID                  1809 // 0711
%token STRUCT                1824 // 0720
%token UNION                 1826 // 0722
%token ENUM                  1807 // 070F
%token SIZEOF                1823 // 071F
%token CASE                  1803 // 070B
%token DEFAULT               1808 // 0710
%token IF                    1795 // 0703
%token ELSE                  1796 // 0704
%token SWITCH                1802 // 070A
%token WHILE                 1794 // 0702
%token DO                    1797 // 0705
%token FOR                   1793 // 0701
%token GOTO                  1798 // 0706
%token CONTINUE              1799 // 0707
%token BREAK                 1800 // 0708
%token RETURN                1801 // 0709

%token IDENTIFIER            1536 // 0600
%token TYPE_NAME             1537 // 1829 // 1537 // 0601
%token DECLARATOR            1538 // 1830 // 1538 // 0602
%token ENUMERATOR            1539 // 1831 // 1539 // 0603

%%

S_      
        : translation_unit
        ;

primary_expression
        : IDENTIFIER
        | CONSTANT
        | STRING_LITERAL
        | '(' expression ')'
        ;

postfix_expression
        : primary_expression
        | postfix_expression '[' expression ']'
        | postfix_expression '(' ')'
        | postfix_expression '(' argument_expression_list ')'
        | postfix_expression '.' IDENTIFIER
        | postfix_expression PTR_OP IDENTIFIER
        | postfix_expression INC_OP
        | postfix_expression DEC_OP
        ;

argument_expression_list
        : assignment_expression
        | argument_expression_list ',' assignment_expression
        ;

unary_expression
        : postfix_expression
        | INC_OP unary_expression
        | DEC_OP unary_expression
        | unary_operator cast_expression
        | SIZEOF unary_expression
        | SIZEOF '(' type_name ')'
        ;

unary_operator
        : '&'
        | '*'
        | '+'
        | '-'
        | '~'
        | '!'
        ;

cast_expression
        : unary_expression
        | '(' type_name ')' cast_expression
        ;

multiplicative_expression
        : cast_expression
        | multiplicative_expression '*' cast_expression
        | multiplicative_expression '/' cast_expression
        | multiplicative_expression '%' cast_expression
        ;

additive_expression
        : multiplicative_expression
        | additive_expression '+' multiplicative_expression
        | additive_expression '-' multiplicative_expression
        ;

shift_expression
        : additive_expression
        | shift_expression LEFT_OP additive_expression
        | shift_expression RIGHT_OP additive_expression
        ;

relational_expression
        : shift_expression
        | relational_expression '<' shift_expression
        | relational_expression '>' shift_expression
        | relational_expression LE_OP shift_expression
        | relational_expression GE_OP shift_expression
        ;

equality_expression
        : relational_expression
        | equality_expression EQ_OP relational_expression
        | equality_expression NE_OP relational_expression
        ;

and_expression
        : equality_expression
        | and_expression '&' equality_expression
        ;

exclusive_or_expression
        : and_expression
        | exclusive_or_expression '^' and_expression
        ;

inclusive_or_expression
        : exclusive_or_expression
        | inclusive_or_expression '|' exclusive_or_expression
        ;

logical_and_expression
        : inclusive_or_expression
        | logical_and_expression AND_OP inclusive_or_expression
        ;

logical_or_expression
        : logical_and_expression
        | logical_or_expression OR_OP logical_and_expression
        ;

conditional_expression
        : logical_or_expression
        | logical_or_expression '?' expression ':' conditional_expression
        ;

assignment_expression
        : conditional_expression
        | unary_expression assignment_operator assignment_expression
        ;

assignment_operator
        : '='
        | MUL_ASSIGN
        | DIV_ASSIGN
        | MOD_ASSIGN
        | ADD_ASSIGN
        | SUB_ASSIGN
        | LEFT_ASSIGN
        | RIGHT_ASSIGN
        | AND_ASSIGN
        | XOR_ASSIGN
        | OR_ASSIGN
        ;

expression
        : assignment_expression
        | expression ',' assignment_expression
        ;

constant_expression
        : conditional_expression
        ;

declaration
        : declaration_specifiers { TREE(LexTypeName,T_Lex::DeclSemicolon); } ';'
        | declaration_specifiers init_declarator_list { TREE(LexTypeName,T_Lex::DeclSemicolon); } ';'
        ;

declaration_specifiers
        : storage_class_specifier
        | storage_class_specifier declaration_specifiers
        | type_specifier
        | type_specifier declaration_specifiers
        | type_qualifier
        | type_qualifier declaration_specifiers
        ;

init_declarator_list
        : init_declarator
        | init_declarator_list { TREE(LexTypeName,T_Lex::DeclComma); } ',' init_declarator
        ;

init_declarator
        : declarator
        | declarator '=' initializer
        ;

storage_class_specifier
        : { TREE(LexTypeName,T_Lex::TypeDef); } TYPEDEF
        | EXTERN
        | STATIC
        | AUTO
        | REGISTER
        ;

type_specifier
        : VOID
        | CHAR
        | SHORT
        | INT
        | LONG
        | FLOAT
        | DOUBLE
        | SIGNED
        | UNSIGNED
        | struct_or_union_specifier
        | enum_specifier
        | TYPE_NAME
        ;

struct_or_union_specifier
        : struct_or_union IDENTIFIER { TREE(LexTypeName,T_Lex::StructBeg); } '{' struct_declaration_list { TREE(LexTypeName,T_Lex::StructEnd); } '}'
        | struct_or_union { TREE(LexTypeName,T_Lex::StructBeg); } '{' struct_declaration_list { TREE(LexTypeName,T_Lex::StructEnd); } '}'
        | struct_or_union IDENTIFIER 
        ;

struct_or_union
        : STRUCT
        | UNION
        ;

struct_declaration_list
        : struct_declaration
        | struct_declaration_list struct_declaration
        ;

struct_declaration
        : specifier_qualifier_list struct_declarator_list ';'
        ;

specifier_qualifier_list
        : type_specifier specifier_qualifier_list
        | type_specifier
        | type_qualifier specifier_qualifier_list
        | type_qualifier
        ;

struct_declarator_list
        : struct_declarator
        | struct_declarator_list ',' struct_declarator
        ;

struct_declarator
        : declarator
        | ':' constant_expression
        | declarator ':' constant_expression
        ;

enum_specifier
        : ENUM { TREE(LexTypeName,T_Lex::EnumBeg); } '{' enumerator_list { TREE(LexTypeName,T_Lex::EnumEnd); } '}'
        | ENUM IDENTIFIER { TREE(LexTypeName,T_Lex::EnumBeg); } '{' enumerator_list { TREE(LexTypeName,T_Lex::EnumEnd); } '}'
        | ENUM IDENTIFIER
        ;

enumerator_list
        : enumerator
        | enumerator_list ',' enumerator
        ;

enumerator
//        : IDENTIFIER
//        | IDENTIFIER '=' constant_expression
        : ENUMERATOR
        | ENUMERATOR '=' constant_expression
        ;

type_qualifier
        : CONST
        | VOLATILE
        ;

declarator
        : pointer direct_declarator
        | direct_declarator
        ;

direct_declarator
//        : IDENTIFIER
        : DECLARATOR
        | '(' declarator ')'
        | direct_declarator '[' constant_expression ']'
        | direct_declarator '[' ']'
        | direct_declarator { TREE(LexTypeName,T_Lex::ParamBeg); } '(' parameter_type_list { TREE(LexTypeName,T_Lex::ParamEnd); } ')'
        | direct_declarator { TREE(LexTypeName,T_Lex::ParamBeg); } '(' identifier_list     { TREE(LexTypeName,T_Lex::ParamEnd); } ')'
        | direct_declarator { TREE(LexTypeName,T_Lex::ParamBeg); } '('                     { TREE(LexTypeName,T_Lex::ParamEnd); } ')'
        ;

pointer
        : '*'
        | '*' type_qualifier_list
        | '*' pointer
        | '*' type_qualifier_list pointer
        ;

type_qualifier_list
        : type_qualifier
        | type_qualifier_list type_qualifier
        ;

parameter_type_list
        : parameter_list
        | parameter_list ',' ELLIPSIS
        ;

parameter_list
        : parameter_declaration
        | parameter_list ',' parameter_declaration
        ;

parameter_declaration
        : declaration_specifiers declarator
        | declaration_specifiers abstract_declarator
        | declaration_specifiers
        ;

identifier_list
        : IDENTIFIER
        | identifier_list ',' IDENTIFIER
        ;

type_name
        : specifier_qualifier_list
        | specifier_qualifier_list abstract_declarator
        ;

abstract_declarator
        : pointer
        | direct_abstract_declarator
        | pointer direct_abstract_declarator
        ;

direct_abstract_declarator
        : '(' abstract_declarator ')'
        | '[' ']'
        | '[' constant_expression ']'
        | direct_abstract_declarator '[' ']'
        | direct_abstract_declarator '[' constant_expression ']'
        | '(' ')'
        | '(' { TREE(LexTypeName,T_Lex::ParamBeg); } parameter_type_list { TREE(LexTypeName,T_Lex::ParamEnd); } ')'
        | direct_abstract_declarator '(' ')'
        | direct_abstract_declarator '(' { TREE(LexTypeName,T_Lex::ParamBeg); } parameter_type_list { TREE(LexTypeName,T_Lex::ParamEnd); } ')'
        ;

initializer
        : assignment_expression
        | '{' initializer_list '}'
        | '{' initializer_list ',' '}'
        ;

initializer_list
        : initializer
        | initializer_list ',' initializer
        ;

statement
        : labeled_statement
        | compound_statement
        | expression_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        ;

labeled_statement
        : IDENTIFIER ':' statement
        | CASE constant_expression ':' statement
        | DEFAULT ':' statement
        ;

compound_statement
        : { TREE(LexTypeName,T_Lex::BegBlock); } '{' { TREE(LexTypeName,T_Lex::EndBlock); } '}'
        | { TREE(LexTypeName,T_Lex::BegBlock); } '{' statement_list { TREE(LexTypeName,T_Lex::EndBlock); } '}'
        | { TREE(LexTypeName,T_Lex::BegBlock); } '{' declaration_list { TREE(LexTypeName,T_Lex::EndBlock); } '}'
        | { TREE(LexTypeName,T_Lex::BegBlock); } '{' declaration_list statement_list { TREE(LexTypeName,T_Lex::EndBlock); } '}'
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

statement_list
        : statement
        | statement_list statement
        ;

expression_statement
        : ';'
        | expression ';'
        ;

selection_statement
        : IF '(' expression ')' statement
        | IF '(' expression ')' statement ELSE statement
        | SWITCH '(' expression ')' statement
        ;

iteration_statement
        : WHILE '(' expression ')' statement
        | DO statement WHILE '(' expression ')' ';'
        | FOR '(' expression_statement expression_statement ')' statement
        | FOR '(' expression_statement expression_statement expression ')' statement
        ;

jump_statement
        : GOTO IDENTIFIER ';'
        | CONTINUE ';'
        | BREAK ';'
        | RETURN ';'
        | RETURN expression ';'
        ;

translation_unit
        : external_declaration
        | translation_unit external_declaration
        ;

external_declaration
        : function_definition
        | declaration
        ;

function_definition
        : declaration_specifiers declarator { TREE(LexTypeName,T_Lex::BegFunc); } declaration_list compound_statement { TREE(LexTypeName,T_Lex::EndFunc); }
        | declaration_specifiers declarator { TREE(LexTypeName,T_Lex::BegFunc); } compound_statement { TREE(LexTypeName,T_Lex::EndFunc); }
        | declarator { TREE(LexTypeName,T_Lex::BegFunc); } declaration_list compound_statement { TREE(LexTypeName,T_Lex::EndFunc); }
        | declarator { TREE(LexTypeName,T_Lex::BegFunc); } compound_statement { TREE(LexTypeName,T_Lex::EndFunc); }
        ;

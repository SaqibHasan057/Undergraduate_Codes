%{
#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.cpp"

int yydebug;
int yyparse(void);
int yylex(void);
SymbolTable *table;
FILE *logout;
extern FILE* yyin;
bool check=false;
char typeOf[100];
char arrayTypeOf[100];
char assignType[100];
extern int line_count;
extern int error;
SymbolInfo* null = new SymbolInfo((char*)"NULL",(char*)"NULL",(char*)"NULL",-9999999);





void yyerror(const char *s)
{
	fprintf(logout,"Error at line no. %d: %s\n\n",line_count,s);
        error++;
	return;
}

%}

%union {char Character;int Integer;double Double;SymbolInfo* sym;}




%token IF
%token ELSE
%token FOR
%token WHILE
%token INT
%token FLOAT
%token DOUBLE
%token CHAR
%token RETURN
%token VOID
%token MAIN
%token PRINTLN
%token <sym> ADDOP
%token <sym> MULOP
%token <sym> ASSIGNOP
%token <sym> RELOP
%token <sym> LOGICOP
%token <sym> NOT
%token SEMICOLON
%token COMMA
%token LPAREN
%token RPAREN
%token LCURL
%token RCURL
%token LTHIRD
%token RTHIRD
%token INCOP
%token DECOP
%token <sym> CONST_INT
%token <sym> CONST_FLOAT
%token <sym> CONST_CHAR
%token <sym> ID

%type <sym> expression
%type <sym> term
%type <sym> unary_expression
%type <sym> simple_expression
%type <sym> rel_expression
%type <sym> logic_expression
%type <sym> factor
%type <sym> variable
%type <sym> declaration_list


%%
Program : INT MAIN LPAREN RPAREN compound_statement 
{fprintf(logout,"Program : INT MAIN LPAREN RPAREN compound_statement\n\n");}
	;


compound_statement : LCURL var_declaration statements RCURL
{fprintf(logout,"compound_statement : LCURL var_declaration statements RCURL\n\n");}
		   | LCURL statements RCURL
{fprintf(logout,"compound_statement : LCURL statements RCURL\n\n");}
		   | LCURL RCURL
{fprintf(logout,"compound_statement : LCURL RCURL\n\n");}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON
{fprintf(logout,"var_declaration : type_specifier declaration_list SEMICOLON\n\n");}
		|  var_declaration type_specifier declaration_list SEMICOLON
{fprintf(logout,"var_declaration : var_declaration type_specifier declaration_list SEMICOLON\n\n");}
		;

type_specifier	: INT 
{fprintf(logout,"type_specifier : INT \n\n");
strcpy(typeOf,"INT");
strcpy(arrayTypeOf,"INT_ARRAY");}
		| FLOAT
{fprintf(logout,"type_specifier : FLOAT\n\n");
strcpy(typeOf,"FLOAT");
strcpy(arrayTypeOf,"FLOAT_ARRAY");}
		| CHAR
{fprintf(logout,"type_specifier : CHAR\n\n");
strcpy(typeOf,"CHAR");
strcpy(arrayTypeOf,"CHAR_ARRAY");}
		;
			
declaration_list : declaration_list COMMA ID 
{

fprintf(logout,"declaration_list : declaration_list COMMA ID  \n\n");

check=table->insert((char*)$3->getName(),(char*)$3->getType(),(char*)typeOf,$3->getValue());

if(check)fprintf(logout,"%s\n\n",$3->getName());
else {yyerror((char*)"Variable with name already declared/multiple declarations");$$=null;}

}

		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
{

fprintf(logout,"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD \n\n");

check=table->insert((char*)$3->getName(),(char*)$3->getType(),(char*)arrayTypeOf,$3->getValue(),(int)$5->getValue());

if(check)fprintf(logout,"%s\n\n",$3->getName());
else {yyerror((char*)"Variable with name already declared/multiple declarations");$$=null;}

}
		 | ID 
{

fprintf(logout,"declaration_list : ID  \n\n");

check=table->insert((char*)$1->getName(),(char*)$1->getType(),(char*)typeOf,$1->getValue());

if(check)fprintf(logout,"%s\n\n",$1->getName());
else {yyerror((char*)"Variable with name already declared/multiple declarations");$$=null;}

}
		 | ID LTHIRD CONST_INT RTHIRD 
{

fprintf(logout,"declaration_list : ID LTHIRD CONST_INT RTHIRD  \n\n");

check=table->insert((char*)$1->getName(),(char*)$1->getType(),(char*)arrayTypeOf,$1->getValue(),(int)$3->getValue());

if(check)fprintf(logout,"%s\n\n",$1->getName());
else {yyerror((char*)"Variable with name already declared/multiple declarations");$$=null;}

}
		 ;

statements : statement 
{fprintf(logout,"statements : statement  \n\n");}
	   | statements statement 
{fprintf(logout,"statement : statements statement \n\n");}
	   ;


statement  : expression_statement 
{fprintf(logout,"statement : expression_statement\n\n");}
	   | compound_statement
{fprintf(logout,"statement : compound_statement  \n\n");} 
	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement 
{fprintf(logout,"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement  \n\n");}
	   | IF LPAREN expression RPAREN statement
{fprintf(logout,"statement : IF LPAREN expression RPAREN statement  \n\n");}
	   | IF LPAREN expression RPAREN statement ELSE statement
{fprintf(logout,"statement : IF LPAREN expression RPAREN statement ELSE statement  \n\n");}
	   | WHILE LPAREN expression RPAREN statement 
{fprintf(logout,"statement : WHILE LPAREN expression RPAREN statement  \n\n");}
	   | PRINTLN LPAREN ID RPAREN SEMICOLON 
{fprintf(logout,"statement : PRINTLN LPAREN ID RPAREN SEMICOLON  \n\n");}
	   | RETURN expression SEMICOLON 
{fprintf(logout,"statement : RETURN expression SEMICOLON   \n\n");}
	   ;
		
expression_statement	: SEMICOLON	
{fprintf(logout,"expression_statement : SEMICOLON  \n\n");}		
			| expression SEMICOLON 
{fprintf(logout,"expression_statement : expression SEMICOLON  \n\n");}
			;
						
variable : ID 	
{

fprintf(logout,"variable : ID  \n\n");

SymbolInfo *s= table->get($1->getName());

if(s==0){yyerror((char*)"No such variable declared");$$=null;}
else if(strcmp(s->getDecType(),"INT_ARRAY")==0 || strcmp(s->getDecType(),"FLOAT_ARRAY")==0 || strcmp(s->getDecType(),"CHAR_ARRAY")==0)yyerror((char*)"Accessing array pointer instead of explicit array value");
else{
SymbolInfo* z=new SymbolInfo((char*)s->getName(),(char*)s->getType(),(char*)s->getDecType(),s->getValue());
$$=z;
}

}	
	 | ID LTHIRD expression RTHIRD 
{

fprintf(logout,"variable : ID LTHIRD expression RTHIRD   \n\n");

SymbolInfo *s= table->get($1->getName());

if(s==0){yyerror((char*)"No such variable declared");$$=null;}
else if ((int)$3->getValue()>=s->getLength())yyerror((char*)"Array Index out of Bounds");
else{
SymbolInfo* z=new SymbolInfo((char*)s->getName(),(char*)s->getType(),(char*)s->getDecType(),s->getArray()[(int)$3->getValue()]);
$$=z;
}

}	 ;
			
expression : logic_expression	
{
fprintf(logout,"expression : logic_expression  \n\n");

$$=$1;

}
	   | variable ASSIGNOP logic_expression 
{

fprintf(logout,"expression : variable ASSIGNOP logic_expression \n\n");

if(strcmp($1->getDecType(),"NULL")==0 || strcmp($3->getDecType(),"NULL")==0 )printf("NULL\n");

else{

if(strcmp($1->getDecType(),"INT_ARRAY")==0 || strcmp($1->getDecType(),"FLOAT_ARRAY")==0 || strcmp($1->getDecType(),"CHAR_ARRAY" )==0){

    if(strcmp($1->getDecType(),"INT_ARRAY")==0 && strcmp($3->getDecType(),"FLOAT")==0)fprintf(logout,":Type Mismatch. Assigning float type to int type\n\n");

    else{
        SymbolInfo *s= table->get($1->getName());
        table->update($1->getName(),$3->getValue(),s->getIndex($1->getValue()));
        table->print(logout);
    }

}

else{

    if(strcmp($1->getDecType(),"INT")==0 && strcmp($3->getDecType(),"FLOAT")==0){
            yyerror((char*)"Type Mismatch. Assigning float type to int type");
            $$=null;
    }
    else{
        table->update($1->getName(),$3->getValue());
        table->print(logout);
    }
 
}

}

}	
	   ;
			
logic_expression : rel_expression 
{

fprintf(logout,"logic_expression : rel_expression  \n\n");
$$=$1;

}	
		 | rel_expression LOGICOP rel_expression 	
{

fprintf(logout,"logic_expression : rel_expression LOGICOP rel_expression   \n\n");

if(strcmp($1->getDecType(),"NULL")==0 || strcmp($3->getDecType(),"NULL")==0 )printf("NULL\n");

else{
$$=$1;
$$->setDecType("INT");
if(strcmp($2->getDecType(),"AND")==0)$$->setValue($1->getValue() && $3->getValue());
if(strcmp($2->getDecType(),"OR")==0)$$->setValue($1->getValue() || $3->getValue());

}

}
		 ;
			
rel_expression	: simple_expression 
{

fprintf(logout,"rel_expression : simple_expression   \n\n");
$$=$1;

}
		| simple_expression RELOP simple_expression	
{

fprintf(logout,"rel_expression : simple_expression RELOP simple_expression  \n\n");

if(strcmp($1->getDecType(),"NULL")==0 || strcmp($3->getDecType(),"NULL")==0 )$$=null;

else{
$$=$1;
$$->setDecType("INT");
if(strcmp($2->getDecType(),"GT")==0)$$->setValue($1->getValue() > $3->getValue());
if(strcmp($2->getDecType(),"GTE")==0)$$->setValue($1->getValue() >= $3->getValue());
if(strcmp($2->getDecType(),"LT")==0)$$->setValue($1->getValue() < $3->getValue());
if(strcmp($2->getDecType(),"LTE")==0)$$->setValue($1->getValue() <= $3->getValue());
if(strcmp($2->getDecType(),"EQ")==0)$$->setValue($1->getValue() == $3->getValue());
if(strcmp($2->getDecType(),"NEQ")==0)$$->setValue($1->getValue() != $3->getValue());
}

}


		;
				
simple_expression : term 
{

fprintf(logout,"simple_expression : term   \n\n");

$$=$1;
}
		  | simple_expression ADDOP term 
{

fprintf(logout,"simple_expression : simple_expression ADDOP term \n\n");

if(strcmp($1->getDecType(),"NULL")==0 || strcmp($3->getDecType(),"NULL")==0 )$$=null;

else{
$$=$1;
if(strcmp($3->getDecType(),"FLOAT")==0 || strcmp($3->getDecType(),"FLOAT_ARRAY")==0)$$=$3;
if(strcmp($2->getDecType(),"ADD")==0)$$->setValue($1->getValue() + $3->getValue());
if(strcmp($2->getDecType(),"SUB")==0)$$->setValue($1->getValue() - $3->getValue());
}

}
		  ;
					
term :	unary_expression
{

fprintf(logout,"term : unary_expression   \n\n");

$$=$1;


}
     |  term MULOP unary_expression
{

fprintf(logout,"term : term MULOP unary_expression  \n\n");


if(strcmp($1->getDecType(),"NULL")==0 || strcmp($1->getDecType(),"NULL")==0 )printf("NULL\n");

else{
$$=$1;
if(strcmp($3->getDecType(),"FLOAT")==0 || strcmp($3->getDecType(),"FLOAT_ARRAY")==0)$$=$3;
if(strcmp($2->getDecType(),"MOD")==0){
      if((strcmp($1->getDecType(),"INT")==0 || strcmp($1->getDecType(),"INT_ARRAY")==0) && (strcmp($3->getDecType(),"INT")==0 || strcmp($3->getDecType(),"INT_ARRAY")==0 ))$$->setValue((int)$1->getValue() / (int)$3->getValue());
      else {
           yyerror((char*)"Modulus using non-integer values\n\n");
           $$=null;
      }
};

if(strcmp($2->getDecType(),"DIV")==0)$$->setValue($1->getValue() / $3->getValue());

if(strcmp($2->getDecType(),"MUL")==0)$$->setValue($1->getValue() * $3->getValue());

}

}
     ;

unary_expression : ADDOP unary_expression  
{

fprintf(logout,"unary_expression : ADDOP unary_expression   \n\n");

$$=$2;

if(strcmp($1->getDecType(),"AND")==0)$$->setValue(1*$2->getValue());
if(strcmp($1->getDecType(),"OR")==0)$$->setValue(-1*$2->getValue());

}
		 | NOT unary_expression 
{

fprintf(logout,"unary_expression : NOT unary_expression  \n\n");


$$=$1;

if($1->getValue()>0)$$->setValue(0);

else $$->setValue(1);

}
		 | factor 
{

fprintf(logout,"unary_expression : factor   \n\n");

$$=$1;


}
		 ;
	
factor	: variable 
{

fprintf(logout,"factor : variable   \n\n");
$$=$1;

}
	| LPAREN expression RPAREN 
{

fprintf(logout,"factor : LPAREN expression RPAREN   \n\n");
$$=$2;
}
	| CONST_INT 
{

fprintf(logout,"factor : CONST_INT  \n\n");

$$=$1;

fprintf(logout,"%d\n\n",(int)$$->getValue());

}
	| CONST_FLOAT
{

fprintf(logout,"factor : CONST_FLOAT   \n\n");

$$=$1;

fprintf(logout,"%f\n\n",(double)$$->getValue());

}
	| CONST_CHAR
{

fprintf(logout,"factor : CONST_CHAR  \n\n");

$$=$1;

fprintf(logout,"%c\n\n",(char)$$->getValue());

}
	| factor INCOP 
{

fprintf(logout,"factor : variable  \n\n");

$$=$1;

$$->setValue($$->getValue()+1);

}
	| factor DECOP
{

fprintf(logout,"factor : factor DECOP   \n\n");

$$=$1;

$$->setValue($$->getValue()-1);

}
	;
%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	yyin=fin;
	logout= fopen("1305057_log.txt","w");
        table=new SymbolTable(100);
        strcpy(typeOf,"int");


	yyparse();
        table->print(logout);
        fprintf(logout,"Line count: %d\nError count: %d\n\n",line_count,error);
	fclose(fin);
	fclose(logout);
        
        
	return 0;
}



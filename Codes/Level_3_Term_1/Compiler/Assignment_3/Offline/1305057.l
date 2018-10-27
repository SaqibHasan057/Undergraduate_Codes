
%option noyywrap



%{
#include "SymbolTable.cpp"
#include "y.tab.h"




extern YYSTYPE yylval;
void yyerror(char *);
extern int line_count=1;
extern int error=0;



%}



digit [0-9]
letter [A-Za-z]
delim [ \t\r\f\v]
newline \n
ws [delim]+
id (_|{letter})(_|{letter}|{digit})*
integer {digit}+
number {digit}*(\.{digit}+)?(E[+-]?{digit}+)?
character [']{letter}[']
ADDOP [+-] 
MULOP [*/%]

%%

{delim}+	{}
{newline} {line_count++;}

"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"int" {return INT;}
"float" {return FLOAT;}
"double" {return DOUBLE;}
"char" {return CHAR;}
"return" {return RETURN;}
"void" {return VOID;}
"main"	{return MAIN;}
"println"	{return PRINTLN;}

{ADDOP} {               SymbolInfo *s;
			if(strcmp(yytext,"+")==0)s= new SymbolInfo((char*)yytext,(char*)"ADDOP",(char*)"ADD",0);
                        if(strcmp(yytext,"-")==0)s= new SymbolInfo((char*)yytext,(char*)"ADDOP",(char*)"SUB",0);
                        yylval.sym = s;	
			return ADDOP;
		}



{MULOP}	{               
                        SymbolInfo *s;
                        if(strcmp(yytext,"%")==0)s= new SymbolInfo((char*)yytext,(char*)"MULOP",(char*)"MOD",0);
	                if(strcmp(yytext,"/")==0)s= new SymbolInfo((char*)yytext,(char*)"MULOP",(char*)"DIV",0);
                        if(strcmp(yytext,"*")==0)s= new SymbolInfo((char*)yytext,(char*)"MULOP",(char*)"MUL",0);
                        yylval.sym = s;			
			return MULOP;
		}


"=" 	{return ASSIGNOP;}

">" |
"<" |
">=" |
"<=" |
"==" |
"!=" {
                        SymbolInfo *s;
	                if(strcmp(yytext,">")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"GT",0);	
                        if(strcmp(yytext,"<")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"LT",0);		
                        if(strcmp(yytext,">=")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"GTEQ",0);	
	                if(strcmp(yytext,"<=")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"LTEQ",0);	
                        if(strcmp(yytext,"==")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"EQ",0);		
                        if(strcmp(yytext,"!=")==0)s= new SymbolInfo((char*)yytext,(char*)"RELOP",(char*)"NEQ",0);	
                        yylval.sym = s;	
		        return RELOP;
	}

"&&"	|
"||"	{               
                        SymbolInfo *s;
                        if(strcmp(yytext,"&&"))s= new SymbolInfo((char*)yytext,(char*)"LOGICOP",(char*)"AND",0);
	                if(strcmp(yytext,"||"))s= new SymbolInfo((char*)yytext,(char*)"LOGICOP",(char*)"OR",0);	
                        yylval.sym = s;	
			
			return LOGICOP;
		}
"!"		{	return NOT; }


";" 	{return SEMICOLON;}
"," 	{return COMMA;}
"(" 	{return LPAREN;}
")" 	{return RPAREN;}
"{" 	{return LCURL;}
"}" 	{return RCURL;}
"[" 	{return LTHIRD;}
"]" 	{return RTHIRD;}
"++" 	{return INCOP;}
"--" 	{return DECOP;}



{integer}	{
				SymbolInfo *s= new SymbolInfo((char*)yytext,(char*)"CONST_INT",(char*)"INT",atoi(yytext));
                                yylval.sym = s;	
				return CONST_INT;
			}
{number} 	{	
				SymbolInfo *s= new SymbolInfo((char*)yytext,(char*)"CONST_FLOAT",(char*)"FLOAT",atof(yytext));
                                yylval.sym = s;	
				return CONST_FLOAT; 
                }
			
{character} 	{	
				SymbolInfo *s= new SymbolInfo((char*)yytext,(char*)"CONST_CHAR",(char*)"CHAR",(double)yytext[1]);
                                yylval.sym = s;	
				return CONST_CHAR; 
			}
{id} 		{	 
				SymbolInfo *s= new SymbolInfo((char*)yytext,(char*)"ID",(char*)"NULL",-9999999);
				yylval.sym = s;			
				return ID;
			}


%%








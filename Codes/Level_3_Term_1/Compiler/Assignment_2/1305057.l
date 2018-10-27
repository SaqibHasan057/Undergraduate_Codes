%option noyywrap

%x COMMENT
%x STRING

%{

#include "SymbolTable.cpp"

int line_count=1;
int error_count=0;
FILE *logout;
FILE *tokenout;
bool check=false;
string add="";
SymbolTable *table;

%}




NEWLINE "\n"
WHITESPACE [ \t\f\r\v]+ 
SPECIAL ([\\][n])|([\\][t])|([\\][\\])|([\\]["])|([\\][a])|([\\][f])|([\\][r])|([\\][b])|([\\][f])|([\\][b])|([\\][v])|([\\][0])

INTEGER [+-]?[0-9]+
CHARACTER [']([^\n \t \\ \" \a \f \r \b \v \0]|{SPECIAL})[']
FLOAT [+-]?[0-9]+(([.][0-9]+)|(E[+-]?[0-9]+)|([.][0-9]+E[+-]?[0-9]+))


ADDOP [+-]
MULOP [*/%]
INCOP ([+][+])|([-][-])
RELOP ([<])|([<][=])|([>])|([>][=])|([=][=])|([!][=])
ASSIGNOP [=]
LOGICOP ([&][&])|([|][|])|([!])
PAREN [()]
CURL [{}]
BRACKET (\[)|(\])
COMMA [,]
SEMICOLON [;]
IDENTIFIER [a-zA-Z_][a-zA-Z_0-9]*

SINGLELINECOMMENT ([/][/].*)

DECIMALPOINTERROR ([.]?[0-9][.]?)*
INVALIDNAME [0-9]+[a-zA-Z_0-9]+
MULTICHARERROR ['][^\n \t \\ \" \a \f \r \b \v \0][^\n \t \\ \" \a \f \r \b \v \0][']
UNTERMINATEDCHAR (['][^\n \t \\ \" \a \f \r \b \v \0])|(['])
ILLNUMBER {FLOAT}[.](([.])*({FLOAT}|{INTEGER})([.])*)*










%%
{NEWLINE} { line_count++;}
{WHITESPACE} {}



"if" {
             fprintf(tokenout,"<IF>");
             fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n\n",line_count,yytext);
     }


"for" {fprintf(tokenout,"<FOR>");
     fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n\n",line_count,yytext);}


"do" { fprintf(tokenout,"<DO>");
    fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n\n",line_count,yytext);}


"int" {fprintf(tokenout,"<INT>");
    fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n\n",line_count,yytext);}


"float" {fprintf(tokenout,"<FLOAT>");
       fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n\n",line_count,yytext);}


"void" {fprintf(tokenout,"<VOID>");
      fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n\n",line_count,yytext);}


"switch" {fprintf(tokenout,"<SWITCH>");
        fprintf(logout,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n\n",line_count,yytext);}


"default" {fprintf(tokenout,"<DEFAULT>");
         fprintf(logout,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);}

"else" {fprintf(tokenout,"<ELSE>");
      fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n\n",line_count,yytext);}


"while" {fprintf(tokenout,"<WHILE>");
       fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n\n",line_count,yytext);}


"break" {fprintf(tokenout,"<BREAK>");
       fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n\n",line_count,yytext);}


"char" {fprintf(tokenout,"<CHAR>");
      fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n\n",line_count,yytext);}


"double" {fprintf(tokenout,"<DOUBLE>");
        fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n\n",line_count,yytext);}


"return" {fprintf(tokenout,"<RETURN>");
        fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n\n",line_count,yytext);}


"case" {fprintf(tokenout,"<CASE>");
      fprintf(logout,"Line no %d: TOKEN <CASE> Lexeme %s found\n\n",line_count,yytext);}


"continue" {fprintf(tokenout,"<CONTINUE>");
          fprintf(logout,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n\n",line_count,yytext);}

{ADDOP} {fprintf(tokenout,"<ADDOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"ADDOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,ADDOP> already exists\n\n",yytext);}


{MULOP} {fprintf(tokenout,"<MULOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"MULOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,MULOP> already exists\n\n",yytext);}


{INCOP} {fprintf(tokenout,"<INCOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"INCOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,INCOP> already exists\n\n",yytext);
      }


{RELOP} {fprintf(tokenout,"<RELOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"RELOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,RELOP> already exists\n\n",yytext);
      }


{ASSIGNOP} {fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"ASSIGNOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,ASSIGNOP> already exists\n\n",yytext);}


{LOGICOP} {fprintf(tokenout,"<LOGICOP,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"LOGICOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,LOGICOP> already exists\n\n",yytext);}


{PAREN} {fprintf(tokenout,"<PAREN,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <PAREN> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"PAREN");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,PAREN> already exists\n\n",yytext);}


{CURL} {fprintf(tokenout,"<CURL,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <CURL> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"CURL");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,CURL> already exists\n\n",yytext);}


{BRACKET} {fprintf(tokenout,"<BRACKET,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <BRACKET> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"ADDOP");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,BRACKET> already exists\n\n",yytext);}


{COMMA} {fprintf(tokenout,"<COMMA,%s>",yytext);
      fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n\n",line_count,yytext);
      check=table->insert(yytext,"COMMA");
      if(check)table->print(logout);
      else fprintf(logout,"<%s,COMMA> already exists\n\n",yytext);}

{SEMICOLON} {fprintf(tokenout,"<SEMICOLON,%s>",yytext);
           fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n\n",line_count,yytext);
           check=table->insert(yytext,"SEMICOLON");
           if(check)table->print(logout);
           else fprintf(logout,"<%s,SEMICOLON> already exists\n\n",yytext);}


{INTEGER} {fprintf(tokenout,"<CONST_INT,%s>",yytext);
         fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n\n",line_count,yytext);
         check=table->insert(yytext,"CONST_INT");
         if(check)table->print(logout);
         else fprintf(logout,"<%s,CONST_INT> already exists\n\n",yytext);}


{FLOAT} {fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
       fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n\n",line_count,yytext);
       check=table->insert(yytext,"CONST_FLOAT");
       if(check)table->print(logout);
       else fprintf(logout,"<%s,CONST_FLOAT> already exists\n\n",yytext);}


{CHARACTER} {fprintf(tokenout,"<CONST_CHAR,%s>",yytext);
           fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
           check=table->insert(yytext,"CONST_CHAR");
           if(check)table->print(logout);
           else fprintf(logout,"<%s,CONST_CHAR> already exists\n\n",yytext);}

{IDENTIFIER} {fprintf(tokenout,"<ID,%s>",yytext);
            fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n\n",line_count,yytext);
            check=table->insert(yytext,"ID");
            if(check)table->print(logout);
            else fprintf(logout,"<%s,IDENTIFIER> already exists\n\n",yytext);}




{SINGLELINECOMMENT} {fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n\n",line_count,yytext);}

["]  {BEGIN STRING;
      add=yytext;
      fprintf(logout,"Line no %d:",line_count);}
<STRING>[\n] {fprintf(logout,"Unterminated string %s\n\n",add.c_str());
              error_count++;
              line_count++;
              BEGIN INITIAL;}
<STRING>[\\][\n] {add+="  ";line_count++;}
<STRING>[^\n\\\"] {add+=yytext;}
<STRING>["] {add+=yytext;
             fprintf(tokenout,"<ID,%s>",add.c_str());
             fprintf(logout," TOKEN <STRING> Lexeme %s found\n\n",add.c_str());
             BEGIN INITIAL;}
<STRING><<EOF>> {fprintf(logout,"Unterminated string %s\n\n",add.c_str());error_count++;
                 yyterminate();}

[/][*] {BEGIN COMMENT;
        add="";
        fprintf(logout,"Line_count %d:",line_count);
        add+=yytext;}
<COMMENT>. {add+=yytext;}
<COMMENT>\n {add+=" ";line_count++;}
<COMMENT>[*][/] {fprintf(logout,"TOKEN <COMMENT> Lexeme %s found\n\n",add.c_str());
               BEGIN INITIAL;}
<COMMENT><<EOF>> {fprintf(logout,"Unterminated comment %s\n\n",add.c_str());error_count++;
                  yyterminate();}

{DECIMALPOINTERROR} {fprintf(logout,"Too many decimal points %s\n\n",yytext);error_count++;}
{ILLNUMBER} {fprintf(logout,"Ill Formed Number %s\n\n",yytext);error_count++;}
{INVALIDNAME} {fprintf(logout,"Invalid suffix or prefix %s\n\n",yytext);error_count++;}
{MULTICHARERROR} {fprintf(logout,"Multi character error %s\n\n",yytext);error_count++;}
{UNTERMINATEDCHAR} {fprintf(logout,"Unterminated character error %s\n\n",yytext);error_count++;}

. {fprintf(logout,"Unidentified Character %s\n\n",yytext);error_count++;}























%%
int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("1305057_log.txt","w");
	tokenout= fopen("1305057_token.txt","w");
        table = new SymbolTable(100);
        

	yyin= fin;
	yylex();
        fprintf(logout,"Line count: %d,Error count: %d\n",line_count-1,error_count);
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include "mpu6050_twi.h"

float Acc_x,Acc_y,Acc_z,Gyro_x,Gyro_y,Gyro_z;
#define diffMassive 10000

int currentColumn=5;
int currentPlayer=1;

int currentDirection=0;
int aX,aY,aZ,gX,gY,gZ;

int gameBoard[8][8]={
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

int printBoard[16][16];

void gameToPrintBoard(){
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			printBoard[i][j]=gameBoard[i/2][j/2];
		}
	}
}

int maskGreen(int row,int start,int end){
	unsigned int mask = 0;
	int c = 7;
	for(int i=start;i<=end;i++){
		if(printBoard[row][i]==1){
			mask=mask|1<<c;
		}
		c=c-1;
	}
	return ~mask;
}

int maskRed(int row,int start,int end){
	unsigned int mask = 0;
	int c = 7;
	for(int i=start;i<=end;i++){
		if(printBoard[row][i]==2){
			mask=mask|1<<c;
		}
		c=c-1;
	}

	return ~mask;

}

void print(){
     PORTB=0xFF;
     PORTD=0xFF;
     for(int i=0;i<8;i++){
	     PORTA=i;
	     PORTB=maskRed(i,0,7);
	     PORTD=maskGreen(i,0,7);
	     _delay_ms(0.05);
	     PORTB=0xFF;
	     PORTD=0xFF;
     }
     for(int i=8;i<16;i++){
	     PORTA=i;
	     PORTB=maskRed(i-8,8,15);
	     PORTD=maskGreen(i-8,8,15);
	     _delay_ms(0.05);
	     PORTB=0xFF;
	     PORTD=0xFF;
     }
     for(int i=16;i<24;i++){
	     PORTA=i;
	     PORTB=maskRed(i-8,0,7);
	     PORTD=maskGreen(i-8,0,7);
	     _delay_ms(0.05);
			PORTB=0xFF;
     }
     for(int i=24;i<32;i++){
	     PORTA=i;
	     PORTB=maskRed(i-16,8,15);
	     PORTD=maskGreen(i-16,8,15);
	     _delay_ms(0.05);
	     PORTB=0xFF;
	     PORTD=0xFF;
     }
}

int winCondition(){
	for(int i=7;i>=2;i--){
		for(int j=1;j<=4;j++){
			if(gameBoard[i][j]!=0 && gameBoard[i][j]==gameBoard[i][j+1]&&gameBoard[i][j+1]==gameBoard[i][j+2]&&gameBoard[i][j+2]==gameBoard[i][j+3])return gameBoard[i][j];
		}
	}

	for(int i=7;i>=5;i--){
		for(int j=1;j<=7;j++){
			if(gameBoard[i][j]!=0 && gameBoard[i][j]==gameBoard[i-1][j]&&gameBoard[i-1][j]==gameBoard[i-2][j]&&gameBoard[i-2][j]==gameBoard[i-3][j])return gameBoard[i][j];
		}
	}

	for(int i=7;i>=5;i--){
		for(int j=1;j<=4;j++){
			if(gameBoard[i][j]!=0 && gameBoard[i][j]==gameBoard[i-1][j+1]&&gameBoard[i-1][j+1]==gameBoard[i-2][j+2]&&gameBoard[i-2][j+2]==gameBoard[i-3][j+3])return gameBoard[i][j];
		}
	}

	for(int i=7;i>=5;i--){
		for(int j=4;j<=7;j++){
			if(gameBoard[i][j]!=0 && gameBoard[i][j]==gameBoard[i-1][j-1]&&gameBoard[i-1][j-1]==gameBoard[i-2][j-2]&&gameBoard[i-2][j-2]==gameBoard[i-3][j-3])return gameBoard[i][j];
		}
	}
	return 0;
}

int putIntoCurrentColumn(){
	for(int i=7;i>=0;i--){
		if(gameBoard[i][currentColumn]==0){
			gameBoard[i][currentColumn]=currentPlayer;
			return 1;
		}
	}
	return 0;
}

void putCurrentPlayer(){
	gameBoard[0][currentColumn]=currentPlayer;
}

void changePlayer(){
    gameBoard[0][currentColumn]=0;
	if(currentPlayer==1)currentPlayer=2;
	else currentPlayer=1;
	gameBoard[0][currentColumn]=currentPlayer;
}

void moveCurrentPlayer(int choice){
	if(choice==1){
		if(currentColumn>1){
		      gameBoard[0][currentColumn]=0;
		      currentColumn=currentColumn-1;
			  gameBoard[0][currentColumn]=currentPlayer;
		}
	}
	else{
		if(currentColumn<7){
		      gameBoard[0][currentColumn]=0;
		      currentColumn=currentColumn+1;
			  gameBoard[0][currentColumn]=currentPlayer;
		}
	}
}


void winPrint(int choice){
     if(choice==1){
	    for(int i=0;i<32;i++){
		   PORTA=i;
		   PORTB=0xFF;
		   PORTD=0x00;
		}
	 }
	 else{
	    for(int i=0;i<32;i++){
		    PORTA=i;
		    PORTB=0x00;
		    PORTD=0xFF;
	    }
	 }
}

void action(){
    Read_RawValue(&Acc_x, &Acc_y, &Acc_z);
    
    aX = (int) Acc_x;
    aY = (int) Acc_y;
    aZ = (int) Acc_z;

	//right
	if(currentDirection!=1 && aZ<-diffMassive)
	{
		currentDirection=1;
		moveCurrentPlayer(1);
		_delay_ms(300);
	}
	
	//left
	else if(currentDirection!=2 && aZ>diffMassive)
	{
		currentDirection=2;
		moveCurrentPlayer(2);
		_delay_ms(300);
	}

	//up
	else if(currentDirection!=3 && aX<-diffMassive)
	{	
		currentDirection=3;
	}
	
	//down
	else if(currentDirection!=4 && aX>diffMassive)
	{
		currentDirection=4;
		putIntoCurrentColumn();
		changePlayer();
		_delay_ms(300);
	}
	

	if((aX>-5000 && aX<5000) && (aZ>-5000 && aZ<5000))
	{
		currentDirection=0;
	}



}

int main(void)
{
	
    /* Replace with your application code */
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
	DDRA=0x1F;//positive row
	DDRB=0xFF;//negative red
	DDRD=0xFF;//negative green
	DDRC=0x00;

	I2C_Init();	
	Gyro_Init();
	putCurrentPlayer();
	
    while (1) 
    {
	gameToPrintBoard();
	print();
	action();
	int x = winCondition();
	if(x!=0){
	     while(1)winPrint(x);
	}
	}

}


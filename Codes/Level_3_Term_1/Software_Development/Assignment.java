import java.util.Scanner;

class Calculator{

	private int a = 0; 
	private int b = 0;
	private int result = 0;
	
}



class Assignment {


	public static void main(String[] args) {

		Calculator calc  = new Calculator();

		Scanner input = new Scanner(System.in);
		int i = 10;
		while(i>0){
			
			input = new Scanner(System.in);

			int dispOpt = input.nextInt();
			Display disp = new Display(dispOpt);
			
			int calcOpt = input.nextInt();
			calc.setA(input.nextInt());
			calc.setB(input.nextInt());
			
			if(calcOpt==1)
				calc.add();
			else if(calcOpt==2)
				calc.sub();
			else if(calcOpt==3)
				calc.mult();
			else if(calcOpt==4)
				calc.div();

			disp.display(calc.getResult());
			i--;
		}
		input.close();
	}

}






class Display {
	private GUI gui = null;
	public Display(int guiOpt){	
		if(guiOpt == 1){
			gui = new Swing();
		} 
		else if(guiOpt == 2){
			gui = new AWT();
		} 
		else if(guiOpt == 3){
			gui = new Motif();
		}
	}
	
	public void display(int result){
		gui.show(result);
	}
}
import java.util.Scanner;

/**
 * Created by Dipto on 06/10/2017.
 */
public class test {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n;
        n=input.nextInt();

        int[][] dummy = new int[n][n];

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                dummy[i][j]=input.nextInt();
            }
        }

        State state = new State(n,dummy);
        state.printBoard();
        state.moveColumn(1,1);
        state.printBoard();
    }
}

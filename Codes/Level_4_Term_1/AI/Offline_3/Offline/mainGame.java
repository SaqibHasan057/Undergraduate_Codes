import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by Dipto on 08/12/2017.
 */
public class mainGame {
    final static int BLACK = 1;
    final static int WHITE = 2;
    final static int BLANK = 0;
    final static String[] heuresticList = {"POSITIONAL","MOBILITY","ABSOLUTECOUNT"};
    final static int TERMINAL_DEPTH = 8;
    static int currentPlayer = BLACK;
    static int oppositePlayer = WHITE;
    static String currentPlayerString = "BLACK";
    static Scanner input = new Scanner(System.in);
    static int xInput = 0;
    static int yInput = 0;
    //static int ALPHA = Integer.MIN_VALUE;
    //static int BETA = Integer.MAX_VALUE;

    public static void printMovesList(ArrayList<int[]> movesArray){
        for(int i=0;i<movesArray.size();i++){
            int[] element = movesArray.get(i);
            System.out.println(element[0]+","+element[1]);
        }
    }

    public static void takeInput(){
        System.out.println("Enter x and y values "+currentPlayerString+" :");
        xInput = input.nextInt();
        yInput = input.nextInt();
    }

    public static void switchPlayer(){
        if(currentPlayer==BLACK){
            currentPlayer=WHITE;
            currentPlayerString="WHITE";
            oppositePlayer=BLACK;
        }
        else{
            currentPlayer=BLACK;
            currentPlayerString="BLACK";
            oppositePlayer=WHITE;
        }
    }

    public static boolean winningCondition(boardState gameBoard){
        boolean filledUp = gameBoard.boardFilledUp();
        boolean noMoreMoves = gameBoard.noMoreMoves();
        int blackScore = gameBoard.countScore(BLACK);
        int whiteScore = gameBoard.countScore(WHITE);

        if(filledUp || noMoreMoves || whiteScore<=0 || blackScore<=0){

            if(blackScore>whiteScore){
                System.out.println("BLACK WINS!!");
            }
            else if(whiteScore>blackScore){
                System.out.println("WHITE WINS!!");
            }
            else{
                System.out.println("DRAW!!");
            }
            return true;
        }

        return false;

    }

    public static boolean endGameCondition(boardState gameBoard){
        boolean filledUp = gameBoard.boardFilledUp();
        boolean noMoreMoves = gameBoard.noMoreMoves();
        int blackScore = gameBoard.countScore(BLACK);
        int whiteScore = gameBoard.countScore(WHITE);

        if(filledUp || noMoreMoves || whiteScore<=0 || blackScore<=0){
            return true;
        }

        return false;

    }

    public static int MAX_VALUE(int depth,boardState gameBoard,String typeOfHeurestic,int parentAlpha,int parentBeta){

        int currentAlpha = parentAlpha;
        int currentBeta = parentBeta;

        if(depth==TERMINAL_DEPTH){
            gameBoard.calculateHeuresticValue(currentPlayer,typeOfHeurestic);
            int retVal = gameBoard.getHeuresticValue();
            return retVal;
        }

        boolean endGame = endGameCondition(gameBoard);

        if(endGame){
            gameBoard.calculateHeuresticValue(currentPlayer,typeOfHeurestic);
            int retVal = gameBoard.getHeuresticValue();
            return retVal;
        }

        ArrayList<int[]> movesList = gameBoard.getSetOfValidMoves(currentPlayer);

        int v = Integer.MIN_VALUE;

        for(int i=0;i<movesList.size();i++){
            int[] element = movesList.get(i);
            boardState newBoard = new boardState(8,gameBoard.copyBoard());
            newBoard.placeCoin(element[0],element[1],currentPlayer);
            int valueRecursion = MIN_VALUE(depth+1,newBoard,typeOfHeurestic,currentAlpha,currentBeta);
            v= Integer.max(v,valueRecursion);
            if(v>=currentBeta)return v;
            currentAlpha = Integer.max(currentAlpha,v);
        }

        return v;






    }

    public static int MIN_VALUE(int depth,boardState gameBoard,String typeOfHeurestic,int parentAlpha,int parentBeta){

        int currentAlpha = parentAlpha;
        int currentBeta = parentBeta;


        if(depth==TERMINAL_DEPTH){
            gameBoard.calculateHeuresticValue(currentPlayer,typeOfHeurestic);
            int retVal = gameBoard.getHeuresticValue();
            return retVal;
        }

        boolean endGame = endGameCondition(gameBoard);

        if(endGame){
            gameBoard.calculateHeuresticValue(currentPlayer,typeOfHeurestic);
            int retVal = gameBoard.getHeuresticValue();
            return retVal;
        }

        ArrayList<int[]> movesList = gameBoard.getSetOfValidMoves(oppositePlayer);

        int v = Integer.MAX_VALUE;

        for(int i=0;i<movesList.size();i++){
            int[] element = movesList.get(i);
            boardState newBoard = new boardState(8,gameBoard.copyBoard());
            newBoard.placeCoin(element[0],element[1],oppositePlayer);
            int valueRecursion = MAX_VALUE(depth+1,newBoard,typeOfHeurestic,currentAlpha,currentBeta);
            v= Integer.min(v,valueRecursion);
            if(v<=currentAlpha)return v;
            currentBeta = Integer.min(currentBeta,v);
        }

        return v;

    }


    public static int[] miniMaxAlgorithm(int depth,boardState gameBoard,String typeOfHeurestic){

        int rootAlpha = Integer.MIN_VALUE;
        int rootBeta = Integer.MAX_VALUE;

        ArrayList<int[]> movesList = gameBoard.getSetOfValidMoves(currentPlayer);
        int v = Integer.MIN_VALUE;
        int bestMoveIndex = 0;


        for(int i=0;i<movesList.size();i++){
            int[] element = movesList.get(i);
            boardState newBoard = new boardState(8,gameBoard.copyBoard());
            newBoard.placeCoin(element[0],element[1],currentPlayer);
            int retVal = MIN_VALUE(depth+1,newBoard,typeOfHeurestic,rootAlpha,rootBeta);
            v = Integer.max(v,retVal);
            if(v>=rootAlpha){
                rootAlpha=v;
                bestMoveIndex=i;
            }
        }
        return movesList.get(bestMoveIndex);
    }

/*
    public static void main(String[] args) {

        double averageTime = 0;

        for(int i=0;i<3;i++) {

            long startTime = System.currentTimeMillis();
            boardState gameBoard = new boardState(8);
            gameBoard.createInitialState();

            while (true) {
                gameBoard.printBoard();
                ArrayList<int[]> movesList = gameBoard.getSetOfValidMoves(currentPlayer);
                boolean hasValidMoves = movesList.size() > 0 ? true : false;

                if (hasValidMoves) {
                    int[] move = miniMaxAlgorithm(0, gameBoard, heuresticList[2]);
                    System.out.println();
                    System.out.println("Computer "+currentPlayerString+ " played move at " + move[0] + "," + move[1]);
                    gameBoard.placeCoin(move[0], move[1], currentPlayer);
                } else {
                    System.out.println("No valid moves for " + currentPlayer);
                }

                boolean endGame = winningCondition(gameBoard);
                if (endGame) break;
                switchPlayer();
                System.out.println();
                System.out.println();
            }
            gameBoard.printBoard();
            long endTime = System.currentTimeMillis();
            double timeTaken = endTime - startTime;
            timeTaken = (double)timeTaken / 1000;

            averageTime+=timeTaken;

            System.out.println("Time taken for iteration "+(i+1)+" : " + timeTaken);
        }

        averageTime = averageTime/100;

        System.out.println("Average time for heurestic: "+averageTime);
    }
    */




    public static void main(String[] args) {
        System.out.println("Hello World!!");
        boardState gameBoard = new boardState(8);
        gameBoard.createInitialState();


        while(true){
            gameBoard.printBoard();
            ArrayList<int[]> movesList = gameBoard.getSetOfValidMoves(currentPlayer);
            boolean hasValidMoves = movesList.size()>0?true:false;
            if(hasValidMoves){
                if(currentPlayer==BLACK) {
                    printMovesList(movesList);
                    takeInput();
                    gameBoard.placeCoin(xInput, yInput, currentPlayer);
                }
                else{
                    int[] move = miniMaxAlgorithm(0,gameBoard,heuresticList[2]);
                    System.out.println();
                    System.out.println("Computer played move at "+move[0]+","+move[1]);
                    gameBoard.placeCoin(move[0],move[1],currentPlayer);
                }
            }
            else{
                System.out.println("No valid moves for "+currentPlayerString);
            }
            boolean endGame = winningCondition(gameBoard);
            if(endGame)break;
            switchPlayer();
            System.out.println();
            System.out.println();
        }
        gameBoard.printBoard();
    }


}

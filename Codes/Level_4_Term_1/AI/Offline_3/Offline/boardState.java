import java.util.ArrayList;

/**
 * Created by Dipto on 08/12/2017.
 */
public class boardState {
    private int BLACK = 1;
    private int WHITE = 2;
    private int BLANK = 0;
    private int boardArray[][];
    private int sizeOfBoard;
    private int heuresticValue;
    private int W1 = 10;
    private int W2 = 10;

    private int positionalHeuresticMatrix[][] = {
            {4,-3,2,2,2,2,-3,4},
            {-3,-3,-1,-1,-1,-1,-4,-3},
            {2,-1,1,0,0,1,-1,2},
            {2,-1,0,1,1,0,-1,2},
            {2,-1,0,1,1,0,-1,2},
            {2,-1,1,0,0,1,-1,2},
            {-3,-4,-1,-1,-1,-1,-4,-3},
            {4,-3,2,2,2,2,-3,4}
    };

    private int positionalHeuresticMatrix2[][] = {
            {100,-20,10,5,5,10,-20,100},
            {-20,-50,-2,-2,-2,-2,-50,-20},
            {10,-2,-1,-1,-1,-1,-2,10},
            {5,-2,-1,-1,-1,-1,-2,5},
            {5,-2,-1,-1,-1,-1,-2,5},
            {10,-2,-1,-1,-1,-1,-2,10},
            {-20,-50,-2,-2,-2,-2,-50,-20},
            {100,-20,10,5,5,10,-20,100}
    };

    public boardState(int sizeOfBoard){
        this.sizeOfBoard=sizeOfBoard;
        this.heuresticValue = -999;
        boardArray = new int[sizeOfBoard+2][sizeOfBoard+2];

        for(int i=0;i<=sizeOfBoard;i++)boardArray[0][i]=-1;
        for(int i=0;i<=sizeOfBoard;i++)boardArray[i][0]=-1;

        for(int i=0;i<=sizeOfBoard;i++)boardArray[sizeOfBoard+1][i]=-1;
        for(int i=0;i<=sizeOfBoard;i++)boardArray[i][sizeOfBoard+1]=-1;

        for(int i=1;i<=sizeOfBoard;i++)for(int j=1;j<=sizeOfBoard;j++)boardArray[i][j]=0;
    }

    public boardState(int sizeOfBoard,int[][]boardArray){
        this.sizeOfBoard=sizeOfBoard;
        this.heuresticValue = -999;
        this.boardArray = boardArray;
    }

    public void createInitialState(){
        boardArray[4][4]=2;
        boardArray[4][5]=1;
        boardArray[5][4]=1;
        boardArray[5][5]=2;
    }

    public void printBoard(){
        System.out.print("  ");
        for(int i=1;i<=sizeOfBoard;i++) System.out.print(i+" ");
        System.out.println();
        for(int i=1;i<=sizeOfBoard;i++){
            System.out.print(i+" ");
            for(int j=1;j<=sizeOfBoard;j++){
                if(boardArray[i][j]==0) System.out.print("- ");
                if(boardArray[i][j]==1) System.out.print("B ");
                if(boardArray[i][j]==2) System.out.print("W ");
            }
            System.out.println();
        }
    }

    public int[][] copyBoard(){
        int[][] newBoard = new int[sizeOfBoard+2][sizeOfBoard+2];

        for(int i=0;i<=sizeOfBoard+1;i++){
            for(int j=0;j<=sizeOfBoard;j++){
                newBoard[i][j]=boardArray[i][j];
            }
        }

        return newBoard;
    }

    public boolean boardFilledUp(){
        for(int i=1;i<=sizeOfBoard;i++){
            for(int j=1;j<=sizeOfBoard;j++){
                if(boardArray[i][j]==0)return false;
            }
        }
        return true;
    }

    public int countScore(int color){
        int score = 0;
        for(int i=1;i<sizeOfBoard;i++){
            for(int j=1;j<=sizeOfBoard;j++){
                if(boardArray[i][j]==color)score++;
            }
        }
        return score;
    }

    public boolean isValidMove(int x,int y,int color){
        int oppositeColor;
        if(color==BLACK)oppositeColor=WHITE;
        else oppositeColor=BLACK;


        if(boardArray[x][y]!=0)return false;

        //UP
        if(boardArray[x-1][y]==oppositeColor){
            for(int i=x-1;i>=1;i--){
                if(boardArray[i][y]==BLANK)break;
                if(boardArray[i][y]==color)return true;
            }
        }

        //DOWN
        if(boardArray[x+1][y]==oppositeColor){
            for(int i=x+1;i<=sizeOfBoard;i++){
                if(boardArray[i][y]==BLANK)break;
                if(boardArray[i][y]==color)return true;
            }
        }

        //LEFT
        if(boardArray[x][y-1]==oppositeColor){
            for(int i=y-1;i>=1;i--){
                if(boardArray[x][i]==BLANK)break;
                if(boardArray[x][i]==color)return true;
            }
        }

        //RIGHT
        if(boardArray[x][y+1]==oppositeColor){
            for(int i=y+1;i<=sizeOfBoard;i++){
                if(boardArray[x][i]==BLANK)break;
                if(boardArray[x][i]==color)return true;
            }
        }

        //UPPER LEFT
        if(boardArray[x-1][y-1]==oppositeColor){
            int tempX=x-1;
            int tempY=y-1;
            while(tempX>=1 && tempY>=1){
                if(boardArray[tempX][tempY]==BLANK)break;
                if(boardArray[tempX][tempY]==color)return true;
                tempX--;
                tempY--;
            }
        }



        //UPPER RIGHT
        if(boardArray[x-1][y+1]==oppositeColor){
            int tempX=x-1;
            int tempY=y+1;
            while(tempX>=1 && tempY<=sizeOfBoard){
                if(boardArray[tempX][tempY]==BLANK)break;
                if(boardArray[tempX][tempY]==color)return true;
                tempX--;
                tempY++;
            }
        }


        //LOWER LEFT
        if(boardArray[x+1][y-1]==oppositeColor){
            int tempX=x+1;
            int tempY=y-1;
            while(tempX<=sizeOfBoard && tempY>=1){
                if(boardArray[tempX][tempY]==BLANK)break;
                if(boardArray[tempX][tempY]==color)return true;
                tempX++;
                tempY--;
            }
        }

        //LOWER RIGHT
        if(boardArray[x+1][y+1]==oppositeColor){
            int tempX=x+1;
            int tempY=y+1;
            while(tempX<=sizeOfBoard && tempY<=sizeOfBoard){
                if(boardArray[tempX][tempY]==BLANK)break;
                if(boardArray[tempX][tempY]==color)return true;
                tempX++;
                tempY++;
            }
        }

        return false;

    }

    public void placeCoin(int x,int y,int color){
        boardArray[x][y]=color;
        flipCoins(x,y,color);
    }


    public void flipCoins(int x,int y,int color){
        int oppositeColor;
        if(color==BLACK)oppositeColor=WHITE;
        else oppositeColor=BLACK;

        int i;
        int tempX;
        int tempY;


        //UP
        if(boardArray[x-1][y]==oppositeColor) {
            for (i = x - 1; i >= 1; i--) {
                if(boardArray[i][y]==BLANK)break;
                if (boardArray[i][y] == color) {
                    for (; i <= x; i++) boardArray[i][y] = color;
                    break;
                }
            }
        }




        //DOWN
        if(boardArray[x+1][y]==oppositeColor) {
            for (i = x + 1; i <= sizeOfBoard; i++) {
                if(boardArray[i][y]==BLANK)break;
                if (boardArray[i][y] == color) {
                    for (; i >= x; i--) boardArray[i][y] = color;
                    break;
                }
            }
        }





        //LEFT
        if(boardArray[x][y-1]==oppositeColor) {
            for (i = y - 1; i >= 1; i--) {
                if(boardArray[x][i]==BLANK)break;
                if (boardArray[x][i] == color) {
                    for (; i <= y; i++) boardArray[x][i] = color;
                    break;
                }
            }
        }




        //RIGHT
        if(boardArray[x][y+1]==oppositeColor) {
            for (i = y + 1; i <= sizeOfBoard; i++) {
                if(boardArray[x][i]==BLANK)break;
                if (boardArray[x][i] == color) {
                    for (; i >= y; i--) boardArray[x][i] = color;
                    break;
                }
            }
        }




        //UPPER LEFT
        if(boardArray[x-1][y-1]==oppositeColor) {
            tempX = x - 1;
            tempY = y - 1;
            while (tempX >= 1 && tempY >= 1) {
                if(boardArray[tempX][tempY]==BLANK)break;
                if (boardArray[tempX][tempY] == color) {
                    while (tempX <= x && tempY <= y) {
                        boardArray[tempX][tempY] = color;
                        tempX++;
                        tempY++;
                    }
                    break;
                }
                tempX--;
                tempY--;
            }
        }






        //UPPER RIGHT
        if(boardArray[x-1][y+1]==oppositeColor) {
            tempX = x - 1;
            tempY = y + 1;
            while (tempX >= 1 && tempY <= sizeOfBoard) {
                if(boardArray[tempX][tempY]==BLANK)break;
                if (boardArray[tempX][tempY] == color) {
                    while (tempX <= x && tempY >= y) {
                        boardArray[tempX][tempY] = color;
                        tempX++;
                        tempY--;
                    }
                    break;
                }
                tempX--;
                tempY++;
            }
        }




        //LOWER LEFT
        if(boardArray[x+1][y-1]==oppositeColor) {
            tempX = x + 1;
            tempY = y - 1;
            while (tempX <= sizeOfBoard && tempY >= 1) {
                if(boardArray[tempX][tempY]==BLANK)break;
                if (boardArray[tempX][tempY] == color) {
                    while (tempX >= x && tempY <= y) {
                        boardArray[tempX][tempY] = color;
                        tempX--;
                        tempY++;
                    }
                    break;
                }
                tempX++;
                tempY--;
            }
        }




        //LOWER RIGHT
        if(boardArray[x+1][y+1]==oppositeColor) {
            tempX = x + 1;
            tempY = y + 1;
            while (tempX <= sizeOfBoard && tempY <= sizeOfBoard) {
                if(boardArray[tempX][tempY]==BLANK)break;
                if (boardArray[tempX][tempY] == color) {
                    while (tempX >= x && tempY >= y) {
                        boardArray[tempX][tempY] = color;
                        tempX--;
                        tempY--;
                    }
                    break;
                }
                tempX++;
                tempY++;
            }
        }
    }

    public ArrayList<int[]> getSetOfValidMoves(int playerColor){
        ArrayList<int[]> setOfValidMoves = new ArrayList<>();
        for(int i=1;i<=sizeOfBoard;i++){
            for(int j=1;j<=sizeOfBoard;j++){
                if(isValidMove(i,j,playerColor)){
                    int[] element = {i,j};
                    setOfValidMoves.add(element);
                }
            }
        }
        return setOfValidMoves;
    }

    public boolean noMoreMoves(){
        ArrayList<int[]> blackMoves = getSetOfValidMoves(BLACK);
        ArrayList<int[]> whiteMoves = getSetOfValidMoves(WHITE);
        if(whiteMoves.size()==0 && blackMoves.size()==0)return true;
        return false;
    }

    public int cornerCount(int color){
        int scoreCount = 0;
        if(boardArray[1][1]==color)scoreCount++;
        if(boardArray[sizeOfBoard][sizeOfBoard]==color)scoreCount++;
        if(boardArray[0][sizeOfBoard]==color)scoreCount++;
        if(boardArray[sizeOfBoard][0]==color)scoreCount++;
        return scoreCount;
    }

    public int getHeuresticValue(){return heuresticValue;}
    public void setHeuresticValue(int heuresticValue){this.heuresticValue=heuresticValue;}

    public void calculateHeuresticValue(int color,String typeOfHeurestic){
        if(typeOfHeurestic=="POSITIONAL")this.heuresticValue=positionalHeurestic(color,2);
        if(typeOfHeurestic=="MOBILITY")this.heuresticValue=mobilityHeurestic(color);
        if(typeOfHeurestic=="ABSOLUTECOUNT")this.heuresticValue=absoluteCountHeurestic(color);
    }

    public int positionalHeurestic(int color,int number){
        int oppositeColor;
        if(color==BLACK)oppositeColor=WHITE;
        else oppositeColor=BLACK;

        int heuresticCount=0;

        if(number==1) {
            for (int i = 1; i <= sizeOfBoard; i++) {
                for (int j = 1; j <= sizeOfBoard; j++) {
                    if (boardArray[i][j] == color) {
                        heuresticCount += 1 * positionalHeuresticMatrix[i - 1][j - 1];
                    } else if (boardArray[i][j] == oppositeColor) {
                        heuresticCount += -1 * positionalHeuresticMatrix[i - 1][j - 1];
                    }
                }
            }
            return heuresticCount;
        }
        else{
            for (int i = 1; i <= sizeOfBoard; i++) {
                for (int j = 1; j <= sizeOfBoard; j++) {
                    if (boardArray[i][j] == color) {
                        heuresticCount += 1 * positionalHeuresticMatrix2[i - 1][j - 1];
                    } else if (boardArray[i][j] == oppositeColor) {
                        heuresticCount += -1 * positionalHeuresticMatrix2[i - 1][j - 1];
                    }
                }
            }
            return heuresticCount;
        }
    }

    public int mobilityHeurestic(int color){
        int oppositeColor;
        if(color==BLACK)oppositeColor=WHITE;
        else oppositeColor=BLACK;

        int colorCornerCount = cornerCount(color);
        int oppositeColorCornerCount = cornerCount(color);

        ArrayList<int[]> colorMoves = getSetOfValidMoves(color);
        ArrayList<int[]> oppositeColorMoves = getSetOfValidMoves(oppositeColor);

        int numberOfColorMoves = colorMoves.size();
        int numberOfOppositeColorMoves = oppositeColorMoves.size();

        int heurestic = W1*(colorCornerCount-oppositeColorCornerCount);
        heurestic += W2*((float)(numberOfColorMoves-numberOfOppositeColorMoves))/(numberOfColorMoves+numberOfOppositeColorMoves);

        return heurestic;
    }

    public int absoluteCountHeurestic(int color){
        int oppositeColor;
        if(color==BLACK)oppositeColor=WHITE;
        else oppositeColor=BLACK;

        int colorCount = countScore(color);
        int oppositeColorCount = countScore(oppositeColor);

        return colorCount-oppositeColorCount;
    }

}

/**
 * Created by Dipto on 05/10/2017.
 */

import java.util.Arrays;

import static java.lang.Math.max;
import static java.lang.Math.abs;
import static java.lang.Math.min;

public class State {
    private int size;
    private int[][] board;
    private double g;
    private double f;
    private State cameFrom;
    private String movement;

    public State(int n, int[][] board) {
        size = n;
        this.board = new int[n][n];
        for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) this.board[i][j] = board[i][j];
        g = Integer.MAX_VALUE;
        f = Integer.MAX_VALUE;
        cameFrom = null;
        movement = "";
    }

    public int getSize() {
        return size;
    }

    public int[][] getBoard() {
        return board;
    }

    public void setG(double g) {
        this.g = g;
    }

    public double getG() {
        return g;
    }

    public void setF(double f) {
        this.f = f;
    }

    public double getF() {
        return f;
    }

    public void setCameFrom(State state) {
        cameFrom = state;
    }

    public State getCameFrom() {
        return cameFrom;
    }

    public void setMovement(String movement) {
        this.movement = movement;
    }

    public String getMovement() {
        return movement;
    }

    void moveColumn(int col, int direction) {
        if (direction == 1) {
            int temp = board[0][col];
            for (int i = 1; i < size; i++) {
                board[i - 1][col] = board[i][col];
            }
            board[size - 1][col] = temp;
        } else if (direction == 2) {
            int temp = board[size - 1][col];
            for (int i = size - 1; i > 0; i--) {
                board[i][col] = board[i - 1][col];
            }
            board[0][col] = temp;
        }
    }

    void moveRow(int row, int direction) {
        if (direction == 3) {
            int temp = board[row][0];
            for (int i = 1; i < size; i++) {
                board[row][i - 1] = board[row][i];
            }
            board[row][size - 1] = temp;
        } else if (direction == 4) {
            int temp = board[row][size - 1];
            for (int i = size - 1; i > 0; i--) {
                board[row][i] = board[row][i - 1];
            }
            board[row][0] = temp;
        }
    }

    public double mismatch(State goal) {
        int[][] goalBoard = goal.getBoard();
        int count = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (this.board[i][j] != goalBoard[i][j]) count = count + 1;
            }
        }
        double ret = (double) count / size;

        return Math.floor(ret);
    }

    public double manhattan_distance(State goal) {
        int[][] goalBoard = goal.getBoard();
        int distance = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int matrixValue = this.board[i][j];
                int position = matrixValue - 1;
                if (position <= i) distance += min(abs(position - i), abs(size - i + position));
                else if (position > i) distance += min(abs(position - i), abs(size + i - position));
            }
        }

        double ret = (double) distance / size;
        return Math.ceil(ret);
    }

    public double multiple_manhattan(State goal) {
        int[][] goalBoard = goal.getBoard();
        int distanceUp = 0;
        int distanceDown = 0;
        int distanceLeft = 0;
        int distanceRight = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int matrixValue = this.board[i][j];
                int position = matrixValue - 1;
                if (position <= i) distanceUp += min(abs(position - i), abs(size - i + position));
                else if (position > i) distanceUp += min(abs(position - i), abs(size + i - position));
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int matrixValue = this.board[i][j];
                int position = size-matrixValue;
                if (position <= i) distanceDown += min(abs(position - i), abs(size - i + position));
                else if (position > i) distanceDown += min(abs(position - i), abs(size + i - position));
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int matrixValue = this.board[i][j];
                int position = matrixValue - 1;
                if (position <= i) distanceLeft += min(abs(position - j), abs(size - j + position));
                else if (position > i) distanceLeft += min(abs(position - j), abs(size + j - position));
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int matrixValue = this.board[i][j];
                int position = size-matrixValue;
                if (position <= i) distanceRight += min(abs(position - j), abs(size - j + position));
                else if (position > i) distanceRight += min(abs(position - j), abs(size + j - position));
            }
        }


        double retUp = Math.ceil((double)distanceUp/size);
        double retDown = Math.ceil((double)distanceDown/size);
        double retLeft = Math.ceil((double)distanceLeft/size);
        double retRight = Math.ceil((double)distanceRight/size);
        double ret = min(min(retUp,retDown),min(retLeft,retRight));

        return Math.ceil(ret);
        //return retRight;

    }

    public boolean match(State goal) {
        int[][] goalBoard = goal.getBoard();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (this.board[i][j] != goalBoard[i][j]) return false;
            }
        }
        return true;
    }

    void printBoard() {
        System.out.println();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    void printMovement() {
        System.out.print(movement);
    }

    @Override
    public boolean equals(Object other) {
        if (!(other instanceof State)) {
            return false;
        }

        State that = (State) other;
        return match(that);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(board);
    }
}
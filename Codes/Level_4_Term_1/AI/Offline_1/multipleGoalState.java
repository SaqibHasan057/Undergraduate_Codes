import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by Dipto on 07/10/2017.
 */
public class multipleGoalState {

    public static final int UP = 1;
    public static final int DOWN = 2;
    public static final int LEFT = 3;
    public static final int RIGHT = 4;


    public static State createGoalState(int size){
        int[][] dummy = new int[size][size];

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                dummy[i][j]=i+1;
            }
        }

        State retState = new State(size,dummy);
        return retState;
    }

    public static State createGoalState1(int size){
        int[][] dummy = new int[size][size];

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                dummy[i][j]=j+1;
            }
        }

        State retState = new State(size,dummy);
        return retState;
    }

    public static State createGoalState2(int size){
        int[][] dummy = new int[size][size];

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                dummy[i][j]=size-i;
            }
        }

        State retState = new State(size,dummy);
        return retState;
    }

    public static State createGoalState3(int size){
        int[][] dummy = new int[size][size];

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                dummy[i][j]=size-j;
            }
        }

        State retState = new State(size,dummy);
        return retState;
    }

    public static ArrayList<State> reconstruct_path(State current){
        ArrayList<State> retList = new ArrayList<>();
        State hold = current;
        retList.add(current);

        while(hold.getCameFrom()!=null){
            hold=hold.getCameFrom();
            retList.add(hold);
        }
        return retList;
    }

    public static void printAnswer(ArrayList<State> path){
        System.out.println("Number of moves: "+(path.size()-1));
        System.out.println("----------------------");
        for(int i=path.size()-1;i>=0;i--){
            State get = path.get(i);
            System.out.println();
            get.printMovement();
            get.printBoard();
            System.out.println();
        }
        System.out.println("----------------------");
    }



    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("input.txt");
        Scanner input = new Scanner(file);

        while (input.hasNext()) {
            int n;
            n = input.nextInt();
            if(n==0)break;

            int[][] dummy = new int[n][n];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dummy[i][j] = input.nextInt();
                }
            }

            State initialState = new State(n, dummy);
            State goalState = createGoalState(n);
            State goalState1 = createGoalState1(n);
            State goalState2 = createGoalState2(n);
            State goalState3 = createGoalState3(n);

            PriorityQueue<State> minHeap = new PriorityQueue<State>(new Comparator<State>() {
                @Override
                public int compare(State o1, State o2) {
                    return Integer.compare((int) o1.getF(), (int) o2.getF());
                }
            });

            Set<State> openSet = new HashSet<>();
            Set<State> closedSet = new HashSet<>();
            ArrayList<State> path = new ArrayList<>();

            minHeap.add(initialState);
            openSet.add(initialState);

            initialState.setG(0);
            initialState.setF(initialState.multiple_manhattan(goalState));
            initialState.setCameFrom(null);

            int count = 0;
            //initialState.printBoard();
            //System.out.println(initialState.getF());
            //System.out.println("Started again!!");

            while (minHeap.isEmpty() == false) {
                //count++;
                //System.out.println(count);
                State current = minHeap.poll();


                if (current.match(goalState) || current.match(goalState1) || current.match(goalState2) || current.match(goalState3)) {
                    System.out.println("Match");
                    path = reconstruct_path(current);
                    break;
                }

                closedSet.add(current);


                //UP
                for (int i = 0; i < n; i++) {
                    State child = new State(n, current.getBoard());
                    child.moveColumn(i, UP);
                    child.setCameFrom(current);

                    if (!openSet.contains(child)) {
                        if (closedSet.contains(child)) continue;

                        double new_g = current.getG() + 1;

                        if (new_g >= child.getG()) continue;

                        child.setG(new_g);
                        child.setF(child.getG() + child.multiple_manhattan(goalState));

                        int x = i + 1;
                        child.setMovement("Column " + x + " UP");

                        openSet.add(child);
                        minHeap.add(child);
                    }
                }

                //DOWN
                for (int i = 0; i < n; i++) {
                    State child = new State(n, current.getBoard());
                    child.moveColumn(i, DOWN);
                    child.setCameFrom(current);

                    if (!openSet.contains(child)) {
                        if (closedSet.contains(child)) continue;


                        double new_g = current.getG() + 1;

                        if (new_g >= child.getG()) continue;

                        child.setG(new_g);
                        child.setF(child.getG() + child.multiple_manhattan(goalState));

                        int x = i + 1;
                        child.setMovement("Column " + x + " DOWN");

                        openSet.add(child);
                        minHeap.add(child);
                    }
                }

                //LEFT
                for (int i = 0; i < n; i++) {
                    State child = new State(n, current.getBoard());
                    child.moveRow(i, LEFT);
                    child.setCameFrom(current);

                    if (!openSet.contains(child)) {
                        if (closedSet.contains(child)) continue;

                        double new_g = current.getG() + 1;

                        if (new_g >= child.getG()) continue;

                        child.setG(new_g);
                        child.setF(child.getG() + child.multiple_manhattan(goalState));

                        int x = i + 1;
                        child.setMovement("Row " + x + " LEFT");

                        openSet.add(child);
                        minHeap.add(child);
                    }
                }

                //RIGHT
                for (int i = 0; i < n; i++) {
                    State child = new State(n, current.getBoard());
                    child.moveRow(i, RIGHT);
                    child.setCameFrom(current);
                    if (!openSet.contains(child)) {
                        if (closedSet.contains(child)) continue;

                        double new_g = current.getG() + 1;

                        if (new_g >= child.getG()) continue;

                        child.setG(new_g);
                        child.setF(child.getG() + child.multiple_manhattan(goalState));

                        int x = i + 1;
                        child.setMovement("Row " + x + " RIGHT");

                        openSet.add(child);
                        minHeap.add(child);
                    }
                }
                //State s = minHeap.peek();
                //s.printBoard();
                //System.out.println(s.getF()+" "+openSet.size());
            }

            printAnswer(path);
            //System.out.println(count);

        }
    }

}

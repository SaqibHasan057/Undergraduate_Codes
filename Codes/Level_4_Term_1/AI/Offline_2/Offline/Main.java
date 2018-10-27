import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

/**
 * Created by Dipto on 10/11/2017.
 */
public class Main {
    static final String file = "hdtt4";
    static final int[] weights = {1,1,1};
    static final int periodsPerDay = 8;
    static final int noOfPeriods = 5*periodsPerDay;
    static int noOfTeachers=0;
    static int noOfClassSize=0;
    static int noOfRoom=0;
    static State initialState;
    static ArrayList<TeacherClassRoom> TCRList;

    static boolean steepestAscent = false;
    static boolean firstClimb = true;
    static boolean randomRestart = false;
    static boolean stochastic = false;




    public static void readInfo(String fileName) throws IOException {
        FileInputStream inputStream = new FileInputStream("data files/"+fileName);
        Scanner input = new Scanner(inputStream);

        for(int i=0;i<5;i++){
            if(i==3)for(int j=0;j<5;j++)input.next();
            else for(int j=0;j<4;j++)input.next();
            int x = input.nextInt();

            if(i==0){
                noOfTeachers = x;
            }
            else if(i==2){
                noOfClassSize = x;
            }
            else if(i==3){
                noOfRoom = x;
            }
        }

        System.out.println("Teacher: "+noOfTeachers+" Class: "+noOfClassSize+" Room: "+noOfRoom);
        inputStream.close();
    }

    static State createInitialState(String fileName) throws FileNotFoundException {
        FileInputStream inputStream = new FileInputStream("data files/"+fileName);
        Scanner input = new Scanner(inputStream);
        ArrayList<TeacherClassRoom>[] periodTable = new ArrayList[noOfPeriods];
        TCRList = new ArrayList<>();

        for(int i=0;i<noOfPeriods;i++){
            periodTable[i]= new ArrayList<>();
        }

        for(int R=0; R<noOfRoom;R++){
            for(int C=0; C<noOfRoom; C++){
                for(int T=0; T<noOfTeachers; T++){
                    int x = input.nextInt();
                    for(int n=0;n<x;n++){
                        TeacherClassRoom temp = new TeacherClassRoom(T,C,R);
                        TCRList.add(temp);
                        //periodTable[0].add(temp);
                    }
                }
            }
        }

        for(int i=0;i<TCRList.size();i++){
            periodTable[i%noOfPeriods].add(TCRList.get(i));
        }



        State ret = new State(noOfPeriods,periodTable,weights);
        return ret;
    }


    static void newInitialState(){
        initialState=null;
        ArrayList<TeacherClassRoom>[] periodTable = new ArrayList[noOfPeriods];
        for(int i=0;i<noOfPeriods;i++){
            periodTable[i]= new ArrayList<>();
        }
        Random rand = new Random();

        for(int i=0;i<TCRList.size();i++){
            int index = rand.nextInt(noOfPeriods);
            periodTable[index].add(TCRList.get(i));
        }
        initialState = new State(noOfPeriods,periodTable,weights);
        initialState.buildConflict();
    }








    public static void main(String[] args) throws IOException {
        readInfo(file+"note.txt");
        initialState = createInitialState(file+"req.txt");
        System.out.println("The total number of distributions are: "+TCRList.size());
        initialState.buildConflict();
        initialState.printConflicts();
        initialState.printTable();




        int iteration = 1;
        System.out.println("Iteration Number: "+iteration);
        while(true) {
            State newChangedState;

            if(steepestAscent)newChangedState = initialState.getMinimumSuccessor(initialState.getSumOfConflicts());
            else if(stochastic)newChangedState = initialState.getStochasticClimb(initialState.getSumOfConflicts());
            else if(firstClimb)newChangedState = initialState.firstChoiceHill();
            else newChangedState=null;

            if(newChangedState==null && steepestAscent){

                System.out.println("We have found a solution!!");
                initialState.printConflicts();
                initialState.printTable();
                break;
            }
            else if(newChangedState==null && stochastic){
                if(randomRestart) {
                    if (initialState.getSumOfConflicts() <= 0) {
                        System.out.println("We have found a solution!!");
                        initialState.printConflicts();
                        initialState.printTable();
                        break;
                    } else {
                        iteration++;
                        newInitialState();
                        System.out.println("Starting iteration number: " + iteration);
                        continue;
                    }
                }
                else{
                    initialState.printConflicts();
                    initialState.printTable();
                    break;
                }
            }
            else if(newChangedState==null && firstClimb){
                if(randomRestart) {
                    if (initialState.getSumOfConflicts() <= 0) {
                        System.out.println("We have found a solution!!");
                        initialState.printConflicts();
                        initialState.printTable();
                        break;
                    } else {
                        iteration++;
                        newInitialState();
                        System.out.println("Starting iteration number: " + iteration);
                        continue;
                    }
                }
                else{
                    initialState.printConflicts();
                    initialState.printTable();
                    break;
                }
            }


           // newChangedState.printConflicts();
            if(initialState.getSumOfConflicts()>newChangedState.getSumOfConflicts()) {
                initialState = newChangedState;
            }
            else{
                //System.out.println("Zolo");
                if(randomRestart) {
                    if (newChangedState.getSumOfConflicts() <= 0) {
                        System.out.println("We have found a solution!!");
                        newChangedState.printConflicts();
                        newChangedState.printTable();
                        break;
                    } else {
                        iteration++;
                        newInitialState();
                        System.out.println("Starting iteration number: " + iteration);
                    }
                }
                else{
                    newChangedState.printConflicts();
                    newChangedState.printTable();
                    break;
                }
            }
        }
    }
}

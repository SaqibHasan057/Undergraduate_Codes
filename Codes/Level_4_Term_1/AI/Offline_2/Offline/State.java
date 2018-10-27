import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Random;

/**
 * Created by Dipto on 10/11/2017.
 */
public class State {
    int []weights;
    int noOfConflicts=0;
    int sumOfConflicts=0;
    int numberOfPeriods;
    ArrayList<TeacherClassRoom>[] periodTable;

    public int getSumOfConflicts(){return sumOfConflicts;}

    public void printConflicts(){
        System.out.println("Number of conflicts:"+noOfConflicts+"\nSum of Conflicts "+sumOfConflicts);
    }

    public void printTable(){
        int periodsPerDay = numberOfPeriods/5;
        int day = 0;
        for(int i=0;i<numberOfPeriods;i++){
            if(i%periodsPerDay==0){
                ++day;
                System.out.println("Day "+day+":");
            }
            ArrayList<TeacherClassRoom> temp = periodTable[i];
            System.out.print("["+(i%periodsPerDay+1)+"] : ");
            for(int j=0;j<temp.size();j++){
                temp.get(j).printTeacherClassRoom();
            }
            System.out.println();
        }
    }

    public void buildConflict(){
        noOfConflicts=0;
        sumOfConflicts=0;
        for(int i=0;i<numberOfPeriods;i++){
            ArrayList<TeacherClassRoom> temp = periodTable[i];

            if(temp.size()==0)continue;

            for(int j=0;j<temp.size();j++){
                for(int k = j +1; k<temp.size();k++){
                    if(temp.get(j).getTeacher()==temp.get(k).getTeacher()){
                        noOfConflicts++;
                        sumOfConflicts+=weights[1];
                    }
                    if(temp.get(j).getRoom()==temp.get(k).getRoom()){
                        noOfConflicts++;
                        sumOfConflicts+=weights[2];
                    }
                    if(temp.get(j).getClassSize()==temp.get(k).getClassSize()){
                        noOfConflicts++;
                        sumOfConflicts+=weights[0];
                    }
                }
            }

        }
    }

    public State(int numberOfPeriods,ArrayList<TeacherClassRoom>[] periodTable,int[]weights){
        this.numberOfPeriods=numberOfPeriods;
        this.periodTable=periodTable;
        this.weights = weights;
        //buildConflict();
    }

    public ArrayList<int[]> getConflictingElement(){
        ArrayList<int[]> ret = new ArrayList<>();
        for(int i=0;i<numberOfPeriods;i++){
            ArrayList<TeacherClassRoom> temp = periodTable[i];

            if(temp.size()==0)continue;

            for(int j=0;j<temp.size();j++){
                for(int k = j +1; k<temp.size();k++){
                    if(temp.get(j).getTeacher()==temp.get(k).getTeacher() || temp.get(j).getRoom()==temp.get(k).getRoom() || temp.get(j).getClassSize()==temp.get(k).getClassSize()){
                        int[] newNode = new int[2];
                        newNode[0]=i;
                        newNode[1]=j;
                        ret.add(newNode);
                        break;
                    }

                }
            }

        }
        return ret;
    }

    public void switchElement(int index1, int index2,int index3){
        TeacherClassRoom get = periodTable[index1].get(index2);
        periodTable[index1].remove(index2);
        periodTable[index3].add(get);
    }

    public ArrayList<TeacherClassRoom>[] newTable(){
        ArrayList<TeacherClassRoom>[] copyPeriodTable = new ArrayList[numberOfPeriods];
        for(int u=0;u<numberOfPeriods;u++){copyPeriodTable[u]=new ArrayList<>();}
        for(int u=0;u<numberOfPeriods;u++){
            ArrayList<TeacherClassRoom> temp = periodTable[u];

            for(int v=0;v<temp.size();v++){
                TeacherClassRoom oldElement = temp.get(v);
                TeacherClassRoom newElement = new TeacherClassRoom(oldElement.getTeacher(),oldElement.getClassSize(),oldElement.getRoom());
                copyPeriodTable[u].add(newElement);
            }
        }
        return copyPeriodTable;
    }

    public State firstChoiceHill(){
        ArrayList<int[]> conflictElementSet = getConflictingElement();
        if(conflictElementSet.size()==0)return null;
        //System.out.println(index[0]+","+index[1]);
        ArrayList<State> newStatesArray = new ArrayList<>();





        for(int j=0;j<conflictElementSet.size();j++) {
            int[] index = conflictElementSet.get(j);
            for (int i = 0; i < numberOfPeriods; i++) {
                if (index[0] == i) continue;
                ArrayList<TeacherClassRoom>[] copyPeriodTable = newTable();
                State newState = new State(this.numberOfPeriods, copyPeriodTable, this.weights);
                newState.switchElement(index[0], index[1], i);
                newState.buildConflict();
                if(newState.getSumOfConflicts()<sumOfConflicts)return newState;
                newStatesArray.add(newState);
            }
        }

        return null;


    }

    public State getStochasticClimb(int sumOfConflicts){
        ArrayList<int[]> conflictElementSet = getConflictingElement();
        if(conflictElementSet.size()==0)return null;
        //System.out.println(index[0]+","+index[1]);
        ArrayList<State> newStatesArray = new ArrayList<>();





        for(int j=0;j<conflictElementSet.size();j++) {
            int[] index = conflictElementSet.get(j);
            for (int i = 0; i < numberOfPeriods; i++) {
                if (index[0] == i) continue;
                ArrayList<TeacherClassRoom>[] copyPeriodTable = newTable();
                State newState = new State(this.numberOfPeriods, copyPeriodTable, this.weights);
                newState.switchElement(index[0], index[1], i);
                newState.buildConflict();
                if(newState.getSumOfConflicts()<sumOfConflicts)newStatesArray.add(newState);
            }
        }



        if(newStatesArray.size()>0){
            Random rand = new Random();
            int randomIndex = rand.nextInt(newStatesArray.size());
            return newStatesArray.get(randomIndex);
        }
        else return null;
    }


    public State getMinimumSuccessor(int sumOfConflicts){
        ArrayList<int[]> conflictElementSet = getConflictingElement();
        if(conflictElementSet.size()==0)return null;
        //System.out.println(index[0]+","+index[1]);
        ArrayList<State> newStatesArray = new ArrayList<>();





        for(int j=0;j<conflictElementSet.size();j++) {
            int[] index = conflictElementSet.get(j);
            for (int i = 0; i < numberOfPeriods; i++) {
                if (index[0] == i) continue;
                ArrayList<TeacherClassRoom>[] copyPeriodTable = newTable();
                State newState = new State(this.numberOfPeriods, copyPeriodTable, this.weights);
                newState.switchElement(index[0], index[1], i);
                newState.buildConflict();
                newStatesArray.add(newState);
            }
        }

        int minimumIndex =0;
        int minima = Integer.MAX_VALUE;

        for(int i=0;i<newStatesArray.size();i++){
            //System.out.print(newStatesArray.get(i).getSumOfConflicts()+ " ");
            if(newStatesArray.get(i).getSumOfConflicts()<minima){
                minima=newStatesArray.get(i).getSumOfConflicts();
                minimumIndex = i;
            }
        }

        return newStatesArray.get(minimumIndex);
    }



// stochastic: select random from the best(already written)
    // first choice: select random conflict element, do a shift and then see if it is better






}

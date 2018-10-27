/**
 * Created by Dipto on 10/11/2017.
 */
public class TeacherClassRoom {
    private int Teacher;
    private int ClassSize;
    private int Room;

    public TeacherClassRoom(int Teacher,int ClassSize,int Room){
        this.Teacher=Teacher;
        this.ClassSize=ClassSize;
        this.Room=Room;
    }

    public void setTeacher(int Teacher){
        this.Teacher=Teacher;
    }

    public void setClassSize(int ClassSize){
        this.ClassSize=ClassSize;
    }

    public void setRoom(int Room){
        this.Room=Room;
    }
    
    public int getTeacher(){return Teacher;}
    public int getClassSize(){return ClassSize;}
    public int getRoom(){return Room;}

    public void printTeacherClassRoom(){
        System.out.print("(T"+Teacher+",C"+ClassSize+",R"+Room+") ");
    }
}

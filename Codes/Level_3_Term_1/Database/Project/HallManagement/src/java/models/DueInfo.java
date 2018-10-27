/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package models;

/**
 *
 * @author Dipto
 */
public class DueInfo {
    private String student_id;
    private String student_name;
    private int timeDelay;
    private int amountDue;
    
    public DueInfo(String student_id,String student_name,int timeDelay,int amountDue){
        this.student_id=student_id;
        this.student_name=student_name;
        this.timeDelay=timeDelay;
        this.amountDue=amountDue;
    }
    
    public void setStudentID(String student_id){this.student_id=student_id;}
    public void setStudentName(String student_name){this.student_name=student_name;}
    public void setTimeDelay(int timeDelay){this.timeDelay=timeDelay;}
    public void setAmountDue(int amountDue){this.amountDue=amountDue;}
    
    public String getStudentID(){return student_id;}
    public String getStudentName(){return student_name;}
    public int getTimeDelay(){return timeDelay;}
    public int getAmountDue(){return  amountDue;}
}

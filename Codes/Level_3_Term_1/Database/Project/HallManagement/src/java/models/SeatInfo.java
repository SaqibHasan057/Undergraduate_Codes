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
public class SeatInfo {
    private String student_id;
    private String student_name;
    private String startDate;
    private String endDate;
    
    public SeatInfo(String student_id,String student_name,String startDate,String endDate){
        this.student_id=student_id;
        this.student_name=student_name;
        this.startDate=startDate;
        this.endDate=endDate;
    }
    
    public void setStudentID(String student_id){this.student_id=student_id;}
    public void setStudentName(String student_name){this.student_name=student_name;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setEndDate(String endDate){this.endDate=endDate;}
    
    public String getStudentID(){return student_id;}
    public String getStudentName(){return student_name;}
    public String getStartDate(){return startDate;}
    public String getEndDate(){return  endDate;}
}

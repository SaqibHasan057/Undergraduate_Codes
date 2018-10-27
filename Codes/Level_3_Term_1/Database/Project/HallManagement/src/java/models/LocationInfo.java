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
public class LocationInfo {
    private String studentName;
    private String studentID;
    private String startDate;
    private String wing;
    private int floor;
    
    public LocationInfo(String studentName,String studentID,String startDate,String wing,int floor){
        this.studentName=studentName;
        this.studentID=studentID;
        this.startDate=startDate;
        this.wing=wing;
        this.floor=floor;
    }
    
    public void setStudentName(String studentName){this.studentName=studentName;}
    public void setStudentID(String studentID){this.studentID=studentID;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setWing(String wing){this.wing=wing;}
    public void setFloor(int floor){this.floor=floor;}
    
    public String getStudentName(){return studentName;}
    public String getStudentID(){return studentID;}
    public String getStartDate(){return startDate;}
    public String getWing(){return wing;}
    public int getFloor(){return floor;}
}

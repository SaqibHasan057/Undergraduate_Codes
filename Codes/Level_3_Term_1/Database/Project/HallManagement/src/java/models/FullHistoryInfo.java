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
public class FullHistoryInfo {
    private String allocationID;
    private String roomID;
    private String seatID;
    private String startDate;
    private String endDate;
    private String wing;
    private int floor;
    
    public FullHistoryInfo(String allocationID,String startDate,String endDate,String seatID,String roomID,String wing,int floor){
        this.allocationID=allocationID;
        this.roomID=roomID;
        this.seatID=seatID;
        this.startDate=startDate;
        this.endDate=endDate;
        this.wing=wing;
        this.floor=floor;
    }
    
    public void setAllocationID(String allocationID){this.allocationID=allocationID;}
    public void setRoomID(String roomID){this.roomID=roomID;}
    public void setSeatID(String seatID){this.seatID=seatID;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setEndDate(String endDate){this.endDate=endDate;}
    public void setWing(String wing){this.wing=wing;}
    public void setFloor(int floor){this.floor=floor;}
    
    public String getAllocationID(){return allocationID;}
    public String getRoomID(){return roomID;}
    public String getSeatID(){return seatID;}
    public String getStartDate(){return startDate;}
    public String getEndDate(){return endDate;}
    public String getWing(){return wing;}
    public int getFloor(){return floor;}
    
    
    
    
    

    
    

}

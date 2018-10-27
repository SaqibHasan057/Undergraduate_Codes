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
public class HistoryInfo {

    private String allocationID;
    private String roomID;
    private String seatID;
    private String startDate;
    private String endDate;
    
    public HistoryInfo(String allocationID,String roomID,String seatID,String startDate,String endDate){
        this.allocationID=allocationID;
        this.roomID=roomID;
        this.seatID=seatID;
        this.startDate=startDate;
        this.endDate=endDate;
    }
    
    public void setAllocationID(String allocationID){this.allocationID=allocationID;}
    public void setRoomID(String roomID){this.roomID=roomID;}
    public void setSeatID(String seatID){this.seatID=seatID;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setEndDate(String endDate){this.endDate=endDate;}
    
    public String getAllocationID(){return allocationID;}
    public String getRoomID(){return roomID;}
    public String getSeatID(){return seatID;}
    public String getStartDate(){return startDate;}
    public String getEndDate(){return endDate;}
}

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
public class HallfeeHistoryInfo {
    
    
    private String feeID;
    private String seatID;
    private String roomID;
    private String payDate;
    private String center;
    private String method;
    private int amount;
    private String startDate;
    private String deadline;
    
    public HallfeeHistoryInfo(String feeID,String seatID,String roomID,String payDate,String center,String method,int amount,String startDate,String deadline){
        this.feeID=feeID;
        this.seatID=seatID;
        this.roomID=roomID;
        this.payDate=payDate;
        this.center=center;
        this.method=method;
        this.amount=amount;
        this.startDate=startDate;
        this.deadline=deadline;
    }
    
    public void setFeeID(String feeID){this.feeID=feeID;}
    public void setSeatID(String seatID){this.seatID=seatID;}
    public void setRoomID(String roomID){this.roomID=roomID;}
    public void setPayDate(String payDate){this.payDate=payDate;}
    public void setCenter(String center){this.center=center;}
    public void setMethod(String method){this.method=method;}
    public void setAmount(int amount){this.amount=amount;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setDeadline(String deadline){this.deadline=deadline;}
    
    public String getFeeID(){return feeID;}
    public String getSeatID(){return seatID;}
    public String getRoomID(){return roomID;}
    public String getPayDate(){return payDate;}
    public String getCenter(){return center;}
    public String getMethod(){return method;}
    public int getAmount(){return amount;}
    public String getStartDate(){return startDate;}
    public String getDeadline(){return deadline;}
    
    
    
}

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
public class SeatView {
    public String seatID;
    public String roomID;
    public int floor;
    public String wing;
    
    public SeatView(String seatID,String roomID,int floor,String wing){
        this.seatID=seatID;
        this.roomID=roomID;
        this.floor=floor;
        this.wing=wing;
    }
    
    public void setSeatID(String seatID){this.seatID=seatID;}
    public void setRoomID(String roomID){this.roomID=roomID;}
    public void setFloor(int floor){this.floor=floor;}
    public void setWing(String wing){this.wing=wing;}
    
    public String getSeatID(){return seatID;}
    public String getRoomID(){return roomID;}
    public int getFloor(){return floor;}
    public String getWing(){return wing;}
    
    
}

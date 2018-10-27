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
public class HallPaymentInfo {
    private String receiptID;
    private int delay;
    private String studentID;
    private String feeID;
    private int due;
    
    public HallPaymentInfo(String receiptID,int delay,String studentID,String feeID,int due){
        this.receiptID=receiptID;
        this.delay=delay;
        this.studentID=studentID;
        this.feeID=feeID;
        this.due=due;
    }
    
    public void setReceiptID(String receipt){this.receiptID=receiptID;}
    public void setDelay(int delay){this.delay=delay;}
    public void setStudentID(String studentID){this.studentID=studentID;}
    public void setFeeID(String feeID){this.feeID=feeID;}
    public void setDue(int due){this.due=due;}
    
    public String getReceiptID(){return receiptID;}
    public int getDelay(){return delay;}
    public String getStudentID(){return studentID;}
    public String getFeeID(){return feeID;}
    public int getDue(){return due;}
    
}

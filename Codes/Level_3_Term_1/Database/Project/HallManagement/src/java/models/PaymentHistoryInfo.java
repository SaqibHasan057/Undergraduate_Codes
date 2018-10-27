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
public class PaymentHistoryInfo {
    private String receiptID;
    private int delay;
    private String studentID;
    private String feeID;
    private int due;
    private String payDate;
    private String center;
    private String method;
    private String startDate;
    private String deadline;
    
    public PaymentHistoryInfo(String receiptID,int delay,String studentID,String feeID,int due,String payDate,String center,String method,String startDate,String deadline){
        this.receiptID=receiptID;
        this.delay=delay;
        this.studentID=studentID;
        this.feeID=feeID;
        this.due=due;
        this.payDate=payDate;
        this.center=center;
        this.method=method;
        this.startDate=startDate;
        this.deadline=deadline;
    }

   
    
    public void setReceiptID(String receiptID){this.receiptID=receiptID;}
    public void setDelay(int delay){this.delay=delay;}
    public void setStudentID(String studentID){this.studentID=studentID;}
    public void setFeeID(String feeID){this.feeID=feeID;}
    public void setDue(int due){this.due=due;}
    public void setPayDate(String payDate){this.payDate=payDate;}
    public void setCenter(String center){this.center=center;}
    public void setMethod(String method){this.method=method;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setDeadline(String deadline){this.deadline=deadline;}
    
    public String getReceiptID(){return receiptID;}
    public int getDelay(){return delay;}
    public String getStudentID(){return studentID;}
    public String getFeeID(){return feeID;}
    public int getDue(){return due;}
    public String getPayDate(){return payDate;}
    public String getCenter(){return center;}
    public String getMethod(){return method;}
    public String getStartDate(){return startDate;}
    public String getDeadline(){return deadline;}
    
    
}

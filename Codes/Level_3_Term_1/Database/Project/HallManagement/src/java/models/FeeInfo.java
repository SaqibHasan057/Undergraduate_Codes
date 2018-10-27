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
public class FeeInfo {
    
    private String fee_id;
    private String type;
    private int amount;
    private String deadline;
    private String startDate;
    private int due;
    private int year;
    private int month;
    
    public FeeInfo(String fee_id,String type,int amount,String deadline,String startDate,int due,int year,int month){
        this.fee_id=fee_id;
        this.type=type;
        this.amount=amount;
        this.deadline=deadline;
        this.startDate=startDate;
        this.due=due;
        this.year=year;
        this.month=month;
    }
    
    public void setFeeID(String fee_id){this.fee_id=fee_id;}
    public void setType(String type){this.type=type;}
    public void setAmount(int amount){this.amount=amount;}
    public void setDeadline(String deadline){this.deadline=deadline;}
    public void setStartDate(String startDate){this.startDate=startDate;}
    public void setDue(int due){this.due=due;}
    public void setYear(int year){this.year=year;}
    public void setMonth(int month){this.month=month;}
    
    public String getFeeID(){return fee_id;}
    public String getType(){return type;}
    public int getAmount(){return amount;}
    public String getDeadline(){return deadline;}
    public String getStartDate(){return startDate;}
    public int getDue(){return due;}
    public int getYear(){return year;}
    public int getMonth(){return month;}
    
    
}

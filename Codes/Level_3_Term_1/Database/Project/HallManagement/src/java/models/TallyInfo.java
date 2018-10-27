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
public class TallyInfo {
   
    
    private String typeName;
    private int count;
    private int sumCost;
    private int sumRepairCost;
    
    public TallyInfo(String typeName,int count,int sumCost,int sumRepairCost){
        this.typeName=typeName;
        this.count=count;
        this.sumCost=sumCost;
        this.sumRepairCost=sumRepairCost;
    }
    
    public void setTypeName(String typeName){this.typeName=typeName;}
    public void setCount(int count){this.count=count;}
    public void setSumCost(int sumCost){this.sumCost=sumCost;}
    public void setSumRepairCost(int sumRepairCost){this.sumRepairCost=sumRepairCost;}
    
    public String getTypeName(){return typeName;}
    public int getCount(){return count;}
    public int getSumCost(){return sumCost;}
    public int getSumRepairCost(){return sumRepairCost;}

}

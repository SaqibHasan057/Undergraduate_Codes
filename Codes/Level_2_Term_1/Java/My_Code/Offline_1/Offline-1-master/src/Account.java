/**
 * Created by Saqib Hasan on 9/17/2015.
 */
public class Account {
    private Customer customer;
    private int accountNumber;
    private double balance;
    private String branch;

    public Account(Customer customer,int accountNumber,double balance){
        this.customer=customer;
        this.accountNumber=accountNumber;
        this.balance=balance;
    }

    public Account(Customer customer,int accountNumber,String branch){
        this.customer=customer;
        this.accountNumber=accountNumber;
        this.branch=branch;
        balance=0;
    }

    public void setBranch(String branch){
        this.branch=branch;
    }

    public void setBalance(double balance){
        this.balance=balance;
    }

    public void credit(double amount){
        balance+=amount;
    }

    public void debit(double amount){
        if(balance<amount) System.out.println("Amount withdrawn exceeds the current balance.\n");
        else balance-=amount;
    }

    public String getCustomerName(){
        return customer.getName();
    }

    public int getAccountNumber(){
        return accountNumber;
    }

    public double getBalance(){
        return balance;
    }

    public String getBranch(){
        return branch;
    }

    public Customer getCustomer(){
        return customer;
    }

    public void print(){
        System.out.println("Customer: "+customer.getName()+" Branch: "+branch+" A/C no: "+accountNumber+" Balance: "+balance+"\n");
    }
}

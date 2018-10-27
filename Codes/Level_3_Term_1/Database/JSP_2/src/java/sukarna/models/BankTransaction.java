
package sukarna.models;

public class BankTransaction 
{
    String accountNo;
    double amount;
    String datetime;

    public BankTransaction(String accountNo, double amount, String datetime) {
        this.accountNo = accountNo;
        this.amount = amount;
        this.datetime = datetime;
    }

    public String getAccountNo() {
        return accountNo;
    }

    public void setAccountNo(String accountNo) {
        this.accountNo = accountNo;
    }

    public double getAmount() {
        return amount;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }

    public String getDatetime() {
        return datetime;
    }

    public void setDatetime(String datetime) {
        this.datetime = datetime;
    }
    
    
}

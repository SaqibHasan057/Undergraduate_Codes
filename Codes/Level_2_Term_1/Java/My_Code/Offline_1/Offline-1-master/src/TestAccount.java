/**
 * Created by Saqib Hasan on 9/17/2015.
 */
public class TestAccount {
    public static void main(String[] args) {
        Customer john=new Customer("John Doe","john@doe.com",'m');
        System.out.println(john.getName()+" ("+john.getGender()+") at "+john.getEmail()+"\n");
        Customer mary=new Customer("Mary Jane");
        mary.setGender('f');
        mary.setEmail("mary@jane.com");
        mary.print();

        Account a1=new Account(john,8111,99.99);
        a1.setBranch("b1");
        System.out.println("Customer: " + a1.getCustomerName() + " Branch: " + a1.getBranch() + " A/C no: " + a1.getAccountNumber() + " Balance: " + a1.getBalance() + "\n");
        a1.credit(20);
        a1.debit(10);
        System.out.println("Customer: "+a1.getCustomerName()+" Branch: "+a1.getBranch()+" A/C no: "+a1.getAccountNumber()+" Balance: "+a1.getBalance()+"\n");

        Account a2=new Account(mary,8222,"main");
        a2.print();
        a2.setBalance(100);
        a2.credit(20);
        a2.debit(200);
        a2.print();

        a1.getCustomer().print();
        a2.getCustomer().print();
    }
}

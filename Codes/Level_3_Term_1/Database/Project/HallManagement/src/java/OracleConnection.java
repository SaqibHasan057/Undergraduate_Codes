/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Dipto
 */
import models.StudentInfo;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import models.FeeInfo;
import models.DueInfo;
import models.FeeViewInfo;
import models.FullHistoryInfo;
import models.HallPaymentInfo;
import models.HallfeeHistoryInfo;
import models.HistoryInfo;
import models.LocationInfo;
import models.PaymentHistoryInfo;
import models.SeatInfo;
import models.SeatView;
import models.TallyInfo;



public class OracleConnection {
    private String URL = "jdbc:oracle:thin:@localhost:1521/orcl";
    private String username = "skb";
    private String password = "skb";

    private Connection conn = null;
    public OracleConnection()
    {
        try
        {
            Class.forName("oracle.jdbc.OracleDriver");
            conn = DriverManager.getConnection(URL, username, password);
            if(conn!=null) System.out.println("Connection successfully established.");
            else System.out.println("Could not establish connection");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public Connection getConnection(){return conn;}
    
    public boolean existUser(String username,String password)
    {
       try
        {
            String query = "select * from login where username = ? and password = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);
            stmt.setString(2, password);
            ResultSet rs = stmt.executeQuery();
            if(rs.next())
            {
               return true;
            }
            return false;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return false;
        }   
        
    }
    
     public void createUser(String username,String password)
    {
       try
        {
            String query = "insert into login values(?,?)";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        
    }
    
    public ResultSet Query(String selectStatement) throws SQLException{
        PreparedStatement stmt;
        stmt = conn.prepareStatement(selectStatement);
        ResultSet rs = stmt.executeQuery();
        return rs;   
    }
    
    public ResultSet Query(PreparedStatement stmt) throws SQLException{
        ResultSet rs = stmt.executeQuery();
        return rs;   
    }
    
    public void RunQuery(PreparedStatement stmt) throws SQLException{
        ResultSet rs = stmt.executeQuery();
    }
    
    public ArrayList<StudentInfo> getStudentTable(){
        ArrayList<StudentInfo> list = new ArrayList<StudentInfo>();
        
        String selectStatement = "select * from student";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String studentid=rs.getString("student_id");
                String firstName=rs.getString("first_name");
                String lastName=rs.getString("last_name");
                String fatherFname=rs.getString("father_fname");
                String fatherLname=rs.getString("father_lname");
                String motherFname=rs.getString("mother_fname");
                String motherLname=rs.getString("mother_lname");
                String street=rs.getString("street");
                String city=rs.getString("city");
                String state=rs.getString("state");
                String pin=rs.getString("pin");
                String guardian=rs.getString("guardian_contact_no");
                String dob=rs.getString("dob");
                String phoneNo=getPhoneNo(studentid);
                String email=getEmail(studentid);
                
                StudentInfo studentInfo = new StudentInfo(studentid,firstName,lastName,fatherFname,fatherLname,motherFname,motherLname,street,city,state,pin,guardian,dob,phoneNo,email);
                list.add(studentInfo);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
     public ArrayList<StudentInfo> getStudentTable(String student_id){
        ArrayList<StudentInfo> list = new ArrayList<StudentInfo>();
        
        String selectStatement = "select * from student where student_id=?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,student_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String studentid=rs.getString("student_id");
                String firstName=rs.getString("first_name");
                String lastName=rs.getString("last_name");
                String fatherFname=rs.getString("father_fname");
                String fatherLname=rs.getString("father_lname");
                String motherFname=rs.getString("mother_fname");
                String motherLname=rs.getString("mother_lname");
                String street=rs.getString("street");
                String city=rs.getString("city");
                String state=rs.getString("state");
                String pin=rs.getString("pin");
                String guardian=rs.getString("guardian_contact_no");
                String dob=rs.getString("dob");
                String phoneNo=getPhoneNo(studentid);
                String email=getEmail(studentid);
                
                StudentInfo studentInfo = new StudentInfo(studentid,firstName,lastName,fatherFname,fatherLname,motherFname,motherLname,street,city,state,pin,guardian,dob,phoneNo,email);
                list.add(studentInfo);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    
     
    public String getPhoneNo(String studentID){
        String number="";
        try
        {
            String query = "select * from phone where student_id=?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, studentID);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
               number=rs.getString("phone_no");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        return number;
    }
    
    public String getCurrentStudentID(){
        String stringID="";
        try
        {
            String query = "select student_id_seq.currval from dual";
            PreparedStatement stmt = conn.prepareStatement(query);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
               stringID=rs.getString("currval");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        return stringID;
    }
    
    public void setPhoneNo(String studentID,String phoneNo){
        try
        {
            String query = "insert into phone values(?,?)";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, studentID);
            stmt.setString(2, phoneNo);
            ResultSet rs = stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    public String getEmail(String studentID){
        String number="";
        try
        {
            String query = "select * from email where student_id=?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, studentID);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
               number=rs.getString("email");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        return number;
    }
    
    
    
    public void setEmail(String studentID,String email){
        try
        {
            String query = "insert into email values(?,?)";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, studentID);
            stmt.setString(2, email);
            ResultSet rs = stmt.executeQuery();
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    
    public void newPhoneNo(String studentID,String phoneNo){
        try
        {
            String query = "update phone set phone_no=? where student_id=?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, phoneNo);
            stmt.setString(1, studentID);
            ResultSet rs = stmt.executeQuery();
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    public void newEmail(String studentID,String email){
        try
        {
            String query = "update phone set email=? where student_id=?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, email);
            stmt.setString(2, studentID);
            ResultSet rs = stmt.executeQuery();
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    
    
    
    public ArrayList<FeeInfo> getFeeTable(String typeName){
        ArrayList<FeeInfo> list = new ArrayList<FeeInfo>();
        
        String selectStatement = "select * from fee where type = ?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,typeName);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String feeID=rs.getString("fee_id");
                String type=rs.getString("type");
                int amount=rs.getInt("amount");
                String deadline=rs.getString("deadline");
                String startDate=rs.getString("startDate");
                int due=rs.getInt("due");
                int year=rs.getInt("year");
                int month=rs.getInt("month");
                
                
                FeeInfo feeInfo = new FeeInfo(feeID,type,amount,deadline,startDate,due,year,month);
                list.add(feeInfo);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public int getSumOfFee(String typeName){
        int amount = 0;
        try
        {
            String query = "select sum(amount) sumamount from fee where type=?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, typeName);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())amount=rs.getInt("sumamount");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        return amount;
    }
    
    public int getTotalSum(){
        int amount = 0;
        try
        {
            String query = "select sum(amount) sumamount from fee";
            PreparedStatement stmt = conn.prepareStatement(query);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())amount=rs.getInt("sumamount");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
        return amount;
    }
    
    public ArrayList<DueInfo> getDueTable(){
        ArrayList<DueInfo> list = new ArrayList<DueInfo>();
        
        String selectStatement = "select * from student join hallpayment on (student.student_id=hallpayment.student_id)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String studentID=rs.getString("student_id");
                String studentName=rs.getString("first_name")+" "+rs.getString("last_name");
                int delay = rs.getInt("delay");
                int amount = rs.getInt("due");
                DueInfo due = new DueInfo(studentID, studentName, delay, amount);
                list.add(due);
              
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<SeatInfo> getSeatTable(String seat_id){
        ArrayList<SeatInfo> list = new ArrayList<SeatInfo>();
        
        String selectStatement = "select * from allocation a join student s on (a.student_id = s.student_id) where seat_id = ? ";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, seat_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String studentID=rs.getString("student_id");
                String studentName=rs.getString("first_name")+" "+rs.getString("last_name");
                String startDate = rs.getString("allocationdate");
                String endDate = rs.getString("enddate");
                SeatInfo due = new SeatInfo(studentID, studentName, startDate, endDate);
                list.add(due);
              
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<LocationInfo> getLocationTable(String seat_id){
        ArrayList<LocationInfo> list = new ArrayList<LocationInfo>();
        
        String selectStatement = "select *" +
"from allocation a join student s\n" +
"on (a.student_id = s.student_id)\n" +
"join hallroom h\n" +
"on (a.room_id = h.room_id)\n" +
"where a.seat_id =? and a.enddate is null";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, seat_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String studentID=rs.getString("student_id");
                String studentName=rs.getString("first_name")+" "+rs.getString("last_name");
                String startDate = rs.getString("allocationdate");
                String wing = rs.getString("wing");
                int floor = rs.getInt("floor");
                LocationInfo due = new LocationInfo(studentID, studentName, startDate, wing, floor);
                list.add(due);
                System.out.println(floor);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<HistoryInfo> getHistoryTable(String student_id){
        ArrayList<HistoryInfo> list = new ArrayList<HistoryInfo>();
        
        String selectStatement = "select *\n" +
"from allocation a join hallroom h\n" +
"on (a.room_id = h.room_id)\n" +
"where a.student_id = ?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, student_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String allocationID=rs.getString("allocation_id");
                String roomID=rs.getString("room_id");
                String seatID = rs.getString("seat_id");
                String allocationDate = rs.getString("allocationdate");
                String endDate = rs.getString("enddate");
                HistoryInfo add = new HistoryInfo(allocationID,roomID,seatID,allocationDate,endDate);
                list.add(add);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<TallyInfo> getEquipmentTallyTable(){
        ArrayList<TallyInfo> list = new ArrayList<TallyInfo>();
        
        String selectStatement = "select t.name , count(e.type_id) countType, sum(e.cost) sumCost, sum(e.repairCost) sumRepairCost\n" +
"from equipment e join type t\n" +
"on (e.type_id = t.type_id)\n" +
"group by t.type_id , t.name";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String typeName=rs.getString("name");
                int count=rs.getInt("countType");
                int sumCost = rs.getInt("sumCost");
                int sumRepairCost = rs.getInt("sumRepairCost");
                TallyInfo add = new TallyInfo(typeName, count, sumCost, sumRepairCost);
                list.add(add);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<Integer> getTotalEquipmentCost(){
        ArrayList<Integer> list = new ArrayList<>();
        
        String selectStatement = "select sum(cost) sumCost,sum(repaircost) sumRepairCost from equipment";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                int sumCost = rs.getInt("sumCost");
                int sumRepairCost = rs.getInt("sumRepairCost");
                list.add(sumCost);
                list.add(sumRepairCost);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
     public ArrayList<FullHistoryInfo> getAllocationHistoryTable(String student_id){
        ArrayList<FullHistoryInfo> list = new ArrayList<FullHistoryInfo>();
        
        String selectStatement = "select *\n" +
"from allocation a join hallroom h on (a.room_id=h.room_id)\n" +
"where a.student_id= ?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,student_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String allocationID=rs.getString("allocation_id");
                String startDate=rs.getString("allocationdate");
                String endDate=rs.getString("enddate");
                String seatID=rs.getString("seat_id");
                String roomID=rs.getString("room_id");
                int floor=rs.getInt("floor");
                String wing=rs.getString("wing");
                
                
                FullHistoryInfo newTemp = new FullHistoryInfo(allocationID,startDate,endDate,seatID,roomID,wing,floor);
                list.add(newTemp);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
     
     public String getSeatID(String student_id){
         String selectStatement = "select seat_id from ALLOCATION where student_id=? and enddate is null";
         String output="";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,student_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                output=rs.getString("seat_id");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return output;

    }
    
     
    public ArrayList<HallfeeHistoryInfo> getHallfeeHistoryTable(String student_id){
        ArrayList<HallfeeHistoryInfo> list = new ArrayList<HallfeeHistoryInfo>();
        String selectStatement = "select *\n" +
"from hallfee h  join fee f\n" +
"on (h.fee_id = f.fee_id) where seat_id=?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,getSeatID(student_id));
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String feeID=rs.getString("fee_id");
                String seatID=rs.getString("seat_id");
                String roomID=rs.getString("room_id");
                String payDate=rs.getString("paydate");
                String center=rs.getString("center");
                String method=rs.getString("method");
                int amount=rs.getInt("amount");
                String startDate=rs.getString("startdate");
                String endDate=rs.getString("deadline");
               
                HallfeeHistoryInfo newTemp = new HallfeeHistoryInfo(feeID, seatID, roomID, payDate, center, method, amount, startDate, endDate);
                list.add(newTemp);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
      
       public ArrayList<PaymentHistoryInfo> getPaymentHistoryTable(String student_id){
        ArrayList<PaymentHistoryInfo> list = new ArrayList<PaymentHistoryInfo>();

        String selectStatement = "select h.receipt_id,delay,h.student_id,h.fee_id,h.due due1,dateofpay,center,method,startdate,deadline\n" +
"from hallpayment h join Pay p\n" +
"on (h.receipt_id = p.receipt_id)\n" +
"join Fee f\n" +
"on (h.fee_id = f.fee_id) where h.student_id=?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,student_id);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String receiptID=rs.getString("receipt_id");
                int delay=rs.getInt("delay");
                String studentID=rs.getString("student_id");
                String feeID=rs.getString("fee_id");
                int due=rs.getInt("due1");
                String payDate=rs.getString("dateofpay");
                String center=rs.getString("center");
                String method=rs.getString("method");
                String startDate=rs.getString("startdate");
                String deadline=rs.getString("deadline");
                
                PaymentHistoryInfo newTemp = new PaymentHistoryInfo(receiptID,delay,studentID,feeID,due,payDate,center,method,startDate,deadline);
                list.add(newTemp);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
       
    public void enterIntoLogFile(String username){
        try
        {
            String query = "DECLARE\n" +
"BEGIN\n" +
"ENTER_INTO_LOGFILE(?);\n" +
"\n" +
"END ;";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1,username);
            ResultSet rs = stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    public void enterIntoUpdateLogFile(String username,String tablename){
        try
        {
            String query = "DECLARE\n" +
"BEGIN\n" +
"ENTER_INTO_UPDATELOGFILE(?,?);\n" +
"\n" +
"END ;";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1,username);
            stmt.setString(2,tablename);
            ResultSet rs = stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }   
    }
    
    public ArrayList<FeeViewInfo> getFeeViewTable(String student_id){
        ArrayList<FeeViewInfo> list = new ArrayList<FeeViewInfo>();

        String selectStatement = "select * from fee";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String feeID=rs.getString("fee_id");
                String type=rs.getString("type");
                int amount=rs.getInt("amount");
                String deadline=rs.getString("deadline");
                String startdate=rs.getString("startdate");
                int due=rs.getInt("due");
                int year=rs.getInt("year");
                int month=rs.getInt("month");
                
                FeeViewInfo newTemp = new FeeViewInfo(feeID, type, amount, deadline, startdate, due, year, month);
                list.add(newTemp);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<SeatView> getUnoccupiedSeatViewTable(){
        ArrayList<SeatView> list = new ArrayList<SeatView>();

        String selectStatement = "select *\n" +
"from seat s join hallroom h\n" +
"on (s.HALLROOM_ID=h.ROOM_ID)\n" +
"where OCCUPIED=0";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String seatID=rs.getString("seat_id");
                String roomID=rs.getString("room_id");
                int floor=rs.getInt("floor");
                String wing=rs.getString("wing");
                
                SeatView add = new SeatView(seatID, roomID, floor, wing);
                list.add(add);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public ArrayList<SeatView> getOccupiedSeatViewTable(){
        ArrayList<SeatView> list = new ArrayList<SeatView>();

        String selectStatement = "select *\n" +
"from seat s join hallroom h\n" +
"on (s.HALLROOM_ID=h.ROOM_ID)\n" +
"where OCCUPIED=1;";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String seatID=rs.getString("seat_id");
                String roomID=rs.getString("room_id");
                int floor=rs.getInt("floor");
                String wing=rs.getString("wing");
                
                SeatView add = new SeatView(seatID, roomID, floor, wing);
                list.add(add);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return list;

    }
    
    public void addFee(String feeID,String type,int amount,String deadline,String startdate,int due,int year,int month){
        String selectStatement = "insert into fee values(?,?,?,?,?,?,?,?)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, feeID);
            stmt.setString(2, type);
            stmt.setInt(3, amount);
            stmt.setString(4, deadline);
            stmt.setString(5, startdate);
            stmt.setInt(6, due);
            stmt.setInt(7, year);
            stmt.setInt(8, month);
            ResultSet rs = stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public void addEquipment(String equipmentID,int cost,int repait,int repairCost,String buyDate,String roomID,String typeID){
        String selectStatement = "insert into fee values(?,?,?,?,?,?,?)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, equipmentID);
            stmt.setInt(2, cost);
            stmt.setInt(3, repait);
            stmt.setInt(4, repairCost);
            stmt.setString(5, buyDate);
            stmt.setString(6, roomID);
            stmt.setString(7, typeID);
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public void addPayment(String receiptID,int delay,String studentID,String feeID,int due){
        String selectStatement = "insert into fee values(?,?,?,?,?)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, receiptID);
            stmt.setInt(2, delay);
            stmt.setString(3, studentID);
            stmt.setString(4, feeID);
            stmt.setInt(5, due);
            ResultSet rs = stmt.executeQuery();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public boolean addAllocation(String studentID,String seatID){
        boolean x = validStudentID(studentID);
        boolean y = validSeatID(seatID);
        boolean z = isOccupied(seatID);
        if(x==false || y==false || z==false){System.out.println("NO RUN");return false;}
        String selectStatement = "INSERT INTO ALLOCATION(ALLOCATION_ID,ROOM_ID,ALLOCATIONDATE,STUDENT_ID,SEAT_ID) VALUES (ALLOCATION_ID_SEQ.NEXTVAL,?,SYSDATE,?,?)\n" +
"\n" +
"";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,findRoomID(seatID) );
            stmt.setString(2, studentID);
            stmt.setString(3, seatID);
            ResultSet rs = stmt.executeQuery();
            System.out.println(seatID+studentID);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
    
    public boolean endAllocation(String seatID){
        boolean y = validSeatID(seatID);
        if(y==false){System.out.println("NO RUN");return false;}
        String selectStatement = "update allocation set enddate=SYSDATE where seat_id=? and enddate is null";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,seatID);
            ResultSet rs = stmt.executeQuery();
            System.out.println(seatID);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
    
    public boolean validStudentID(String studentID){
        String selectStatement = "SELECT VALID_STUDENT_ID(?) A FROM STUDENT";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,studentID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return true;
                else return false;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
    public boolean validSeatID(String seatID){
        String selectStatement = "SELECT VALID_SEAT_ID(?) A FROM SEAT";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,seatID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return true;
                else return false;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
    public boolean validFeeID(String feeID){
        String selectStatement = "SELECT IS_FEE_ID(?) A FROM FEE";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,feeID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return true;
                else return false;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
    public boolean validRoomID(String roomID){
        String selectStatement = "SELECT IS_VALID_ROOM(?) A FROM ROOM";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,roomID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return true;
                else return false;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
    public boolean isOccupied(String seatID){
        String selectStatement = "SELECT IS_OCCUPIED(?) A FROM SEAT";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,seatID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return false;
                else return true;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
    public String findRoomID(String seatID){
        String selectStatement = "select HALLROOM_ID from SEAT where SEAT_ID=?";
        String output="";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,seatID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                output=rs.getString("HALLROOM_ID");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return output;
    }
    
    public String findTypeID(String name){
        String selectStatement = "select TYPE_ID from TYPE where NAME=?";
        String output="";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,name);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                output=rs.getString("TYPE_ID");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return output;
    }
    
     public boolean validEquipmentID(String equipmentID){
        String selectStatement = "SELECT IS_VALID_EQUIPMENT(?) A FROM EQUIPMENT";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,equipmentID);
            ResultSet rs = stmt.executeQuery();
            
            while(rs.next())
            {
                String output=rs.getString("A");
                
                if(output.equals("SUCCESS"))return true;
                else return false;
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }
    
     
    
    public boolean addHallPayment(int delay,String studentID,String feeID,String center,String method){
        boolean x = validStudentID(studentID);
        boolean y = validFeeID(feeID);
        if(x==false || y==false){System.out.println("NO RUN");return false;}
        String selectStatement = "DECLARE\n" +
"BEGIN\n" +
"INSERT_INTO_HALL_PAY(?,?,?,?,?); " +
"\n" +
"END;";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1,studentID);
            stmt.setString(2,feeID);
            //stmt.setInt(3,due);
            stmt.setInt(3,delay);
            stmt.setString(4,center);
            stmt.setString(5,method);
            ResultSet rs = stmt.executeQuery();
            System.out.println(feeID+studentID);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
    
    public boolean addHallFee(String feeID,String seatID,String center,String method){
        boolean x = validFeeID(feeID);
        boolean y = validSeatID(seatID);
        if(x==false || y==false){System.out.println("NO RUN");return false;}
        String selectStatement = "insert into hallfee values(HALLFEE_ID_SEQ.NEXTVAL,?,?,?,SYSDATE,?,?)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setString(1, feeID);
            stmt.setString(2, seatID);
            stmt.setString(3,findRoomID(seatID) );
            stmt.setString(4, center);
            stmt.setString(5, method);
            ResultSet rs = stmt.executeQuery();
            System.out.println(seatID+feeID);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
    
    public boolean addNewEquipment(int cost,String roomID,String name ){
        boolean x = validRoomID(roomID);
        if(x==false){System.out.println("NO RUN");return false;}
        String selectStatement = "INSERT INTO EQUIPMENT VALUES(EQUIPMENT_ID_SEQ.NEXTVAL,?, 0,0,SYSDATE,?,?)";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setInt(1, cost);
            stmt.setString(2, roomID);
            stmt.setString(3,findTypeID(name) );
            ResultSet rs = stmt.executeQuery();
            System.out.println(cost+roomID);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
    
     public boolean updateRepairCost(String equipmentID,int repaircost){
        boolean x = validEquipmentID(equipmentID);
        if(x==false){System.out.println("NO RUN");return false;}
        String selectStatement = "update equipment set repait=repait+1,repaircost=repaircost+? where equipment_id=?";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            stmt.setInt(1,repaircost);
            stmt.setString(2, equipmentID);
            ResultSet rs = stmt.executeQuery();
            System.out.println("opiods");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return true;
    }
   

    
}

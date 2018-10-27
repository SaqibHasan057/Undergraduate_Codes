/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sukarna.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author samsung
 */
public class DataAccess 
{
    String dbURL = "jdbc:oracle:thin:@localhost:1521:XE";
    String username = "hr";
    String password = "hr";

    Connection conn = null;
    public DataAccess()
    {
        try
        {
            Class.forName("oracle.jdbc.OracleDriver");
            conn = DriverManager.getConnection(dbURL, username, password);
            if(conn!=null) System.out.println("Connection successfully established.");
            else System.out.println("Could not establish connection");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    public List<String> getEmployeeNames()
    {
        List<String> employeeNames = new ArrayList<String>();
        String selectStatement = "select first_name, last_name from employees";
        try
        {    
            PreparedStatement stmt = conn.prepareStatement(selectStatement);
            ResultSet rs = stmt.executeQuery();
            while(rs.next())
            {
                String first = rs.getString("first_name");
                String last = rs.getString("last_name");
                String name = first + " " + last;
                employeeNames.add(name);
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        return employeeNames;
    }
    public int createAccount(String firstName, String lastName, String username, 
            String password)
    {
        try
        {
            String insertCommand = "insert into account values(?,?,?,?)";
            PreparedStatement stmt = conn.prepareStatement(insertCommand);
            stmt.setString(1, firstName);
            stmt.setString(2, lastName);
            stmt.setString(3, username);
            stmt.setString(4, password);
            int count = stmt.executeUpdate();
            return count;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return 0;
        }
        
        
        
    }
    
   
    public boolean existUser(String username,String password)
    {
        try
        {
            String query = "select * from account where username = ? and password = ?";
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
    
/*
//Call function sample:
    
    String sql = "{ ? = call FUNCT_PERSON(?,?) }";
    CallableStatement statement = connection.prepareCall(sql);
    statement.setString(2,username);
    statement.setString(3,password);
    statement.registerOutParameter(1, java.sql.Types.INTEGER);  

    statement.execute();   
    //this is the main line
    long id = statement.getLong(1);
    if (id > 0) {
        //proceed to another page
    } else {
        //Go back to the login page
    }*/
    
 /*
    String sql = "{ call PROC_PERSON(?,?,?) }";
    CallableStatement statement = connection.prepareCall(sql);
    statement.setString(2,username);
    statement.setString(3,password);
    statement.registerOutParameter(1, java.sql.Types.INTEGER);  

    statement.execute();   
    //this is the main line
    long id = statement.getLong(1);
    if (id > 0) {
        //proceed to another page
    } else {
        //Go back to the login page
    }*/ 
}

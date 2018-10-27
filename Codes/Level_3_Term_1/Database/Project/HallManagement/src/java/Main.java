
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import models.StudentInfo;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Dipto
 */
public class Main {
    public static void main(String args[]) throws SQLException{
       System.out.println("Hello World!!");
       OracleConnection connection = new OracleConnection();
       boolean b=connection.existUser("mma","mma");
       if(b)System.out.println("YEAH BEBE!!");
       else System.out.println("NOOOOOOOO");
        String query = "insert into student values(?,?,?,?,?,?,?,?,?,?,?,?,?)";
           
    }
}

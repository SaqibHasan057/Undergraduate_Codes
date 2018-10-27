
import java.io.IOException;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import models.DueInfo;
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
public class StudentUpdateController extends HttpServlet{
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException, SQLException {
        
        
        HttpSession session = request.getSession();
        OracleConnection db = new OracleConnection();
        String studentID = request.getParameter("student_id");
        ArrayList<StudentInfo> studentList = db.getStudentTable(studentID);
        String newfirstName = request.getParameter("firstName");
        String newlastName = request.getParameter("lastName");
        String newfatherFname = request.getParameter("fatherFname");
        String newfatherLname = request.getParameter("fatherLname");
        String newmotherFname = request.getParameter("motherFname");
        String newmotherLname = request.getParameter("motherLname");
        String newstreet = request.getParameter("street");
        String newcity = request.getParameter("city");
        String newstate = request.getParameter("state");
        String newpin = request.getParameter("pin");
        String newguardian = request.getParameter("guardian");
        String newdob = request.getParameter("dob");
        String newphoneNo = request.getParameter("phoneNo");
        String newemail = request.getParameter("email");
        
        
        if(newfirstName.trim().length()!=0)studentList.get(0).setFirstName(newfirstName);
        if(newlastName.trim().length()!=0)studentList.get(0).setLastName(newlastName);
        if(newfatherFname.trim().length()!=0)studentList.get(0).setFatherFname(newfatherFname);
        if(newfatherLname.trim().length()!=0)studentList.get(0).setFatherLname(newfatherLname);
        if(newmotherFname.trim().length()!=0)studentList.get(0).setMotherFname(newmotherFname);
        if(newmotherLname.trim().length()!=0)studentList.get(0).setMotherLname(newmotherLname);
        if(newstreet.trim().length()!=0)studentList.get(0).setStreet(newstreet);
        if(newcity.trim().length()!=0)studentList.get(0).setCity(newcity);
        if(newstate.trim().length()!=0)studentList.get(0).setState(newstate);
        if(newpin.trim().length()!=0)studentList.get(0).setPin(newpin);
        if(newguardian.trim().length()!=0)studentList.get(0).setGuardian(newguardian);
        if(newdob.trim().length()!=0)studentList.get(0).setDOB(newdob);
        if(newphoneNo.trim().length()!=0)studentList.get(0).setPhoneNo(newphoneNo);
        if(newemail.trim().length()!=0)studentList.get(0).setEmail(newemail);
        
            String query = "update student set first_name=?,last_name=?,father_fname=?,father_lname=?,mother_fname=?,mother_lname=?,street=?,city=?,state=?,pin=?,guardian_contact_no=?,dob=? where student_id=?;";
            System.out.println("POPO");
            PreparedStatement stmt = db.getConnection().prepareStatement(query);
            //stmt.set(1, "STUDENT_ID_SEQ.NEXTVAL");
            stmt.setString(1, studentList.get(0).getFirstName());
            stmt.setString(2, studentList.get(0).getLastName());
            stmt.setString(3, studentList.get(0).getFatherFname());
            stmt.setString(4, studentList.get(0).getFatherLname());
            stmt.setString(5, studentList.get(0).getMotherFname());
            stmt.setString(6, studentList.get(0).getMotherLname());
            stmt.setString(7, studentList.get(0).getStreet());
            stmt.setString(8, studentList.get(0).getCity());
            stmt.setString(9, studentList.get(0).getState());
            stmt.setString(10, studentList.get(0).getPin());
            stmt.setString(11, studentList.get(0).getGuardian());
            stmt.setString(12, studentList.get(0).getDOB());
            stmt.setString(13, studentList.get(0).getStudentID());
            db.RunQuery(stmt);
            db.newPhoneNo(db.getCurrentStudentID(), newphoneNo);
            db.newEmail(db.getCurrentStudentID(), newemail);
            String user =(String)session.getAttribute("User");
            db.enterIntoUpdateLogFile(user,"student");
            System.out.println("BUET");
            RequestDispatcher rd = request.getRequestDispatcher("student.jsp");
            rd.forward(request, response);
        }  
    
// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            processRequest(request, response);
        } catch (SQLException ex) {
            Logger.getLogger(StudentInsertController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            processRequest(request, response);
        } catch (SQLException ex) {
            Logger.getLogger(StudentInsertController.class.getName()).log(Level.SEVERE, null, ex);
            RequestDispatcher rd = request.getRequestDispatcher("student.jsp");
            rd.forward(request, response);
        }
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
    
}

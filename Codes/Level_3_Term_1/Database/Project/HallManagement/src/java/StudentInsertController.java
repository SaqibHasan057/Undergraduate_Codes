
import java.io.IOException;
import java.sql.Date;
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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Dipto
 */
public class StudentInsertController extends HttpServlet {
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException, SQLException {
        
        HttpSession session = request.getSession();
        
        String firstName = request.getParameter("firstName");
        String lastName = request.getParameter("lastName");
        String fatherFname = request.getParameter("fatherFname");
        String fatherLname = request.getParameter("fatherLname");
        String motherFname = request.getParameter("motherFname");
        String motherLname = request.getParameter("motherLname");
        String street = request.getParameter("street");
        String city = request.getParameter("city");
        String state = request.getParameter("state");
        String pin = request.getParameter("pin");
        String guardian = request.getParameter("guardian");
        String dob = request.getParameter("dob");
        String phoneNo = request.getParameter("phoneNo");
        String email = request.getParameter("email");
        
        System.out.println(dob);
        
        if(firstName.trim().length()==0 || lastName.trim().length()==0 || fatherFname.trim().length()==0 || 
                fatherLname.trim().length()==0|| motherFname.trim().length()==0 || motherLname.trim().length()==0 || street.trim().length()==0 
                || city.trim().length()==0 || state.trim().length()==0
                || pin.trim().length()==0 || guardian.trim().length()==0 || dob.trim().length()==0 || phoneNo.trim().length()==0 || email.trim().length()==0)
        {
            RequestDispatcher rd = request.getRequestDispatcher("ERROR.jsp");
            rd.forward(request, response);
        }
        else{
            String query = "insert into student values(STUDENT_ID_SEQ.NEXTVAL,to_date(?,'MM/DD/YYYY') ,?,?,?,?,?,?,?,?,?,?,?)";
            System.out.println("POPO");
            OracleConnection db = new OracleConnection();
            PreparedStatement stmt = db.getConnection().prepareStatement(query);
            //stmt.set(1, "STUDENT_ID_SEQ.NEXTVAL");
            stmt.setString(1, dob);
            stmt.setString(2, firstName);
            stmt.setString(3, lastName);
            stmt.setString(4, fatherFname);
            stmt.setString(5, fatherLname);
            stmt.setString(6, motherFname);
            stmt.setString(7, motherLname);
            stmt.setString(8, street);
            stmt.setString(9, city);
            stmt.setString(10, state);
            stmt.setString(11, pin);
            stmt.setString(12, guardian);
            db.RunQuery(stmt);
            db.setPhoneNo(db.getCurrentStudentID(), phoneNo);
            db.setEmail(db.getCurrentStudentID(), email);
            String user =(String)session.getAttribute("User");
            db.enterIntoUpdateLogFile(user,"student");
            System.out.println("BUET");
            RequestDispatcher rd = request.getRequestDispatcher("student.jsp");
            rd.forward(request, response);
        }   
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

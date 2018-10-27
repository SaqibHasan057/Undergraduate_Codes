
import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import models.FeeInfo;
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
public class FeeViewController extends HttpServlet{
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        OracleConnection connection = new OracleConnection();
        ArrayList<FeeInfo> listYearly = connection.getFeeTable("yearly");
        ArrayList<FeeInfo> listMonthly = connection.getFeeTable("monthly");
        Integer yearlyFee = connection.getSumOfFee("yearly");
        Integer monthlyFee = connection.getSumOfFee("monthly");
        Integer total = connection.getTotalSum();
        HttpSession session = request.getSession();
        session.setAttribute("listYear", listYearly);
        session.setAttribute("listMonth", listMonthly);
        session.setAttribute("sumYearly", yearlyFee);
        session.setAttribute("sumMonthly", monthlyFee);
        session.setAttribute("total", total);
        RequestDispatcher rd = request.getRequestDispatcher("feeView.jsp");
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
        processRequest(request, response);
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
        processRequest(request, response);
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

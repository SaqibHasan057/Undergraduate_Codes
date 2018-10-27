package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;

public final class refer_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List<String> _jspx_dependants;

  private org.glassfish.jsp.api.ResourceInjector _jspx_resourceInjector;

  public java.util.List<String> getDependants() {
    return _jspx_dependants;
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;

    try {
      response.setContentType("text/html;charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;
      _jspx_resourceInjector = (org.glassfish.jsp.api.ResourceInjector) application.getAttribute("com.sun.appserv.jsp.resource.injector");

      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
      out.write("<html>\n");
      out.write("    <head>\n");
      out.write("        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
      out.write("        <title>Refer Page</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("    <center>\n");
      out.write("        ");

            String username = (String) session.getAttribute("User");
            if(username==null)
            {
                RequestDispatcher rd = request.getRequestDispatcher("index.html");
                rd.forward(request, response);
            }
            out.println("<h1>Welcome "+username+" </h1>");
        
      out.write("\n");
      out.write("        <h3>Choose your ACTION</h3>\n");
      out.write("        <a href=\"student.jsp\">Enter a new student or view/update the current students.</a><br><br><br>\n");
      out.write("        <a href=\"allocation.jsp\">Create allocation for a student.</a><br><br><br>\n");
      out.write("        <a href=\"feeView.jsp\">View all the fees paid by the students</a><br><br><br>\n");
      out.write("        <a href=\"dueView.jsp\">View all the dues of the students</a><br><br><br>\n");
      out.write("        <a href=\"seatView.jsp\">View Allocation to each Seat</a><br><br><br>\n");
      out.write("        <a href=\"historyView.jsp\">View the allocation history of student</a><br><br><br>\n");
      out.write("        <a href=\"equipmentView.jsp\">View information about all the equipments in the Hall</a><br><br><br>\n");
      out.write("        <a href=\"locationView.jsp\">View the location of the seat</a><br><br><br>\n");
      out.write("        <a href=\"seatView.jsp\">View information related to student's allocation timeline on a particular seat</a><br><br><br>\n");
      out.write("        <a href=\"studentProfileView.jsp\">Get the profile of the student</a><br><br><br>\n");
      out.write("         <a href=\"insertHallPayment.jsp\">Insert a new Hall Payment</a><br><br><br>\n");
      out.write("         <a href=\"HallFeeInsert.jsp\">Insert a new Hall Fee</a><br><br><br>\n");
      out.write("         <a href=\"addEquipment.jsp\">Enter a new equipment</a><br><br><br>\n");
      out.write("         <a href=\"repairEquipment.jsp\">Update repair cost of equipment</a><br><br><br>\n");
      out.write("         \n");
      out.write("         <a href=\"refer.jsp\">Go Back</a><br>\n");
      out.write("        <form method=\"post\" action=\"LogoutController.do\">\n");
      out.write("            <input type=\"submit\" value=\"Logout\" />\n");
      out.write("        </form>\n");
      out.write("    </center>\n");
      out.write("    </body>\n");
      out.write("</html>\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
        else throw new ServletException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}

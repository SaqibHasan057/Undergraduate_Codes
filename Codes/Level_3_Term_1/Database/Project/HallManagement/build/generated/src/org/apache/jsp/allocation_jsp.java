package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import models.SeatView;
import models.DueInfo;
import java.util.ArrayList;

public final class allocation_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
      out.write("<html>\n");
      out.write("    <head>\n");
      out.write("        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
      out.write("        <title>Allocation Page</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("    <center>\n");
      out.write("        <h1>Give the Student an Allocation</h1>\n");
      out.write("        <form method=\"post\" action=\"AllocationInsert.do\">\n");
      out.write("            Student ID <input type=\"text\" name=\"student_id\" /><br>\n");
      out.write("            Seat ID<input type=\"text\" name=\"seat_id\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"Insert\" /><br><br><br><br><br>\n");
      out.write("        </form>\n");
      out.write("        <h1>End the Student's Allocation</h1>\n");
      out.write("        <form method=\"post\" action=\"AllocationEnd.do\">\n");
      out.write("            Seat ID<input type=\"text\" name=\"seat_id\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"End Date\" />\n");
      out.write("        </form>\n");
      out.write("        <h1>Change the Allocation of the Student</h1>\n");
      out.write("        <form method=\"post\" action=\"AllocationChange.do\">\n");
      out.write("            Student ID <input type=\"text\" name=\"student_id\" /><br>\n");
      out.write("            Old Seat ID<input type=\"text\" name=\"old_seat_id\" /><br>\n");
      out.write("            New Seat ID<input type=\"text\" name=\"new_seat_id\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"Change\" /><br><br><br><br><br>\n");
      out.write("        </form>\n");
      out.write("        <form method=\"post\" action=\"UnoccupiedSeatViewController.do\">\n");
      out.write("            <input type=\"submit\" value=\"View empty seats\" />\n");
      out.write("        </form>\n");
      out.write("        <h2>All the unoccupied seats in the hall</h1>\n");
      out.write("        ");
 
            
            ArrayList<SeatView> list= (ArrayList<SeatView>) session.getAttribute("unoccupiedSeat");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("List of free seats<br/>");
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Seat ID|</td><td>|Room ID|</td><td>|Floor|</td><td>"
                        + "|Wing|</td>"
                        + "</tr>");
                int count=0;
                for(SeatView exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td><td>|%s|</td>",
                            count, exe.getSeatID(),exe.getRoomID(),exe.getFloor(),exe.getWing()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
            }
        
      out.write("\n");
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

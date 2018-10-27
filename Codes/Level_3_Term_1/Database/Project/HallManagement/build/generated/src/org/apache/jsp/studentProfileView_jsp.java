package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import models.PaymentHistoryInfo;
import models.HallfeeHistoryInfo;
import models.FullHistoryInfo;
import models.StudentInfo;
import java.util.ArrayList;

public final class studentProfileView_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
      out.write("<html>\n");
      out.write("    <head>\n");
      out.write("        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
      out.write("        <title>JSP Page</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("    <center>\n");
      out.write("        <form method=\"post\" action=\"StudentProfileController.do\">\n");
      out.write("            Student ID <input type=\"text\" name=\"student_id\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"View Profile\" />\n");
      out.write("        </form>\n");
      out.write("        <h2>View the student's profile</h1>\n");
      out.write("        ");
 
            
            ArrayList<StudentInfo> list1 = (ArrayList<StudentInfo>) session.getAttribute("student");
            out.println("<h1>Student's Personal Information</h1><br/>");
            if(list1==null)
            {
                out.println("");
            }
            else if(list1.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|First Name|</td><td>|Last Name|</td><td>"
                        + "|Father Fname|</td><td>|Father Lname|</td><td>|Mother Fname|</td><td>|Mother Lname|</td><td>"
                        + "|Street|</td><td>|City|</td><td>|State|</td><td>|Pin|</td><td>|Guardian Contact No.|</td><td>|Date of Birth|</td><td>|Phone|</td><td>|Email|</td></tr>");
                int count=0;
                for(StudentInfo exe: list1)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>"
                            + "<td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getStudentID(),exe.getFirstName(),exe.getLastName(),exe.getFatherFname(),exe.getFatherLname(),
                            exe.getMotherFname(),
                            exe.getMotherLname(),exe.getStreet(),exe.getCity(),exe.getState(),exe.getPin(),
                            exe.getGuardian(),exe.getDOB(),exe.getPhoneNo(),exe.getEmail()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
            
            ArrayList<FullHistoryInfo> list2 = (ArrayList<FullHistoryInfo>) session.getAttribute("allocation");
            out.println("<h1>Student's History of Allocation</h1><br/>");
            if(list2==null)
            {
                out.println("");
            }
            else if(list2.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Allocation ID|</td><td>|Start Date|</td><td>|End Date|</td><td>"
                        + "|Seat ID|</td><td>|Room ID|</td><td>|Floor|</td><td>|Wing|</td><td></tr>");
                int count=0;
                for(FullHistoryInfo exe: list2)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td><td>|%s|</td>",
                            count, exe.getAllocationID(),exe.getStartDate(),exe.getEndDate(),exe.getSeatID(),exe.getRoomID(),
                            exe.getFloor(),
                            exe.getWing()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
            
            ArrayList<HallfeeHistoryInfo> list3 = (ArrayList<HallfeeHistoryInfo>) session.getAttribute("hallfee");
            out.println("<h1>Student's History of Hallfee</h1><br/>");
            if(list3==null)
            {
                out.println("");
            }
            else if(list3.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Fee ID|</td><td>|Seat ID|</td><td>|Room ID|</td><td>"
                        + "|Pay Date|</td><td>|Center|</td><td>|Method|</td><td>|Amount|</td><td>"
                        + "|Start Date|</td><td>|End Date|</td></tr>");
                int count=0;
                for(HallfeeHistoryInfo exe: list3)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>"
                            + "<td>|%s|</td><td>|%d|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getFeeID(),exe.getSeatID(),exe.getRoomID(),exe.getPayDate(),exe.getCenter(),
                            exe.getMethod(),
                            exe.getAmount(),exe.getStartDate(),exe.getDeadline()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
            
            ArrayList<PaymentHistoryInfo> list4 = (ArrayList<PaymentHistoryInfo>) session.getAttribute("payment");
            out.println("<h1>Student's History of Payments</h1><br/>");
            if(list4==null)
            {
                out.println("");
            }
            else if(list4.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Receipt ID|</td><td>|Delay|</td><td>|Student ID|</td><td>"
                        + "|Fee ID|</td><td>|Due|</td><td>|Pay Date|</td><td>|Center|</td><td>"
                        + "|Method|</td><td>|Start Date|</td><td>|End Date|</td></tr>");
                int count=0;
                for(PaymentHistoryInfo exe: list4)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td>"
                            + "<td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getReceiptID(),exe.getDelay(),exe.getStudentID(),exe.getFeeID(),exe.getDue(),
                            exe.getPayDate(),
                            exe.getCenter(),exe.getMethod(),exe.getStartDate(),exe.getDeadline()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        
      out.write("\n");
      out.write("    </center>\n");
      out.write("    </body>\n");
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

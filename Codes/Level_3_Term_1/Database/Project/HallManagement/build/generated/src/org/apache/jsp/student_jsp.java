package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import java.util.ArrayList;
import models.StudentInfo;

public final class student_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("<!DOCTYPE html>\n");
      out.write("<html>\n");
      out.write("    <head>\n");
      out.write("        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
      out.write("        <title>Student</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("        <a href=\"refer.jsp\">Go Back</a><br>\n");
      out.write("        <center>\n");
      out.write("        <h1>Create your account!</h1>\n");
      out.write("        <form method=\"post\" action=\"StudentInsertController.do\">\n");
      out.write("            First Name <input type=\"text\" name=\"firstName\" /><br>\n");
      out.write("            Last Name <input type=\"text\" name=\"lastName\" /> <br/>\n");
      out.write("            Father First Name <input type=\"text\" name=\"fatherFname\" /><br>\n");
      out.write("            Father Last Name <input type=\"text\" name=\"fatherLname\" /><br>\n");
      out.write("            Mother First Name <input type=\"text\" name=\"motherFname\" /><br>\n");
      out.write("            Mother Last Name <input type=\"text\" name=\"motherLname\" /><br>\n");
      out.write("            Street <input type=\"text\" name=\"street\" /><br>\n");
      out.write("            City <input type=\"text\" name=\"city\" /><br>\n");
      out.write("            State <input type=\"text\" name=\"state\" /><br>\n");
      out.write("            PIN <input type=\"text\" name=\"pin\" /><br>\n");
      out.write("            Guardian Contact Number <input type=\"text\" name=\"guardian\" /><br>\n");
      out.write("            Date of Birth(MM/DD/YYYY) <input type=\"text\" name=\"dob\" /><br>\n");
      out.write("            Phone<input type=\"text\" name=\"phoneNo\" /><br>\n");
      out.write("            Email<input type=\"text\" name=\"email\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"Insert\" />\n");
      out.write("        </form>\n");
      out.write("        <br><br><br><br><br>\n");
      out.write("        <form method=\"post\" action=\"StudentDeleteController.do\">\n");
      out.write("            Student ID <input type=\"text\" name=\"ID\" /><br>\n");
      out.write("            <input type=\"submit\" value=\"Delete\" />\n");
      out.write("        </form>\n");
      out.write("        <br><br><br><br><br>\n");
      out.write("        <form method=\"post\" action=\"StudentViewController.do\">\n");
      out.write("            <input type=\"submit\" value=\"View\" />\n");
      out.write("        </form>\n");
      out.write("    \n");
      out.write("        <h2>View the profiles of all the students</h1>\n");
      out.write("        ");
 
            
            ArrayList<StudentInfo> list = (ArrayList<StudentInfo>) session.getAttribute("studentView");
            if(list==null)
            {
                out.println("");
            }
            else if(list.size()==0)
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
                for(StudentInfo exe: list)
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

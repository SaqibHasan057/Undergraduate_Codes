package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import models.DueInfo;
import java.util.ArrayList;

public final class dueView_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("        <title>JSP Page</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("        <form method=\"post\" action=\"DueViewController.do\">\n");
      out.write("            <input type=\"submit\" value=\"View Due\" />\n");
      out.write("        </form>\n");
      out.write("        <center>  \n");
      out.write("        <h2>Your transaction records</h1>\n");
      out.write("        ");
 
            
            ArrayList<DueInfo> list= (ArrayList<DueInfo>) session.getAttribute("list");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Due List<br/>");
                out.println("<table>");
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|Student Name|</td><td>|Time Delayed|</td><td>"
                        + "|Amount Due|</td>"
                        + "</tr>");
                int count=0;
                for(DueInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td>",
                            count, exe.getStudentID(),exe.getStudentName(),exe.getTimeDelay(),exe.getAmountDue()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
            }
        
      out.write("\n");
      out.write("    </center>\n");
      out.write("    \n");
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

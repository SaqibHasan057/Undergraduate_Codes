package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import models.FeeInfo;
import java.util.ArrayList;
import java.util.ArrayList;

public final class feeView_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("        <title>JSP Page</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("        <form method=\"post\" action=\"FeeViewController.do\">\n");
      out.write("            <input type=\"submit\" value=\"View\" />\n");
      out.write("        </form>\n");
      out.write("        <center>  \n");
      out.write("        <h2>Your transaction records</h1>\n");
      out.write("        ");
 
            
            ArrayList<FeeInfo> listYearly = (ArrayList<FeeInfo>) session.getAttribute("listYear");
            ArrayList<FeeInfo> listMonthly = (ArrayList<FeeInfo>) session.getAttribute("listMonth");
            Integer yearAmount = (Integer) session.getAttribute("sumYearly");
            Integer monthAmount = (Integer) session.getAttribute("sumMonthly");
            Integer totalAmount = (Integer) session.getAttribute("total");
            if(listYearly==null || listMonthly==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Yearly Fee List<br/>");
                out.println("<table>");
                out.println("<tr><td>|Row Number|</td><td>|Fee ID|</td><td>|Amount|</td><td>|Deadline|</td><td>"
                        + "|Start Date|</td><td>|Due|</td><td>|Year|</td><td>|Month|</td>"
                        + "</tr>");
                int count=0;
                for(FeeInfo exe: listYearly)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>%d</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%d</td>",
                            count, exe.getFeeID(),exe.getAmount(),exe.getDeadline(),exe.getStartDate(),exe.getDue(),exe.getYear(),
                            exe.getMonth()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
                
                out.println("Monthly Fee List<br/>");
                out.println("<table>");
                out.println("<tr><td>|Row Number|</td><td>|Fee ID|</td><td>|Amount|</td><td>|Deadline|</td><td>"
                        + "|Start Date|</td><td>|Due|</td><td>|Year|</td><td>|Month|</td>"
                        + "</tr>");
                count=0;
                for(FeeInfo exe: listMonthly)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>%d</td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%d</td>",
                            count, exe.getFeeID(),exe.getAmount(),exe.getDeadline(),exe.getStartDate(),exe.getDue(),exe.getYear(),
                            exe.getMonth()));
                    out.println("</tr>");
                }
                out.println("</table><br/><br/><br/><br/><br/><br/><br/><br/><br/>");
                
                out.println("Sum of all yearly fees="+yearAmount.intValue()+"<br/>");
                out.println("Sum of all monthly fees="+monthAmount.intValue()+"<br/>");
                out.println("Total sum of fees="+totalAmount.intValue()+"<br/>");
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

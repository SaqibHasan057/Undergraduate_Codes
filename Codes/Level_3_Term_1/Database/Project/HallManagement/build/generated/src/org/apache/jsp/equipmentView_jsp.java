package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import models.TallyInfo;
import java.util.ArrayList;

public final class equipmentView_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("        <form method=\"post\" action=\"EquipmentTallyController.do\">\n");
      out.write("            <input type=\"submit\" value=\"View Equipment List\" />\n");
      out.write("        </form>\n");
      out.write("        <center>  \n");
      out.write("        <h2>Your transaction records</h1>\n");
      out.write("        ");
 
            
            ArrayList<TallyInfo> list= (ArrayList<TallyInfo>) session.getAttribute("list");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Equipment List<br/>");
                out.println("<table>");
                out.println("<tr><td>|Row Number|</td><td>|Equipment Name|</td><td>|Number/Count|</td><td>|Total Cost|</td><td>"
                        + "|Total Repair Cost|</td>"
                        + "</tr>");
                int count=0;
                for(TallyInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%d|</td><td>|%d|</td><td>|%d|</td>",
                            count, exe.getTypeName(),exe.getCount(),exe.getSumCost(),exe.getSumRepairCost()));
                    out.println("</tr>");
                }
                out.println("</table><br/><br/><br/><br/><br/><br/><br/>");
                
            }
        
      out.write("\n");
      out.write("        <form method=\"post\" action=\"TotalEquipmentCost.do\">\n");
      out.write("            <input type=\"submit\" value=\"View Total EquipmentCost\" />\n");
      out.write("        </form>\n");
      out.write("        <center>  \n");
      out.write("        <h2>Your transaction records</h1>\n");
      out.write("        ");
 
           
            Integer sumCost= (Integer) session.getAttribute("sumCost");
            Integer sumRepairCost= (Integer) session.getAttribute("sumRepairCost");
            if(sumCost==null || sumRepairCost==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Total cost of all equipments: "+sumCost.intValue()+"<br/>");
                out.println("Total repair cost of all equipments: "+sumRepairCost.intValue()+"<br/>");
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

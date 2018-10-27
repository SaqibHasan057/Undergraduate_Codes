package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import java.util.ArrayList;
import sukarna.models.BankTransaction;

public final class showStatement_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("        <title>Show Statement</title>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("        ");
      org.apache.jasper.runtime.JspRuntimeLibrary.include(request, response, "navigation.jsp", out, false);
      out.write(" \n");
      out.write("        <form method=\"post\" action=\"ShowStatementServlet.do\">\n");
      out.write("            Account No: <input type=\"text\" name=\"bankAccountNo\" />\n");
      out.write("            <input type=\"submit\" value=\"Show Statement\"/>          \n");
      out.write("        </form>\n");
      out.write("        \n");
      out.write("        <h2>Your transaction records</h1>\n");
      out.write("        ");
 
            
            ArrayList<BankTransaction> transactions = (ArrayList<BankTransaction>) session.getAttribute("transactions");
            if(transactions==null)
            {
                out.println("");
            }
            else if(transactions.size()==0)
            {
                out.println("Account have no transaction records.");
            }
            else 
            {
                out.println("<table>");
                out.println("<hr><td>Sl.</td><td>Amount</td><td>Datetime</td></tr>");
                int count=0;
                for(BankTransaction trans: transactions)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format("<td>%d.</td><td>%10.2f</td><td>%s</td>", count, trans.getAmount(), trans.getDatetime()) );
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        
      out.write("\n");
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

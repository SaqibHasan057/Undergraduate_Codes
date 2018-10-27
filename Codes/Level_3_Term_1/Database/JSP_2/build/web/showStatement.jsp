<%-- 
    Document   : showStatement.jsp
    Created on : Nov 29, 2016, 2:23:54 PM
    Author     : samsung
--%>

<%@page import="java.util.ArrayList"%>
<%@page import="sukarna.models.BankTransaction"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Show Statement</title>
    </head>
    <body>
        <jsp:include page="navigation.jsp" /> 
        <form method="post" action="ShowStatementServlet.do">
            Account No: <input type="text" name="bankAccountNo" />
            <input type="submit" value="Show Statement"/>          
        </form>
        
        <h2>Your transaction records</h1>
        <% 
            
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
        %>
    </body>
</html>

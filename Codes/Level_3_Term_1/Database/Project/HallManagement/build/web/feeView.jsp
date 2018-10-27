<%-- 
    Document   : feeView
    Created on : 15-Dec-2016, 9:34:32 AM
    Author     : Dipto
--%>

<%@page import="models.FeeInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <form method="post" action="FeeViewController.do">
            <input type="submit" value="View" />
        </form>
        <center>  
        <h2>The records of all the fees based on type</h1>
        <% 
            
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
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Fee ID|</td><td>|Amount|</td><td>|Deadline|</td><td>"
                        + "|Start Date|</td><td>|Due|</td><td>|Year|</td><td>|Month|</td>"
                        + "</tr>");
                int count=0;
                for(FeeInfo exe: listYearly)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td><td>|%d|</td><td>|%d|</td>",
                            count, exe.getFeeID(),exe.getAmount(),exe.getDeadline(),exe.getStartDate(),exe.getDue(),exe.getYear(),
                            exe.getMonth()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
                
                out.println("Monthly Fee List<br/>");
                out.println("<table border=\"1\">");
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
        %>
    </center>
    
    </body>
</html>

<%-- 
    Document   : dueView
    Created on : 15-Dec-2016, 12:28:24 PM
    Author     : Dipto
--%>

<%@page import="models.DueInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Due Viewpage</title>
    </head>
    <body>
        <center> 
        <form method="post" action="DueViewController.do">
            <input type="submit" value="View Due" />
        </form>
        <h2>The records of all the dues in the hall</h1>
        <% 
            
            ArrayList<DueInfo> list= (ArrayList<DueInfo>) session.getAttribute("dueView");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Due List<br/>");
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|Student Name|</td><td>|Time Delayed|</td><td>"
                        + "|Amount Due|</td>"
                        + "</tr>");
                int count=0;
                for(DueInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td><td>|%d|</td>",
                            count, exe.getStudentID(),exe.getStudentName(),exe.getTimeDelay(),exe.getAmountDue()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
            }
        %>
    </center>
    
    </body>
</html>

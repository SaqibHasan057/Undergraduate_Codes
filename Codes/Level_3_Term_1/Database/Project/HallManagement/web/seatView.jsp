<%-- 
    Document   : SeatView
    Created on : 15-Dec-2016, 3:47:58 PM
    Author     : Dipto
--%>

<%@page import="models.SeatInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page import="models.StudentInfo"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Seat Viewpage</title>
    </head>
    <body>
        <center>
        <form method="post" action="SeatViewController.do">
            Enter seat_id: <input type="text" name="seat_id" /> <br/>
            <input type="submit" value="View" />
        </form>

        <h2>View all those allocated to the seat</h1>
        <% 
            
            ArrayList<SeatInfo> list = (ArrayList<SeatInfo>) session.getAttribute("seatView");
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
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|Student Name|</td><td>|Start Date|</td><td>"
                        + "|End Date|</td></tr>");
                int count=0;
                for(SeatInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getStudentID(),exe.getStudentName(),exe.getStartDate(),exe.getEndDate()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        %>
    </center>
    </body>
</html>

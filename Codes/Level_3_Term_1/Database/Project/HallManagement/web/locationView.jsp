<%-- 
    Document   : locationView
    Created on : 15-Dec-2016, 5:31:41 PM
    Author     : Dipto
--%>

<%@page import="models.LocationInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Location Viewpage</title>
    </head>
    <body>
        <center>
        <form method="post" action="LocationViewController.do">
            Enter seat_id: <input type="text" name="seat_id" /> <br/>
            <input type="submit" value="View Location of Allocated Seat along with Students" />
        </form>
        <h2>The records of all those allocated to the seat</h1>
        <% 
            
            ArrayList<LocationInfo> list = (ArrayList<LocationInfo>) session.getAttribute("locationView");
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
                        + "|Wing|</td><td>|Floor|</td></tr>");
                int count=0;
                for(LocationInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td>",
                            count, exe.getStudentID(),exe.getStudentName(),exe.getStartDate(),exe.getWing(),exe.getFloor()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        %>
    </center>
    </body>
</html>

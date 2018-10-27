<%-- 
    Document   : occupancy
    Created on : 19-Dec-2016, 8:03:50 AM
    Author     : Dipto
--%>

<%@page import="models.SeatView"%>
<%@page import="models.LocationInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <center>
        <form method="post" action="LocationViewController.do">
            Enter seat_id: <input type="text" name="seat_id" /> <br/>
            <input type="submit" value="View Location of Allocated Seat along with Students" />
        </form>
        <h2>The records of all those allocated to the seat</h1>
        <% 
            
            ArrayList<SeatView> list = (ArrayList<SeatView>) session.getAttribute("unoccupiedSeatList");
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
                out.println(list.get(1).getFloor());
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Seat ID|</td><td>|Room ID|</td><td>|Floor|</td><td>"
                        + "|Wing|</td></tr>");
                int count=0;
                for(SeatView exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%d|</td><td>|%s|</td>",
                            count, exe.getSeatID(),exe.getRoomID(),exe.getFloor(),exe.getWing()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        %>
    </center>
    </body>
</html>

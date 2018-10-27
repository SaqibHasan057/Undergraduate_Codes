<%-- 
    Document   : allocation
    Created on : 15-Dec-2016, 7:48:07 AM
    Author     : Dipto
--%>

<%@page import="models.SeatView"%>
<%@page import="models.DueInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Allocation Page</title>
    </head>
    <body>
    <center>
        <h1>Give the Student an Allocation</h1>
        <form method="post" action="AllocationInsert.do">
            Student ID <input type="text" name="student_id" /><br>
            Seat ID<input type="text" name="seat_id" /><br>
            <input type="submit" value="Insert" /><br><br><br><br><br>
        </form>
        <h1>End the Student's Allocation</h1>
        <form method="post" action="AllocationEnd.do">
            Seat ID<input type="text" name="seat_id" /><br>
            <input type="submit" value="End Date" />
        </form>
        <h1>Change the Allocation of the Student</h1>
        <form method="post" action="AllocationChange.do">
            Student ID <input type="text" name="student_id" /><br>
            Old Seat ID<input type="text" name="old_seat_id" /><br>
            New Seat ID<input type="text" name="new_seat_id" /><br>
            <input type="submit" value="Change" /><br><br><br><br><br>
        </form>
        <form method="post" action="UnoccupiedSeatViewController.do">
            <input type="submit" value="View empty seats" />
        </form>
        <h2>All the unoccupied seats in the hall</h1>
        <% 
            
            ArrayList<SeatView> list= (ArrayList<SeatView>) session.getAttribute("unoccupiedSeat");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("List of free seats<br/>");
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Seat ID|</td><td>|Room ID|</td><td>|Floor|</td><td>"
                        + "|Wing|</td>"
                        + "</tr>");
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

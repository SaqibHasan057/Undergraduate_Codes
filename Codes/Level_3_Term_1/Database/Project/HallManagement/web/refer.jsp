<%-- 
    Document   : refer
    Created on : 3-Dec-2016, 11:44:37 AM
    Author     : Dipto
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Refer Page</title>
    </head>
    <body>
    <center>
        <%
            String username = (String) session.getAttribute("User");
            if(username==null)
            {
                RequestDispatcher rd = request.getRequestDispatcher("index.html");
                rd.forward(request, response);
            }
            out.println("<h1>Welcome "+username+" </h1>");
        %>
        <h3>Choose your ACTION</h3>
        <a href="student.jsp">Enter a new student or view/update the current students.</a><br><br><br>
        <a href="allocation.jsp">Create allocation for a student.</a><br><br><br>
        <a href="feeView.jsp">View all the fees paid by the students</a><br><br><br>
        <a href="dueView.jsp">View all the dues of the students</a><br><br><br>
        <a href="seatView.jsp">View Allocation to each Seat</a><br><br><br>
        <a href="historyView.jsp">View the allocation history of student</a><br><br><br>
        <a href="equipmentView.jsp">View information about all the equipments in the Hall</a><br><br><br>
        <a href="locationView.jsp">View the location of the seat</a><br><br><br>
        <a href="seatView.jsp">View information related to student's allocation timeline on a particular seat</a><br><br><br>
        <a href="studentProfileView.jsp">Get the profile of the student</a><br><br><br>
         <a href="insertHallPayment.jsp">Insert a new Hall Payment</a><br><br><br>
         <a href="HallFeeInsert.jsp">Insert a new Hall Fee</a><br><br><br>
         <a href="addEquipment.jsp">Enter a new equipment</a><br><br><br>
         <a href="repairEquipment.jsp">Update repair cost of equipment</a><br><br><br>
         
         
        <form method="post" action="LogoutController.do">
            <input type="submit" value="Logout" />
        </form>
    </center>
    </body>
</html>

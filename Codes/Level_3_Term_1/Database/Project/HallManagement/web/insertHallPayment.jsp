<%-- 
    Document   : addHallPayment
    Created on : 19-Dec-2016, 10:42:29 AM
    Author     : Dipto
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
    <center>
        <h1>Insert a Hall Payment</h1>
        <form method="post" action="HallPaymentInsertController.do">
            Student ID <input type="text" name="student_id" /><br>
            Fee ID<input type="text" name="fee_id" /><br>
            Delay<input type="text" name="delay" /><br>
            Center<input type="text" name="center" /><br>
            Method<input type="text" name="method" /><br>
            <input type="submit" value="Insert Hall Payment" /><br><br><br><br><br>
        </form>
    </center>
    </body>
</html>

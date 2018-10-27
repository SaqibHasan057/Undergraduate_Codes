<%-- 
    Document   : HallFeeInsert
    Created on : 19-Dec-2016, 12:15:52 PM
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
        <h1>Enter a new Hall Fee</h1>
        <form method="post" action="HallFeeInsertController.do">
            Fee ID <input type="text" name="fee_id" /><br>
            Seat ID<input type="text" name="seat_id" /><br>
            Center<input type="text" name="center" /><br>
            Method<input type="text" name="method" /><br>
            <input type="submit" value="Insert Hall Fee" /><br><br><br><br><br>
        </form>
    </center>
    </body>
</html>

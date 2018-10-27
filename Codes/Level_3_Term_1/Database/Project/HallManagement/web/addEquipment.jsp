<%-- 
    Document   : addEquipment
    Created on : 19-Dec-2016, 1:06:36 PM
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
        <h1>Add a new equipment to the database</h1>
        <form method="post" action="EquipmentInsertController.do">
            Cost<input type="text" name="cost" /><br>
            Type<select name="name" >
                <option value = "BED">BED</option>
                <option value = "CHAIR">CHAIR</option>
                <option value = "TABLE">TABLE</option>
            </select><br>
            Room ID<input type="text" name="room_id" /><br>
            
            <input type="submit" value="Enter New Equipment" /><br><br><br><br><br>
        </form>
    </center>
    </body>
</html>

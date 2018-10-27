<%-- 
    Document   : repairEquipment
    Created on : 19-Dec-2016, 1:51:02 PM
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
        <h1>Add a new equipment</h1>
        <form method="post" action="RepairCostController.do">
            Repair Cost<input type="text" name="repair_cost" /><br>
            Equipment ID<input type="text" name="equipment_id" /><br>
            <input type="submit" value="Update Repair Cost" />
        </form>
    </center>
    </body>
</html>

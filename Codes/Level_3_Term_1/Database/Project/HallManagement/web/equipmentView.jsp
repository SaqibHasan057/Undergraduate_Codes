<%-- 
    Document   : equipmentTallyView
    Created on : 17-Dec-2016, 4:27:40 PM
    Author     : Dipto
--%>

<%@page import="models.TallyInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <form method="post" action="EquipmentTallyController.do">
            <input type="submit" value="View Equipment List" />
        </form>
        <center>  
        <h2>The records of all the equipments in the hall</h1>
        <% 
            
            ArrayList<TallyInfo> list= (ArrayList<TallyInfo>) session.getAttribute("equipmentTally");
            if(list==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Equipment List<br/>");
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Equipment Name|</td><td>|Number/Count|</td><td>|Total Cost|</td><td>"
                        + "|Total Repair Cost|</td>"
                        + "</tr>");
                int count=0;
                for(TallyInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%d|</td><td>|%d|</td><td>|%d|</td>",
                            count, exe.getTypeName(),exe.getCount(),exe.getSumCost(),exe.getSumRepairCost()));
                    out.println("</tr>");
                }
                out.println("</table><br/><br/><br/><br/><br/><br/><br/>");
                
            }
        %>
        <form method="post" action="TotalEquipmentCost.do">
            <input type="submit" value="View Total EquipmentCost" />
        </form>
        <center>  
        <h2>Your transaction records</h1>
        <% 
           
            Integer sumCost= (Integer) session.getAttribute("sumCost");
            Integer sumRepairCost= (Integer) session.getAttribute("sumRepairCost");
            if(sumCost==null || sumRepairCost==null)
            {
                out.println("");
            }
            else 
            {
                out.println("Total cost of all equipments: "+sumCost.intValue()+"<br/>");
                out.println("Total repair cost of all equipments: "+sumRepairCost.intValue()+"<br/>");
            }
        %>
    </center>
    </body>
</html>

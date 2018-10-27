<%-- 
    Document   : debitCredit.jsp
    Created on : Nov 29, 2016, 3:04:24 PM
    Author     : samsung
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <jsp:include page="navigation.jsp" /> 
        <h1>Enter debit/credit information </h1>
        <form method="post" action="transactionProcess.do">
            <table>
                <tr>
                    <td> Account No: </td>
                    <td>  <input type="text" name="bankAccountNo"/> </td> 
                </tr> 
                <tr> 
                    <td> Amount: </td> 
                    <td> <input type="text" name="amount" /> </td>
                </tr>
                <tr>
                    <td>
                        <input type="radio" name="transactionType" value="debit"/>Debit
                    </td>
                    <td> 
                        <input type="radio" name="transactionType" value="credit"/>Credit<br>
                    </td>
                </tr>
                <tr>
                    <td> 
                        <input type="submit" value="Process"/>
                    </td>
                    <td></td>
                </tr>
                
            </table>
        </form>
        <%
            Boolean result = (Boolean) session.getAttribute("transactionProcessResult");
            if(result==null)
            {
                
            }
            else if(result==true)
            {
                out.println("Transaction succesfully processed.");
            }
            else
            {
                out.println("Transaction error.");
            }
        %>
    </body>
</html>

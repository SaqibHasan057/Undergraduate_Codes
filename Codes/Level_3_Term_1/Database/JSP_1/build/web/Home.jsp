<%-- 
    Document   : Home.jsp
    Created on : Nov 19, 2016, 3:38:10 PM
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
        <%
            String username = (String) session.getAttribute("username");
            if(username==null)
            {
                RequestDispatcher rd = request.getRequestDispatcher("index.html");
                rd.forward(request, response);
            }
        %>
        <form method="post" action="AddToCart.do">
            <h1>Please choose a product</h1>
            <input type="radio" name="product" value="Apple" /> Apple <br/>
            <input type="radio" name="product" value="Mango" /> Mango <br/>
            <input type="radio" name="product" value="Orange" /> Orange <br/>
            <input type="text" name="amount" maxlength="2" /> Kg <br/>
            <input type="submit" value="Add to Cart">
        </form>
        </br>
        <a href="Checkout.jsp">Checkout</a>
    </body>
</html>

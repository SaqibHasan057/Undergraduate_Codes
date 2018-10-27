<%-- 
    Document   : Checkout.jsp
    Created on : Nov 19, 2016, 4:02:28 PM
    Author     : samsung
--%>

<%@page import="java.util.ArrayList"%>
<%@page import="sukarna.models.CartItem"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <h1>Here is your products</h1>
        <% 
        
            ArrayList<CartItem> cart = (ArrayList<CartItem>)session.getAttribute("cart");
            
            int counter = 1;
            for(CartItem item: cart)
            {
                out.print( String.format("%d. %s - %s Kg </br>", counter,
                        item.getProduct(), item.getAmount()) );
                counter++;
            }
            
        
        %>
    </body>
</html>

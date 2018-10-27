<%-- 
    Document   : createAccount.jsp
    Created on : Nov 19, 2016, 4:26:10 PM
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
        <h1>Create your account!</h1>
        <form method="post" action="CreateAccount.do">
            First Name <input type="text" name="firstName" /><br>
            Last Name <input type="text" name="lastName" /> <br/>
            Username <input type="text" name="username" /> <br/>
            Password <input type="password" name="password" /> <br/>
            <input type="submit" value="Create" />
        </form>
    </body>
</html>

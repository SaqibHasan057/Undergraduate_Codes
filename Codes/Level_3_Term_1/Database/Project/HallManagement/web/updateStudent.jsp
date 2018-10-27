<%-- 
    Document   : updateStudent
    Created on : 20-Dec-2016, 4:09:14 AM
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
        <h1>Create your account!</h1>
        <form method="post" action="StudentUpdateController.do">
            Student_id <input type="text" name="student_id" /><br>
            First Name <input type="text" name="firstName" /><br>
            Last Name <input type="text" name="lastName" /> <br/>
            Father First Name <input type="text" name="fatherFname" /><br>
            Father Last Name <input type="text" name="fatherLname" /><br>
            Mother First Name <input type="text" name="motherFname" /><br>
            Mother Last Name <input type="text" name="motherLname" /><br>
            Street <input type="text" name="street" /><br>
            City <input type="text" name="city" /><br>
            State <input type="text" name="state" /><br>
            PIN <input type="text" name="pin" /><br>
            Guardian Contact Number <input type="text" name="guardian" /><br>
            Date of Birth(MM/DD/YYYY) <input type="text" name="dob" /><br>
            Phone<input type="text" name="phoneNo" /><br>
            Email<input type="text" name="email" /><br>
            <input type="submit" value="Insert" />
        </form>
    </body>
</html>

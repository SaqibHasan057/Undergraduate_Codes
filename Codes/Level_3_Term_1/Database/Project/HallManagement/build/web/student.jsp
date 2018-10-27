<%-- 
    Document   : student
    Created on : 4-Dec-2016, 7:38:17 AM
    Author     : Dipto
--%>

<%@page import="java.util.ArrayList"%>
<%@page import="models.StudentInfo"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Student</title>
    </head>
    <body>
        <center>
        <h1>Create your account!</h1>
        <form method="post" action="StudentInsertController.do">
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
        <br><br><br><br><br>
        <form method="post" action="StudentDeleteController.do">
            Student ID <input type="text" name="ID" /><br>
            <input type="submit" value="Delete" />
        </form>
        <br><br><br><br><br>
        <form method="post" action="StudentViewController.do">
            <input type="submit" value="View" />
        </form>
    
        <h2>View the profiles of all the students</h1>
        <% 
            
            ArrayList<StudentInfo> list = (ArrayList<StudentInfo>) session.getAttribute("studentView");
            if(list==null)
            {
                out.println("");
            }
            else if(list.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|First Name|</td><td>|Last Name|</td><td>"
                        + "|Father Fname|</td><td>|Father Lname|</td><td>|Mother Fname|</td><td>|Mother Lname|</td><td>"
                        + "|Street|</td><td>|City|</td><td>|State|</td><td>|Pin|</td><td>|Guardian Contact No.|</td><td>|Date of Birth|</td><td>|Phone|</td><td>|Email|</td></tr>");
                int count=0;
                for(StudentInfo exe: list)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>"
                            + "<td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getStudentID(),exe.getFirstName(),exe.getLastName(),exe.getFatherFname(),exe.getFatherLname(),
                            exe.getMotherFname(),
                            exe.getMotherLname(),exe.getStreet(),exe.getCity(),exe.getState(),exe.getPin(),
                            exe.getGuardian(),exe.getDOB(),exe.getPhoneNo(),exe.getEmail()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        %>
    </center>
    </body>
</html>

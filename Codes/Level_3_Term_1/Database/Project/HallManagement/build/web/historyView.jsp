<%-- 
    Document   : historyView
    Created on : 15-Dec-2016, 6:20:07 PM
    Author     : Dipto
--%>

<%@page import="models.HistoryInfo"%>
<%@page import="models.StudentInfo"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>History Viewpage</title>
    </head>
    <body>
        <form method="post" action="HistoryController.do">
            Student ID <input type="text" name="student_id" /><br>
            <input type="submit" value="Get Student and Allocation Details" />
        </form>
        <center>
        <h2>The history of the student in the hall</h1>
        <% 
            
            ArrayList<StudentInfo> studentList = (ArrayList<StudentInfo>) session.getAttribute("studentList");
            ArrayList<HistoryInfo> historyList = (ArrayList<HistoryInfo>) session.getAttribute("historyList");
            if(studentList==null || historyList==null )
            {
                out.println("");
            }
            else if(studentList.size()==0 || historyList.size()==0)
            {
                out.println("No records to show.");
            }
            else 
            {
                
                out.println("Student Information<table border=\"1\">");
                out.println("<tr><td>|Row Number|</td><td>|Student ID|</td><td>|First Name|</td><td>|Last Name|</td><td>"
                        + "|Father Fname|</td><td>|Father Lname|</td><td>|Mother Fname|</td><td>|Mother Lname|</td><td>"
                        + "|Street|</td><td>|City|</td><td>|State|</td><td>|Pin|</td><td>|Guardian Contact No.|</td><td>|Date of Birth|</td></tr>");
                int count=0;
                for(StudentInfo exe: studentList)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>"
                            + "<td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getStudentID(),exe.getFirstName(),exe.getLastName(),exe.getFatherFname(),exe.getFatherLname(),
                            exe.getMotherFname(),
                            exe.getMotherLname(),exe.getStreet(),exe.getCity(),exe.getState(),exe.getPin(),
                            exe.getGuardian(),exe.getDOB()));
                    out.println("</tr>");
                }
                out.println("</table>");
                
                out.println("<br/><br/><br/><br/><br/><br/>Allocation History<br/><table>");
                out.println("<tr><td>|Row Number|</td><td>|Allocation ID|</td><td>|Room ID|</td><td>|Seat ID|</td><td>|Start Date|</td><td>"
                        + "|End Date|</td></tr>");
                count=0;
                for(HistoryInfo exe: historyList)
                {
                    count++;
                    out.println("<tr>");
  
                    out.println( String.format( "<td>|%d|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td><td>|%s|</td>",
                            count, exe.getAllocationID(),exe.getRoomID(),exe.getSeatID(),exe.getStartDate(),exe.getEndDate()));
                    out.println("</tr>");
                }
                out.println("</table>");
            }
        %>
    </center>
    </body>
</html>

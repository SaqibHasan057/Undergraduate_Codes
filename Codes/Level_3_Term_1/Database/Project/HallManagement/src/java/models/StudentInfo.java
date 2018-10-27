package models;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Dipto
 */
public class StudentInfo {
    private String student_id;
    private String first_name;
    private String last_name;
    private String father_fname;
    private String father_lname;
    private String mother_fname;
    private String mother_lname;
    private String street;
    private String city;
    private String state;
    private String pin;
    private String guardian_contact_no;
    private String dob;
    private String phoneNo;
    private String email;
    
    public StudentInfo (String student_id,String first_name,String last_name,String father_fname,String father_lname,String mother_fname,String mother_lname,String street,String city,String state,String pin,String guardian_contact_no,String dob,String phoneNo,String email)
    {
        this.student_id=student_id;
        this.first_name=first_name;
        this.last_name=last_name;
        this.father_fname=father_fname;
        this.mother_fname=mother_fname;
        this.mother_lname=mother_lname;
        this.street=street;
        this.city=city;
        this.state=state;
        this.pin=pin;
        this.guardian_contact_no=guardian_contact_no;
        this.dob=dob;
        this.phoneNo=phoneNo;
        this.email=email;
        
    }
    public void setStudentID(String student_id){this.student_id=student_id;}
    public void setFirstName(String first_name){this.first_name=first_name;}
    public void setLastName(String last_name){this.last_name=last_name;}
    public void setFatherFname(String father_fname){this.father_fname=father_fname;}
    public void setFatherLname(String father_lname){this.father_lname=father_lname;}
    public void setMotherFname(String mother_fname){this.mother_fname=mother_fname;}
    public void setMotherLname(String mother_lname){this.mother_lname=mother_lname;}
    public void setStreet (String street){this.street=street;}
    public void setCity(String city){this.city=city;}
    public void setState(String state){this.state=state;}
    public void setPin(String pin){this.pin=pin;}
    public void setGuardian(String Guardian){this.guardian_contact_no=Guardian;}
    public void setDOB(String dob){this.dob=dob;}
    public void setPhoneNo(String phoneNo){this.phoneNo=phoneNo;}
    public void setEmail(String email){this.email=email;}
    
    
    public String getStudentID(){return student_id;}
    public String getFirstName(){return first_name;}
    public String getLastName(){return last_name;}
    public String getFatherFname(){return father_fname;}
    public String getFatherLname(){return father_lname;}
    public String getMotherFname(){return mother_fname;}
    public String getMotherLname(){return mother_lname;}
    public String getStreet(){return street;}
    public String getCity(){return city;}
    public String getState(){return state;}
    public String getPin(){return pin;}
    public String getGuardian(){return guardian_contact_no;}
    public String getDOB(){return dob;}
    public String getPhoneNo(){return phoneNo;}
    public String getEmail(){return email;}
    
    
}

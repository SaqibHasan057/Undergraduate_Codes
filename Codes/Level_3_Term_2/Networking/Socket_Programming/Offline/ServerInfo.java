package sample;

import java.io.Serializable;
import java.util.Date;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ServerInfo implements Serializable{
    private String examName;
    private String examRules;
    private Date startTime;
    private Integer duration;
    private Integer warningTime;
    private String location;
    private Integer studentIDStart;
    private Integer studentIDEnd;
    private Integer backupTime;

    public ServerInfo(String examName,String examRules,Date startTime,int duration,int warningTime,String location,int studentIDStart,int studentIDEnd,int backupTime){
        this.examName=examName;
        this.examRules=examRules;
        this.startTime=startTime;
        this.duration=duration;
        this.warningTime=warningTime;
        this.location=location;
        this.studentIDStart=studentIDStart;
        this.studentIDEnd=studentIDEnd;
        this.backupTime=backupTime;
    }

    public void setExamName(String examName){this.examName=examName;}
    public void setExamRules(String examRules){this.examRules=examRules;}
    public void setStartTime(Date startTime){this.startTime=startTime;}
    public void setDuration(int duration){this.duration=duration;}
    public void setWarningTime(int duration){this.duration=duration;}
    public void setLocation(String location){this.location=location;}
    public void setStudentIDStart(int studentIDStart){this.studentIDStart=studentIDStart;}
    public void setStudentIDEnd(int studentIDEnd){this.studentIDEnd=studentIDEnd;}
    public void setBackupTime(int backupTime){this.backupTime=backupTime;}


    public String getExamName(){return examName;}
    public String getExamRules(){return examRules;}
    public Date getStartTime(){return startTime;}
    public Integer getDuration(){return duration;}
    public Integer getWarningTime(){return warningTime;}
    public String getLocation(){return location;}
    public Integer getStudentIDStart(){return studentIDStart;}
    public Integer getStudentIDEnd(){return studentIDEnd;}
    public Integer getBackupTime(){return backupTime;}

}

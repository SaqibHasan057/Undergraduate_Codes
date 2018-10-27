package sample;

import java.io.Serializable;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ClientInfo implements Serializable {
    private Integer studentID;
    private Integer portNumber;
    private String serverIP;
    private  String ownIP;

    public ClientInfo(int studentID,int portNumber,String serverIP,String ownIP){
        this.studentID=studentID;
        this.portNumber=portNumber;
        this.serverIP=serverIP;
        this.ownIP=ownIP;
    }

    public void setStudentID(Integer studentID){this.studentID=studentID;}
    public void setPortNumber(Integer portNumber){this.portNumber=portNumber;}
    public void setServerIP(String serverIP){this.serverIP=serverIP;}
    public void setOwnIP(String ownIP){this.ownIP=ownIP;}

    public Integer getStudentID(){return studentID;}
    public Integer getPortNumber(){return portNumber;}
    public String getServerIP(){return serverIP;}
    public String getOwnIP(){return ownIP;}

}

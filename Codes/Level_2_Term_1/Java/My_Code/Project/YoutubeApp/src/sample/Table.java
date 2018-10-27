package sample;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.scene.control.Button;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.net.Socket;

/**
 * Created by Dipto on 19/11/2015.
 */
public class Table implements Runnable,Serializable{
    private String NameofVideo;

    public Table(String UserName){
        this.NameofVideo=UserName;
    }

    public String getNameofVideo(){

        return NameofVideo;
    }

    public void setNameofVideo(String name){

        this.NameofVideo=name;
    }



    @Override
    public void run() {

    }

}
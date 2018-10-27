package sample;

import javafx.beans.property.SimpleStringProperty;
import javafx.scene.control.Button;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Created by Dipto on 19/11/2015.
 */
public class client implements Runnable{
    private final SimpleStringProperty ClientName;
    private Socket mysocket;
    private Thread myThread;
    private DataOutputStream meBeingSentMessage;

    public client(String clientName){
        this.ClientName=new SimpleStringProperty(clientName);
    }


    public String getClientName(){
        return ClientName.get();
    }

    public void setClientName(String name){
        ClientName.set(name);
    }

    public void setMysocket(Socket socket) throws IOException {
        this.mysocket = socket;
        meBeingSentMessage = new DataOutputStream(mysocket.getOutputStream());
    }

    public DataOutputStream getMeBeingSentMessage(){
        return meBeingSentMessage;
    }

    public void start(){
        myThread = new Thread(this);
        myThread.start();
    }


    @Override
    public void run() {

    }
}
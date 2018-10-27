package sample;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Created by Dipto on 20/11/2015.
 */
public class Controller2 implements Runnable {
    Main main;
    @FXML
    TextArea textArea;
    Thread clientThread;
    DataInputStream getFromServer;
    DataOutputStream sendNametoServer;
    String theNameOfThisClient;



    public void start() throws InterruptedException {
        clientThread = new Thread(this);
        clientThread.start();
    }

    public void getNameofthisClient(String param){
        this.theNameOfThisClient = param;
    }

    public String printName(){
        return theNameOfThisClient;
    }

    @Override
    public void run() {
        try {
            Socket socket = new Socket("localhost",699);
            getFromServer = new DataInputStream(socket.getInputStream());
            sendNametoServer = new DataOutputStream(socket.getOutputStream());
            sendNametoServer.writeUTF(theNameOfThisClient);

            while(true){
                String getServerMessage = getFromServer.readUTF();
                textArea.setText(getServerMessage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void setMain(Main main){
        this.main = main;
    }
}

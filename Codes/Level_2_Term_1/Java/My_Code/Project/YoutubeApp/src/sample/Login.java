package sample;

import com.sun.org.apache.xpath.internal.SourceTree;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Tab;
import javafx.scene.control.TextField;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Dipto on 29/11/2015.
 */
public class Login {
    Main main;
    @FXML
    private TextField UserName;
    @FXML
    private TextField Password;
    @FXML
    private Button Enter;

    @FXML
    void setEnter(ActionEvent event) throws Exception {
       try {
           Socket socket = new Socket("localhost", 7000);
           ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
           ObjectInputStream input = new ObjectInputStream(socket.getInputStream());
           output.writeObject("CLIENT");
           output.writeObject(UserName.getText());
           output.writeObject(Password.getText());
           Object access = input.readObject();
           access.toString();
           System.out.println(access);
           ArrayList<Table> tableList =(ArrayList<Table>) input.readObject();
           if(access.equals("YES")) {
               System.out.println(access);
               main.showSecondMenu(tableList,socket,input,output);
           }
           //else if(access.equals("NO")) SourceTree
       }
       catch (IOException e){
           e.printStackTrace();
       }
    }

    void setMain(Main main){this.main=main;}

}

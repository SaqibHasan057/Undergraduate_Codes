package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

/**
 * Created by Dipto on 29/11/2015.
 */
public class Register {
    Main main;

    @FXML
    private TextField ClientName;

    @FXML
    private PasswordField Password;

    @FXML
    private PasswordField confirmPassword;

    @FXML
    private Button Register;

    @FXML
    void setRegister(ActionEvent event) throws Exception {
        String s1 = Password.getText();
        String s2 = confirmPassword.getText();
        if(s1.equals(s2))
        {
            try {
                Socket socket = new Socket("localhost", 7000);
                ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
                ObjectInputStream input = new ObjectInputStream(socket.getInputStream());
                output.writeObject("REGISTER");
                output.writeObject(ClientName.getText());
                output.writeObject(Password.getText());
                main.showFirstMenu();
            }
            catch (IOException e){
                e.printStackTrace();
            }
            main.showFirstMenu();

        }
        else
        {
            //Alert notSame = new Alert(Alert.AlertType.valueOf("The passwords are not same"));
        }
        System.out.println("BUTTON WORKS!!!");
    }
    void setMain(Main main){this.main=main;}
}

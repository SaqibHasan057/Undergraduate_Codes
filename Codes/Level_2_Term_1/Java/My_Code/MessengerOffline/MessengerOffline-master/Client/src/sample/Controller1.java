package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

import java.net.Socket;

/**
 * Created by Dipto on 20/11/2015.
 */
public class Controller1 {
    private Main main;
    Socket returnSocket;
    @FXML
    Button connect = new Button();
    @FXML
    TextField service = new TextField();
    @FXML
    void click(ActionEvent event){
            try{
                main.nameOfClient = service.getText();
                main.showMessagePage();
            }catch(Exception e){
                e.printStackTrace();
            }
    }
    @FXML
    public void setMain(Main here){
        this.main = here;
    }
    public String getName(){
        return service.getText();
    }
}

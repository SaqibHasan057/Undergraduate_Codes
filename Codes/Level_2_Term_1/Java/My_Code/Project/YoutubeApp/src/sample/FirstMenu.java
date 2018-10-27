package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

/**
 * Created by Dipto on 29/11/2015.
 */
public class FirstMenu {
    Main main;
    @FXML
    Button Login;
    @FXML
    Button Register;

    @FXML
    void LoginButton(ActionEvent event) throws Exception {
        try {
            main.showLogin();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    void RegisterButton(ActionEvent event) throws Exception {
        try {
            main.showRegister();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void setMain(Main main){
        this.main = main;
    }
}

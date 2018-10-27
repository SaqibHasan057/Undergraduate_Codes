package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.net.Inet4Address;
import java.net.Socket;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ClientStartController {
    private ClientMain main;

    @FXML
    TextField studentID;

    @FXML
    TextField portNumber;

    @FXML
    TextField serverIP;

    @FXML
    Button connect;

    @FXML
    public void connectToServer() throws IOException {
        ClientInfo info = new ClientInfo(Integer.parseInt(studentID.getText()),Integer.parseInt(portNumber.getText()),serverIP.getText(), Inet4Address.getLocalHost().toString());
        main.showClientRun(info);
    }

    public void setMain(ClientMain main){this.main=main;}
}

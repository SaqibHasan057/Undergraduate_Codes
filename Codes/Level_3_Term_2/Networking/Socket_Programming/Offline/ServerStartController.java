package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.util.Date;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ServerStartController {
    Main main;

    @FXML
    private TextField examName;

    @FXML
    private TextArea examRules;

    @FXML
    private TextField startTime;

    @FXML
    private TextField duration;

    @FXML
    private TextField warningTime;

    @FXML
    private TextField studentID;

    @FXML
    private TextField backupTime;

    @FXML
    private TextField fileLocation;

    @FXML
    private Button Done;

    @FXML
    void DoneButton(ActionEvent event) throws Exception {
        try {
            String array[] = studentID.getText().split("-");
            Date startDate = new Date(startTime.getText());
            ServerInfo info = new ServerInfo(examName.getText(),examRules.getText(),startDate,Integer.parseInt(duration.getText()), Integer.parseInt(warningTime.getText()),fileLocation.getText(),Integer.parseInt(array[0]),Integer.parseInt(array[1]),Integer.parseInt(backupTime.getText()));
            System.out.println(info.getExamName());
            main.showServerRun(info);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void setMain(Main main){
        this.main=main;
    }



}

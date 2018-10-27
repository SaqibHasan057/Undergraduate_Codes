package sample;


import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringPropertyBase;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.Callback;

import java.awt.event.ActionEvent;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.String;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.util.Observable;
import java.util.ResourceBundle;


public class Controller implements Initializable,Runnable {
    private Main main;
    private ServerSocket serverSocket;
    Thread serve;
    private DataOutputStream sendToClient;
    private DataInputStream getNameFromClient;
    @FXML
    private TextArea textArea;
    @FXML
    private TableView<client>tableView = new TableView<client>();
    @FXML
    TableColumn<client,String> Name;
    @FXML
    TableColumn<client,String> Action;
    @FXML
    ObservableList<client> data = FXCollections.observableArrayList();
    @Override
    public void initialize(URL url,ResourceBundle rb){
        Name.setCellValueFactory(new PropertyValueFactory<client, String>("ClientName"));
        Name.setCellFactory(TextFieldTableCell.<client>forTableColumn());

        Action.setCellValueFactory(new PropertyValueFactory<client, String>("button"));
        Callback<TableColumn<client, String>, TableCell<client, String>> cellFactory =
                new Callback<TableColumn<client, String>, TableCell<client, String>>() {
                    @Override
                    public TableCell call( final TableColumn<client, String> param ) {
                        final TableCell<client, String> cell = new TableCell<client, String>() {
                            final Button btn = new Button("Select");

                            @Override
                            public void updateItem(String item, boolean empty) {
                                // action of 'Select' button click
                                btn.setOnAction( ( javafx.event.ActionEvent event ) -> {
                                            client temp = getTableView().getItems().get( getIndex() );
                                            System.out.println(temp.getClientName());
                                            DataOutputStream sending = temp.getMeBeingSentMessage();
                                            try {
                                                sending.writeUTF(textArea.getText());
                                            } catch (IOException e) {
                                                e.printStackTrace();
                                            }
                                            textArea.clear();
                                            data.remove(temp);
                                        }
                                );
                                if(empty)setGraphic(null);
                                else setGraphic(btn);
                                setText(null);
                            }
                        };
                        return cell;
                    }
                };
        Action.setCellFactory(cellFactory);
        tableView.setItems(data);
    }
    public Controller(){
        serve = new Thread(this);
        serve.start();

    }

    public void run(){
        try {
            serverSocket = new ServerSocket(699);
        while(true) {
            Socket acceptance = serverSocket.accept();
            getNameFromClient = new DataInputStream(acceptance.getInputStream());
            client yourClient = new client(getNameFromClient.readUTF());
            data.add(yourClient);
            yourClient.setMysocket(acceptance);
            yourClient.start();
        }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setMain(Main main){this.main=main;}
}


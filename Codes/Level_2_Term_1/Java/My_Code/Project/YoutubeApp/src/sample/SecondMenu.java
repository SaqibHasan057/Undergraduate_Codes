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
import java.io.*;
import java.lang.String;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.ResourceBundle;


public class SecondMenu implements Initializable,Runnable {
    Main main;
    private Socket menuSocket;
    private ObjectOutputStream menuOutput;
    private ObjectInputStream menuInput;
    private Thread menuThread;
    public final static int FILE_SIZE = 1000000000;
    @FXML
    private TableView<Table>tableView = new TableView<Table>();
    @FXML
    TableColumn<Table,String> NameOfVideo;
    @FXML
    TableColumn<Table,String> Select;
    @FXML
    ObservableList<Table> data ;
    @Override
    public void initialize(URL url,ResourceBundle rb){
        NameOfVideo.setCellValueFactory(new PropertyValueFactory<Table, String>("NameofVideo"));
        NameOfVideo.setCellFactory(TextFieldTableCell.<Table>forTableColumn());
        Callback<TableColumn<Table, String>, TableCell<Table, String>> cellFactory =
                new Callback<TableColumn<Table, String>, TableCell<Table, String>>() {
                    @Override
                    public TableCell call( final TableColumn<Table, String> param ) {
                        final TableCell<Table, String> cell = new TableCell<Table, String>() {
                            final Button btn = new Button("Play");
                            @Override
                            public void updateItem(String item, boolean empty) {
                                // action of 'Select' button click
                                btn.setOnAction( ( javafx.event.ActionEvent event ) -> {
                                    Table temp = getTableView().getItems().get(getIndex());
                                    String toBeSent = temp.getNameofVideo();
                                    try {
                                        menuOutput.writeObject(toBeSent);
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                    File myFile = new File("D:\\Level_2_Term_1\\Object_Oriented_Programming_Sessional\\YoutubeAppServer\\src\\sample\\MyVideo.mp4");
                                    FileOutputStream fos = null;
                                    try {
                                        fos = new FileOutputStream(myFile);
                                    } catch (FileNotFoundException e) {
                                        e.printStackTrace();
                                    }
                                    int number_of_packets = 0;
                                    try {
                                        number_of_packets =(int)menuInput.readObject();
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    } catch (ClassNotFoundException e) {
                                        e.printStackTrace();
                                    }
                                    System.out.println(number_of_packets);
                                    while(number_of_packets>0) {
                                        try {
                                            byte copy[] = new byte[1024];
                                            Object get = menuInput.readObject();
                                            System.out.println(get.getClass());
                                            copy = (byte[])get;
                                            fos.write(copy);
                                            System.out.println("Got Packet");
                                        } catch (IOException e) {
                                            e.printStackTrace();
                                        } catch (ClassNotFoundException e) {
                                            e.printStackTrace();
                                        }
                                        number_of_packets--;
                                    }
                                    try {
                                        fos.close();
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                    System.out.println(myFile.length());
                                    if (myFile != null) {
                                        System.out.println("FILE HAS BEEN TRANSFERRED");
                                        try {
                                            main.showPlayer(myFile);
                                        } catch (Exception e) {
                                            e.printStackTrace();
                                        }
                                    }
                                });
                                if(empty)setGraphic(null);
                                else setGraphic(btn);
                                setText(null);
                            }
                        };
                        return cell;
                    }
                };
        Select.setCellFactory(cellFactory);
        tableView.setItems(data);
    }
   public void setTableView(ArrayList<Table> fromServer){
        data=FXCollections.observableArrayList(fromServer);
       System.out.println(data);
       tableView.setItems(data);
    }

    public void start(){
        this.menuThread = new Thread(this);
        menuThread.start();
    }

    public void run(){
        while (true){

        }
    }

    public void setMain(Main main){this.main=main;}

    public void setAll(Socket socket,ObjectInputStream input,ObjectOutputStream output){
        this.menuSocket=socket;
        this.menuInput=input;
        this.menuOutput=output;
    }

}


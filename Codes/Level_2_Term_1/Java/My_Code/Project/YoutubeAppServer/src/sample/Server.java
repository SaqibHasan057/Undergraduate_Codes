package sample;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;

import javax.swing.*;
import javax.tools.JavaFileManager;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.util.*;

/**
 * Created by Dipto on 02/12/2015.
 */
public class Server implements Initializable,Runnable {
    private Main main;
    private Thread thread;
    private ServerSocket serverSocket;
    private ArrayList data = new ArrayList();
    private ObservableList<Table> myTable ;
    private Hashtable<String,String> client;
    private HashMap<String,String> link = new HashMap<String, String>();
    private ArrayList<Table> myList = new ArrayList<Table>();

    @FXML
    private Button addFile;



    public void start() throws IOException {
        System.out.println("Hello");
        this.thread = new Thread(this);
        serverSocket = new ServerSocket(7000);
        thread.start();
    }

    @Override
    public void run() {
        System.out.println(client);
        while(true){
            try {
                Socket connectionToClient = serverSocket.accept();
                System.out.println("GOT IT");
                ObjectInputStream getFromClient = new ObjectInputStream(connectionToClient.getInputStream());
                ObjectOutputStream sendtoClient = new ObjectOutputStream(connectionToClient.getOutputStream());
                String type = (String) getFromClient.readObject();
                if (type.equals("CLIENT")) {
                    Object name = getFromClient.readObject();
                    Object password = getFromClient.readObject();
                    password.toString();
                    name.toString();
                    if (client.containsKey(name) && client.containsValue(password)) {
                        sendtoClient.writeObject("YES");
                        //TransferObject transfer = new TransferObject(myTable);
                        sendtoClient.writeObject(myList);
                        ClientHandler clientHandler = new ClientHandler(connectionToClient, getFromClient, sendtoClient, link);
                        data.add(clientHandler);
                        System.out.println(data);
                    }
                }
                else if (type.equals("REGISTER")) {
                    String name = (String) getFromClient.readObject();
                    String password = (String) getFromClient.readObject();
                    System.out.println(name+" "+password);
                    File append = new File("src//sample//ClientList.txt");
                    BufferedWriter out = new BufferedWriter(new FileWriter(append,true));
                    out.write(name+" "+password);
                    out.newLine();
                    out.flush();
                    out.close();
                    client.put(name, password);
                    System.out.println(client);
                }
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        client = new Hashtable();
        try {
            Scanner s = new Scanner(new File("src//sample//ClientList.txt"));
            while(s.hasNext()){
                String name = s.next();
                String password = s.next();
                client.put(name,password);

            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        /*client.put("Saqib", "man");
        client.put("Rukshar", "jew");
        client.put("Duran", "Lord");
        client.put("Rajesh", "sad");*/
        myTable = FXCollections.observableArrayList(
                new Table("Assassins Creed Syndicate"),
                new Table("Witcher 3: The Wild Hunt")
        );
        myList.add(new Table("Assassins Creed Syndicate"));
        myList.add(new Table("Batman Arkham City"));
        myList.add(new Table("Witcher 3: The Wild Hunt"));
        myList.add(new Table("Gintama"));
        link.put("Assassins Creed Syndicate","D://Level_2_Term_1//Object_Oriented_Programming_Sessional//YoutubeAppServer//src//sample/Assassin.mp4");
        link.put("Batman Arkham City","D://Level_2_Term_1//Object_Oriented_Programming_Sessional//YoutubeAppServer//src//sample/Batman.mp4");
        //link.put("Gintama","D://Level_2_Term_1//Object_Oriented_Programming_Sessional//YoutubeAppServer//src/sample/Gintama.mp4");
        link.put("Witcher 3 The Wild Hunt","D://Level_2_Term_1//Object_Oriented_Programming_Sessional//YoutubeAppServer//src/sample/Witcher3.mp4");
    }

    @FXML
    public void addAllFiles(ActionEvent event){
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("//User//Dipto"));
        int result = fileChooser.showOpenDialog(new JFrame());
        if(result==fileChooser.APPROVE_OPTION) {
            File add = fileChooser.getSelectedFile();
            String name = add.getName();
            name = name.substring(0,name.length()-4);
            if(link.containsKey(name)==false)link.put(name, add.getAbsolutePath());
            else System.out.println("Repeat");
            System.out.println(link);
        }
    }






    public void setMain(Main main){
        this.main=main;
    }
}

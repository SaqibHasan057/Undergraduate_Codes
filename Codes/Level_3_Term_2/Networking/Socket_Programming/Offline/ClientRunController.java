package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.text.TextFlow;
import javafx.stage.FileChooser;

import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.io.*;
import java.net.Socket;
import java.util.Date;
import java.util.Scanner;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ClientRunController implements Runnable{
    private ClientInfo info;
    private ClientMain main;
    private Socket s = null;
    private BufferedReader br = null;
    private PrintWriter pr = null;
    private ObjectInputStream objectInputStream = null;
    private ObjectOutputStream objectOutputStream = null;
    private Thread thread;
    private ServerInfo serverInfo;

    @FXML
    TextArea textArea;




    public void start() throws IOException {
        System.out.println("Thread Start");
        this.thread = new Thread(this);
        this.thread.start();
    }

    @Override
    public void run() {
        String foldername=null;

        try
        {
            s=new Socket(info.getServerIP(),info.getPortNumber());

            objectInputStream = new ObjectInputStream(s.getInputStream());
            objectOutputStream = new ObjectOutputStream(s.getOutputStream());
            JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
            jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

            int returnValue = jfc.showOpenDialog(null);

            if (returnValue == JFileChooser.APPROVE_OPTION) {
                foldername = jfc.getCurrentDirectory().getAbsolutePath();
            }

        }
        catch(Exception e)
        {
            System.err.println("Problem in connecting with the server. Exiting main.");
            return;
        }

        Scanner input = new Scanner(System.in);
        String strSend = null, strRecv = null;

        try
        {
            objectOutputStream.writeObject(info);
            String enable = (String)objectInputStream.readObject();
            if(enable.equals("invalid")){
                textArea.appendText("Please enter a valid Student ID");
                thread.sleep(10000);
                cleanUp();
                main.showClientStart();
            }
            serverInfo = (ServerInfo)objectInputStream.readObject();
            System.out.println(serverInfo.getExamName());

            textArea.appendText("Exam Name:"+serverInfo.getExamName()+"\n");
            textArea.appendText("Exam Rules:"+serverInfo.getExamRules()+"\n");
            textArea.appendText("Start time:"+serverInfo.getStartTime().toString()+"\n");
            textArea.appendText("Duration:"+serverInfo.getDuration()+"\n");
            textArea.appendText("Backup Time:"+serverInfo.getBackupTime()+"\n");
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.err.println("Error in reading from the socket. Exiting main.");
            //cleanUp();
            System.exit(0);
        }

        try
        {
            System.out.println("First Count");
            File myFile = new File(foldername+"/"+info.getStudentID()+"mydoc.doc");
            FileOutputStream fos = null;
            try {
                fos = new FileOutputStream(myFile);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
            int number_of_packets = 0;
            try {
                number_of_packets = (int) objectInputStream.readObject();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            System.out.println(number_of_packets);
            int current_packet = 1;
            while (current_packet <= number_of_packets) {
                try {
                    byte copy[] = new byte[1024];
                    int packet_got = 0;
                    packet_got = (int) objectInputStream.readObject();
                    Object get = objectInputStream.readObject();
                    copy = (byte[]) get;

                        System.out.println("Got Packet " + packet_got);
                        fos.write(copy);

                        current_packet++;
                        //Thread.sleep(100);
                    } catch (ClassNotFoundException e1) {
                    e1.printStackTrace();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
            try {
                fos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println(myFile.length());
            System.out.println("Exited first count");
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.err.println("Could not transfer file.");
        }

        textArea.appendText("Exam has started!\n");

        Date date = new Date();
        System.out.println(date.toString());
        long endTime = serverInfo.getStartTime().getTime()+serverInfo.getDuration()*60*1000;
        long warningTime = serverInfo.getStartTime().getTime()+serverInfo.getWarningTime()*60*1000;

        while(true){
            String getCurrentTimeStatus="";
            try {
                 getCurrentTimeStatus = (String)objectInputStream.readObject();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }

            if(getCurrentTimeStatus.equals("timeAlmostOver"))textArea.appendText("The exam is almost over\n");

            if(getCurrentTimeStatus.equals("timeOver")){
                textArea.appendText("Exam is over\n");

                try {
                    File myFile = new File(foldername+"/"+info.getStudentID()+"mydoc.doc");
                    int length = 1024;
                    byte[] packets = null;
                    FileInputStream fis = new FileInputStream(myFile);
                    System.out.println(myFile.length());
                    int number_of_chunks = (int) myFile.length() / (1024);
                    if(myFile.length()%(1024)!=0)number_of_chunks++;
                    int fileSize = (int) myFile.length();
                    objectOutputStream.writeObject(number_of_chunks);
                    int current_packet = 1;
                    while (fileSize > 0) {
                        if (fileSize < (1024)) length = fileSize;
                        packets = new byte[length];
                        fis.read(packets);
                        objectOutputStream.writeObject(current_packet);
                        objectOutputStream.writeObject(packets);
                        current_packet++;
                        fileSize -= length;
                        System.out.println(fileSize);
                        System.out.println("ACKNOWLEDGED " + current_packet);
                    }
                    fis.close();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                System.out.println("File Sent Successfully!!");

                break;
            }




            try {

                strRecv = (String)objectInputStream.readObject();

                if(strRecv.equals("TIMELEFT")){
                    textArea.appendText("You have only "+(endTime-System.currentTimeMillis())/1000+" seconds left!!"+"\n");
                }
                else if(!strRecv.equals("")){
                    textArea.appendText(strRecv+"\n");
                }

                thread.sleep(serverInfo.getBackupTime()*1000);
                System.out.println("Sleep Over");


                try {
                    File myFile = new File(foldername+"/"+info.getStudentID()+"mydoc.doc");
                    int length = 1024;
                    byte[] packets = null;
                    FileInputStream fis = new FileInputStream(myFile);
                    System.out.println(myFile.length());
                    int number_of_chunks = (int) myFile.length() / (1024);
                    if(myFile.length()%(1024)!=0)number_of_chunks++;
                    int fileSize = (int) myFile.length();
                    objectOutputStream.writeObject(number_of_chunks);
                    int current_packet = 1;
                    while (fileSize > 0) {
                        if (fileSize < (1024)) length = fileSize;
                        packets = new byte[length];
                        fis.read(packets);
                        objectOutputStream.writeObject(current_packet);
                        objectOutputStream.writeObject(packets);
                        current_packet++;
                        fileSize -= length;
                        System.out.println(fileSize);
                        System.out.println("ACKNOWLEDGED " + current_packet);
                    }
                    fis.close();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                System.out.println("File Sent Successfully!!");
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }


        }


        try {
            cleanUp();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void cleanUp() throws IOException {
        this.objectInputStream.close();
        this.objectOutputStream.close();
        this.s.close();
    }
    public void setMain(ClientMain main){this.main=main;}

    public void setInfo(ClientInfo info){this.info=info;}
}

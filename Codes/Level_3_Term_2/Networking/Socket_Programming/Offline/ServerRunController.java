package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextField;
import sample.Main;
import sample.ServerInfo;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Optional;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ServerRunController implements Runnable {

    private ServerInfo info;
    private Main main;
    private int workerThreadCount=0;
    private Thread thread;
    private int id ;
    private ArrayList<WorkerThread>workerThreadArrayList;
    private HashMap<String,Integer> mapOfUsers;

    @FXML
    private TextField updateBox;

    @FXML
    private Button update;


    public ServerRunController(){
    }

    public void start() throws IOException {
        System.out.println("Hello");
        id=0;
        workerThreadArrayList = new ArrayList<>();
        mapOfUsers = new HashMap<>();
        this.thread = new Thread(this);
        thread.start();
    }

    @Override
    public void run() {

        try
        {
            ServerSocket ss = new ServerSocket(5555);
            System.out.println("Server has been started successfully.");

            while(true)
            {
                Socket s = ss.accept();		//TCP Connection
                ObjectOutputStream outputStream = new ObjectOutputStream(s.getOutputStream());
                ObjectInputStream inputStream = new ObjectInputStream(s.getInputStream());
                ClientInfo clientInfo = (ClientInfo)inputStream.readObject();

                if(clientInfo.getStudentID()<=info.getStudentIDEnd() && clientInfo.getStudentID()>=info.getStudentIDStart()) {

                    outputStream.writeObject("OK");
                    id++;
                    boolean alreadyThere;
                    if(mapOfUsers.containsValue(clientInfo.getStudentID()))alreadyThere=true;
                    else{
                        alreadyThere = false;
                        File dir = new File(String.valueOf(clientInfo.getStudentID()));
                        dir.mkdir();
                    }
                    WorkerThread wt = new WorkerThread(this, s, clientInfo.getStudentID(), info, inputStream, outputStream, alreadyThere);
                    Thread t = new Thread(wt);
                    t.start();
                    workerThreadArrayList.add(wt);
                    workerThreadCount++;
                    mapOfUsers.put(clientInfo.getOwnIP(), clientInfo.getStudentID());
                    System.out.println(clientInfo.getOwnIP() + " " + clientInfo.getStudentID());
                    System.out.println(workerThreadCount);
                    System.out.println("Client [" + id + "] is now connected. No. of worker threads = " + workerThreadCount);
                }
                else{
                    outputStream.writeObject("invalid");
                    s.close();
                }
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.err.println("Problem in ServerSocket operation. Exiting main.");
        }
    }

    public void setMain(Main main){this.main=main;}
    public void setServerInfo(ServerInfo info){this.info=info;}

    @FXML
    public void sendUpdate(){
        String str = updateBox.getText();
        for(int i=0;i<workerThreadArrayList.size();i++){
            workerThreadArrayList.get(i).setUpdate(str);
        }
    }

    @FXML
    public void sendWarning(){
        Date date = new Date();
        String str = "TIMELEFT";
        for(int i=0;i<workerThreadArrayList.size();i++){
            workerThreadArrayList.get(i).setUpdate(str);
        }
    }
}

class WorkerThread implements Runnable
{
    private Socket socket;
    private InputStream is;
    private OutputStream os;
    private ObjectInputStream objectInputStream;
    private ObjectOutputStream objectOutputStream;
    private ServerInfo info;
    private ServerRunController serverRunController;
    private boolean alreadyExists ;

    private String update;

    private int id = 0;

    public WorkerThread(ServerRunController serverRunController,Socket s, int id, ServerInfo info, ObjectInputStream objectInputStream, ObjectOutputStream objectOutputStream, boolean exists)
    {
        this.socket = s;
        this.id=id;
        this.info=info;
        this.objectInputStream=objectInputStream;
        this.objectOutputStream=objectOutputStream;
        this.serverRunController = serverRunController;
        update = "";
        this.alreadyExists=exists;

    }



    public void run()
    {
        try {

            objectOutputStream.writeObject(info);
            System.out.println("1");
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }


        while (true) {
            Date currentTime = new Date();
            if (currentTime.getTime() >= info.getStartTime().getTime()) {
                try {
                    File myFile;
                    if(alreadyExists)myFile = new File(id+"/answerDoc.doc");
                    else myFile = new File(info.getLocation());
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
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                    return;

                } catch (IOException e1) {
                    e1.printStackTrace();
                    return;

                }
                System.out.println("File Sent Successfully!!");
                break;
            }
        }

        long endTime = info.getStartTime().getTime()+info.getDuration()*60*1000;
        long warningTime = info.getStartTime().getTime()+info.getWarningTime()*60*1000;
        System.out.println(endTime);



        while(true) {
            Date date1 = new Date();
            System.out.println(date1.getTime());
            try {
                if(date1.getTime()>=endTime) objectOutputStream.writeObject("timeOver");
                else if (date1.getTime()>=warningTime) objectOutputStream.writeObject("timeAlmostOver");
                else objectOutputStream.writeObject("");
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
            if (date1.getTime() >= endTime) {
                try {
                    objectOutputStream.writeObject(update);
                    update = "";
                    System.out.println("update sent");
                    System.out.println("First Count");

                    int number_of_packets = 0;
                    try {
                        number_of_packets = (int) objectInputStream.readObject();
                    } catch (IOException e) {
                        e.printStackTrace();
                        return;

                    } catch (ClassNotFoundException e) {
                        e.printStackTrace();
                        return;

                    }
                    System.out.println(number_of_packets);
                    File myFile = new File(id+"/answerDoc.doc");
                    FileOutputStream fos = null;
                    try {
                        fos = new FileOutputStream(myFile);
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                        return;

                    }
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
                            return;

                        } catch (IOException e1) {
                            e1.printStackTrace();
                            return;

                        }
                        }
                    try {
                        fos.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                        return;

                    }
                    System.out.println(myFile.length());
                    System.out.println("Exited first count");
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                    System.err.println("Could not transfer file.");
                    close();
                    return;

                }
                System.out.println("This Exam has finally Ended!!s");
                break;
            }






            try {
                objectOutputStream.writeObject(update);
                update = "";
                System.out.println("update sent");
                System.out.println("First Count");

                int number_of_packets = 0;
                try {
                    number_of_packets = (int) objectInputStream.readObject();
                } catch (IOException e) {
                    e.printStackTrace();
                    return;

                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                    return;

                }
                System.out.println(number_of_packets);
                File myFile = new File(id+"/answerDoc.doc");
                FileOutputStream fos = null;
                try {
                    fos = new FileOutputStream(myFile);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                    continue;
                }
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
                        return;

                    } catch (IOException e1) {
                        e1.printStackTrace();
                        return;

                    }
                }
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }
                System.out.println(myFile.length());
                System.out.println("Exited first count");
            }
            catch(Exception e)
            {
                e.printStackTrace();
                System.err.println("Could not transfer file.");
                close();
                return;

            }

        }





        /*TestServer.workerThreadCount--;
        System.out.println("Client [" + id + "] is now terminating. No. of worker threads = "
                + TestServer.workerThreadCount);*/
    }

    public void close(){
        try
        {
            this.is.close();
            this.os.close();
            this.socket.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public void setUpdate(String update){this.update=update;}
}

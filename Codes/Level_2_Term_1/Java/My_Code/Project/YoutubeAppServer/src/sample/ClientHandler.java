package sample;

import java.io.*;
import java.net.Socket;
import java.util.HashMap;

/**
 * Created by Dipto on 02/12/2015.
 */
public class ClientHandler implements Serializable,Runnable {
    private Socket mysocket;
    private ObjectInputStream myInput;
    private ObjectOutputStream myOuput;
    private HashMap<String,String> myLink;
    private Thread mythread;


    public ClientHandler(Socket socket,ObjectInputStream input,ObjectOutputStream output,HashMap<String,String> link){
        this.mysocket=socket;
        this.myInput=input;
        this.myOuput=output;
        this.myLink=link;
        mythread=new Thread(this);
        mythread.start();
    }

    @Override
    public void run() {
        while(true){
            System.out.println("HEY");
            if(mysocket==null) System.out.println("OKAY0");
            String read = null;
            try {
                read = (String)myInput.readObject();
                System.out.println(read);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            String path = myLink.get(read);
            System.out.println(path);
            try {
                File myFile = new File (path);
                int length=1024;
                byte[] packets = null;
                FileInputStream fis = new FileInputStream(myFile);
                System.out.println(myFile.length());
                int number_of_chunks = (int)myFile.length()/(1024);
                number_of_chunks++;
                int fileSize = (int) myFile.length();
                myOuput.writeObject(number_of_chunks);
                while(fileSize>0){
                    if(fileSize<(1024))length=fileSize;
                    packets = new byte[length];
                    fis.read(packets);
                    myOuput.writeObject(packets);
                    fileSize-=length;
                    System.out.println(fileSize);
                    System.out.println("Successful");
                }
                System.out.println("File sent");
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}


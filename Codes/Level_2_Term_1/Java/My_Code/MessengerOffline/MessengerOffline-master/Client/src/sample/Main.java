package sample;

import com.sun.org.apache.xpath.internal.SourceTree;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import javax.sound.midi.Soundbank;
import java.io.IOException;
import java.net.Socket;

public class Main extends Application {
    Stage stage;
    Socket mysocket;
    public String nameOfClient;

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        showLoginPage();
    }

    public void showLoginPage() throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("ClientLoginFXML.fxml"));
        Parent root = loader.load();
        Controller1 controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,600,400);
        stage.setScene(scene);
        stage.setTitle("Login Page");
        stage.show();
    }

    public void showMessagePage()throws Exception{
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("MessageGotFXML.fxml"));
        Parent root = loader.load();
        Controller2 controller2 = loader.getController();
        controller2.getNameofthisClient(nameOfClient);
        controller2.start();
        controller2.setMain(this);
        Scene scene = new Scene(root,600,400);
        stage.setScene(scene);
        stage.setTitle(nameOfClient);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

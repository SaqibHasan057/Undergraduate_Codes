package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("ServerFXML.fxml"));
        Parent root = loader.load();
        Controller controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,800,640);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Server");
        primaryStage.show();
    }


    public static void main(String[] args) throws Exception{
        launch(args);
    }
}

package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    Stage serverStage;

    @Override
    public void start(Stage primaryStage) throws Exception{
        serverStage = primaryStage;
        setServerpage();
    }


    public static void main(String[] args) {
        launch(args);
    }

    public void setServerpage() throws IOException {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("sample.fxml"));
        Parent root = loader.load();
        Server controller = loader.getController();
        controller.setMain(this);
        controller.start();
        Scene scene = new Scene(root,600,400);
        serverStage.setScene(scene);
        serverStage.setTitle("Login Page");
        serverStage.show();
    }
}

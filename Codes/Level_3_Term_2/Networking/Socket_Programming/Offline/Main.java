package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    Stage stage;

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        stage.setResizable(false);
        showServerStart();
    }

    public void showServerStart() throws IOException {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("ServerStart.fxml"));
        Parent root = loader.load();
        ServerStartController controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,800,640);
        stage.setScene(scene);
        stage.setTitle("Server Start");
        stage.show();
    }

    public void showServerRun(ServerInfo info) throws IOException {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("ServerRun.fxml"));
        Parent root = loader.load();
        ServerRunController controller = loader.getController();
        controller.setServerInfo(info);
        controller.setMain(this);
        controller.start();
        Scene scene = new Scene(root,800,640);
        stage.setScene(scene);
        stage.setTitle("Server Run");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
        System.exit(0);
    }
}

package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

/**
 * Created by Dipto on 02/03/2017.
 */
public class ClientMain extends Application {


        Stage stage;

        @Override
        public void start(Stage primaryStage) throws Exception{
            stage = primaryStage;
            stage.setResizable(false);
            showClientStart();
        }



        public void showClientStart() throws IOException {
            FXMLLoader loader= new FXMLLoader();
            loader.setLocation(getClass().getResource("ClientStart.fxml"));
            Parent root = loader.load();
            ClientStartController controller = loader.getController();
            controller.setMain(this);
            Scene scene = new Scene(root,800,640);
            stage.setScene(scene);
            stage.setTitle("Client Start");
            stage.show();
        }

        public void showClientRun(ClientInfo info) throws IOException {
            FXMLLoader loader= new FXMLLoader();
            loader.setLocation(getClass().getResource("ClientRun.fxml"));
            Parent root = loader.load();
            ClientRunController controller = loader.getController();
            controller.setInfo(info);
            controller.setMain(this);
            controller.start();
            Scene scene = new Scene(root,800,640);
            stage.setScene(scene);
            stage.setTitle("Client Run");
            stage.show();
        }



        public static void main(String[] args) {
            launch(args);
            System.exit(0);
        }


}

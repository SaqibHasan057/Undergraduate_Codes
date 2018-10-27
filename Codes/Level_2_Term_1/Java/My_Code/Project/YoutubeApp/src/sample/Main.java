package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;

import java.io.File;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class Main extends Application {
    Stage stage;
    Stage playerStage = new Stage();

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        showFirstMenu();
    }

    public void showPlayer2() {
        Media movie = new Media(new File("D://Level_2_Term_1//Object_Oriented_Programming_Sessional//YoutubeApp//src//sample/Assassin.mp4").toURI().toString());
        MediaPlayer mov = new MediaPlayer(movie);
        MediaView m = new MediaView(mov);
        Group root = new Group();
        root.getChildren().add(m);
        mov.play();
        Scene scene = new Scene(root,800,640);
        stage.setScene(scene);
        stage.show();
    }

    public void showFirstMenu() throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("FirstMenu.fxml"));
        Parent root = loader.load();
        FirstMenu controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,800,640);
        stage.setScene(scene);
        stage.setTitle("First Menu");
        stage.show();
    }

    public void showLogin() throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("Login.fxml"));
        Parent root = loader.load();
        Login controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,600,400);
        stage.setScene(scene);
        stage.setTitle("Login Page");
        stage.show();
    }

    public void showRegister() throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("Register.fxml"));
        Parent root = loader.load();
        Register controller = loader.getController();
        controller.setMain(this);
        Scene scene = new Scene(root,600,400);
        stage.setScene(scene);
        stage.setTitle("Register Page");
        stage.show();
    }

    public void showPlayer(File file) throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("Player.fxml"));
        Parent root = loader.load();
        Player controller = loader.getController();
        controller.setMain(this);
        controller.setPath(file);
        controller.start();
        Scene scene = new Scene(root,800,640);
        playerStage.setScene(scene);
        playerStage.setTitle("Player Page");
        playerStage.show();
        controller.stop();
    }
    public void showSecondMenu(ArrayList<Table> l, Socket socket, ObjectInputStream streamIn,ObjectOutputStream streamOut) throws Exception {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("SecondMenu.fxml"));
        Parent root = loader.load();
        SecondMenu controller = loader.getController();
        controller.setTableView(l);
        controller.setAll(socket,streamIn,streamOut);
        controller.setMain(this);
        controller.start();
        Scene scene = new Scene(root,800,640);
        stage.setScene(scene);
        stage.setTitle("Secondmenu Page");
        stage.show();
    }



    public static void main(String[] args) {
        launch(args);
    }
}

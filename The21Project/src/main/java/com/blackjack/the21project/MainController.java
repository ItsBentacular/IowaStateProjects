package com.blackjack.the21project;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import java.io.File;

import java.io.IOException;
import java.net.URISyntaxException;

public class MainController {
    private Stage stage;
    private Scene scene;
    private Parent root;

    public void MainMenu(ActionEvent event) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/com/blackjack/the21project/Scene1.fxml"));
        stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void openSettings(ActionEvent event) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/com/blackjack/the21project/Scene2.fxml"));
        stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    public void gameStart(ActionEvent event) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/com/blackjack/the21project/GameScene.fxml"));
        stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    private void changeScene(String fxmlPath, ActionEvent event) throws IOException {
        // Load the new FXML file
        Parent root = FXMLLoader.load(getClass().getResource(fxmlPath));

        // Get the current stage from the event source (button press)
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();

        // Create and set the new scene
        Scene scene = new Scene(root);
        stage.setScene(scene);

        // Reapply fullscreen mode
        stage.setFullScreen(true);

        stage.show();
    }

    @FXML
    private void playGame(ActionEvent event) throws IOException {
        gameStart(event);
    }

    @FXML
    private void quitGame() {
        Platform.exit();
    }


    // private Slider volumeSlider;


    @FXML
    private Button resolutionButton;

    /* public static void mediaPlayer() {
        try {
            String path = "/sounds/main_menu.mp3";
            Media media = new Media(MainController.class.getResource(path).toURI().toString());
            MediaPlayer mediaPlayer = new MediaPlayer(media);
            mediaPlayer.play();
        } catch (Exception e) {
            System.err.println("Error playing audio: " + e.getMessage());
        }
    }
*/
    @FXML
    private Slider volumeSlider;

    private static MediaPlayer mediaPlayer;

    public void initialize() {
        if (mediaPlayer == null) {
            try {
                String path = "/sounds/main_menu.mp3";
                Media media = new Media(getClass().getResource(path).toURI().toString());
                mediaPlayer = new MediaPlayer(media);
                mediaPlayer.setCycleCount(MediaPlayer.INDEFINITE);
                mediaPlayer.setVolume(0.5);
                mediaPlayer.play();
            } catch (Exception e) {
                System.err.println("Error loading media: " + e.getMessage());
            }
        }

        if (volumeSlider != null) {
            volumeSlider.setValue(mediaPlayer.getVolume() * 100);
            volumeSlider.valueProperty().addListener((obs, oldVal, newVal) -> {
                mediaPlayer.setVolume(newVal.doubleValue() / 100.0);
            });
        }
    }

    public static MediaPlayer getMediaPlayer() {
        return mediaPlayer;
    }





}
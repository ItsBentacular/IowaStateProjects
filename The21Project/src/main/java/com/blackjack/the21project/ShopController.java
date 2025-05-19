package com.blackjack.the21project;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.io.IOException;

public class ShopController {

    @FXML
    private Label balanceLabel;

    private Money money;
    private Game game;

    public void setGame(Game game) {
        this.game = game;
        setMoney(game.getMoney());
    }

    public void setMoney(Money money) {
        this.money = money;
        updateBalanceLabel();
    }

    private void updateBalanceLabel() {
        if(money != null) {
            balanceLabel.setText("Balance: $" + money.getBalance());
        }
    }

    @FXML
    public void initialize() {
        // This method is called after the FXML is loaded
        if (money != null) {
            updateBalanceLabel();
        }
    }


    @FXML
    private void closeShop(ActionEvent event) {
        try {
            // Load the new scene from FXML
            FXMLLoader loader = new FXMLLoader(getClass().getResource("GameScene.fxml"));
            Parent Root = loader.load();

            GameController gameController = loader.getController();
            gameController.setGame(game);

            // Get the current stage from the button's event
            Stage currentStage = (Stage) ((Node) event.getSource()).getScene().getWindow();


            // Set the new scene
            Scene Scene = new Scene(Root);
            currentStage.setScene(Scene);
            currentStage.setTitle("Game"); // Optional: change window title

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

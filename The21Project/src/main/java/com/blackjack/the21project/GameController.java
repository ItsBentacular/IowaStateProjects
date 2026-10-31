package com.blackjack.the21project;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.io.IOException;
import java.util.List;

public class GameController {
    @FXML
    private HBox dealerCardsArea;
    @FXML
    private HBox playerCardsArea;
    @FXML
    private Label dealerScoreLabel;
    @FXML
    private Label playerScoreLabel;
    @FXML
    private Label gameStatusLabel;
    @FXML
    private Button hitButton;
    @FXML
    private Button standButton;
    @FXML
    private Button newGameButton;
    @FXML
    private Label balanceLabel;
    @FXML
    private TextField betInput;
    @FXML
    private Button placeBetButton;
    @FXML
    private Label currentBetLabel;


    private Game game;

    @FXML
    public void initialize() {
        game = new Game();
        updateMoneyDisplay();

        // Create context menu for game options
        ContextMenu gameMenu = new ContextMenu();
        MenuItem newGameItem = new MenuItem("New Game");
        MenuItem returnToMainItem = new MenuItem("Return to Main Menu");
        SeparatorMenuItem separator = new SeparatorMenuItem();
        MenuItem exitItem = new MenuItem("Exit Game");

        // Add actions with immediate money update for new game
        newGameItem.setOnAction(event -> {
            handleNewGame();
            updateMoneyDisplay();  // Update money display right after new game starts
            betInput.clear();     // Clear any existing bet input
            currentBetLabel.setText("Current Bet: $0"); // Reset current bet display
        });
        returnToMainItem.setOnAction(event -> returnToMainMenu());
        exitItem.setOnAction(event -> Platform.exit());

        // Add all items to menu
        gameMenu.getItems().addAll(newGameItem, separator, returnToMainItem, exitItem);

        // Style the menu
        String menuStyle = "-fx-font-size: 14px;";
        gameMenu.setStyle(menuStyle);
        newGameItem.setStyle(menuStyle);
        returnToMainItem.setStyle(menuStyle);
        exitItem.setStyle(menuStyle);

        // Add ESC key handler
        Platform.runLater(() -> {
            Scene scene = playerCardsArea.getScene();
            scene.setOnKeyPressed(event -> {
                if (event.getCode() == KeyCode.ESCAPE) {
                    Window window = scene.getWindow();

                    // Show menu first to get its dimensions
                    gameMenu.show(window, 0, 0);

                    // Calculate center position
                    double centerX = window.getX() + (window.getWidth() - gameMenu.getWidth()) / 2;
                    double centerY = window.getY() + (window.getHeight() - gameMenu.getHeight()) / 2;

                    // Reposition menu
                    gameMenu.hide();
                    gameMenu.show(window, centerX, centerY);
                }
            });
        });

        // Hide original new game button
        newGameButton.setVisible(false);
        newGameButton.setManaged(false);

        // Initialize rest of the game UI
        disableGameButtons(true);
        updatePlayerCards();
        updateDealerCards(false);
    }

    private void returnToMainMenu() {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("/com/blackjack/the21project/Scene1.fxml"));
            Scene scene = playerCardsArea.getScene();
            Stage stage = (Stage) scene.getWindow();
            stage.setScene(new Scene(root));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setGame(Game game) {
        this.game = game;
        updateMoneyDisplay();
    }




    private void updateMoneyDisplay() {
        balanceLabel.setText("Balance: $" + game.getMoney().getBalance());
        currentBetLabel.setText("Current Bet: $" + game.getMoney().getCurrentBet());
    }

    private void disableGameButtons(boolean disabled) {
        hitButton.setDisable(disabled);
        standButton.setDisable(disabled);
    }

    @FXML
    private void handlePlaceBet() {
        try {
            int betAmount = Integer.parseInt(betInput.getText());
            if (betAmount > 0 && betAmount <= game.getMoney().getBalance()) {
                game.getMoney().placeBet(betAmount);
                game.startNewHand();  // Use startNewHand instead of startNewGame so money doesn't reset.
                updateMoneyDisplay();
                updatePlayerCards();
                updateDealerCards(false);
                disableGameButtons(false);
                placeBetButton.setDisable(true);
                betInput.setDisable(true);
            } else {
                gameStatusLabel.setText("Invalid bet amount!");
            }
        } catch (NumberFormatException e) {
            gameStatusLabel.setText("Please enter a valid number!");
        }
    }



    private void updatePlayerCards() {
        playerCardsArea.getChildren().clear();
        for (Card card : game.getPlayerHand()) {
            playerCardsArea.getChildren().add(card.getImageView());
        }
        playerScoreLabel.setText("Hand: " + game.getPlayerScore());
    }

    private void updateDealerCards(boolean showAll) {
        dealerCardsArea.getChildren().clear();
        List<Card> dealerCards = game.getDealerHand();

        for (int i = 0; i < dealerCards.size(); i++) {
            if (i == 0 || showAll) {
                dealerCardsArea.getChildren().add(dealerCards.get(i).getImageView());
            } else {
                // Add face-down card
                ImageView faceDownCard = createFaceDownCard();
                dealerCardsArea.getChildren().add(faceDownCard);
            }
        }

        if (showAll) {
            dealerScoreLabel.setText("Hand: " + game.getDealerScore());
        } else {
            dealerScoreLabel.setText("Hand: ?");
        }
    }

    private ImageView createFaceDownCard() {
        String backImagePath = "/com/blackjack/the21project/images/cards/card_back.png";
        Image backImage = new Image(getClass().getResourceAsStream(backImagePath));
        ImageView imageView = new ImageView(backImage);
        imageView.setFitWidth(193.5);  // Match with Card class CARD_WIDTH or else it looks weird
        imageView.setFitHeight(282); // Match with Card class CARD_HEIGHT or else it looks weird
        imageView.setPreserveRatio(true);
        return imageView;
    }

    @FXML
    private void handleHit() {
        game.playerHit();
        updatePlayerCards();

        if (game.isPlayerBust()) {
            gameOver("Bust! You lose!");
        }
    }

    @FXML
    private void handleStand() {
        game.dealerPlay();
        updateDealerCards(true);

        String result = game.determineWinner();
        gameOver(result);
    }

    @FXML
    private void handleNewGame() {
        startNewGame();
    }

    private void startNewGame() {
        game.startNewGame();
        updatePlayerCards();
        updateDealerCards(false);
        gameStatusLabel.setText("");
        hitButton.setDisable(false);
        standButton.setDisable(false);
    }

    private void gameOver(String message) {
        gameStatusLabel.setText(message);
        hitButton.setDisable(true);
        standButton.setDisable(true);
        placeBetButton.setDisable(false);
        betInput.setDisable(false);
        updateMoneyDisplay();
    }
    @FXML
    private void openShop(ActionEvent event) {
        try {
            // Load the new scene from FXML
            FXMLLoader loader = new FXMLLoader(getClass().getResource("Shop.fxml"));
            Parent shopRoot = loader.load();
            ShopController shopController = loader.getController();
            shopController.setMoney(game.getMoney());
            shopController.setGame(game);

            // Get the current stage from the button's event
            Stage currentStage = (Stage) ((Node) event.getSource()).getScene().getWindow();

            // Set the new scene
            Scene shopScene = new Scene(shopRoot);
            currentStage.setScene(shopScene);
            currentStage.setTitle("Shop"); // Optional: change window title

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
package com.blackjack.the21project;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class Card {
    private final String suit;
    private final int value;
    private final ImageView imageView;
    private static final double CARD_WIDTH = 193.5;
    private static final double CARD_HEIGHT = 282;

    public Card(String suit, int value) {
        this.suit = suit;
        this.value = value;

        // Convert number value to word format for game logic
        String valueWord = convertValueToWord(value);

        // Construct image's path using the correct naming format MAKE SURE TO USE THE SAME FORMAT OR CRASH
        String imagePath = "/com/blackjack/the21project/images/cards/" +
                valueWord + "_of_" + suit + ".png";

        // Try to load the card image, use placeholder if not found
        Image image;
        try {
            var imageStream = getClass().getResourceAsStream(imagePath);
            if (imageStream != null) {
                image = new Image(imageStream);
            } else {
                image = createPlaceholderImage(valueWord, suit);
            }
        } catch (Exception e) {
            image = createPlaceholderImage(valueWord, suit);
        }

        this.imageView = new ImageView(image);
        this.imageView.setFitWidth(CARD_WIDTH);
        this.imageView.setFitHeight(CARD_HEIGHT);
        this.imageView.setPreserveRatio(true);
    }

    private Image createPlaceholderImage(String valueWord, String suit) {
        try {
            var placeholderStream = getClass().getResourceAsStream("/com/blackjack/the21project/images/cards/placeholder.png");
            if (placeholderStream == null) {
                throw new RuntimeException("placeholder.png not found in resources");
            }
            return new Image(placeholderStream);
        } catch (Exception e) {
            throw new RuntimeException("Failed to load placeholder.png", e);
        }
    }


    private String convertValueToWord(int value) {
        return switch (value) {
            case 1 -> "Ace";
            case 2 -> "Two";
            case 3 -> "Three";
            case 4 -> "Four";
            case 5 -> "Five";
            case 6 -> "Six";
            case 7 -> "Seven";
            case 8 -> "Eight";
            case 9 -> "Nine";
            case 10 -> "Ten";
            case 11 -> "Jack";
            case 12 -> "Queen";
            case 13 -> "King";
            default -> String.valueOf(value);
        };
    }

    public String getSuit() {
        return suit;
    }

    public int getValue() {
        return value;
    }

    public ImageView getImageView() {
        return imageView;
    }

    @Override
    public String toString() {
        return value + " of " + suit;
    }
}
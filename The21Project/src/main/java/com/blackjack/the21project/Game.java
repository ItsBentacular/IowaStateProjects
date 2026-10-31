package com.blackjack.the21project;

import java.util.List;

public class Game {
    private final Deck deck;
    private final Player player;
    private final Player dealer;
    private boolean gameOver;
    private Money money;

    public Game() {
        deck = new Deck();
        player = new Player();
        dealer = new Player();
        money = new Money(100);
        gameOver = false;
    }

    public Money getMoney() {
        return money;
    }

    public void dealInitialCards() {
        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());
        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());

        if (player.getScore() == 21 && player.getHand().size() == 2){
            gameOver = true; // blackjack check
        }
    }

    public void playerHit() {
        if (!gameOver) {
            player.addCard(deck.drawCard());
            int playerScore = player.getScore();

            // End game if player busts OR hits 21
            if (playerScore >= 21) {
                gameOver = true;
                dealerTurn();  // Let dealer finish their turn
            }
        }
    }


    public void playerStand() {
        if (!gameOver) {
            dealerTurn();
            gameOver = true;
        }
    }

    private void dealerTurn() {
        while (dealer.getScore() < 17) {
            dealer.addCard(deck.drawCard());
        }
    }

    public Player getPlayer() {
        return player;
    }

    public Player getDealer() {
        return dealer;
    }

    public boolean isGameOver() {
        return gameOver;
    }


    public String getGameResult() {

        if(!gameOver) {
            dealerTurn();
            gameOver = true;
        }

        int playerScore = player.getScore();
        int dealerScore = dealer.getScore();

        // Check for player's initial 21 (instant win)
        if (playerScore == 21 && player.getHand().size() == 2) {
            money.winBlackjack();
            //System.out.println(playerScore);
            //System.out.println(dealerScore);
            return "Blackjack! You win!";
        }

        // Check for player bust
        if (playerScore > 21) {
            money.loseBet();
            //System.out.println(playerScore);
            //System.out.println(dealerScore);
            return "Bust! You lose with " + playerScore + ".";
        }

        // Check for dealer bust
        if (dealerScore > 21) {
            money.winBet();
            //System.out.println(playerScore);
            //System.out.println(dealerScore);
            return "Dealer busts with " + dealerScore + ". You win!";
        }

        if (gameOver) {
            if (playerScore > dealerScore) {
                money.winBet();
                //System.out.println(playerScore);
                //System.out.println(dealerScore);
                return "You win with " + playerScore + " against dealer's " + dealerScore + "!";
            } else if (dealerScore > playerScore) {
                money.loseBet();
                //System.out.println(playerScore);
                //System.out.println(dealerScore);
                return "Dealer wins with " + dealerScore + " against your " + playerScore + "!";
            } else if (playerScore == dealerScore){
                money.tie();
                //System.out.println(playerScore);
                //System.out.println(dealerScore);
                return "It's a tie at " + playerScore + "!";

            }
        }
        System.out.println(playerScore);
        System.out.println(dealerScore);
        return "";

    }




public List<Card> getPlayerHand() {
        return player.getHand();
    }

    public List<Card> getDealerHand() {
        return dealer.getHand();
    }

    public int getPlayerScore() {
        return player.getScore();
    }

    public int getDealerScore() {
        return dealer.getScore();
    }

    public boolean isPlayerBust() {
        return player.getScore() > 21;
    }

    public void dealerPlay() {
        dealerTurn();
    }

    public String determineWinner() {
        return getGameResult();
    }

    public void startNewGame() {
        deck.shuffle();
        player.getHand().clear();
        dealer.getHand().clear();
        gameOver = false;
        money = new Money(100);
        dealInitialCards();
    }

    public void startNewHand() {
        deck.shuffle();
        player.getHand().clear();
        dealer.getHand().clear();
        gameOver = false;
        dealInitialCards();
    }
}
package com.blackjack.the21project;

import java.util.ArrayList;
import java.util.List;

public class Player {
    private List<Card> hand;
    private int score;

    public Player() {
        hand = new ArrayList<>();
        score = 0;
    }

    public void addCard(Card card) {
        hand.add(card);
        calculateScore();
    }

    public List<Card> getHand() {
        return hand;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    private void calculateScore() {
        score = 0;
        int aces = 0;

        for (Card card : hand) {
            if (card.getValue() == 1) {
                aces++;
            } else if (card.getValue() > 10) {
                score += 10;
            } else {
                score += card.getValue();
            }
        }

        // Handle aces
        for (int i = 0; i < aces; i++) {
            if (score + 11 <= 21) {
                score += 11;
            } else {
                score += 1;
            }
        }
    }
}
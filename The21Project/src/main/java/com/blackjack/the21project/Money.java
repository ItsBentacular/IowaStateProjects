package com.blackjack.the21project;

public class Money {
    private int balance;
    private int currentBet;

    public Money(int initialBalance) {
        this.balance = initialBalance;
        this.currentBet = 0;
    }

    public boolean placeBet(int amount) {
        if (amount <= balance && amount > 0) {
            currentBet = amount;
            balance -= amount;
            return true;
        }
        return false;
    }

    public void winBet() {
        balance += (currentBet * 2); // Player gets their bet back plus winnings
        currentBet = 0;
    }

    public void winBlackjack() {
        balance += (currentBet * 2.5); // Blackjack typically pays 3:2
        currentBet = 0;
    }

    public void loseBet() {
        currentBet = 0; // Player already lost their bet when they placed it
    }

    public void tie() {
        balance += currentBet; // Return the bet amount
        currentBet = 0;
    }

    public int getBalance() {
        return balance;
    }

    public int getCurrentBet() {
        return currentBet;
    }
}

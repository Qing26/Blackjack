// ConsoleApplication2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

// Initialize the card values
int cardValues[13] = { 1,2,3,4,5,6,7,8,9,10,10,10,11 }; // Simplified array

int playerHand[12], botHand[12];
int playerHandSize = 0, botHandSize = 0;

// Declaring functions
void dealCard(int hand[], int& handSize, bool isPlayer);
int calculateTotal(int hand[], int handSize);
void checkDecks();
void suddenWin();
void askAnotherCard(bool isPlayer);
void croupierFinalTurn();

int main() {
    srand(time(0)); // Seed for random number generation

    // Initial card distribution
    dealCard(playerHand, playerHandSize, true);
    dealCard(playerHand, playerHandSize, true);
    dealCard(botHand, botHandSize, false);

    // Check initial decks and handle possible sudden win
    checkDecks();

    return 0;
}

void dealCard(int hand[], int& handSize, bool isPlayer) {
    int cardValueIndex = rand() % 13; // Random card value
    int cardValue = cardValues[cardValueIndex];

    // Special handling for Ace
    if (cardValue == 11 && isPlayer) {
        cout << "You've drawn an Ace. Do you want it to be 1 or 11? ";
        cin >> cardValue;
        while (cardValue != 1 && cardValue != 11) {
            cout << "Invalid choice. Please choose 1 or 11: ";
            cin >> cardValue;
        }
    }

    hand[handSize++] = cardValue;
}

int calculateTotal(int hand[], int handSize) {
    int total = 0;
    for (int i = 0; i < handSize; i++) {
        total += hand[i];
    }
    return total;
}

void checkDecks() {
    int playerTotal = calculateTotal(playerHand, playerHandSize);
    int botTotal = calculateTotal(botHand, botHandSize);

    cout << "Player's hand total value: " << playerTotal << endl;
    cout << "Bot's hand total value: " << botTotal << endl;

    if (playerTotal == 21) {
        suddenWin(); // Check for sudden win scenario
    }
    else if (playerTotal < 21) {
        askAnotherCard(true); // Player's turn to ask for another card
    }
    else {
        cout << "Bust! You've exceeded 21. You lose." << endl;
    }
}

void suddenWin() {
    dealCard(botHand, botHandSize, false); // Bot gets a new card
    int botTotal = calculateTotal(botHand, botHandSize);

    if (botTotal != 21) {
        cout << "Sudden win! Player wins with a Blackjack!" << endl;
    }
    else {
        cout << "It's a tie! Both player and bot hit Blackjack." << endl;
    }
}

void askAnotherCard(bool isPlayer) {
    char choice;
    while (true) {
        cout << "Do you want another card? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            dealCard(playerHand, playerHandSize, isPlayer);
            int playerTotal = calculateTotal(playerHand, playerHandSize);
            cout << "Player's hand total value: " << playerTotal << endl;
            if (playerTotal >= 21) break;
        }
        else {
            break;
        }
    }

    if (isPlayer) {
        int playerTotal = calculateTotal(playerHand, playerHandSize);
        if (playerTotal > 21) {
            cout << "Bust! You've exceeded 21. You lose." << endl;
        }
        else if (playerTotal == 21) {
            cout << "21! Let's see what the croupier gets." << endl;
        }
        else {
            croupierFinalTurn(); // It's now the croupier's turn
        }
    }
}

void croupierFinalTurn() {
    int playerTotal = calculateTotal(playerHand, playerHandSize);
    int botTotal = calculateTotal(botHand, botHandSize);

    while (botTotal < 17) { //croupier must hit until their total is 17 or higher
        dealCard(botHand, botHandSize, false);
        botTotal = calculateTotal(botHand, botHandSize);
    }

    cout << "Croupier's final hand total value: " << botTotal << endl;

    if (botTotal > 21 || botTotal < playerTotal) {
        cout << "Player wins!" << endl;
    }
    else if (botTotal > playerTotal) {
        cout << "Croupier wins!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }
}
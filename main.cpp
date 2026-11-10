#include <iostream>
#include "Blackjack.h"
#include "Common.h"
#include "Player.h"
#include "Renderer.h"

bool doPlayAgain() {
    return ConsoleInput::charInput("\nPlay again? (y/n): ", "yn") == 'y';
}

void gameLoop() {
    std::cout << "Hello, welcome to C++ Blackjack\n\n";

    Player player{ConsoleInput::stringInput("Enter your name: "),
    ConsoleInput::numericInput<double>("Enter your buy in balance: ")};

    Player dealer{"Dealer", 100000};

    std::cout << "Welcome " << player.getName() << std::endl;
    printBalance(player);

    do {
        if (const Result result = blackjack(dealer, player); result != Result::null_result)
            finish(result, dealer, player);
        printBalance(player);
        dealer.reset();
        player.reset();
        if (player.getBalance() <= 0) {
            std::cout << "Looks like you have run out of money to play with... :(\n";
            break;
        }
    } while (doPlayAgain());
    std::cout << "Goodbye " << player.getName() << "!";
}

int main() {
    gameLoop();
    return 0;
}
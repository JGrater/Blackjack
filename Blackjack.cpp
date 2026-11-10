//
// Created by JGrater on 28/10/2026.
//

#include "Blackjack.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Renderer.h"
#include "Settings.h"

Play doPlay(const bool canDoubleDown, const bool canSplit) {
    char input{};
    do {
        if (canDoubleDown && canSplit) {
            input = ConsoleInput::charInput("(h) to hit, (s) to stand , (d) to double down , (p) to split: ", "hsdp");
        } else if (canDoubleDown) {
            input = ConsoleInput::charInput("(h) to hit, (s) to stand , (d) to double down: ", "hsd");
        } else if (canSplit) {
            input = ConsoleInput::charInput("(h) to hit, (s) to stand , (p) to split: ", "hsp");
        } else {
            input = ConsoleInput::charInput("(h) to hit, (s) to stand: ", "hs");
        }
        using enum Play;
        switch (input) {
            case 'h':
                return hit;
            case 's':
                return stand;
            case 'd':
                return double_down;
            case 'p':
                return split;
            default:
                continue;
        }
    } while (true);
}

bool isBust(const int score) {
    return score > Settings::bust;
}

bool isNaturalBlackjack(const Hand& hand) {
    return hand.score == Settings::bust && hand.hand.size() == 2;
}


bool dealerTurn(Deck& deck, Hand& hand) {
    while (hand.score < Settings::dealerHold) {
        Card card {deck.dealCard()};
        hand.pickUp(card);
        std::cout << "The dealer pulls a " << card << ". They now have: " << hand.score << ".\n";
    }

    return isBust(hand.score);
}

void playerPickUp(Deck& deck, Hand& hand) {
    const Card card {deck.dealCard()};
    hand.pickUp(card);
    std::cout << "Your were dealt a " << card << ".";
    if (hand.score == Settings::bust) {
        std::cout << " Blackjack! ";
    }
}

bool playerTurn(Deck& deck, Player& dealer, Player& player, const bool isSplitHand) {
    using enum Play;
    Hand& hand = isSplitHand ? player.getSplitHand() : player.getHand();
    while (hand.score < Settings::bust) {
        const Play play{ doPlay(player.canBet(hand.bet), player.canSplit()) };
        if (play == stand) {
            break;
        }
        if (play == double_down) {
            isSplitHand ? player.splitHandBet(hand.bet) : player.bet(hand.bet);
            playerPickUp(deck, hand);
            std::cout << "  You now have: " << hand.score << std::endl;
            break;
        }
        if (play == hit) {
            playerPickUp(deck, hand);
            std::cout << "  You now have: " << hand.score << std::endl;
        }
        if (play == split) {
            player.splitHand();
            blackjackSplit(deck, dealer, player);
            break;
        }
    }
    return isBust(hand.score);
}


void placeBet(Player& player) {
    do {
        if (const double bet{ConsoleInput::numericInput<double>("Place your bet (Min: 1, Max: 500): ")};
            bet >= Settings::minBet &&
            bet <= Settings::maxBet &&
            player.canBet(bet)
        ) {
            player.bet(bet);
            return;
        }
        std::cout << "Can not make that bet. Try again...\n";
    } while (true);
}


void deal(Hand& dealerHand, Hand& playerHand, Deck& deck) {
    deck.shuffle();

    playerHand.pickUp(deck.dealCard());

    dealerHand.pickUp(deck.dealCard());
    std::cout << "\nDealer is showing ?? ";
    printHand(dealerHand);
    std::cout << std::endl;

    playerHand.pickUp(deck.dealCard());

    dealerHand.pickUp(deck.dealCard());

    std::cout << "You have ";
    printHand(playerHand);
    if (isNaturalBlackjack(playerHand)) {
        std::cout << " Blackjack!";
        playerHand.naturalBlackjack = true;
    }
    std::cout << std::endl;
}

void applyResult(Hand& hand, const int dealerScore) {
    using enum Result;
    if (hand.score == dealerScore) {
        hand.result = draw;
    } else if (hand.score > dealerScore) {
        hand.result = win;
    } else {
        hand.result = loss;
    }
}

void playSplit(Deck& deck, Player& dealer, Player& player) {
    using enum Result;
    Hand& hand = player.getHand();
    Hand& splitHand = player.getSplitHand();

    playerPickUp(deck, splitHand);
    std::cout << "\nYour first hand is showing ";
    printHand(splitHand);
    std::cout << std::endl;
    if (playerTurn(deck,dealer,player,true)) {
        std::cout << "You went bust!\n";
        splitHand.result = loss;
    }

    playerPickUp(deck, hand);
    std::cout << "\nYour second hand is showing ";
    printHand(hand);
    std::cout << std::endl;
    if (playerTurn(deck,dealer,player,false)) {
        std::cout << "You went bust!\n";
        hand.result = loss;
    }

    std::cout << "The dealer flips a " << dealer.getHand().hand[1] << ". They now have: " << dealer.getHand().score << ".\n";

    if (dealerTurn(deck, dealer.getHand())) {
        std::cout << "The dealer went bust!\n";
        if (hand.result != loss)
            hand.result = win;
        if (splitHand.result != loss)
            splitHand.result = win;
        return;
    }

    if (hand.result != loss) {
        applyResult(hand, dealer.getHand().score);
    }
    if (splitHand.result != loss) {
        applyResult(splitHand, dealer.getHand().score);
    }
}


double applyWinnings(Player& dealer, Player& player, const bool isSplitHand) {
    using enum Result;
    Hand const& hand = isSplitHand ? player.getSplitHand() : player.getHand();
    double winnings{0};
    if (hand.result == win && hand.naturalBlackjack) {
        winnings = 2.5*hand.bet;
        player.setBalance(player.getBalance() + 2.5*hand.bet);
        dealer.setBalance(dealer.getBalance() - hand.bet);
    } else if (hand.result == win) {
        winnings = 2*hand.bet;
        player.setBalance(player.getBalance() + 2*hand.bet);
        dealer.setBalance(dealer.getBalance() - hand.bet);
    } else if (hand.result == draw) {
        winnings = hand.bet;
        player.setBalance(player.getBalance() + hand.bet);
    } else if (hand.result == loss) {
        winnings = 0 - hand.bet;
        dealer.setBalance(dealer.getBalance() + hand.bet);
    }
    return winnings;
}

void finishSplit(Player& dealer, Player& player) {
    const double winnings{
        applyWinnings(dealer, player, false) +
        applyWinnings(dealer, player, true)
    };
    printSplitResult({player.getHand().result, player.getSplitHand().result}, winnings);
}

void finish(const Result result, Player& dealer, Player& player) {
    printResult(result, applyWinnings(dealer, player, false));
}


void blackjackSplit(Deck& deck, Player& dealer, Player& player) {
    std::cout << "Splitting hand...\n";
    playSplit(deck, dealer, player);
    finishSplit(dealer, player);
}

Result blackjack(Player& dealer, Player& player) {
    using enum Result;
    Deck deck{};
    placeBet(player);
    deal(dealer.getHand(), player.getHand(), deck);

    if (playerTurn(deck,dealer,player,false)) {
        if (player.getHand().result != null_result)
            return null_result;
        std::cout << "You went bust!\n";
        player.getHand().result = loss;
        return loss;
    }

    if (player.getHand().result != null_result)
        return null_result;

    std::cout << "The dealer flips a " << dealer.getHand().hand[1] << ". They now have: " << dealer.getHand().score << ".\n";

    if (dealerTurn(deck, dealer.getHand())) {
        std::cout << "The dealer went bust!\n";
        player.getHand().result = win;
        return win;
    }
    applyResult(player.getHand(), dealer.getHand().score);
    return player.getHand().result;
}

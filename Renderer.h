//
// Created by JGrater on 03/11/2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <string_view>

#include "Blackjack.h"

namespace Colours {
    static constexpr std::string_view RESET{"\033[0m"};
    static constexpr std::string_view GREEN{"\033[32m"};
    static constexpr std::string_view RED{"\033[31m"};
}

inline void printBalance(const Player& player) {
    using namespace Colours;
    const double winnings = player.getWinnings();
    std::cout << "Balance: " << player.getBalance() << " (";
    winnings >= 0 ? std::cout << GREEN << "+" : std::cout << RED;
    std::cout << winnings << RESET << ")\n";
}

inline void printHand(const Hand& hand) {
    for (auto c : hand.hand) {
        std::cout << c << " ";
    }
    std::cout << "(" << hand.score << ")";
}

inline void printResult(const Result result, const double winnings) {
    using namespace Colours;
    using enum Result;
    switch (result) {
        case win:
            std::cout << "You won! Winnings: " << GREEN << "+" << winnings << RESET << std::endl;
            break;
        case draw:
            std::cout << "You drew!\n";
            break;
        case loss:
            std::cout << "You lost! Winnings: " << RED << winnings << RESET << std::endl;
            break;
        default:
            std::cout << "Invalid result!\n";
    }
}

inline void printSplitResult(const std::array<Result, 2> results, const double winnings) {
    using namespace Colours;
    using enum Result;
    for (int i = 1; i >= 0; --i) {
        std::cout << "For your ";
        std::cout << (i == 1 ? "first hand " : "second hand ");
        switch (results[i]) {
            case win:
                std::cout << "you won!\n";
                break;
            case draw:
                std::cout << "you drew!\n";
                break;
            case loss:
                std::cout << "you lost!\n";
                break;
            default:
                std::cout << "Invalid result!";
        }
    }
    std::cout << "Total winnings: ";
    if (winnings >= 0) {
        std::cout << GREEN << "+";
    } else {
        std::cout << RED;
    }
    std::cout << winnings << RESET << std::endl;
}

#endif //RENDERER_H

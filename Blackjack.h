//
// Created by JGrater on 28/10/2026.
//

#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Player.h"

namespace Settings {
    static constexpr int bust{21};
    static constexpr int dealerHold{17};
    static constexpr bool dealerHitSoft{true};

    static constexpr double minBet{1};
    static constexpr double maxBet{500};
}

enum Play {
    hit,
    stand,
    double_down,
    split,

    null_play
};

void blackjackSplit(Deck& deck, Player& dealer, Player& player);
Result blackjack(Player& dealer, Player& player);
void finish(Result result, Player& dealer, Player& player);

#endif //BLACKJACK_H

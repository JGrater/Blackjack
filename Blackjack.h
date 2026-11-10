//
// Created by JGrater on 28/10/2026.
//

#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Player.h"

enum class Play {
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

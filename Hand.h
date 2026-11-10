//
// Created by JGrater on 10/11/2026.
//

#ifndef HAND_H
#define HAND_H
#include <vector>

#include "Deck.h"
#include "Settings.h"


enum class Result {
    win,
    loss,
    draw,

    null_result
};

struct Hand {
    std::vector<Card> hand{};
    int score{0};
    int aceCount{0};
    double bet{0};
    Result result{Result::null_result};
    bool naturalBlackjack{false};


    void pickUp(const Card& card) {
        hand.push_back(card);
        score += card.value();

        if (card.rank == Card::ace)
            ++aceCount;

        if (score > Settings::bust && aceCount > 0) {
            score -= 10;
            --aceCount;
        }
    }
};


#endif //HAND_H

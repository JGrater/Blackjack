//
// Created by JGrater on 28/10/2026.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <cassert>

#include "Deck.h"

enum Result {
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
    Result result{null_result};
    bool naturalBlackjack{false};


    void pickUp(const Card& card) {
        hand.push_back(card);
        score += card.value();
        if (card.rank == Card::ace)
            ++aceCount;
    }

    void toSoftAce() {
        assert(aceCount > 0 && "Player::toSoftAce() does not have an ace");
        score -= 10;
        --aceCount;
    }
};

class Player {
public:
    explicit Player(const std::string_view name, const double buyIn) :
        m_name{name}, m_balance{buyIn}, m_buyIn{buyIn} {}

    std::string_view getName() const { return m_name; }
    Hand & getHand() { return m_hand; }
    Hand & getSplitHand() { return m_splitHand; }
    double getBalance() const { return m_balance; }
    double getWinnings() const { return m_balance - m_buyIn; }

    void setBalance(const double balance) { m_balance = balance; }

    bool canSplit() const;
    bool canBet(double bet) const;

    void splitHand();
    void bet(double bet);
    void splitHandBet(double bet);
    void reset();

private:
    std::string_view m_name{};
    Hand m_hand{};
    Hand m_splitHand{};
    double m_balance{0};
    const double m_buyIn{0};
};

#endif //PLAYER_H

//
// Created by JGrater on 28/10/2026.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "Hand.h"

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
    std::string m_name{};
    Hand m_hand{};
    Hand m_splitHand{};
    double m_balance{0};
    const double m_buyIn{0};
};

#endif //PLAYER_H

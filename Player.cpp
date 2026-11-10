//
// Created by JGrater on 29/10/2026.
//
#include "Player.h"
#include <cassert>

bool Player::canSplit() const {
    if (m_hand.hand.size() == 2 &&
        m_hand.hand[0].value() == m_hand.hand[1].value() &&
        m_splitHand.hand.empty() &&
        canBet(m_hand.bet))
        return true;
    return false;
}

bool Player::canBet(const double bet) const {
    return bet <= m_balance;
}

void Player::splitHand() {
    assert(m_hand.hand.size() == 2 && "Player::splitHand() does not have an hand");
    assert(m_hand.hand[0].value() == m_hand.hand[1].value() && "Player::splitHand() can not split hand");
    const Card firstHandCard = m_hand.hand[0];
    const Card secondHandCard = m_hand.hand[1];
    const double originalBet = m_hand.bet;
    reset();
    m_hand.pickUp(firstHandCard);
    m_splitHand.pickUp(secondHandCard);
    m_hand.bet = originalBet;
    m_splitHand.bet = originalBet;
    m_balance -= originalBet;
}

void Player::bet(const double bet) {
    m_hand.bet += bet;
    m_balance -= bet;
}

void Player::splitHandBet(const double bet) {
    m_splitHand.bet += bet;
    m_balance -= bet;
}

void Player::reset() {
    m_hand = {};
    m_splitHand = {};
}

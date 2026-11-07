//
// Created by JGrater on 27/10/2026.
//

#include "Deck.h"
#include <cassert>


Deck::Deck() {
    std::size_t index = 0;
    for (const auto suit : Card::suits)
        for (const auto rank : Card::ranks)
            m_cards[index++] = Card { rank, suit };
}

Card Deck::dealCard() {
    assert(m_topCard != s_noCards && "Deck::dealCard() ran out of cards");
    return m_cards[m_topCard++];
}

void Deck::shuffle() {
    std::ranges::shuffle(m_cards, Random::mt);
    m_topCard = 0;
}
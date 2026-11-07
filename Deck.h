//
// Created by JGrater on 27/10/2026.
//

#ifndef DECK_H
#define DECK_H
#include "Common.h"



struct Card {
    enum Rank {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,

        max_rank
    };

    enum Suit {
        clubs,
        diamonds,
        hearts,
        spades,

        max_suit
    };

    static constexpr std::array<Rank, max_rank> ranks{ ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king };
    static constexpr std::array<Suit, max_suit> suits{ clubs,diamonds,hearts,spades };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        static constexpr std::array textRanks {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
        static constexpr std::array textSuits {"\u2663", "\u2666", "\u2665", "\u2660"};
        static constexpr std::string_view red{"\033[31m"};
        static constexpr std::string_view reset{"\033[0m"};

        if (card.suit == diamonds || card.suit == hearts) {
            os << red;
        }
        os << textRanks[card.rank] << textSuits[card.suit] << reset;
        return os;
    }

    int value() const {
        static constexpr std::array rankValues { 11,2,3,4,5,6,7,8,9,10,10,10,10};
        return rankValues[rank];
    }

    static_assert(ranks.size() == max_rank);
    static_assert(suits.size() == max_suit);
};


class Deck {
public:
    Deck();
    Card dealCard();
    void shuffle();
private:
    static constexpr int s_noCards{52};

    std::array<Card, s_noCards> m_cards{};
    int m_topCard{0};
};



#endif //DECK_H

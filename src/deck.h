#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <memory>

class Deck {
    public:
        Deck(unsigned seed);
        ~Deck();

        void shuffle();
        std::vector<std::shared_ptr<Card>> deal();
        void printDeck();
    private:
        const size_t CARD_COUNT;
        std::vector<std::shared_ptr<Card>> _cards;
        size_t _dealt;
        unsigned _seed;
};

#endif

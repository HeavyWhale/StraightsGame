#include "deck.h"

using std::vector;

Deck::Deck(unsigned seed) 
     : CARD_COUNT{Card::SUIT_LIST.length() * Card::MAX_RANK}, _cards{}, _dealt{0}, _seed(seed) {

    for (int i = 0; i < (int)Card::SUIT_LIST.length(); i++) {
        for (int j = 0; j < Card::MAX_RANK; j++) {
            _cards.emplace_back(std::make_shared<Card> (Card{j, Card::SUIT_LIST[i]}));
        }
    }
}

Deck::~Deck() {}

vector<std::shared_ptr<Card>>  Deck::deal() {
    _dealt = _dealt % CARD_COUNT + Card::MAX_RANK;
    return std::vector<std::shared_ptr<Card>> 
        {_cards.begin() + _dealt - Card::MAX_RANK, _cards.begin() + _dealt};
}

void Deck::shuffle() {
    std::default_random_engine rng{_seed};
    std::shuffle( _cards.begin(), _cards.end(), rng );
}

void Deck::printDeck() {
    for (int i = 0; i < (int)Card::SUIT_LIST.length(); i++) {
        for (int j = 0; j < Card::MAX_RANK; j++) {
            auto card = _cards[i*Card::MAX_RANK + j];
            std::cout << ' ' << (*card).repr();
        }
        std::cout << std::endl;
    }
}

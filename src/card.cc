#include "card.h"

using std::string;

const std::string Card::SUIT_LIST = "CDHS";
const std::vector<std::string> Card::SUIT_LIST_FULL {"Club", "Diamond", "Heart", "Spade"};
const std::string Card::RANK_LIST = "A23456789TJQK";

Card::Card() {}

Card::Card (int rank, char suit) {
    if (rank >= MAX_RANK) {
        throw;
    }
    _rank = rank;

    auto found = std::find(SUIT_LIST.begin(), SUIT_LIST.end(), suit);
    if (found == SUIT_LIST.end()) {
        throw;
    }
    _suit = found - SUIT_LIST.begin();
}

Card::Card (char rank, char suit) {
    auto found1 = std::find(RANK_LIST.begin(), RANK_LIST.end(), rank);
    if (found1 == RANK_LIST.end()) {
        throw;
    }
    _rank = found1 - RANK_LIST.begin();

    auto found2 = std::find(SUIT_LIST.begin(), SUIT_LIST.end(), suit);
    if (found2 == SUIT_LIST.end()) {
        throw;
    }
    _suit = found2 - SUIT_LIST.begin();
}

Card::~Card() {}

string Card::getSuitName() const {
    return SUIT_LIST_FULL[_suit];
}

string Card::repr() const {
    return string{RANK_LIST[_rank]} + SUIT_LIST[_suit];
}

std::pair<int, int> Card::operator*() const {
    return std::pair<int, int> {_rank, _suit};
}

bool Card::operator==(const Card& other) const {
    return (_rank == other._rank) && (_suit == other._suit);
}

bool Card::operator<(const Card& other) const {
    return _rank < other._rank;
}

bool Card::operator>(const Card& other) const {
    return _rank > other._rank;
}

bool Card::isFirst() const {
    return _rank == 0;
}

bool Card::isLast() const {
    return _rank == MAX_RANK;
}

bool Card::isNextTo(const Card& other) const {
    if (other.isFirst()) {
        return (*other).first + 1 == _rank;
    } else if (other.isLast()) {
        return (*other).first - 1 == _rank;
    } else {
        return (*other).first + 1 == _rank || (*other).first - 1 == _rank;
    }
}

bool Card::isSeven() const {
    return _rank == 6;
}

#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <algorithm>

class Card {
    public:
        Card();
        Card(int rank, char suit);
        Card(char rank, char suit);
        ~Card();

        static const std::string SUIT_LIST;
        static const std::vector<std::string> SUIT_LIST_FULL;
        static const std::string RANK_LIST;

        static const int MAX_RANK = 13;
        static const int MAX_SUIT = 4;

        std::string getSuitName() const;
        std::string repr() const;
        std::pair<int, int> operator*() const;
        bool operator==(const Card&) const;
        bool operator<(const Card&) const;
        bool operator>(const Card&) const;
        bool isFirst() const;
        bool isLast() const;
        bool isSeven() const;
        bool isNextTo(const Card&) const;
    private:
        int _rank;
        int _suit;
};

#endif

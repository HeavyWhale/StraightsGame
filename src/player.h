#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "playertype.h"
#include "strategy.h"
#include "info.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

class Tableau;

class Player {

    public:
        Player (Tableau* theTableau, PlayerType playerType, int order);

        int getScore() const;
        std::string getPlayerOdr() const;
        const std::vector<std::shared_ptr<Card>>& getHand() const;
        const std::vector<std::shared_ptr<Card>>& getDiscarded() const;

        bool handEmpty() const;
        int calculateScore() const;
        void updateScore();
        
        void receiveCards(std::vector<std::shared_ptr<Card>> cardVec);
        std::shared_ptr<Card> play(const Card& ref);
        Card discard(const Card& ref);
        
        void clearDiscarded();
        void setStrategy(PlayerType pType);
        Info executeStrategy();
        std::vector<Card> getPlayableCards();
    private:
        // fields:
        int _curScore;
        Tableau* _theTableau;
        std::string _playerOdr;
        std::unique_ptr<Strategy> _strategy;
        std::vector<std::shared_ptr<Card>> _hand;
        std::vector<std::shared_ptr<Card>> _discarded;

        // methods:
        std::shared_ptr<Card> popAt(std::vector<std::shared_ptr<Card>>::iterator it);
        std::shared_ptr<Card> popCard(const Card& ref);
};

class NotInHandException {
    private:
        const Card& _card;
    public:
        NotInHandException(const Card& card);
        const Card& getCard() const;
};

#endif

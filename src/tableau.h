#ifndef TABLEAU_H
#define TABLEAU_H

#include "deck.h"
#include "subject.h"
#include "info.h"
#include "playertype.h"
#include <algorithm>
#include <memory>
#include <map>
#include <iostream>

class Player;

class Tableau : public Subject {
    public:
        Tableau(unsigned seed);
        ~Tableau();

        bool _gameIsOver;

        const int MAX_PLAYER = 4;
        const int MAX_SCORE = 80;
        const Card KICK_OFF_CARD = Card{'7', 'S'};

        int getCurPlayerPos() const;
        const Player* getCurPlayer() const;
        std::vector<std::unique_ptr<Player>>& getPlayers();
        const std::map<std::string, std::vector<std::shared_ptr<Card>>>& getPlayedCardsMap();
        std::vector<int>& getPlayerScores();
        
        void invitePlayer(PlayerType pType);
        std::vector<Card> generatePlayableCards(Player* player);

        void play(const Card& ref);
        void discard(const Card& ref);
        void deck();
        void quit();
        void ragequit();

    private:
        //fields:
        std::unique_ptr<Deck> _deck;
        std::vector<std::unique_ptr<Player>> _players;
        std::vector<int> _playerScores;

        bool _isFirstTurn;
        std::vector<std::unique_ptr<Player>>::iterator _curPlayer;
        std::map<std::string, std::vector<std::shared_ptr<Card>>> _playedCardsMap;

        //methods:
        // cycle back to first player in the _players if reach end
        void proceedToNextPlayer();
        void proceedUntilCurIsHuman();
        void sortVec(std::vector<std::shared_ptr<Card>>& vec);

        // setup fields: _playerScores, _playedCardsMap
        // deal cards to each player and set _curPlayer to the one who holds the KICK_OFF_CARD
        void initRound(bool isNewGame);

};

class NotPlayableException {
    private:
        const Card& _card;
    public:
        NotPlayableException(const Card& card);
        const Card& getCard() const;
};

#endif

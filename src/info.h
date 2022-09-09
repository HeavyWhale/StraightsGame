#ifndef INFO_H
#define INFO_H

#include "card.h"
#include <memory>
#include <map>

class Player;

enum class State { Play, Discard, HumanMove, Ragequit, EndRound, StartRound };

class Info {
    public: 
        Info(State state, const Card refCard, std::shared_ptr<Card> card);

        State _state;
        const Card _refCard;
        std::shared_ptr<Card> _card;
        const std::vector<int> _newScores;
};

#endif

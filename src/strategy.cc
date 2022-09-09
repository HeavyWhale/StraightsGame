#include "strategy.h"
#include "player.h"

Strategy::Strategy(Player* player) : _player{player} {}

HumanStrategy::HumanStrategy(Player* player) : Strategy{player} {}

ComputerStrategy::ComputerStrategy(Player* player) : Strategy{player} {}

Info HumanStrategy::nextMove() {
    if (_player->handEmpty()) {
        return Info{State::EndRound, Card{}, std::shared_ptr<Card> (nullptr)};
    }

    return Info{State::HumanMove, Card{}, std::shared_ptr<Card> (nullptr)};
}

Info ComputerStrategy::nextMove() {
    if (_player->handEmpty()) {
        return Info{State::EndRound, Card{}, std::shared_ptr<Card> (nullptr)};
    }

    auto playableCards = _player->getPlayableCards();

    //std::cout << "# hand:" << reprVector(_player->getHand()) << std::endl;
    //std::cout << "# playableCards:" << reprVector(playableCards) << std::endl;
    
    if (!playableCards.empty()) {
        auto playedCard = _player->play(playableCards[0]);
        //std::cout << "# After play hand:" << reprVector(_player->getHand()) << std::endl;
        //std::cout << "# played card: " << playedCard->repr() << std::endl;
        return Info{State::Play, Card{}, playedCard};
    } else {
        auto firstCard = Card{*(_player->getHand()[0])};
        return Info{State::Discard, _player->discard(firstCard), std::shared_ptr<Card> (nullptr)};
    }
}

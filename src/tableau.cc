#include "player.h"
#include "tableau.h"
#include "textView.h"

Tableau::Tableau(unsigned seed)
     : Subject{}, _deck{std::make_unique<Deck> (seed)}, _isFirstTurn{true},
       _gameIsOver{false} {

    attachView(std::make_unique<TextView> (this));
}

Tableau::~Tableau() {}

std::vector<int>& Tableau::getPlayerScores() {
    return _playerScores;
}

const Player* Tableau::getCurPlayer() const {
    return (*_curPlayer).get();
}

std::vector<std::unique_ptr<Player>>& Tableau::getPlayers() {
    return _players;
}

int Tableau::getCurPlayerPos() const {
    return _curPlayer - _players.begin();
}

const std::map<std::string, std::vector<std::shared_ptr<Card>>>& Tableau::getPlayedCardsMap() {
    return _playedCardsMap;
}

void Tableau::initRound(bool isNewGame) {
    if (isNewGame) {
        for (int i = 0; i < MAX_PLAYER; i++) _playerScores.emplace_back(0);
        for (const auto& suitName : Card::SUIT_LIST_FULL) {
            _playedCardsMap.emplace(suitName, std::vector<std::shared_ptr<Card>>{});
        }
    } else {
        for (const auto& suitName : Card::SUIT_LIST_FULL) {
            _playedCardsMap[suitName].clear();
        }
        for (auto& pPlayer : _players) {
            pPlayer->clearDiscarded();
        }
    }

    _deck->shuffle();
    for (auto players_it = _players.begin(); players_it != _players.end(); players_it++) {
        std::vector<std::shared_ptr<Card>> dealtCards = _deck->deal();
        for (const auto& pCard : dealtCards) {
            if (*pCard == Tableau::KICK_OFF_CARD) {
                _curPlayer = players_it;
            }
        }
        (*players_it)->receiveCards(dealtCards);
    }

    Info info {State::StartRound, Card{}, std::shared_ptr<Card> (nullptr)};
    updateViews(info);

    proceedUntilCurIsHuman();
}

void Tableau::proceedToNextPlayer() {
    if (++_curPlayer == _players.end()) {
        _curPlayer = _players.begin();
    }
}

void Tableau::sortVec(std::vector<std::shared_ptr<Card>>& vec) {
    std::sort(vec.begin(), vec.end(), 
                [](const std::shared_ptr<Card>& a, const std::shared_ptr<Card>& b)
    { 
        return *a < *b; 
    });
}

void Tableau::proceedUntilCurIsHuman() {
    while (true) {
        if (_gameIsOver) break;
        Info info = (*_curPlayer)->executeStrategy();
        
        if (info._state == State::HumanMove) {
            // _curPlayer is Human
            updateViews(info);
            break;
        } else if (info._state == State::Play) {
            updateViews(info);
            _isFirstTurn = false;
            auto playedCard = info._card;
            _playedCardsMap[playedCard->getSuitName()].emplace_back(playedCard);
            sortVec(_playedCardsMap[playedCard->getSuitName()]);
        } else if (info._state == State::Discard) {
            updateViews(info);
        } else if (info._state == State::EndRound) {
            updateViews(info);
            if (_gameIsOver == true) {
                break;
            } else {
                initRound(false);
                break;
            }
        }

        proceedToNextPlayer();
    }
}

void Tableau::invitePlayer(PlayerType pType) {
    _players.emplace_back(std::make_unique<Player> (this, pType, _players.size()+1));
    if (_players.size() >= MAX_PLAYER) {
        initRound(true);
    }
}

std::vector<Card> Tableau::generatePlayableCards(Player* player) {
    if (player == nullptr) player = (*_curPlayer).get();
    if (_isFirstTurn) return std::vector<Card> {KICK_OFF_CARD};

    const auto& hand = player->getHand();
    std::vector<Card> result {};

    for (const auto& pCard : hand) {
        if (pCard->isSeven()) {
            result.push_back(Card{*pCard});
            continue;
        }

        for (const auto& playedCard : _playedCardsMap[pCard->getSuitName()]) {
            if (playedCard->isNextTo(*pCard)) {
                result.push_back(Card{*pCard});
            }
        }
    }

    return result;
}

void Tableau::play(const Card& ref) {
    auto playableCards = generatePlayableCards(nullptr);
    auto found = std::find(playableCards.begin(), playableCards.end(), ref);

    if (found == playableCards.end()) {
        throw NotPlayableException {ref};
    } else {
        _isFirstTurn = false;
        auto playedCard = (*_curPlayer)->play(ref);
        _playedCardsMap[playedCard->getSuitName()].emplace_back(playedCard);
        sortVec(_playedCardsMap[playedCard->getSuitName()]);

        Info info {State::Play, Card{}, playedCard};
        updateViews(info);

        proceedToNextPlayer();
        proceedUntilCurIsHuman();
    }
}

void Tableau::discard(const Card& ref) {
    auto playableCards = generatePlayableCards(nullptr);

    if (playableCards.empty()) {
        (*_curPlayer)->discard(ref);
        Info info {State::Discard, ref, std::shared_ptr<Card> (nullptr)};
        updateViews(info);
        
        proceedToNextPlayer();
        proceedUntilCurIsHuman();
    } else {
        throw "You have a legal play.";
    }
}

void Tableau::deck() {
    _deck->printDeck();
}

void Tableau::quit() {
    _gameIsOver = true;
}

void Tableau::ragequit() {
    (*_curPlayer)->setStrategy(PlayerType::Computer);
    std::cout << "Player " << (*_curPlayer)->getPlayerOdr() 
              << " ragequits. A computer will now take over." << std::endl;
    proceedUntilCurIsHuman();
}

NotPlayableException::NotPlayableException(const Card& card) : _card{card} {}

const Card& NotPlayableException::getCard() const {
    return _card;
}

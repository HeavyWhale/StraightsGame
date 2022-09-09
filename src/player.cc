#include "player.h"
#include "tableau.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

Player::Player ( Tableau* theTableau, PlayerType playerType, int order ) :
    _theTableau{theTableau}, _hand{}, _discarded{}, _playerOdr{std::to_string(order)},
    _curScore{0} {
    
    setStrategy(playerType);
}

bool Player::handEmpty() const {
    return _hand.empty();
}

int Player::getScore() const {
    return _curScore;
}

std::string Player::getPlayerOdr() const {
    return _playerOdr;
}

void Player::updateScore() {
    _curScore += calculateScore();
}

int Player::calculateScore() const {
    int result = 0;
    for (auto& card : _discarded) {
        result += (*(*card)).first + 1;
    }
    return result;
}

const vector<shared_ptr<Card>>& Player::getHand() const {
    return _hand;
}

const vector<shared_ptr<Card>>& Player::getDiscarded() const {
    return _discarded;
}

shared_ptr<Card> Player::popAt(vector<shared_ptr<Card>>::iterator it) {
    if (it == _hand.end()) throw std::out_of_range ("Card: given iterator it is out of range");
    auto temp = *it;
    _hand.erase(it);

    return temp;
}

shared_ptr<Card> Player::popCard(const Card& ref) {
    auto found = std::find_if(_hand.begin(), _hand.end(), [&](shared_ptr<Card> const& c) {
        return *c == ref;
    });
    if (found == _hand.end()) throw NotInHandException {ref};
    auto temp = std::move(*found);
    _hand.erase(found);
    
    return temp;
}

void Player::receiveCards(vector<shared_ptr<Card>> cardVec) {
    _hand.swap(cardVec);
}

shared_ptr<Card> Player::play(const Card& ref) {
    return popCard(ref);
}

Card Player::discard(const Card& ref) {
    _discarded.emplace_back(popCard(ref));
    return ref;
}

void Player::clearDiscarded() {
    _discarded.clear();
}

void Player::setStrategy(PlayerType pType) {
    switch (pType) {
        case PlayerType::Computer:
            _strategy = unique_ptr<Strategy> {new ComputerStrategy{this}};
            break;

        case PlayerType::Human:
            _strategy = unique_ptr<Strategy> {new HumanStrategy{this}};
            break;
        
        default:
            break;
    }
}

Info Player::executeStrategy() {
    return _strategy->nextMove();
}

std::vector<Card> Player::getPlayableCards() {
    return _theTableau->generatePlayableCards(this);
}

NotInHandException::NotInHandException(const Card& card) : _card{card} {}

const Card& NotInHandException::getCard() const {
    return _card;
}





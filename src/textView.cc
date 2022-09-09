#include "textView.h"
#include "tableau.h"


using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::cout;
using std::endl;

TextView::TextView(Tableau* theTableau) : View(theTableau) {}

TextView::~TextView() {}

string TextView::reprVector(std::vector<Card> cardVec, bool toggle) const {
    std::string result = "";
    for (const auto& it : cardVec) {
        result += (" " + (toggle ? string{it.repr()[0]} : (it.repr())));
    }
    return result;
}

string TextView::reprVector(std::vector<std::shared_ptr<Card>> pCardVec, bool toggle) const {
    std::string result = "";
    for (const auto& it : pCardVec) {
        result += (" " + (toggle ? string{(*it).repr()[0]} : ((*it).repr())));
    }
    return result;
}

void TextView::displayRoundEndInfo() {
    std::vector<int>& playerScores = _theTableau->getPlayerScores();
    std::vector<int> winnerPos {};
    
    int player_pos = 0;
    for (const auto& pPlayer : _theTableau->getPlayers()) {
        const auto discarded = pPlayer->getDiscarded();
        int score = pPlayer->getScore();
        int newScore = pPlayer->calculateScore();

        cout << "Player" << pPlayer->getPlayerOdr() << "'s discards:";
        cout << reprVector(discarded) << endl;
        cout << "Player" << pPlayer->getPlayerOdr() << "'s score: ";
        cout << std::to_string(score) << " + " << std::to_string(newScore)
             << " = " << std::to_string(score += newScore) << endl;
        
        if (score >= _theTableau->MAX_SCORE) {
            winnerPos.emplace_back(player_pos);
        }

        pPlayer->updateScore();
        playerScores[player_pos++] = score;
    }

    if (!winnerPos.empty()) {
        _theTableau->_gameIsOver = true;

        auto& players = _theTableau->getPlayers();

        std::sort(players.begin(), players.end(), 
                  [](const std::unique_ptr<Player> & a, const std::unique_ptr<Player> & b)
        { 
            return a->getScore() < b->getScore(); 
        });

        int winningScore = players[0]->getScore();
        cout << "Player" << players[0]->getPlayerOdr();

        for (auto& pPlayer : players) {
            if (pPlayer->getScore() == winningScore && pPlayer != *(players.begin())) {
                cout << ", Player" << pPlayer->getPlayerOdr();
            }
        }
        cout << " wins!" << endl;
    }
}

void TextView::displayRoundStartInfo() {
    cout << "A new round begins. It’s Player" << _theTableau->getCurPlayerPos()+1
         << "’s turn to play." << endl;
}

void TextView::displayAvailableInfo() {
    cout << "Cards on the table:" << endl;
    const auto& playedCardsMap = _theTableau->getPlayedCardsMap();

    for (const auto& suit : Card::SUIT_LIST_FULL) {
        cout << suit << "s:" << reprVector(playedCardsMap.at(suit), true) << endl;
    }

    cout << "Your hand:" << reprVector(_theTableau->getCurPlayer()->getHand()) << endl;
    cout << "Legal plays:" << reprVector(_theTableau->generatePlayableCards(nullptr)) << endl;
}

void TextView::displayPlayInfo(const std::shared_ptr<Card> card) {
    cout << "Player" << std::to_string(_theTableau->getCurPlayerPos()+1) 
         << " plays " << (*card).repr() << "." << endl;
}

void TextView::displayDiscardInfo(const Card& card) {
    cout << "Player" << std::to_string(_theTableau->getCurPlayerPos()+1) 
         << " discards " << card.repr() << "." << endl;
}

void TextView::displayRagequitInfo() {
    cout << "Player" << std::to_string(_theTableau->getCurPlayerPos()+1)
         << " ragequits. A computer will now take over." << endl;
}

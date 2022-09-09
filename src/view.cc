#include "view.h"
#include "subject.h"
#include "tableau.h"

View::View(Tableau* theTableau) : _theTableau{theTableau} {}

View::~View() {}

void View::notify(Info& info) {
    
    switch (info._state) {

        case State::Play :
            displayPlayInfo(info._card);
            break;

        case State::Discard :
            displayDiscardInfo(info._refCard);
            break;
        
        case State::HumanMove :
            displayAvailableInfo();
            break;

        case State::Ragequit :
            displayRagequitInfo();
            break;

        case State::EndRound :
            displayRoundEndInfo();
            break;

        case State::StartRound :
            displayRoundStartInfo();
            break;

        default:
            break;
    }
}

void View::displayRoundEndInfo() {}

void View::displayRoundStartInfo() {}

void View::displayAvailableInfo() {}

void View::displayPlayInfo(const std::shared_ptr<Card> card) {}

void View::displayDiscardInfo(const Card& card) {}

void View::displayRagequitInfo() {}

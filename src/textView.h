#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"
#include "player.h"

class Tableau;

class TextView : public View {
    public:
        TextView(Tableau* theTableau);
        ~TextView();
    private:
        // display the message when end round:
        //   calculate each palyer's new scores;
        //      If any of them is beyond 80 score, print the winners
        void displayRoundEndInfo() override;
        
        // display the message when round started, and who's turn to play
        void displayRoundStartInfo() override;

        // display available info for a human player
        void displayAvailableInfo() override;

        // display the paly move for a computer player
        void displayPlayInfo(const std::shared_ptr<Card> card) override;

        // display the discard move for a computer player
        void displayDiscardInfo(const Card& card) override;

        // display the info for ragequit
        void displayRagequitInfo() override;
        
        int calculateScore(std::vector<std::shared_ptr<Card>> pCardVec) const;

        std::string reprVector(std::vector<std::shared_ptr<Card>> pCardVec, bool toggle = false) const;
        std::string reprVector(std::vector<Card> cardVec, bool toggle = false) const;
};

#endif

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include "info.h"

class Tableau;

class View {
    public:
        virtual ~View() = 0;
        void notify(Info& info);

    protected:
        View(Tableau* theTableau);
        Tableau* _theTableau;
        // display the message when end round:
        //   calculate each palyer's new scores;
        //      If any of them is beyond 80 score, print the winners
        virtual void displayRoundEndInfo();

        // display the message when round started, and who's turn to play
        virtual void displayRoundStartInfo();

        // display available info for a human player
        virtual void displayAvailableInfo();

        // display the paly move for a computer player
        virtual void displayPlayInfo(const std::shared_ptr<Card> card);

        // display the discard move for a computer player
        virtual void displayDiscardInfo(const Card& card);

        // display the info for ragequit
        virtual void displayRagequitInfo();
};


#endif

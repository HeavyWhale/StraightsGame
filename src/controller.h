#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "tableau.h"
#include "player.h"
#include <string>
#include <memory>
#include <iostream>

class Controller {
    public:
        Controller(unsigned seed);
        ~Controller();

        bool gameIsOver();
        const int MAX_PLAYER = 4;

        bool addPlayer(std::string option);   
        void play(std::string option); 
        void discard(std::string option);
        void deck();
        void quit();
        void ragequit();

    private:
        std::unique_ptr<Tableau> _theTableau;
};

#endif

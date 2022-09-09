#include "controller.h"

Controller::Controller(unsigned seed)
     : _theTableau{std::make_unique<Tableau> (seed)} {}

Controller::~Controller() {}

bool Controller::gameIsOver() {
    return _theTableau->_gameIsOver;
}

bool Controller::addPlayer(std::string option) {
    if (option == "h") {
        _theTableau->invitePlayer(PlayerType::Human);
        return true;
    } else if (option == "c") {
        _theTableau->invitePlayer(PlayerType::Computer);
        return true;
    } else {
        std::cout << "Invalid option, please try again." << std::endl;
        return false;
    }
}

void Controller::play(std::string option) {
    try {
        Card ref {option.at(0), option.at(1)};
        _theTableau->play(ref);
    } catch (...) {
        std::cout << "This is not a legal play." << std::endl;
    }
}

void Controller::discard(std::string option) {
    try {
        Card ref {option.at(0), option.at(1)};
        _theTableau->discard(ref);
    } catch (NotInHandException& e) {
        std::cout << "You cannot discard the card " << e.getCard().repr() 
                  << ", since it's not in your hand." << std::endl;
    } catch (...) {
        std::cout << "You have a legal play. You may not discard." << std::endl;
    }
}

void Controller::deck() {
    _theTableau->deck();
}

void Controller::quit() {
    _theTableau->quit();
}

void Controller::ragequit() {
    _theTableau->ragequit();
}

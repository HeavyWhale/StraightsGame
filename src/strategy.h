#ifndef STRATEGY_H
#define STRATEGY_H

#include "info.h"

class Player;

class Strategy {
    public:
        Strategy(Player* player);
        virtual Info nextMove() = 0;
    protected:
        Player* _player;
};

class HumanStrategy : public Strategy {
    public:
        HumanStrategy(Player* player);
        Info nextMove() override;
};

class ComputerStrategy : public Strategy {
    public:
        ComputerStrategy(Player* player);
        Info nextMove() override;
};


#endif

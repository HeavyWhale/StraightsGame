#include "info.h"

Info::Info(State state, const Card refCard, std::shared_ptr<Card> card)
     : _state{state}, _refCard{refCard}, _card{card} {}

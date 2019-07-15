#include "Transition.h"
#include <cstring>

/*
    changechange!@!
*/

Transition::Transition(std::string initialState, char symbol, std::string endingState): initialState(initialState), symbol(symbol), endingState(endingState){

}

std::string Transition::getInitialState() const{
    return initialState;
}

char Transition::getSymbol() const{
    return symbol;
}

std::string Transition::getEndingState() const{
    return endingState;
}

void Transition::print(std::ostream& stream) const{
    stream << initialState << " -" << symbol << "-> " << endingState << std::endl;
}

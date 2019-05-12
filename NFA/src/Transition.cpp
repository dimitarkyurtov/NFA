#include "Transition.h"
#include <cstring>


Transition::Transition(char initialState, char symbol, char endingState): initialState(initialState), symbol(symbol), endingState(endingState){

}

char Transition::getInitialState() const{
    return initialState;
}

char Transition::getSymbol() const{
    return symbol;
}

char Transition::getEndingState() const{
    return endingState;
}

void Transition::print(std::ostream& stream) const{
    stream << initialState << " -" << symbol << "-> " << endingState << std::endl;
}

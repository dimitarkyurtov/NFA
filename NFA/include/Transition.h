#ifndef TRANSITION_H
#define TRANSITION_H
#include<iostream>


class Transition
{
    public:
        Transition(char initialState = '\0', char symbol = '\0', char endingState = '\0');
        void print(std::ostream& stream = std::cout) const;
        char getInitialState() const;
        char getSymbol() const;
        char getEndingState() const;

    private:
        char initialState;
        char symbol;
        char endingState;
};

#endif // TRANSITION_H

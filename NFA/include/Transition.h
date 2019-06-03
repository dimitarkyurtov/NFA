#ifndef TRANSITION_H
#define TRANSITION_H
#include<iostream>
#include<string>


class Transition
{
    public:
        Transition(std::string initialState = "", char symbol = '\0', std::string endingState = "");
        void print(std::ostream& stream = std::cout) const;
        std::string getInitialState() const;
        char getSymbol() const;
        std::string getEndingState() const;

    private:
        std::string initialState;
        char symbol;
        std::string endingState;
};

#endif // TRANSITION_H

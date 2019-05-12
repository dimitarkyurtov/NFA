#ifndef AUTOMATON_H
#define AUTOMATON_H
#include"Transition.h"
#include<iostream>

class Automaton
{
    public:
        Automaton();
        Automaton(const Automaton& other);
        const Automaton& operator=(const Automaton& other);
        bool isWordRecognisable(const char* word) const;
        bool addTransition(const Transition& other);
        bool addStartingState(const char& state);
        bool addEndingState(const char& state);
        Automaton* unite(const Automaton& other) const;
        void print(std::ostream& stream = std::cout) const;
        ~Automaton();

    private:
        char* states;
        char* initialStates;
        char* finalStates;
        Transition* deltaFunction;
        unsigned transitionCounter;
        unsigned transitionCapacity;
        void copy(const Automaton& other);
        void resize();
        bool isStartingState(const char& state) const;
        bool isEndingState(const char& state) const;
        void destroy();
};

#endif // AUTOMATON_H

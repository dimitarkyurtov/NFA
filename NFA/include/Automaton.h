#ifndef AUTOMATON_H
#define AUTOMATON_H
#include"Transition.h"
#include"Counter.h"
#include<iostream>
#include<string>

class Automaton
{
    public:
        Automaton();
        Automaton(const Automaton& other);
        Automaton(const char* word);
        Automaton(char singleton, Counter counter);
        const Automaton& operator=(const Automaton& other);
        bool Deterministic() const;
        void Determinate();
        bool Empty() const;
        bool Finite() const;
        bool isWordRecognisable(const char* word);
        bool addTransition(const Transition& other);
        bool addStartingState(const std::string& state);
        bool addEndingState(const std::string& state);
        Automaton* operator+(const Automaton& other);
        Automaton* operator+();
        Automaton* operator*(const Automaton& other);
        void print(std::ostream& stream = std::cout) const;
        ~Automaton();

    private:
        char* alphabet;
        std::string* states;
        unsigned statesSize;
        std::string* initialStates;
        unsigned initialStatesSize;
        std::string* finalStates;
        unsigned finalStatesSSize;
        Transition* deltaFunction;
        unsigned transitionCounter;
        unsigned transitionCapacity;
        void copy(const Automaton& other);
        void resize();
        void addState(const std::string& state);
        void cpyStringArray(std::string* str1, std::string* str2, unsigned size);
        bool recursion(const std::string state) const;
        bool recursion2(const std::string& state, std::string& previousStates) const;
        void function(std::string startingState, const char& symbol, std::string* queue, unsigned& queueCounter, Automaton* automatonHelper) const;
        bool isStartingState(const std::string& state) const;
        bool isEndingState(const std::string& state) const;
        bool isState(const std::string& state) const;
        Automaton* unite(const Automaton& other) const;
        Automaton* concat(const Automaton& other) const;
        Automaton* un() const;
        void destroy();
};

#endif // AUTOMATON_H

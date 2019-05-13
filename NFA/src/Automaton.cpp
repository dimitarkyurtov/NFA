#include "Automaton.h"
#include <cstring>

Automaton::Automaton()
{

    states = new char[1];
    states[0] = '\0';
    finalStates = new char[1];
    finalStates[0] = '\0';
    initialStates = new char[1];
    initialStates[0] = '\0';
    deltaFunction = new Transition[4];
    transitionCapacity = 4;
    transitionCounter = 0;
}

void Automaton::copy(const Automaton& other){
    deltaFunction = new Transition[other.transitionCounter];
    for(unsigned i = 0; i < transitionCounter; i ++){
        deltaFunction[i] = other.deltaFunction[i];
    }
    transitionCounter = other.transitionCounter;
    transitionCapacity = other.transitionCapacity;
    states = new char[strlen(other.states) + 1];
    initialStates = new char[strlen(other.initialStates) + 1];
    finalStates = new char[strlen(other.finalStates) + 1];
    strcpy(states, other.states);
    strcpy(initialStates, other.initialStates);
    strcpy(finalStates, other.finalStates);
}

void Automaton::resize(){
    transitionCapacity *= 2;
    Transition* newDeltaFunc = new Transition [transitionCapacity];
    for(unsigned i = 0; i < transitionCounter; i ++){
        newDeltaFunc[i] = deltaFunction[i];
    }
    delete []deltaFunction;
    deltaFunction = newDeltaFunc;
}

void Automaton::destroy(){
    delete []deltaFunction;
    delete []states;
    delete []initialStates;
    delete []finalStates;
}

Automaton::Automaton(const Automaton& other){
    copy(other);
}

const Automaton& Automaton::operator=(const Automaton& other){
    if(this != &other){
        destroy();
        copy(other);
    } return *this;
}

bool Automaton::addStartingState(const char& state){
    unsigned length = strlen(initialStates);
    char * newInitialStates = new char[length + 2];
    strcpy(newInitialStates, initialStates);
    newInitialStates[length] = state;
    newInitialStates[length+1] = '\0';
    delete initialStates;
    initialStates = newInitialStates;
    return true;
}

bool Automaton::addEndingState(const char& state){
    unsigned length = strlen(finalStates);
    char * newFinalStates = new char[length + 2];
    strcpy(newFinalStates, finalStates);
    newFinalStates[length] = state;
    newFinalStates[length+1] = '\0';
    delete finalStates;
    finalStates = newFinalStates;
    return true;
}

bool Automaton::addTransition(const Transition& other){
    if(transitionCounter == transitionCapacity){
        resize();
    }
    deltaFunction[transitionCounter++] = other;
    return true;
}

void Automaton::print(std::ostream& stream) const{
    for(unsigned i = 0; i < transitionCounter; i ++){
        deltaFunction[i].print(stream);
    }
}


bool Automaton::isStartingState(const char& state) const{
    unsigned length = strlen(initialStates);
    for(unsigned i = 0; i < length; i ++){
        if(state == initialStates[i]){
            return true;
        }
    }
    return false;
}

bool Automaton::isEndingState(const char& state) const{
    unsigned length = strlen(finalStates);
    for(unsigned i = 0; i < length; i ++){
        if(state == finalStates[i]){
            return true;
        }
    }
    return false;
}

bool Automaton::isWordRecognisable(const char* word) const{
    unsigned length = strlen(word);
    unsigned length2 = strlen(initialStates);
    char state;
    unsigned j;
    unsigned i;
    for(unsigned k = 0; k < length2; k ++){
        state = initialStates[k];
        i = 0;
        j = 0;
        while(i != length && j != transitionCounter){
            j = 0;
            while(j != transitionCounter && (deltaFunction[j].getInitialState() != state || word[i] != deltaFunction[j].getSymbol())){
                j ++;
            }
            if(j != transitionCounter){
                state = deltaFunction[j].getEndingState();
            }
            i ++;
        }
        if(i == length && isEndingState(state) && j != transitionCounter){
            return true;
        }
    }
    return false;
}

Automaton* Automaton::unite(const Automaton& other) const{
    Automaton* unity = new Automaton;
    unity->addStartingState('A');
    Transition transition;
    unsigned length = strlen(initialStates);
    for(unsigned i = 0; i < length; i ++){
        for(unsigned j = 0; j < transitionCounter; j ++){
            if(initialStates[i] == deltaFunction[j].getInitialState()){
                    transition = Transition('A', deltaFunction[j].getSymbol(), deltaFunction[j].getEndingState());
                    unity->addTransition(transition);
            }
        }
    }
    length = strlen(other.initialStates);
    for(unsigned i = 0; i < length; i ++){
        for(unsigned j = 0; j < other.transitionCounter; j ++){
            if(other.initialStates[i] == other.deltaFunction[j].getInitialState()){
                    transition = Transition('A', other.deltaFunction[j].getSymbol(), other.deltaFunction[j].getEndingState());
                    unity->addTransition(transition);
            }
        }
    }
    length = transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        if(!this->isStartingState(deltaFunction[i].getInitialState())){
            unity->addTransition(deltaFunction[i]);
        }

        if(this->isEndingState(deltaFunction[i].getEndingState())){
            unity->addEndingState(deltaFunction[i].getEndingState());
        }
    }

    length = other.transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        if(!other.isStartingState(other.deltaFunction[i].getInitialState())){
            unity->addTransition(other.deltaFunction[i]);
        }

        if(other.isEndingState(other.deltaFunction[i].getEndingState())){
            unity->addEndingState(other.deltaFunction[i].getEndingState());
        }
    }
    return unity;
}

Automaton::~Automaton()
{
    destroy();
}
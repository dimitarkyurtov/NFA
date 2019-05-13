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

Automaton::Automaton(char singleton, Counter counter){
    states = new char[1];
    states[0] = '\0';
    finalStates = new char[1];
    finalStates[0] = '\0';
    initialStates = new char[1];
    initialStates[0] = '\0';
    deltaFunction = new Transition[4];
    transitionCapacity = 4;
    transitionCounter = 0;
    this->addTransition(Transition(counter.getStarState(), singleton, counter.getEndState()));
}

Automaton::Automaton(char* word){
    unsigned length = strlen(word);
    Counter counter;
    Automaton automat(word[0], counter);
    ++counter;
    Automaton automatHelper;/*!!!!*/
    std::cout << counter.getStarState() << std::endl;
    for(unsigned i = 1; i < length; i ++){
        if(word[i] == ')'){
            automat = +automat;
            i++;
        }else
        if(word[i] == '+'){
            automatHelper = Automaton(word[i+1], counter);
            ++counter;
            i ++;
            automat = automat + automatHelper;
        }else
        if(word[i+1] == '*'){
            automatHelper = Automaton(word[i], counter);
            ++counter;
            i++;
            automatHelper = +automatHelper;
        }else{
            automatHelper = Automaton(word[i], counter);
            ++counter;
            std::cout << counter.getStarState() << std::endl;
            automatHelper.print();
        }
        automat = *(automat*automatHelper);
    }
    *this = automat;
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

const Automaton& Automaton::operator=(const Automaton* other){
    if(this != other){
        destroy();
        deltaFunction = new Transition[other->transitionCounter];
        for(unsigned i = 0; i < transitionCounter; i ++){
            deltaFunction[i] = other->deltaFunction[i];
        }
        transitionCounter = other->transitionCounter;
        transitionCapacity = other->transitionCapacity;
        states = new char[strlen(other->states) + 1];
        initialStates = new char[strlen(other->initialStates) + 1];
        finalStates = new char[strlen(other->finalStates) + 1];
        strcpy(states, other->states);
        strcpy(initialStates, other->initialStates);
        strcpy(finalStates, other->finalStates);
    } return *this;
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

        if(this->isStartingState(deltaFunction[i].getInitialState()) && this->isEndingState(deltaFunction[i].getInitialState())){
            unity->addEndingState('A');
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

        if(other.isStartingState(other.deltaFunction[i].getInitialState()) && other.isEndingState(other.deltaFunction[i].getInitialState())){
            unity->addEndingState('A');
        }
    }


    return unity;
}

Automaton* Automaton::concat(const Automaton& other) const{
    Automaton* concat = new Automaton;
    unsigned length = transitionCounter;
    unsigned length2 = other.transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        for(unsigned j = 0; j < length2; j ++){
            if(this->isEndingState(this->deltaFunction[i].getEndingState()) && other.isStartingState(other.deltaFunction[j].getInitialState())){
                concat->addTransition(Transition(deltaFunction[i].getEndingState(), other.deltaFunction[j].getSymbol(), other.deltaFunction[j].getEndingState()));
            }
            if(other.isEndingState(other.deltaFunction[j].getInitialState())){
                concat->addEndingState(deltaFunction[i].getInitialState());
            }
        }
    }

    length = transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        if(this->isStartingState(this->deltaFunction[i].getInitialState())){
            concat->addStartingState(this->deltaFunction[i].getInitialState());
        }
        concat->addTransition(deltaFunction[i]);
    }


    length = other.transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        if(other.isEndingState(other.deltaFunction[i].getEndingState())){
            concat->addEndingState(other.deltaFunction[i].getEndingState());
        }
        if(!other.isStartingState(other.deltaFunction[i].getInitialState())){
            concat->addTransition(other.deltaFunction[i]);
        }
    }
    return concat;
}

Automaton* Automaton::un() const{
    Automaton* un = new Automaton;
    unsigned length = transitionCounter;
    for(unsigned i = 0; i < length; i ++){
        un->addTransition(deltaFunction[i]);
        if(this->isStartingState(deltaFunction[i].getInitialState())){
            un->addStartingState(deltaFunction[i].getInitialState());
        }
        if(this->isEndingState(deltaFunction[i].getEndingState())){
            un->addEndingState(deltaFunction[i].getEndingState());
            for(unsigned j = 0; j < length; j ++){
                if(this->isStartingState(deltaFunction[j].getInitialState())){
                    un->addTransition(Transition(deltaFunction[i].getEndingState(), deltaFunction[j].getSymbol(), deltaFunction[j].getEndingState()));
                }
            }
        }
    }
    return un;
}

Automaton* Automaton::operator+(const Automaton& other){
    return this->unite(other);
}

Automaton* Automaton::operator+(){
    return this->un();
}

Automaton* Automaton::operator*(const Automaton& other){
    return this->concat(other);
}

Automaton::~Automaton()
{
    destroy();
}

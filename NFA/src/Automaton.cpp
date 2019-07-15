#include "Automaton.h"
#include <cstring>

Automaton::Automaton()
{
    /* change

        test3
    */

    states = new std::string[10];
    states[0] = "";
    alphabet = new char[2];
    alphabet[0] = 'a';
    alphabet[1] = 'b';
    statesSize = 0;
    finalStates = new std::string[10];
    finalStates[0] = "";
    finalStatesSSize = 0;
    initialStates = new std::string[10];
    initialStates[0] = "";
    initialStatesSize = 0;
    deltaFunction = new Transition[4];
    transitionCapacity = 4;
    transitionCounter = 0;
}

void Automaton::copy(const Automaton& other){
    strcpy(alphabet, other.alphabet);
    deltaFunction = new Transition[other.transitionCounter];
    for(unsigned i = 0; i < other.transitionCounter; i ++){
        deltaFunction[i] = other.deltaFunction[i];
    }
    transitionCounter = other.transitionCounter;
    transitionCapacity = other.transitionCapacity;
    states = new std::string[other.statesSize + 1];
    initialStates = new std::string[other.initialStatesSize + 1];
    finalStates = new std::string[other.finalStatesSSize + 1];
    unsigned length = other.statesSize;
    for(unsigned i = 0; i < length; i ++){
        states[i] = other.states[i];
    }
    length = other.initialStatesSize;
    for(unsigned i = 0; i < length; i ++){
        initialStates[i] = other.initialStates[i];
    }
    length = other.finalStatesSSize;
    for(unsigned i = 0; i < length; i ++){
        finalStates[i] = other.finalStates[i];
    }
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

bool Automaton::addTransition(const Transition& other){

    if(transitionCounter == transitionCapacity){
        resize();
    }
    deltaFunction[transitionCounter++] = other;
    return true;
}

/*
Automaton::Automaton(const char* word){
    states = new char[1];
    states[0] = '\0';
    finalStates = new char[1];
    finalStates[0] = '\0';
    initialStates = new char[1];
    initialStates[0] = '\0';
    deltaFunction = new Transition[4];
    transitionCapacity = 4;
    transitionCounter = 0;
    unsigned length = strlen(word);
    Automaton* automaton = new Automaton;
    Counter counter;
    Transition transition;
    unsigned j = 0;
    for(unsigned i = 0; i < length; i ++){
        if(word[i] == '('){
            this->addEndingState(counter.getStarState());
            automaton = new Automaton;
            j = i+1;
            automaton->addStartingState(counter.getStarState());
            while(j < length && word[j] != ')' && word[j]){
                    transition = Transition(counter.getStarState(), word[j], counter.getEndState());
                    ++counter;
                    automaton->addTransition(transition);
                    j ++;
                  }
            automaton->addEndingState(counter.getStarState());
            i = j+1;
            this->addStartingState('0');
            automaton->operator=(*(automaton->un()));
            this->operator=(*(this->concat(*automaton)));
           }
           else if(word[i] == '+'){
            automaton = new Automaton;
            j = i+1;
            automaton->addStartingState(counter.getStarState());
            while(j < length && word[j] != '+' && word[j] != '(' && word[j] != '*'){

                    transition = Transition(counter.getStarState(), word[j], counter.getEndState());
                    ++counter;
                    automaton->addTransition(transition);
                    j ++;
                  }
            automaton->addEndingState(counter.getEndState());
            i = j - 1;
            this->addStartingState('0');
            this->operator=(*(this->unite(*automaton)));
        }else {
            transition = Transition(counter.getStarState(), word[i], counter.getEndState());
            ++counter;
            this->addTransition(transition);
        }
    }
    this->addEndingState(counter.getStarState());
}*/

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

void Automaton::cpyStringArray(std::string* str1, std::string* str2, unsigned size){
    for(unsigned i = 0; i < size; i ++){
        str1[i] = str2[i];
    }
}

bool Automaton::Deterministic() const{
    for(unsigned i = 0; i < transitionCounter; i ++){
        for(unsigned j = 0; j < transitionCounter; j ++){
            if(i != j){
                if(deltaFunction[i].getInitialState() == deltaFunction[j].getInitialState() && deltaFunction[i].getSymbol() == deltaFunction[j].getSymbol()){
                    return false;
                }
            }
        }
    } return true;
}

bool Automaton::recursion(const std::string state) const{
    if(this->isStartingState(state)){
        return false;
    }else{
        for(unsigned i = 0; i < transitionCounter; i ++){
            if(deltaFunction[i].getEndingState().compare(state) == 0){
                return recursion(deltaFunction[i].getInitialState());
            }
        }
    }
    return true;
}

bool Automaton::Empty() const{
    unsigned length = finalStatesSSize;
    for(unsigned i = 0; i < length; i ++){
        if(!recursion(finalStates[i])){
            return false;
        }
    } return true;
}

bool Automaton::Finite() const{
    std::string previousStates;
    return !recursion2(deltaFunction[0].getInitialState(), previousStates);
}

bool Automaton::recursion2(const std::string& state, std::string& previousStates) const{
    for(unsigned i = 0; i < transitionCounter; i ++){
        if(deltaFunction[i].getInitialState() == state){
            previousStates += state;
            recursion2(deltaFunction[i].getEndingState(), previousStates);
        }
        for(unsigned j = 0; j < previousStates.length()-1; j ++){
            for(unsigned k = j+1; k < previousStates.length(); k ++){
                if(previousStates.at(j) == previousStates.at(k)){
                    return true;
                }
            }
        }
    }
    return false;
}



bool Automaton::addStartingState(const std::string& state){
    unsigned length = initialStatesSize;
    std::string * newInitialStates = new std::string[length + 1];
    cpyStringArray(newInitialStates, initialStates, length);
    newInitialStates[length] = state;
    initialStatesSize++;
    delete initialStates;
    initialStates = newInitialStates;
    return true;
}

bool Automaton::addEndingState(const std::string& state){
    unsigned length = finalStatesSSize;
    std::string * newFinalStates = new std::string[length + 1];
    cpyStringArray(newFinalStates, finalStates, length);
    newFinalStates[length] = state;
    finalStatesSSize++;
    delete finalStates;
    finalStates = newFinalStates;
    return true;
}

void Automaton::print(std::ostream& stream) const{
    for(unsigned i = 0; i < transitionCounter; i ++){
        deltaFunction[i].print(stream);
    }
}


bool Automaton::isStartingState(const std::string& state) const{
    unsigned length = initialStatesSize;
    for(unsigned i = 0; i < length; i ++){
        if(state.compare(initialStates[i]) == 0){
            return true;
        }
    }
    return false;
}

bool Automaton::isEndingState(const std::string& state) const{
    unsigned length = finalStatesSSize;
    for(unsigned i = 0; i < length; i ++){
        if(state == finalStates[i]){
            return true;
        }
    }
    return false;
}

bool Automaton::isState(const std::string& state) const{
    unsigned length = statesSize;
    for(unsigned i = 0; i < length; i ++){
        if(state == states[i]){
            return true;
        }
    }
    return false;
}

void Automaton::addState(const std::string& state){
    states[statesSize++] = state;
}

void Automaton::function(std::string startingState, const char& symbol, std::string* queue, unsigned& queueCounter, Automaton* automatonHelper) const{
    std::string str;
    bool isEndingState;
    for(unsigned i = 0; i < transitionCounter; i ++){
        if(startingState.find(deltaFunction[i].getInitialState()) != std::string::npos && deltaFunction[i].getSymbol() == symbol){
            if(this->isEndingState(deltaFunction[i].getEndingState())){
                isEndingState = 1;
            }
            str += deltaFunction[i].getEndingState();
        }
    }
    if(!str.empty()){
        automatonHelper->addTransition(Transition(startingState, symbol, str));
        if(isEndingState){
            automatonHelper->addEndingState(str);
        }
        bool br = 0;
        for(unsigned i = 0; i < queueCounter; i ++){
            if(queue[i] == str){
                br++;
            }
        }
        if(br == 0){
            queue[queueCounter++] = str;

        }
    }

}

void Automaton::Determinate(){
    unsigned length = initialStatesSize;
    Automaton* automatonHelper = new Automaton;
    std::string* queue = new std::string[100];
    unsigned queueCounter = 0;
    unsigned queueCounter2 = length;
    for(unsigned i = 0; i < length; i ++){
        automatonHelper->addStartingState(initialStates[i]);
    }
    for(unsigned i = 0; i < length; i ++){
        queue[queueCounter++] = initialStates[i];
        for(unsigned j = 0; j < 2; j ++){
            function(initialStates[i], alphabet[j], queue, queueCounter, automatonHelper);
        }
   }
   while(queueCounter != queueCounter2){
        for(unsigned i = 0; i < 2; i ++){
            function(queue[queueCounter2], alphabet[i], queue, queueCounter, automatonHelper);
        }
        queueCounter2++;
   }
   copy(*automatonHelper);
}

bool Automaton::isWordRecognisable(const char* word){
    if(!Deterministic()){
        Determinate();
    }
    unsigned length = strlen(word);
    unsigned length2 = initialStatesSize;
    std::string state;
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
    unity->addStartingState("A");
    Transition transition;

    unsigned length = initialStatesSize;
    for(unsigned i = 0; i < length; i ++){
        for(unsigned j = 0; j < transitionCounter; j ++){
            if(initialStates[i] == deltaFunction[j].getInitialState()){
                    transition = Transition("A", deltaFunction[j].getSymbol(), deltaFunction[j].getEndingState());
                    unity->addTransition(transition);
            }
        }
    }

    length = other.initialStatesSize;
    for(unsigned i = 0; i < length; i ++){
        for(unsigned j = 0; j < other.transitionCounter; j ++){
            if(other.initialStates[i] == other.deltaFunction[j].getInitialState()){
                    transition = Transition("A", other.deltaFunction[j].getSymbol(), other.deltaFunction[j].getEndingState());
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
            unity->addEndingState("A");
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
            unity->addEndingState("A");
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

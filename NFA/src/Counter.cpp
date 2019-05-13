#include "Counter.h"
#include<iostream>

Counter::Counter()
{
    startState = '0';
    endState = '1';
}

char Counter::getStarState() const{
    return startState;
}

char Counter::getEndState() const{
    return endState;
}

const Counter& Counter::operator++(){
    switch(endState){
        case '9': endState = 'a'; break;
        case 'z': endState = 'A'; break;
        case 'Z': std::cout << "OffLimit" << std::endl; break;
        default: endState ++;
    }

    switch(startState){
        case '9': startState = 'a'; break;
        case 'z': startState = 'A'; break;
        case 'Z': std::cout << "OffLimit" << std::endl; break;
        default: startState ++;
    }
}

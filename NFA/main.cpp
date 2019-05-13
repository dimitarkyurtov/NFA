#include <iostream>
#include"Transition.h"
#include"Automaton.h"
#include<cstring>

using namespace std;

int main()
{
    Transition  tr4('W', 'a', 'Q'), tr1('Q', 'a', 'R'), tr2('R', 'b', 'S'), tr3('S', 'a', 'T');
    Automaton automat, automat2;
    automat.addTransition(tr1);
    automat.addTransition(tr4);
    automat.addStartingState('W');
    automat.addEndingState('R');

    automat2.addTransition(tr2);
    automat2.addTransition(tr3);
    automat2.addStartingState('R');
    automat2.addEndingState('T');
    Automaton automat3("aaaa");
    automat3.print();
    return 0;
}

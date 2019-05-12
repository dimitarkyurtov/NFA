#include <iostream>
#include"Transition.h"
#include"Automaton.h"
#include<cstring>

using namespace std;

int main()
{
    Transition tr1('Q', 'a', 'R'), tr2('R', 'b', 'S'), tr3('S', 'a', 'T');
    Automaton automat, automat2;
    automat.addTransition(tr1);
    automat.addStartingState('Q');
    automat.addEndingState('R');

    automat2.addTransition(tr2);
    automat2.addStartingState('R');
    automat2.addEndingState('S');
    Automaton*  automat3= automat2.unite(automat);
    automat3->print();
    cout << automat3->isWordRecognisable("ab");
    return 0;
}

#include <iostream>
#include"Transition.h"
#include"Automaton.h"
#include<cstring>
void * __gxx_personality_v0=0;
void * _Unwind_Resume =0;

using namespace std;

int main()
{
    /* Lamoxd!!
        !!

        change3
    */
    Transition  tr4("q0", 'a', "q0"), tr1("q0", 'b', "q0"), tr2("q0", 'a', "q1"), tr3("q1", 'b', "q2");
    Automaton automat;
    automat.addTransition(tr4);
    automat.addTransition(tr1);
    automat.addTransition(tr2);
    automat.addTransition(tr3);
    automat.addStartingState("q0");
    automat.addEndingState("q2");
    automat.print();
    cout << endl << endl;
    cout << automat.isWordRecognisable("ababab");
    return 0;
}

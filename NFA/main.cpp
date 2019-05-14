#include <iostream>
#include"Transition.h"
#include"Automaton.h"
#include<cstring>



using namespace std;

int main()
{
    Transition  tr4('W', 'a', 'Q'), tr1('Q', 'a', 'R'), tr2('R', 'b', 'S'), tr3('S', 'a', 'T');
    Automaton automat3("dcba+ad");
    automat3.print();
    return 0;
}

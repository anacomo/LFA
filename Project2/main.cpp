#include <fstream>
#include "Automata.cpp"
using namespace std;
ifstream in("data.in");

int main()
{
    Automata A(5, 0);
    A.setInitState(0);
    A.addTransition(0, 1, 'a');
    A.addTransition(0, 4, 'l');
    A.addTransition(0, 1, 'l');
    A.addTransition(1, 2, 'l');
    A.addTransition(2, 3, 'l');
    A.addTransition(3, 5, 'l');
    A.addTransition(3, 4, 'b');
    A.addTransition(4, 5, 'a');
    A.addFinalState(5);
    //A.showMyAutomata();
    //Automata A;
    // reading a lambda nfa
    //in >> A;
    //A.graphVizAutomata();
    cout << "\n";
    A.lambdaCompletion();
    cout << "\nHello world!" << endl;
    A.showMyAutomata();
    A.graphVizAutomata();
    return 0;
}

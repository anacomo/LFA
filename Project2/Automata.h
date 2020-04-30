#ifndef AUTOMATA_H
#define AUTOMATA_H

#include<bits/stdc++.h>
using namespace std;

class Automata{
private:
    int nrStates, nrTransitions;
    vector <map <char, set <int> > > transitions;
    vector <map <char, int>> dfaTransitions;
    set <int> initialState, finalState;
    int initState;
    set <pair <int, int> > visited;
    const string sigma = "abcdefghijklmnopqrstuvwxyz";

    vector <bool> deadStates = vector <bool> (transitions.size(), false);
public:
    // constructors
    Automata();
    Automata(int n, int t);
    // adding elements to automata, which is a lambda NFA
    void addTransition(int source, int destination, char letter);
    void setInitialState(int start);
    void setInitState(int start);
    void addFinalState(int f);
    // setters
    void setNrTransitions(int value);
    void setNrStates(int value);
    void updateNrTransitions();
    // show Automata
    void showMyAutomata();
    // graphviz maker
    void graphVizAutomata();
    // reading the automata
    friend istream & operator >>(istream &in, Automata &A);

    /** Lambda NFA to DFA process:
    1. Lambda NFA to NFA
        a. Lambda Completion
        b. Lambda Transition Removal
    2. NFA to DFA
    3. DFA minimization
    */

    void lambdaCompletion();
    void nfaToDfa();
    void dfaMinimization();
    void findDeadStates();
    //destructor
    ~Automata();
};

#endif // AUTOMATA_H

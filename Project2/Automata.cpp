#include "Automata.h"

Automata::Automata(){
    //ctor
}
Automata::~Automata(){
    //dtor
}

Automata::Automata(int n, int t): nrStates(n), transitions(n+1), nrTransitions(t){

}

// adding elements to my automata
void Automata::addTransition(int source, int destination, char letter){
    this->transitions[source][letter].insert(destination);
    this->nrTransitions++;
}
void Automata::setInitialState(int start){
    this->initialState.insert(start);
}

void Automata::setInitState(int start) {
    this->initState = start;
}

void Automata::addFinalState(int f){
    finalState.insert(f);
}

void Automata::setNrTransitions(int value) {
    this->nrStates = value;
}

void Automata::setNrStates(int value) {
    this->nrTransitions = value;
}

void Automata::updateNrTransitions() {
    this->nrTransitions = 0;
    for(auto it : transitions)
        for(auto it2 : it)
            this->nrTransitions += it2.second.size();
    cout << "Updated number of transitions and it is " << this->nrTransitions << '\n';
}

// show my Automata
void Automata::showMyAutomata(){
    cout << "Number of states: " << nrStates << '\n';
    cout << "Number of transitions: " << nrTransitions << '\n';

    cout << "Initial states: ";
    set <int>::iterator itr;
    for(itr = initialState.begin(); itr != initialState.end(); ++itr)
        cout << *itr << " ";
    cout << '\n';

    cout << "Final States: ";
    for(itr = finalState.begin(); itr != finalState.end(); ++itr)
        cout << *itr << " ";
    cout << '\n';
}

void Automata::graphVizAutomata(){
    cout << "Copy this code and run it in GraphViz\n";
    cout << "digraph finite_state_machine{\n\trankdir = LR;\n";
    cout << "\tnode[shape = doublecircle]; ";
    set <int>::iterator itr;
    for(itr = finalState.begin(); itr!= finalState.end(); ++itr)
        cout << *itr << " ";
    cout << ";\n";
    cout << "\tnode[shape = circle];\n";

    // creating transitions
        for(int i = 0; i < this->nrStates; i++)
            for(auto startState : transitions[i])
                for(auto transItr : startState.second){
                    cout << '\t';
                    cout << i << " -> ";
                    cout << transItr << " ";
                    cout << "[label = \"" << startState.first << "\"];\n";
                    }
    // creating initial states
    cout << "\t";
    cout << "node [shape = plaintext, label=\" \"]; " ;
    for(itr = initialState.begin(); itr != initialState.end(); itr++)
        cout << "s" << *itr << " ";
    cout << ";\n";
    for(itr = initialState.begin(); itr != initialState.end(); itr++)
        cout << "\ts" << *itr << " -> " << *itr << "\n";

    cout << "\t}\n";
}

istream & operator >>(istream &in, Automata &A){
        /* Automata is given by (Q, Sigma, delta, s, F), where
        1. Q is the number of states
        2. Sigma is the alphabet
        3. delta is the transition function, delta : Q x Sigma -> Q
        4. s is the start state
        5. F is the final state set

        Rules for reading the automata data:
        1. Number of states
        2. Transitions 0, 1, 'a'
        3. Initial State
        4. Number of final states
        5. Final states
        */
        // reading the number of states
        int n;
        in >> n;
        A.setNrStates(n);
        int t;
        in >> t;
        A.setNrTransitions(t);
        //A = Automata(n, t);
        int source, destination;
        char letter;
        // reading the transitions
        for(int i = 0; i < t; ++i){
            in >> source >> destination >> letter;
            A.addTransition(source, destination, letter);
            }
        // reading the initial state
        int start;
        in >> start;
        A.setInitialState(start);
        // reading the number of final states
        int finalst, f;
        in >> finalst;
        for(int i = 0; i < finalst; ++i){
            in >> f;
            A.addFinalState(f);
            }
        return in;
    }

/// actual homework functions

void Automata::lambdaCompletion(){
    /* Theory: Lambda Completion
    for p, q, r in Q
        whenever (p, l, q), (q, x, r) in delta(transitions)
        add (p, x, r) to delta
    until no new transitions are added to delta

    Lambda Transition Removal
    whenever (p, l, q) in delta and p is inital state
        make q initial state
    whenever (p, l, q) in delta and q is final state
        make p final state
    */
    bool addedtransition = true;
    while(addedtransition){
        addedtransition = false;
        for(int i = 0; i < this->nrStates; i++){
            if(this->transitions[i]['l'].count('l'))
                continue;
            for(auto itrTrans : this->transitions[i]['l']){
                for(auto state : this->transitions[itrTrans]){
                    for(auto it2 : state.second){
                        //cout << "i added "<< i << ' ' << it2 << '\n';
                        this->transitions[i][state.first].insert(it2);
                        addedtransition = true;
                    }
                }
            // add initial states
            if(this->initialState.find(i) != this->initialState.end()){
                this->initialState.insert(itrTrans);
                //cout << "i added " << itrTrans << " as initial state\n";
                addedtransition = true;
            }
            // add final states
            if(this->finalState.find(itrTrans) != this->finalState.end()){
                this->finalState.insert(i);
                //cout << "i added " << i << "as final state\n";
                addedtransition = 1;
            }
            }
        this->transitions[i]['l'].clear();
        }
    }
    updateNrTransitions();
}

void Automata::nfaToDfa() 
{
    vector <map <char, int> > newTrans;
    int newInitState;
    set <int> newFinalState;
    map < set<int>, int > subset;
    set <int> tmp;
    queue <set <int> > que;
    int i = 0;
    tmp.insert(newInitState);
    que.push(tmp);
    if(this->finalState.count(this->initState))
        newFinalState.insert(i);
    subset[tmp] = i;
    i++;
    tmp.clear();

    while(!que.empty())
    {
        set <int> cStates = que.front();
        que.pop();
        for(char c : sigma)
            {
                for(auto it1 : cStates)
                {
                    for(auto it2 : transitions[it1][c])
                        tmp.insert(it2);
                }
            if(tmp.empty())
                continue;
            if(subset.find(tmp) == subset.end())
                {
                    subset[tmp] = i;
                    i++;
                    for(auto it2 : tmp)
                    {
                        if(this->finalState.find(it2) != this->finalState.end())
                            newFinalState.insert(subset[tmp]);
                    }
                newTrans.emplace_back(map <char, int>());
                que.push(tmp);
                }
            newTrans[subset[cStates]][c] = subset[tmp];
            tmp.clear();
            }
    }
    this->initState = newInitState;
    this->finalState = newFinalState;
    this->dfaTransitions = newTrans;
}

void Automata::findDeadStates() {
    queue <int> q;
    q.push(this->initState);
    while (!q.empty())
    {
        int aState = q.front();
        q.pop();
        for(auto tr : this->dfaTransitions[aState])
            if(this->deadStates[tr.second] == true)
            {
                this->deadStates[tr.second] = false;
                q.push(tr.second);
            }

    }
    
}


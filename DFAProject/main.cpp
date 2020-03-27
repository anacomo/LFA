#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ifstream in("data.in");
//this project accepts only Deterministic Finite Automata
class Automata
{
private:
    int nrStates, nrTransitions, nrFinalStates, initialState;
    set <int> finalState;
    multimap < pair <int, int>, char> transitions;
    int nrWords;
    string word;
    bool visited[100][100];

public:
    Automata()
    {   in >> nrStates;
        cout << "Number of states: " << nrStates << '\n';
        //Transitions
        in >> nrTransitions;
        cout << "Number of transitions: " << nrTransitions << '\n';
        int source, destination;
        char letter;
        for(int i = 0; i < nrTransitions; ++i)
        {
            in >> source >> destination >> letter;
            pair <int, int> p;
            p.first = source;
            p.second = destination;
            transitions.insert(pair <pair <int, int>, char> (p, letter));
        }
        multimap < pair <int, int>, char> ::iterator itr;
        for(itr = transitions.begin(); itr != transitions.end(); ++itr)
            cout << itr -> first.first << " " << itr -> first.second << " "<< itr -> second << '\n';
        // Initial State
        in >> initialState;
        cout << "Initial state: " << initialState << '\n';
        // Final States
        in >> nrFinalStates;
        cout << "Number of final states: " << nrFinalStates << '\n';
        int f;
        for(int i = 0; i < nrFinalStates; ++i)
        {
            in >> f;
            finalState.insert(f);
        }
        set <int> ::iterator itr2;
        for(itr2 = finalState.begin(); itr2 != finalState.end(); ++itr2)
            cout << *itr2 << " ";
        cout << '\n';
        //trebuie sa schimb ca sa iau fiecare word pe rand
        // mai bine fac un get pentru fiecare word
        // hai ca am schimbat pana la urma
        in >> nrWords;
        cout << "Number of words: " << nrWords << '\n';
    }
    bool acceptedDFA(string word);
    void showResultsDFA();
};

bool Automata::acceptedDFA(string word){
    int currentState = this->initialState;
    int len = word.length();
    bool found = 1;
    for(int i = 0; i < len && found == 1; i++)
        {found = 0;
        //caut tranzitia potrivita
        for(int j = 0; j < this->nrStates; ++j)
            if(transitions.find(make_pair(currentState, j))->second == word[i])
                {//cout << "e bun ";
                currentState = j;
                found = 1;
                }
        if(found == 0)
            return 0;
        }
    if(finalState.find(currentState) != finalState.end())
        return 1;
    return 0;
}
void Automata::showResultsDFA(){
        for(int i = 0; i < nrWords; ++i)
            {in >> word;
            cout << word << " " << acceptedDFA(word) << '\n';
            }
}
int main()
{
    Automata A;
    A.showResultsDFA();
    cout <<"\n";
    cout << "Hello world!" << endl;
    return 0;
}

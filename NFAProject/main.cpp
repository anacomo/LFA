#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ifstream in("data.in");
ofstream out("data.out");

class Automata{
    int nrStates, nrTransitions, nrFinalStates, initialState;
    set <int> finalState;
    vector <map <char, vector <int> > > transitions;
    int nrWords;
    string word;
    //bool visited[100][100];
    set <pair <int, int>> visited;
public:
    Automata();
    bool acceptedNFA(string word, int currentState, unsigned int i);
    void showResultsNFA();
    void shortestElements(int k);
};
Automata::Automata(){
    in >> nrStates;
    cout << "Number of states: " << nrStates << '\n';
    //Transitions
    in >> nrTransitions;
    cout << "Number of transitions: " << nrTransitions << '\n';
    int source, destination;
    char letter;
    vector<map<char, vector<int>>>::iterator itr;
    for(int i = 0; i < nrTransitions; ++i)
    //for(itr = transitions.begin(); itr != transitions.end(); ++itr)
        {in >> source >> destination >> letter;
        transitions[source][letter].push_back(destination);
        }
    ///for(i = 0; i < nrTransitions; i++)
    //incerc sa fac o afisare ceva
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
}
bool Automata::acceptedNFA(string word, int currentState, unsigned int i){
    visited.insert(make_pair(currentState, i));
    if(i == word.size())
        {if(finalState.find(currentState) != finalState.end())
            return true;
        else
            return false;
        }
    bool accepted = false;
    if(transitions[currentState].find(word[i]) != transitions[currentState].end())
        for(auto itr : transitions[currentState][word[i]])
            if(visited.find(make_pair(itr, i + 1)) == visited.end())
                accepted = accepted || acceptedNFA(word, itr, i+1);
    return accepted;
}
void Automata::showResultsNFA(){
    visited.clear();
    for(int i = 0; i < nrWords; ++i)
        {in >> word;
        cout << word << " " << acceptedNFA(word, initialState, 0) << '\n';
        }
}
void Automata::shortestElements(int k){
    int i = 0;
    queue <pair <int, string>> queue1;
    string word;
    queue1.push(make_pair(initialState, word));
    while(!queue1.empty() && i <= 1e4 && k >= 1)
        {int state = queue1.front().first;
        word = queue1.front().second;
        queue1.pop();
        if(finalState.find(state) != finalState.end())
            {k--;
            cout << word <<"\n";
            }
        for(auto itr : transitions[state])
            {word.push_back(itr.first);
            for(auto itr2: itr.second)
                queue1.push(make_pair(itr2, word));
            word.pop_back();
            }
        i++;
        }
}
int main()
{   Automata A;
    cout << "Hello world!" << endl;
    return 0;
}

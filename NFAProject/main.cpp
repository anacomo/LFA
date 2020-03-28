#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
ifstream in("data.in");

class Automata{
    int nrStates, initialState, nrTransitions;
    vector<map <char, vector <int> > >transitions;
    set <int> finalState;
    set <pair <int, int>> visited;
public:
    Automata(){}
    Automata(int n, int t) : nrStates(n), transitions(n + 1), nrTransitions(t){}
    void addTransition(int source, int destination, char letter){
        transitions[source][letter].push_back(destination);
    }
    void setInitialState(int start){
        initialState = start;
    }
    void addFinalState(int f){
        finalState.insert(f);
    }
    void showMyAutomata(){
        cout << "Number of states : " << nrStates << endl;
        cout << "Number of transitions: " << nrTransitions << endl;
        //iterating through the transitions
        //vector<map <char, vector <int> > > :: iterator it;
        //for(it = transitions.begin(); it != transitions.end(); ++it)
            //cout << it.first;
        //for(int i = 0; i < nrStates; ++i)
            //if(transitions[i]['a'][0])
                //cout << transitions[i]['a'][0];
        //for(int i = 0; i < nrTransitions; ++i)
            //cout << transitions[i].first;
        //ma las jur
        cout << "Initial state: " << initialState << endl;
        cout << "Final states: ";
        set <int>::iterator itr;
        for(itr = finalState.begin(); itr != finalState.end(); ++itr)
            cout << *itr << " ";
        cout << endl;
        //cout << "Number of words: " << nrWords;
    }
    bool acceptedNFA(string &word, int state, unsigned int i){
        visited.insert(make_pair(state, i));
        if(i == word.size())
            {if(finalState.find(state) != finalState.end())
                return true;
            else
                return false;
            }
        bool accepted = false;
        if(transitions[state].find(word[i]) != transitions[state].end())
            for(auto j : transitions[state][word[i]])
                if(visited.find(make_pair(j, i+1)) == visited.end())
                    accepted |= acceptedNFA(word, j, i+1);
        return accepted;
    }
    void showResultsNFA(string word){
        visited.clear();
        cout << word << ' ' << acceptedNFA(word, initialState, 0);
    }
    void firstWords(int k){
        int i = 0;
        queue <pair <int, string> > queue1;
        string word;
        queue1.push(make_pair(initialState, word));
        while(!queue1.empty() && i < k)
            {int state = queue1.front().first;
            word = queue1.front().second;
            queue1.pop();
            if(finalState.find(state) != finalState.end())
                {i++;
                cout << word << '\n';
                }
            for(auto itr : transitions[state])
                {word.push_back(itr.first);
                for(auto itr1 : itr.second)
                    queue1.push(make_pair(itr1, word));
                word.pop_back();
                }
            }
    }
    friend istream & operator>>(istream &in, Automata &A){
        // reading the number of states
        int n;
        in >> n;
        //reading the number of transitions
        int t;
        in >> t;
        A = Automata(n, t);
        int source, destination;
        char letter;
        //reading the transitions
        for(int i = 0; i < t; ++i)
            {in >> source >> destination >> letter;
            A.addTransition(source, destination, letter);
            }
        // reading the initial state
        int start;
        in >> start;
        A.setInitialState(start);
        //reading the number of the final states
        int finalst, f;
        in >> finalst;
        //reading the final states
        for(int i = 0; i < finalst; ++i)
            {in >> f;
            A.addFinalState(f);
            }
        return in;
    }
};
int main()
{/*   Automata A(5, 5);
    A.setInitialState(0);
    A.addTransition(0, 1, 'a');
    A.addTransition(1, 2, 'b');
    A.addTransition(2, 1, 'a');
    A.addTransition(0, 3, 'a');
    A.addTransition(3, 4, 'd');
    A.addFinalState(1);
    A.addFinalState(2);
    A.addFinalState(3);
    A.addFinalState(4);
    A.showMyAutomata();
    A.showResultsNFA("abababababad");*/
    Automata A;
    in >> A;
    A.showMyAutomata();
    string word;
    int nrWords;
    in >> nrWords;
    cout << "\nTests: \n";
    for(int i = 0; i < nrWords; ++i)
        {in >> word;
        A.showResultsNFA(word);
        cout << '\n';
        }
    cout << "\nFirst words: \n";
    A.firstWords(100);
    cout << "Hello world!" << endl;
    return 0;
}

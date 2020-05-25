#include <set>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

map<string, set<string>> oldG, newGrammar; // grammar
const string EPSILON = "l";

set<string> gEpsilon;
string newGrammar_start;
ifstream fin("data.in");

set<string> newGrammar_symbols; //nodurile din newGrammar;
struct Automata
{
    map<string, set<pair<string, char>>> transitions;
    string start;
    set<string> ends;
    int nrStates = 0;
    int nrTrans = 0;
};
Automata automata;

int main()
{
    // rg -> epsilon free gr
    string leftSide, rightSide;
    while (fin >> leftSide >> rightSide)
    {
        oldG[leftSide].insert(rightSide);
        if (rightSide != EPSILON)
        {
            newGrammar[leftSide].insert(rightSide);
            gEpsilon.insert(leftSide);
        }
    }
    // for every N-l
    for (auto &leftSide : gEpsilon)
    {
        for (auto const &[key, rightSide] : newGrammar)
        {
            for (auto &x : rightSide)
            {
                if (auto pos = x.find(leftSide); pos != string::npos)
                {
                    string aux = x;
                    aux.erase(pos, leftSide.length());
                    newGrammar[key].insert(aux);
                }
            }
        }
    }

    if (oldG["S"].find(EPSILON) != oldG["S"].end())
    {
        newGrammar["S0"].insert(EPSILON);
        for (auto &x : newGrammar["S"])
        {
            newGrammar["S0"].insert(x);
        }
        newGrammar_start = "S0";
    }
    else
    {
        newGrammar_start = "S";
    }

    automata.start = newGrammar_start;
    automata.ends.insert("D0");
    if (newGrammar[newGrammar_start].find(EPSILON) != newGrammar[newGrammar_start].end())
        automata.ends.insert(newGrammar_start);

    for (auto const &[leftSide, val] : newGrammar)
    {
        for (auto &rightSide : val)
        {
            if (rightSide != EPSILON)
            {
                if (rightSide.length() == 1)
                {
                    automata.transitions[leftSide].insert(make_pair("D0", rightSide[0]));
                }
                else
                {

                    int posFin, posNotFin;
                    if (rightSide[0] >= 'a' && rightSide[0] <= 'z')
                    {
                        posFin = 0;
                        posNotFin = 1;
                    }
                    else
                    {
                        posFin = 1;
                        posNotFin = 0;
                    }
                    automata.transitions[leftSide].insert(make_pair(string(1, rightSide[posNotFin]), rightSide[posFin]));
                }
            }
        }
    }

    for (auto const &[key, rightSide] : newGrammar)
    {
        cout << key << ' ';
        for (auto &x : rightSide)
        {
            cout << x << ' ';
        }
        cout << '\n';
    }

    cout << endl;

    for (auto const &[key, val] : automata.transitions)
    {
        for (auto &p : val)
        {
            automata.nrTrans++;
            newGrammar_symbols.insert(key);
            newGrammar_symbols.insert(p.first);
        }
    }
    cout << newGrammar_symbols.size() << '\n'
         << automata.nrTrans << '\n';
    for (auto const &[key, val] : automata.transitions)
    {
        for (auto &p : val)
        {
            cout << key << ' ' << p.first << ' ' << p.second << '\n';
        }
    }
    cout << newGrammar_start << '\n'
         << automata.ends.size() << '\n';
    for (auto &x : automata.ends)
        cout << x << ' ';
    return 0;
}
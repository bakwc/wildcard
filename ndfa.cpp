#include <iostream>
#include "ndfa.h"

TNdfa::TNdfa(const std::string &regexp) {
    const char* cregexp = regexp.c_str();
    for (size_t i = 0; i < regexp.size() + 1; i++) {
        if (cregexp[i] != '*') {
            TState state;
            state.SecondActive = false;
            state.Transition1.Symbol = regexp[i];
            state.Transition1.StateNum = States.size() + 1;

            States.push_back(state);
        } else {
            TState state;
            state.SecondActive = true;
            state.Transition1.Symbol = regexp[i + 1];
            state.Transition1.StateNum = States.size() + 1;

            state.Transition2.Symbol = '?';
            state.Transition2.StateNum = States.size();

            States.push_back(state);
            i++;
        }
    }
    CurrStates.clear();
    CurrStates.push_back(0);
}

bool TNdfa::CheckWord(const std::string &word) {
    CurrStates.clear();
    CurrStates.push_back(0);
    const char* cword = word.c_str();
    EResult res = RES_Failed;
    for (size_t i = 0; i < word.size() + 1; i++) {
        res = AddSymbol(cword[i]);
        if (res == RES_Failed) {
            break;
        }
    }
    return res == RES_Finished;
}

void TNdfa::Print() {
    for (size_t i = 0; i < States.size(); i++) {
        std::cout << i << " -" <<
                     States[i].Transition1.Symbol << "-> " <<
                     States[i].Transition1.StateNum << "\n";
        if (States[i].SecondActive) {
            std::cout << i << " -" <<
                         States[i].Transition2.Symbol << "-> " <<
                         States[i].Transition2.StateNum << "\n";
        }
    }
}

void CheckAndAdd(std::vector<int>& states,
                 const TTransition& transition,
                 char symbol)
{
    if (transition.Symbol == symbol ||
            transition.Symbol == '?')
    {
        states.push_back(transition.StateNum);
    }
}

EResult TNdfa::AddSymbol(char symbol) {
    std::vector<int> newStates;
    for (size_t i = 0; i < CurrStates.size(); i++) {
        CheckAndAdd(newStates,
                    States[CurrStates[i]].Transition1,
                    symbol);
        if (States[CurrStates[i]].SecondActive) {
            CheckAndAdd(newStates,
                        States[CurrStates[i]].Transition2,
                        symbol);
        }
    }

    bool finishedState = false;
    for (size_t i = 0; i < newStates.size(); i++) {
        if (newStates[i] == States.size()) {
            finishedState = true;
        }
    }

    if (newStates.size() == 0) {
        return RES_Failed;
    }
    if (symbol == '\0' && finishedState) {
        return RES_Finished;
    }
    CurrStates = newStates;
    return RES_Ok;
}

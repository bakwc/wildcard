#pragma once
#include <string>
#include <vector>

struct TTransition {
    char Symbol;
    int StateNum;
};

struct TState {
    TTransition Transition1;
    TTransition Transition2;
    bool SecondActive;
};

enum EResult {
    RES_Ok,
    RES_Failed,
    RES_Finished
};

class TNdfa {
public:
    TNdfa(const std::string& regexp);
    void Print();
    bool CheckWord(const std::string& word);
    EResult AddSymbol(char symbol);
private:
    std::vector<int> CurrStates;
    std::vector<TState> States;
};

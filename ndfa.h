/*
   Wild card matching algorithm.
 (based on multistate NDFA)
 https://github.com/bakwc/wildcard
 */
#pragma once
#include <string>
#include <vector>

struct TState;
struct TTransition;

class TWildcardNdfa {
    enum EResult {
        RES_Ok,
        RES_Failed,
        RES_Finished
    };
public:
    TWildcardNdfa(const std::string& regexp);
    bool Match(const std::string& word);
public:
    void Print();
    EResult AddSymbol(char symbol);
    void Reset();
private:
    bool CheckAndAdd(std::vector<int>& states,
                     const TTransition& transition,
                     char symbol);
private:
    std::vector<int> CurrStates;
    std::vector<TState> States;
};

struct TTransition {
    char Symbol;
    int StateNum;
};

struct TState {
    TTransition Transition1;
    TTransition Transition2;
    bool SecondActive;
};


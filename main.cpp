#include <iostream>
#include "ndfa.h"

using namespace std;

int main()
{
    TNdfa regexp("s?f");

    regexp.Print();


    if (regexp.CheckWord("ssdf")) {
        cout << "Matched!\n";
    } else {
        cout << "Not matched!\n";
    }
    return 0;
}


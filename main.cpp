#include <iostream>
#include "ndfa.h"

using namespace std;

int main()
{
    TNdfa regexp("abc*q?c");

    regexp.Print();


    if (regexp.CheckWord("aqc")) {
        cout << "Matched!\n";
    } else {
        cout << "Not matched!\n";
    }
    return 0;
}


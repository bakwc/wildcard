#include <iostream>
#include "ndfa.h"

using namespace std;

int main()
{
    TWildcardNdfa wildcard("*@*.com");
    if (wildcard.Match("example@example.com")) {
        cout << "Matched!\n";
    } else {
        cout << "Not matched!\n";
    }
    return 0;
}


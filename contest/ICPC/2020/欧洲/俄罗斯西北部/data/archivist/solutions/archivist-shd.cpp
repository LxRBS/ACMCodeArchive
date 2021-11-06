#include <iostream>
#include <string>

int main () {
    int year;
    std::cin >> year;

    std::string res;
    switch (year) {
        case 1996:
        case 1997:
        case 2000:
        case 2007:
        case 2008:
        case 2013:
        case 2018: res = "SPbSU"; break;

        case 2006: res = "PetrSU, ITMO"; break;

        default: res = "ITMO"; break;
    }

    std::cout << res << "\n";
    return 0;
}

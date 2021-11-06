#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef long long ll;

int main() {
    //for (ll i = 1; i <= 30; ++i) {
        ll i = 654;
        ofstream curfile;
        curfile.open(to_string(i) + string(".in"));
        curfile << i << endl;
        curfile.close();
    //}
}

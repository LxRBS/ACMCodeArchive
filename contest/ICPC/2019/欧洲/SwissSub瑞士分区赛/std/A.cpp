#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

bool is_seq_arithmetic(vector<long long> V) {
    sort( V.begin(), V.end() );
    long long D = V[1] - V[0];
    for (int i=0; i<int(V.size()); ++i) if (V[i] != V[0] + i*D) return false;
    return true;
}

int main() {
    vector<long long> ages(6);
    for (long long &x : ages) cin >> x;
    sort( ages.begin(), ages.end() );
    vector<long long> possible_differences = { ages[1] - ages[0], ages[2] - ages[1] };
    set<long long> answers;
    for (long long d : possible_differences) for (long long x : ages) for (long long add : vector<long long>{x-d,x+d}) if (add > 0) {
        vector<long long> new_ages = ages;
        new_ages.push_back(add);
        if (is_seq_arithmetic(new_ages)) answers.insert(add);
    }
    for (long long x : answers) cout << x << endl;
}
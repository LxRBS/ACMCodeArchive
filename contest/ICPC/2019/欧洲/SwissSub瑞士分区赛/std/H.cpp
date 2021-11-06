#include <algorithm>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    int W;
    cin >> W;
    map< string, string > wordlist;
    for (int w=0; w<W; ++w) {
        string word;
        cin >> word;
        string sorted_word = word;
        sort( sorted_word.begin(), sorted_word.end() );
        if (wordlist.count(sorted_word) == 0) wordlist[sorted_word] = word;
    }

    int Q;
    cin >> Q;
    for (int q=0; q<Q; ++q) {
        string query;
        cin >> query;
        sort( query.begin(), query.end() );
        string answer = "";
        for (int subset = 1; subset < (1<<9); ++subset) {
            string used = "";
            for (int i=0; i<9; ++i) if (subset & 1<<i) used += query[i];
            if (wordlist.count(used) == 0) continue;
            if (used.size() < answer.size()) continue;
            if (used.size() > answer.size()) { answer = wordlist[used]; continue; }
            answer = min( answer, wordlist[used] );
        }
        if (answer == "") answer = "IMPOSSIBLE";
        cout << answer << "\n";
    }
}
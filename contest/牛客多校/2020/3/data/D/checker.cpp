#include <bits/stdc++.h>
#ifdef HOME
#include "/Users/dreamoon/Code/MTF/testlib.h"
#else
#include "testlib.h"
#endif
using namespace std;
int n, m;
const int MAX_V = 1000 * 1000 * 1000;
pair<int,int> read_pair(InStream& in){
    int x=in.readInt(-MAX_V, MAX_V);
    int y=in.readInt(-MAX_V, MAX_V);
    return make_pair(x,y);
}
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0 ,1, 0, -1};
inline int readAndCheckAnswer(InStream& in, int cs) {
    std::vector<std::pair<int,int>> a(n);
    string yes_no = in.readToken();
    if(yes_no == "No") return 0;
    if(yes_no != "Yes") in.quitf(_wa, "the first line of each query must be Yes/No (test %d)", cs);
    set<pair<int,int>> AA;
    for(int i = 0; i < n; i++) {
        a[i] = read_pair(in);
        if(AA.count(a[i])) {
            in.quitf(_wa, "there are two black grid at the same position (test %d)", cs);
        }
        AA.insert(a[i]);
    }
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            pair<int,int> nxt=make_pair(a[i].first + dx[j], a[i].second + dy[j]);
            if(!AA.count(nxt)) cnt++;
        }
    }
    if(cnt != m) {
        in.quitf(_wa, "Test %d request %d pairs. But there are %d pairs.", cs, m, cnt);
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    for(int cs = 1; cs <= T; cs++) {
        n = inf.readInt();
        m = inf.readInt();
        int ja = readAndCheckAnswer(ans, cs);
        int pa = readAndCheckAnswer(ouf, cs);
        if(ja > pa) {
            quitf(_wa, "Jury find a better solution one test %d", cs);
        }
        else if(ja < pa) {
            quitf(_fail, "Participant find a better solution on test %d", cs);
        }
    }

    quitf(_ok, "correct answer");
}


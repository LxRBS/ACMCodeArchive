#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;++i)
#include "testlib.h"

using namespace std;

const int N=1e6+5;
int a[N],n,Ans[N];
string s;
set<pair<int,int>>nset;
int sta[N],top,cnt;
inline int readAndCheckAnswer(InStream& in) {
    string ss = in.readLine("[A-Za-z]{2,3}");
    if (ss == "NO") {
        return -1;
    } else if (ss == "YES") {
        rep(i,n)Ans[i]=in.readInt(1, n);
        nset.clear();
        top=cnt=0;
        rep(i,n<<1)if(s[i-1]=='('){
            auto p=make_pair(sta[top],Ans[++cnt]);
            if(nset.find(p)!=nset.end())
                in.quitf(_wa, "Not unique at %d", cnt);
            nset.insert(p);
            sta[++top]=cnt;
        }else --top;
        sort(a+1,a+n+1);
        sort(Ans+1,Ans+n+1);
        rep(i,n)if(a[i]!=Ans[i])
            in.quitf(_wa, "Not the same as input: %d as opposed to %d", Ans[i], a[i]);
        return 1;
    } else
        in.quitf(_wa, "Output should have 'YES' or 'NO' in the first line");
    return 0;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    //i won't be doing val
    n = inf.readInt();
    inf.readEoln();
    s = inf.readLine();
    rep(i,n)a[i] = inf.readInt();

    int ja = readAndCheckAnswer(ans);
    int pa = readAndCheckAnswer(ouf);

    if(ja != -1 && pa == -1)
        quitf(_wa, "Jury has the answer but participant has not");
    if(ja == -1 && pa != -1)
        quitf(_fail, "Participant has the answer but jury has not");

    quitf(_ok, "n=%d", n);
}

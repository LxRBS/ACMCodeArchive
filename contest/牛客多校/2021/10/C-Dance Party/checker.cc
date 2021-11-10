#include "testlib.h"
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi;
int n, k;
vector<vi> a;
vi b,vis;

int readAnswer(InStream &in) {
	int ans = in.readInt(-1, 1000000000);

	if (ans == -1)
		return ans;
	else {
        b = vector<int>(n);
        vis = vector<int>(n);
        b[0] = ans; vis[0] = 0;
        for (int i=1;i<n;i++) b[i] = in.readInt(-1, 1000000000), vis[i] = 0;
        for (int i=0;i<n;i++){
            if (b[i]<1||b[i]>n||vis[b[i]-1]){
                in.quitf(_wa,"not a permutation");
            }
            vis[b[i]-1]=1;
            for (auto x:a[i]){
                if (x==b[i]){
                    in.quitf(_wa,"The %dth women chooses a partner on her list",i+1);
                }
            }
        }
	}

	return 1;
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);

	n = inf.readInt();

	a = vector<vi>(n);
	for (int i = 0; i < n; ++i){
        k = inf.readInt();
        for (int j=0; j<k; j++){
            int x = inf.readInt();
            a[i].pb(x);
        }
	}

	int jans = readAnswer(ans);
	int pans = readAnswer(ouf);

	if (jans == -1) {
		if (pans != -1)
			quitf(_fail, "Participant found answer but jury doesn't");
	} else {
		if (pans == -1)
			quitf(_wa, "Jury found answer but participant doesn't");
	}

	quitf(_ok, "%d", pans);
}

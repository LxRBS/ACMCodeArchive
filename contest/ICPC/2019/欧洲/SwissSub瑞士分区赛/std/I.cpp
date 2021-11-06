#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

typedef long long ll; 

class die {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> A(6); cin >> A;
        ll S; cin >> S;
        int Q; cin >> Q;
        --Q;
        S -= A[Q];

        vector<int> M(3, 0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 6; ++j) {
                int k = min(j, 5-j);
                if (i != k) {
                    M[i] |= 1<<(3*A[j]+k-3);
                }
            }
        }

        map<int, int> C;
        vector<int> D{0};
        C[0] = 0;
        int cur = 0, id = 0;
        while (true) {
            int next = (cur&((1<<27)-1))<<3;
            for (int i = 0; i < 3; ++i) {
                if ((cur & M[i]) != M[i]) next |= 1<<i;
            }
            cur = next;
            D.push_back(cur);
            auto it = C.find(cur);
            if (it != C.end()) break;

            C[cur] = ++id;
        }

        int prep = C[cur];
        int per = id + 1 - C[cur];
        
        if (S > prep) S = (S - prep) % per + prep;

        if ((D[S]>>min(Q,5-Q))&1) cout << "ADA" << '\n';
        else cout << "BOB" << '\n';
    }
};


int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	die solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
    return 0;
}
// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1.1e6;
int x[2][MAXN];
int main(){
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)cin >> x[0][i] >> x[1][i];
    long double res = 0;
    for(int d = 0; d < 2; d++){
        vector<pair<long double,int> > positions;
        for(int i = 0; i < N; i++){
            positions.push_back(make_pair((long double)x[d][i], 1));
            while(positions.size() > 1 && positions[positions.size()-1].first <= positions[positions.size() - 2].first){
                auto a1 = positions[positions.size() - 1], a2 = positions[positions.size() - 2];
                positions.pop_back();
                positions[positions.size()-1] = make_pair((a1.first*a1.second + a2.first * a2.second) / (a1.second + a2.second), a1.second + a2.second);
            }
        }
        int done = 0;
        for(auto z: positions){
            while(z.second-->0)res += pow(x[d][done++]-z.first,2);
        }
    }
    printf("%.10lf\n",(double)res);
	return 0;
}

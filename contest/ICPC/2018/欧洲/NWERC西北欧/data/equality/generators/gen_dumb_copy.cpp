// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

void output(const vector<int> & v, const int f, const int t, const bool front_or_back){
    if(t-f == 1)cout << "[" << v[f] << "]";
    else {
        cout << "concat(";
        if(front_or_back){
            output(v,f,f+1,!front_or_back);
            cout << ",";
            output(v,f+1,t,!front_or_back);
        } else {
            output(v,f,t-1,!front_or_back);
            cout << ",";
            output(v,t-1,t,!front_or_back);
        }
        cout << ")";
    }
}

int main(){
    const int MAXC = 1e6;
    int N = MAXC / 12;
    vector<int> v(N);
    for(int i = 0; i < N; i++)v[i] = (rand() % 9) + 1;
    output(v,0,N,0);
    cout << endl;
    output(v,0,N,1);
    cout << endl;
	return 0;
}

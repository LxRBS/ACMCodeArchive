#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 1E5+5;
#endif

int N;

int proc(){
    // if(1 == N || 2 == N) return 1;
    return (1<<N) - 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; cin>>nofkase;
    while(nofkase--){
        cin>>N;
        cout<<proc()<<endl;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

bool proc(string s){
    for(int i=1;i<16;i+=2)if('1' == s[i])return false;
    return true;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    cout << (proc(s) ? "Yes" : "No") << endl;
    return 0;
}
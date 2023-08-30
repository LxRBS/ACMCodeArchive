/**
 * 给定ABC，问A的C次方与B的C次方的大小关系。
 * ABC均很大，且C >= 1
 * 逐条判断即可
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 61;
#else
int const SZ = 61;
#endif

int A, B, C;

char proc(){
    if(0 == C) return '=';
    
    if(A > 0){
        if(B > 0){
            return A > B ? '>' : (A == B ? '=' : '<');
        }else if(0 == B){
            return '>';
        }else{
            if(C & 1) return '>';
            return A > -B ? '>' : (A == -B ? '=' : '<');
        }
    }else if(0 == A){
        if(B > 0) return '<';
        else if(0 == B) return '=';
        else{
            if(C & 1) return '>';
            return '<';
        }
    }else{
        if(B > 0){
            if(C & 1) return '<';
            return -A > B ? '>' : (-A == B ? '=' : '<');
        }else if(0 == B){
            if(C & 1) return '<';
            return '>';
        }else{
            if(C & 1) return A > B ? '>' : (A == B ? '=' : '<');
            return A > B ? '<' : (A == B ? '=' : '>');
        }
    }
    assert(0);
    return '\0';
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> A >> B >> C;
    cout << proc() << endl;
    return 0;
}
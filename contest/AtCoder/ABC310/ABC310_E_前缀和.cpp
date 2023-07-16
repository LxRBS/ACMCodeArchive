/**
 * 定义一个运算: 0*0=1*0=0*1=1, 1*1=0
 * 要求计算 SIGMA{SIGMA{i*j}}
 * 假设当前数是1，则该数增加的数量就是之前计算出0的数量。
 * 当前数是0，则无条件加1，其实就是之前1和0的数量。
 * 再根据当前数更新1和0的数量
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
string S;

llt proc(){
    int ones = 0;
    int zero = 0;
    llt ans = 0;
    for(char ch : S){
        if(ch == '0'){            
            ones = zero + ones;
            zero = 1; 
            ans += ones;    
        }else if(ch == '1'){
            swap(ones, zero);
            ones += 1;
            ans += ones;  
        }else{
            assert(0);
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> S; 
    cout << proc() << endl;
    return 0;
}
/**
 * 长度为L的数轴上有N只蚂蚁，初始有位置和朝向，速度均为1。
 * 左右两边有挡板，分别可以撞A次和B次
 * 问最后一只蚂蚁掉下去的时间
 * 可以发现每过2L时间，所有蚂蚁均恰好回到原位，且每个挡板均被撞了N次
 * 所以可以先计算掉前面的周期，然后考虑最后一轮
 * 准备两个队列，分别依次记录到达左右挡板的时间
 * 如果还有次数剩余，则将相应的时间加到另外一个队列
 * 否则该蚂蚁直接掉下去
 * 记录最后的时间即可
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

llt const L = 1000000000 + 1;
int N, A, B;
vi Pos;
vi D;

llt proc(){
    int mmin = min(A, B);
    int tt = mmin / N;
    llt ans = 2LL * L * tt;

    A -= tt * N;
    B -= tt * N;
    
    queue<llt> left, right;
    for(int i=0;i<N;++i){
        if(1 == D[i]) continue;
        left.push(Pos[i]);
    }
    for(int i=N-1;i>=0;--i){
        if(0 == D[i]) continue;
        right.push(L - Pos[i]);
    }

    llt tmp = 0;
    while(1){
        if(left.empty()){
            while(not right.empty()) {
                if(B > 0){
                    --B;
                    tmp = max(tmp, right.front() + L);
                }else{
                    tmp = max(tmp, right.front());
                }
                right.pop();
            }
            break;
        }
        if(right.empty()){
            while(not left.empty()){
                if(A > 0){
                    --A;
                    tmp = max(tmp, left.front() + L);
                }else{
                    tmp = max(tmp, left.front());
                }
                left.pop();
            }
            break;
        }

        auto a = left.front();
        auto b = right.front();
        
        if(a <= b){
            left.pop();
            if(0 == A){
                
            }else{
                --A;
                right.push(L + a);
            }  
            tmp = a;
        }else{
            right.pop();
            if(0 == B){

            }else{
                --B;
                left.push(L + b);
            }
            tmp = b; 
        }
    }
    return ans + tmp;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> A >> B;
    Pos.assign(N, 0);
    D.assign(N, 0);
    for(int & i : Pos) cin >> i;
    for(int & i : D) cin >> i;
    cout << proc() << endl;
    return 0;
}



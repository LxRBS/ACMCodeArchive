/**
 * ����ΪL����������Nֻ���ϣ���ʼ��λ�úͳ����ٶȾ�Ϊ1��
 * ���������е��壬�ֱ����ײA�κ�B��
 * �����һֻ���ϵ���ȥ��ʱ��
 * ���Է���ÿ��2Lʱ�䣬�������Ͼ�ǡ�ûص�ԭλ����ÿ���������ײ��N��
 * ���Կ����ȼ����ǰ������ڣ�Ȼ�������һ��
 * ׼���������У��ֱ����μ�¼�������ҵ����ʱ��
 * ������д���ʣ�࣬����Ӧ��ʱ��ӵ�����һ������
 * ���������ֱ�ӵ���ȥ
 * ��¼����ʱ�伴��
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



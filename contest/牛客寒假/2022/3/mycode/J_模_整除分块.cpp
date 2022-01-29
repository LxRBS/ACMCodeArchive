/**
 * ����[S, E]��[L, R]��
 * ����[L, R]֮���ж��ٸ�x����
 * x % P = Q �� Q����[S, E]
 * ����P���Ѹ���
 * ����P��������Ӱ��𰸣�ֱ�Ӱ�P��������
 * ��Σ�S, E����P�Ĳ������ã�����һ��
 * Ȼ�󣬼���S, E, L, R���ǷǸ�������n=E-S+1������Z[P]������������������n��
 * ���ǽ�[L...R]��PΪ��λ���ֳ����Σ�ÿ�����ο��Թ���n��
 * Ȼ��ǰ����ܻ�������С�Σ���Ҫ����һ��
 * Ȼ���ٸ�����Ŀ��������ת����Ӧ�ķǸ������㼴��
 * ���ע��0���������䶼���Լ��㣬�������أ�Ҳ������©
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;
llt P, S, E, L, R;

llt f(llt a, llt b, llt s, llt e){
    assert(a>=0&&b>=0&&s>=0&&e>=0);
    /// in [a, b], how many x satisfied with  s <= x%P <= e
    llt ia = a / P, ma = a % P;
    llt ib = b / P, mb = b % P;
    if(ma) ++ia;
    
    llt n = e - s + 1;
    llt ans = 0;
    ans += n * (ib - ia);

    if(ma && e >= ma){
        llt left = max(ma, s);
        ans += e - left + 1;
    }

    if(s <= mb){
        llt right = min(mb, e);
        ans += right - s + 1;
    }

    return ans;
}

llt proc(){
    if(S > 0){ // se zheng
        if(L >= 0){
            llt t = f(L, R, S, E);
            return t;
        }
        if(R < 0){
            return 0;
        }
        llt t = f(0, R, S, E);
        return t;
    }else if(0 == S){
        if(L >= 0){
            llt t = f(L, R, S, E);
            return t;
        }
        if(R < 0){
            llt t = f(-R, -L, 0, 0);
            return t;
        }
        llt t = f(0, R, S, E);
        llt t2 = f(1, -L, 0, 0);
        return t + t2;
    }

    /// S < 0
    if(E < 0){
        if(L >= 0){
            return 0;
        }
        if(R < 0){
            llt t = f(-R, -L, -E, -S);
            return t;
        }
        llt t = f(1, -L, -E, -S);
        return t;
    }else if(0 == E){
        if(L >= 0){
            llt t = f(L, R, 0, 0);
            return t;
        }
        if(R <= 0){
            llt t = f(-R, -L, 0, -S);
            return t;
        }
        llt t = f(0, -L, 0, -S);
        llt t2 = f(1, R, 0, 0);
        return t + t2;
    }

    if(L >= 0){
        llt t = f(L, R, 0, E);
        return t;
    }
    if(R <= 0){
        llt t = f(-R, -L, 0, -S);
        return t;
    }
    llt t1 = f(1, R, 0, E);
    llt t2 = f(1, -L, 0, -S);
    llt t3 = f(0, 0, 0, E);
    llt t4 = f(0, 0, 1, -S);
    return t1 + t2 + t3 + t4;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin>>P>>S>>E>>L>>R;
    
    if(P < 0) P = -P;
    
    if(S < 0) S = max(S, -(P-1));
    if(E > 0) E = min(E, P-1);

    if(S>=P || E<=-P){
        puts("0"); return 0;
    }

    printf("%lld\n", proc());
    return 0;
}
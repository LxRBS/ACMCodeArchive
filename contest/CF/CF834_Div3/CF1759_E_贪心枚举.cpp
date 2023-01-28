/**
 * 给定一个数组A，给定一个初始值H，做若干次操作，如下三种之一：
 * 1 对于Ai小于H，令H+=Ai/2，且Ai消失
 * 2 使用绿色魔法，使得H*=2，一共有2个绿色魔法
 * 3 使用蓝色魔法，使得H*=3，一共只有1个蓝色魔法
 * 首先，显然魔法越晚用越好，这是贪心。
 * 但是使用绿色还是蓝色不能使用贪心，但是一共只有3种使用魔法的情况，因此可以枚举
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using FQTy = priority_queue<int, vector<int>, function<bool(int, int)>>;
struct PQTy : public FQTy{

void clear(){this->c.clear();}

PQTy(function<bool(int, int)> f):FQTy(f){}

};

PQTy Q([](int a, int b){return a > b;});

int N;
llt H;
int A[SIZE];

int proc223(){
    Q.clear();
    for(int i=0;i<N;++i) Q.push(A[i]);    
    llt u = H;
    int green = 2, blue = 1;
    int ans = 0;
    while(!Q.empty()){
        int h = Q.top();
        if(u > h){
            u += h / 2;
            Q.pop();
            ++ans;
        }else{
            if(green > 0){
                u = u + u;
                --green;
            }else if(blue > 0){
                u = u + u + u;
                --blue;
            }else{
                break;
            }
        }
    }
    return ans;
}

int proc322(){
    Q.clear();
    for(int i=0;i<N;++i) Q.push(A[i]);
    llt u = H;
    int green = 2, blue = 1;
    int ans = 0;
    while(!Q.empty()){
        int h = Q.top();
        if(u > h){
            u += h / 2;
            Q.pop();
            ++ans;
        }else{
            if(blue > 0){
                u = u + u + u;
                --blue;
            }else if(green > 0){
                u = u + u; -- green;
            }else{
                break;
            }
        }
    }
    return ans;    
}

int proc232(){
    Q.clear();
    for(int i=0;i<N;++i) Q.push(A[i]);
    llt u = H;
    int green = 2, blue = 1;
    int ans = 0;
    while(!Q.empty()){
        int h = Q.top();
        if(u > h){
            u += h / 2;
            Q.pop();
            ++ans;
        }else{
            if(green > 1){
                u = u + u; --green;
            }else if(blue > 0){
                u = u + u + u;
                --blue;
            }else if(green > 0){
                u = u + u; -- green;
            }else{
                break;
            }
        }
    }
    return ans; 
}

int proc(){
    int ans = proc232();
    ans = max(ans, proc322());
    ans = max(ans, proc223());
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); H = getInt();
        for(int i=0;i<N;++i) A[i] = getInt();
        printf("%d\n", proc());
    }    
    return 0;
}
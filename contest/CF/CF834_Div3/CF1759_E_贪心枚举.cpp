/**
 * ����һ������A������һ����ʼֵH�������ɴβ�������������֮һ��
 * 1 ����AiС��H����H+=Ai/2����Ai��ʧ
 * 2 ʹ����ɫħ����ʹ��H*=2��һ����2����ɫħ��
 * 3 ʹ����ɫħ����ʹ��H*=3��һ��ֻ��1����ɫħ��
 * ���ȣ���Ȼħ��Խ����Խ�ã�����̰�ġ�
 * ����ʹ����ɫ������ɫ����ʹ��̰�ģ�����һ��ֻ��3��ʹ��ħ�����������˿���ö��
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
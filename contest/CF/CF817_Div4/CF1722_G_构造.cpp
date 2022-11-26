/**
 * 否则一个长度为N的数组，使得：
 * 奇偶位置分别异或和，两个异或和的结果相等
 * 元素互不相等
 * 令MSK=1<<30，基本思路就是奇数位置放X,则偶数位置放X|MSK
 * 如果N是4的倍数，则正好
 * 如果N是4k+1，则令A0=0，正好
 * 如果N是4k+3，则两A0=MSK，正好
 * 如果N是4k+2，则奇数位置异或之后会多一个MSK
 * 因此令A1去掉这个MSK，并且把从第3到28位开始全置1，A3的第3到28位全置1
 */
#include <assert.h>
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
int const SIZE = 1E2+13;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;

int const MSK = 1 << 30;

int N;
vector<int> A;

bool proc(int n){
    vector<int> vec(29, 0);
    auto f = [&vec](){
        int ans = 0;
        for(int i=0;i<29;++i)if(vec[i])ans |= (1<<i);
        return ans;
    };

    fill(vec.begin(), vec.begin()+n, 1);
    do{
        int t = f();
        A.push_back(t);
        A.push_back(t | MSK);
        if(A.size() == N) {
            return true;
        } 
    }while(prev_permutation(vec.begin(), vec.end()));

    return false;
}

void proc(){
    if(1 == N) return (void)printf("0\n");

    A.clear(); A.reserve(N);
    int k = 0;
    switch(N%4){
        case 1: A.push_back(0); break;
        case 3: A.push_back(MSK); break;
        default:;
    } 
       
    for(int i=1;i<29;++i){
        if(proc(i)){
            break;
        }
    }
    if(N%4==2){
        A[1] ^= MSK;
        for(int i=2;i<29;++i) A[1] |= (1<<i), A[3] |= (1<<i);
    }
    auto g = [&]()->bool{
        int ans = 0;
        unordered_set<int> s;
        for(int i=0;i<N;i+=2){
            ans ^= A[i];
            if(s.count(A[i])){
                cerr << "repeat" << endl;
                return false;
            }
            s.insert(A[i]);
        }
        int b = 0;
        for(int i=1;i<N;i+=2){
            b ^= A[i];
            if(s.count(A[i])){
                cerr << "repeat" << endl;
                return false;
            }
            s.insert(A[i]);
        }
        if(ans != b){
            cerr << "not equal" << endl;
            return false;
        }
        return true;
    };
    assert(g());
    for(auto i : A)printf("%d ", i);
    printf("\n");
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
        proc();
	}
    return 0;
}

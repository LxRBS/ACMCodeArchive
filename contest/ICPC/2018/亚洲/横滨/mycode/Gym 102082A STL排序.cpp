/**
    给定若干字符串，比较大小
    字母部分按字典序，数字部分按数值
*/
#include<bits/stdc++.h>
using namespace std;

struct _t{
    char a[16];
    int idx;
}A[1010];

int string2int(string const&s){
    stringstream ss(s);
    int x;
    ss>>x;
    return x;
}

void f(char const a[],vector<string>&v){
    v.clear();
    char const*p = a;
    while(*p){
        if('A'<=*p&&*p<='Z'||('a'<=*p&&*p<='z')){
            v.push_back(string(1,*p));
            ++p;
        }else if('0'<=*p&&*p<='9'){
            string s;
            while('0'<=*p&&*p<='9'){
                s += *p;
                ++p;
            }
            v.push_back(s);
        }else{
            throw runtime_error("XXXXX");
        }
    }
}

bool operator < (_t const&lhs,_t const&rhs){
    vector<string> va,vb;
    f(lhs.a,va);f(rhs.a,vb);
    int sz = min(va.size(),vb.size());
    for(int i=0;i<sz;++i){
        string const&sa = va[i];
        string const&sb = vb[i];
        if(isdigit(sa[0])){
            if(isdigit(sb[0])){
                int a = string2int(sa);
                int b = string2int(sb);
                if(a!=b) return a < b;
            }else{
                return true;
            }
        }else{
            if(isdigit(sb[0])){
                return false;
            }else{
                if(sa[0]!=sb[0]){
                    return sa[0] < sb[0];
                }
            }
        }
    }
    if(va.size()!=vb.size()) return va.size() < vb.size();
    return lhs.idx < rhs.idx;
}

char Ans[1010];
int main(){
    //freopen("1.txt","r",stdin);
    int n;
    scanf("%d",&n);
    ++n;
    for(int i=0;i<n;++i){
        scanf("%s",A[i].a);
        A[i].idx = i;
    }
    sort(A,A+n);
    int k = 0;
    while(A[k].idx) ++k;
    for(int i=0;i<k;++i)Ans[A[i].idx] = '-';
    for(int i=k+1;i<n;++i)Ans[A[i].idx] = '+';
    for(int i=1;i<n;++i)printf("%c\n",Ans[i]);
    return 0;
}
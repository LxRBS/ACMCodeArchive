/**
 * 给定一张数据表，行表示项，列表示属性
 * 再给定一个属性的子集，问按这个子集的标准，数据表中的数据项可以分成多少组，各是多少
 * 按子集的标准排序，然后扫描一遍即可
*/
#include<bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 1010;
#endif

unordered_map<string, int> Dic;

struct _t{
    int idx;
    vector<int> val;
}A[SIZE];

int N, M;
char SQL[51000];

void f(char *p, vector<int> &v){
    int n = strlen(p);
    
    int s = 0;
    while(*(p+s) && *(p+s) == ' ') ++s;
    if(s == n) return;

    while(*(p+n-1) == ' ') --n;

    string t(p+s, p+n);
    v.push_back(Dic[t]);

    return;
}

void proc(){
    int offset = 0;
    while(SQL[offset] != 'B' && SQL[offset] != 'Y') ++offset;
    offset += 3;
    while(SQL[offset] == ' ') ++offset;

    int n = strlen(SQL);
    if(SQL[n-1] == '\n') SQL[--n] = '\0';
    if(SQL[n-1] == ';') SQL[--n] = '\0';

    char const delim[] = ", ";
    char *token;

    vector<int> label;
    token = strtok(SQL+offset, delim);
    f(token, label);
    while(token = strtok(NULL, delim)){
        f(token, label);
    }

    sort(A, A+N, [&](const _t&a, const _t&b)->bool{
        for(auto idx: label){
            if(a.val[idx] != b.val[idx]) return a.val[idx] < b.val[idx];
        }
        return a.idx < b.idx;
    });

    auto isEq = [&](const _t&a, const _t&b)->bool{
        for(auto idx: label){
            if(a.val[idx] != b.val[idx]) return false;
        }
        return true;
    };

    vector<int> ans;
    for(int i=0,cnt;i<N;){
        cnt = 0;
        while(i+cnt<N && isEq(A[i], A[i+cnt])) ++cnt;

        ans.push_back(cnt);
        if((i+=cnt) >= N) break;  
    }
    printf("%d\n%d", ans.size(), ans.front());
    for(unsigned i=1,n=ans.size();i<n;++i)printf(" %d", ans[i]);
    printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d", &N, &M);
    for(int i=0;i<M;++i){
        char a[110];
        scanf("%s", a);
        Dic[string(a)] = i;
    }  
    for(int i=0;i<N;++i){
        A[i].idx = i;
        A[i].val.assign(M, 0);
        for(int j=0;j<M;++j){
            scanf("%d", &(A[i].val[j]));
        }
    }
    fgets(SQL, 50010, stdin);
    fgets(SQL, 50010, stdin);
    proc();
    return 0;
}
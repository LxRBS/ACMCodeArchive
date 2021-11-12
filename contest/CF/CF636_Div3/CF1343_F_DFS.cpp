/**
 * ��һ��δ֪��N����P���ٸ���N-1��Ƭ��
 * ÿ��Ƭ�ΰ������ɸ�������ʾ��Щ�����������������ģ���δ�ذ��ո�����˳��
 * ������С�����һ���𰸾��ɡ�N��200
 * ������
 * �Ե�i��λ�ã�������п��Է��õ�v�����ѡ�
 * �����������
 * ����ǰһ������prev�����п��ܴ�Ƭ�����ѳ����ɸ����ܵ�v�����з���
 * prev�Ժ�һ����û��Ӱ�죬���ʣ�µ�������һ�����Կ�ͷ��
 * ����û��������û����˵�����о�spj�ƺ������⣬Ī�ǿ�������
 * �Լ������Ŀ���ݣ��о����ԡ�
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
int const SIZE = 21;
#else 
int const SIZE = 200100;
#endif

typedef long long llt;

int N, Total;
vector<set<int> > A;
vector<int> Ans;
vector<int> V2Pos[SIZE];

bool Flag[SIZE];

/// ��鵱ǰ�Ƿ���Է�v
/// ������к�v��seg��������ͬ��Ԫ�أ���v���Է�
/// ֻ��v��seg����Ҫ����
bool isOK(int v){
    int flag[SIZE] = {0};
    int k = 0;
    for(auto i: V2Pos[v]){
        if(A[i].size() == 1) continue;

        ++k;
        for(auto j: A[i]){
            ++flag[j];
        }
    }
    for(int i=1;i<=N;++i)if(i!=v){
        if(flag[i] == k) return true;
    }
    return false;
}

inline void dodo(int v){
    Ans.push_back(v);
    Flag[v] = true;
    for(auto i: V2Pos[v]){
        A[i].erase(v);
    }
}

inline void undo(int v){
    Ans.pop_back();
    Flag[v] = false;
    for(auto i: V2Pos[v]){
        A[i].insert(v);
    }
}

bool find(vector<int> &vec, int v){
    vec.clear();
    int flag[SIZE] = {0};
    int k = 0;
    for(auto i: V2Pos[v]){
        if(A[i].empty()) continue;

        ++k;
        for(auto j: A[i]){
            ++flag[j];
        }
    }

    int you = 0;
    for(int i=1;i<=N;++i)if(i!=v){
        if(flag[i] == k) vec.push_back(i);
        else if(flag[i]) you = 1;
    }
    return you;
}

bool dfs(){
    if(Ans.size() == Total){
        return true;
    }

    /// ȡ����һ����
    int prev = Ans.back();
    /// �ҿ��Է���prev�������
    vector<int> vtmp;
    bool b = find(vtmp, prev);
    if(vtmp.empty() && b) return false;
    if(!vtmp.empty())for(auto i: vtmp){
        dodo(i);
        if(dfs()) return true;
        undo(i);
    }else for(int i=1;i<=N;++i)if(!Flag[i] && !V2Pos[i].empty() && isOK(i)){
        dodo(i);
        if(dfs()) return true;
        undo(i);       
    }
    return false;
}

void proc(){
    Ans.clear();
    fill(Flag, Flag+N+1, false);
    for(int i=1;i<=N;++i) V2Pos[i].clear();
    for(int i=0;i<A.size();++i){
        for(auto v: A[i]){
            V2Pos[v].push_back(i);
        }
    }

    Total = 0;
    for(int i=1;i<=N;++i)if(!V2Pos[i].empty()) ++Total;

    for(int i=1;i<=N;++i)if(!Flag[i] && !V2Pos[i].empty() && isOK(i)){       
        dodo(i);
        if(dfs()) break;
        undo(i);
    }

    for(int i=1;i<=N;++i)if(!Flag[i])Ans.push_back(i);
#ifndef ONLINE_JUDGE
    cout<<Ans.size()<<endl;
#endif
    for(auto i: Ans)printf("%d ", i);
    puts("");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), set<int>());
        for(int k, i=1;i<N;++i){
            set<int>& s = A[i];
            k = getInt();
            while(k--){
                s.insert(getInt());
            }
        }
        proc();
    }
    return 0;
}

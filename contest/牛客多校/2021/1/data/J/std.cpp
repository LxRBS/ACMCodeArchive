#include<bits/stdc++.h>
#define N 1000005
using namespace std;
typedef long long LL;
const LL oo = 1e12;
struct Function{
    LL l, r, t; int valid;
    Function():l(0), r(0), t(0), valid(0){}
    Function(LL l_, LL r_, LL t_):l(l_), r(r_), t(t_), valid(1){}
}a[N << 2], ans;
int st[N], ed[N], dist[N];
Function Merge(const Function &A, const Function &B, int d){
    if (!A.valid || !B.valid || A.t + d > B.r) return Function();
    //if (A.t + d + A.r - A.l <= B.l) return Function(A.r, A.r, B.t);
    LL newr = A.t + d + A.r - A.l > B.r ? B.r + A.l - A.t - d : A.r, newl, newt;
    if (A.t + d >= B.l) newl = A.l, newt = B.t + A.t + d - B.l;
    else newl = min(newr, A.l + B.l - A.t - d), newt = B.t;
	return Function(newl, newr, newt);
}
void build(int x, int l, int r){
    if (l == r){
        a[x] = Function(st[l], ed[l], st[l]);
        //printf("%d %d %lld %lld %lld %d\n", l, r, a[x].l, a[x].r, a[x].t, a[x].valid);
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    a[x] = Merge(a[x << 1], a[x << 1 | 1], dist[mid]);
    //printf("%d %d %lld %lld %lld %d\n", l, r, a[x].l, a[x].r, a[x].t, a[x].valid);
}
void UpdateDist(int x, int l, int r, int pos){
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos < mid) UpdateDist(x << 1, l, mid, pos);
    if (pos > mid) UpdateDist(x << 1 | 1, mid + 1, r, pos);
    a[x] = Merge(a[x << 1], a[x << 1 | 1], dist[mid]);
}
void UpdateNode(int x, int l, int r, int pos){
    if (l == r){
        a[x] = Function(st[l], ed[l], st[l]);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) UpdateNode(x << 1, l, mid, pos); 
               else UpdateNode(x << 1 | 1, mid + 1, r, pos);
    a[x] = Merge(a[x << 1], a[x << 1 | 1], dist[mid]);
}
void Query(int x, int l, int r, int ql, int qr){
    if (ql <= l && r <= qr){
        if (ql == l) ans = a[x]; else ans = Merge(ans, a[x], dist[l-1]);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) Query(x << 1, l, mid, ql, qr);
    if (qr > mid) Query(x << 1 | 1, mid + 1, r, ql, qr);
}
int main(){
	//freopen("sample.txt", "r", stdin);
    int T; scanf("%d", &T);
    while (T--){
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i++)
			scanf("%d", &st[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &ed[i]);
        for (int i = 1; i < n; i++)
            scanf("%d", &dist[i]);
        build(1, 1, n);
        int Q; scanf("%d", &Q);
        while (Q--){
            int type; scanf("%d", &type);
            if (!type){
                int l, r; scanf("%d%d", &l, &r);
                ans = Function(-oo, oo, -oo);
                Query(1, 1, n, l, r);
                puts(ans.valid ? "Yes" : "No");
            }
            else if (type == 1){
                int pos, new_dist;
                scanf("%d%d", &pos, &new_dist);
                assert(pos >= 1 && pos < n);
                dist[pos] = new_dist;
                UpdateDist(1, 1, n, pos);
            }
            else{
                int pos; scanf("%d", &pos);
                scanf("%d%d", &st[pos], &ed[pos]);
                UpdateNode(1, 1, n, pos);
            }
        }
    }
}

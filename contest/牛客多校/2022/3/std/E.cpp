#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

vector<int> segments;

int f[1010101];

bool is_segment[1010101];

int N, M, L;

void add(int &x, int y)
{
    x += y;
    if(x >= mod)
        x -= mod;
}

void calc()
{
    add(f[N], f[1]);
    for(int i = 1, k = 0; i <= N; i++)
    {
        if(i - L >= 1 && is_segment[i - L])
            add(f[i], f[i - L]);
        if(i < N)
            add(f[i + 1], f[i]);
        // cerr << "f[" << i << "] = " << f[i] << endl;

        while(k < segments.size() && i - segments[k] >= L)
            k++;

        if(is_segment[i])
        {
            for(int _k = k; _k < segments.size() && segments[_k] < i; _k++)
            {
                int j = segments[_k];
                add(f[i], f[j]);
                f[j] = f[i];
            }
        }
    }
}

int main()
{

    scanf("%d%d%d", &N, &M, &L);

    for(int i = 1; i <= M; i++)
    {
        int s;
        scanf("%d", &s);
        is_segment[s] = 1;
        segments.push_back(s);
    }

    sort(segments.begin(), segments.end());

    f[1] = 1;
    calc();
    int ans1 = f[N], ans2 = f[N - 1];

    // cerr << ans1 << " " << ans2 << endl;

    memset(f, 0, sizeof(f));
    f[2] = 1;
    calc();
    ans1 = 1ll * ans1 * f[N - 1] % mod;
    ans2 = 1ll * ans2 * f[N] % mod;

    int ans = ans1 - ans2;
    if(ans < 0)
        ans += mod;
    printf("%d\n", ans);
    return 0;
}
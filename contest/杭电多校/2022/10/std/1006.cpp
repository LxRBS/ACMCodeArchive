#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
int n, T, F[55][55], num[55];
pair<int, int> pos[2505];
vector<pair<int, int>> Ans;
void Rotate(int x, int y)
{
    // printf("Rotating %d %d\n", x, y);
    assert(x > 0 && y > 0 && x <= n - 1 && y <= 2 * x - 1);
    if (y % 2 == 1)
    {
        int tmpx = F[x][y / 2 + 1];
        int tmpy = F[x + 1][y / 2 + 2];
        int tmpz = F[x + 1][y / 2 + 1];
        F[x][y / 2 + 1] = tmpz;
        F[x + 1][y / 2 + 2] = tmpx;
        F[x + 1][y / 2 + 1] = tmpy;
        pos[tmpz] = {x, y / 2 + 1};
        pos[tmpx] = {x + 1, y / 2 + 2};
        pos[tmpy] = {x + 1, y / 2 + 1};
    }
    else
    {
        int tmpx = F[x][y / 2];
        int tmpy = F[x][y / 2 + 1];
        int tmpz = F[x + 1][y / 2 + 1];
        F[x][y / 2] = tmpz;
        F[x][y / 2 + 1] = tmpx;
        F[x + 1][y / 2 + 1] = tmpy;
        pos[tmpz] = {x, y / 2};
        pos[tmpx] = {x, y / 2 + 1};
        pos[tmpy] = {x + 1, y / 2 + 1};
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= i; j++)
    //     {
    //         printf("%d ", F[i][j]);
    //     }
    //     printf("\n");
    // }
    Ans.push_back({x, y});
}
void RDown(int x, int y)
{
    // printf("RD %d %d\n", x, y);
    Rotate(x, 2 * y - 1);
}
void LUp(int x, int y)
{
    // printf("LU %d %d\n", x, y);
    Rotate(x - 1, 2 * y - 1);
}
void Left(int x, int y)
{
    // printf("L %d %d\n", x, y);
    Rotate(x - 1, 2 * y - 3);
}
void Right(int x, int y)
{
    // printf("R %d %d\n", x, y);
    Rotate(x, 2 * y);
}
void Solve(int x)
{
    for (int i = 1; i <= x; i++)
    {
        int cur = num[x - 1] + i;
        while (pos[cur].first != pos[cur].second)
            LUp(pos[cur].first, pos[cur].second);
        while (pos[cur].first != x)
            RDown(pos[cur].first, pos[cur].second);
        while (pos[cur].second != i)
            Left(pos[cur].first, pos[cur].second);
    }
    if (F[x][x - 1] != num[x] - 1)
        Rotate(x - 1, 2 * x - 4);
}
int main()
{
    for (int i = 1; i <= 50; i++)
    {
        num[i] = i * (i + 1) / 2;
    }
    scanf("%d", &T);
    while (T--)
    {
        Ans.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                scanf("%d", &F[i][j]);
                pos[F[i][j]] = {i, j};
            }
        }
        for (int i = n; i > 2; i--)
            Solve(i);
        assert(F[1][1] + F[2][1] + F[2][2] == 6);
        while (F[1][1] != 1)
        {
            Rotate(1, 1);
        }
        if (F[2][1] == 2 && F[2][2] == 3)
        {
            assert(Ans.size() <= 2 * n * n * n);
            printf("Yes\n");
            printf("%d\n", Ans.size());
            for (auto &p : Ans)
                printf("%d %d\n", p.first, p.second);
        }
        else
            printf("No\n");
    }
}
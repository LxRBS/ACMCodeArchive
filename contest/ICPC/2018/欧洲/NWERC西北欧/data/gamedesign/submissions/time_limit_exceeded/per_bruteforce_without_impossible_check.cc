#include <bits/stdc++.h>
using namespace std;

const int GRIDSZ = 23;

string sol;
int sdx[30] = {}, sdy[30] = {};
int board[GRIDSZ][GRIDSZ] = {};

void printsol(int ex, int ey) {
    printf("%d %d\n", GRIDSZ/2-ex, GRIDSZ/2-ey);
    int n = 0;
    for (int x = 0; x < GRIDSZ; ++x)
        for (int y = 0; y < GRIDSZ; ++y)
            n += board[x][y] > 0;
    printf("%d\n", n);
    for (int x = 0; x < GRIDSZ; ++x)
        for (int y = 0; y < GRIDSZ; ++y)
            if (board[x][y] > 0)
                printf("%d %d\n", x-ex, y-ey);
}

bool solve(int i, int x, int y) {
    if (i == sol.length()) return false;
    int dx = sdx[i], dy = sdy[i], nx = x, ny = y;
    if (board[x+dx][y+dy] > 0) return false;
    while (true) {
        nx += dx; ny += dy;
        if (nx < 1 || ny < 1 || nx >= GRIDSZ-1 || ny >= GRIDSZ-1 || board[nx][ny] > 0)
            break;
        if (i == sol.length()-1 && !board[nx][ny]) {
            printsol(nx, ny);
            return true;
        }
        --board[nx][ny];
        if (board[nx+dx][ny+dy] >= 0) {
            ++board[nx+dx][ny+dy];
            if (solve(i+1, nx, ny)) return true;
            --board[nx+dx][ny+dy];
        }
    }
    nx = x;
    ny = y;
    while (true) {
        nx += dx; ny += dy;
        if (nx < 1 || ny < 1 || nx >= GRIDSZ-1 || ny >= GRIDSZ-1 || board[nx][ny] > 0)
            break;
        ++board[nx][ny];
    }
    return false;
}

int main(void) {
    cin >> sol;
    for (int i = 0; i < sol.length(); ++i) {
        switch(sol[i]) {
        case 'L': sdx[i] = -1; break;
        case 'R': sdx[i] = 1; break;
        case 'D': sdy[i] = -1; break;
        case 'U': sdy[i] = 1; break;
        }
    }
    --board[GRIDSZ/2][GRIDSZ/2];
    if (!solve(0, GRIDSZ/2, GRIDSZ/2))
        printf("impossible\n");
}

#include <iostream>
#include <queue>
using namespace std;

const int MAXCARS = 50;
const int MAXHOPPERS = 100;

class node {
public:
    long long iA, iB, iT;

    node(long long a, long long b, long long t) : iA(a), iB(b), iT(t)
    {}

};

int a[MAXCARS], b[MAXCARS], t[MAXHOPPERS];
queue<node*> list;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

 bool possible(long long target, long long totA, long long totB, long long x, long long y, long long g) {
    if (target % g != 0) {
        return false;
    }
    x *= target / g;
    y *= target / g;
    if (x < 0) {
        long long d = y/(totA/g);
        x += d*totB/g;
        y -= d*totA/g;
    }
    else if (y < 0) {
        long long d = x/(totB/g);
        y += d*totA/g;
        x -= d*totB/g;
    }
//cout << totA << '*' <<  x << '+' << totB << '*' << y << '=' << target << endl;
    return (x >= 0 && y >= 0);
 }

int main()
{
    long long nA, nB, nT;
    long long totA = 0, totB = 0;

    cin >> nA >> nB >> nT;
//cout << nA << ' ' << nB << ',' << nT << endl;
    for(int i=0; i<nA; i++) {
        cin >> a[i];
        totA += a[i];
    }
    for(int i=0; i<nB; i++) {
        cin >> b[i];
        totB += b[i];
    }
    for(int i=0; i<nT; i++)
        cin >> t[i];
    long long x, y, g;
    g = gcd(totA, totB, x, y);    // solve totA*x + totB*y = g
                                  // g = gcd(totA, totB)
//cout << x << ',' << y << endl;
    bool startconfig[nA][nB], nextconfig[nA][nB];
                            // startcondig[i][j] = start config of a[i] and b[j] positioned
                            //    over current train car possible
    for(int i=0; i<nA; i++)
        for(int j=0; j<nB; j++)
            startconfig[i][j] = false;
    startconfig[0][0] = true;
    long long iT = 0;
    while (iT < nT) {
        for(int i=0; i<nA; i++)
            for(int j=0; j<nB; j++)
                nextconfig[i][j] = false;
        long long numLeft = nA*nB;
        for(int i=0; i<nA; i++) {
            for(int j=0; j<nB; j++) {
                if (!startconfig[i][j])
                    continue;
//cout << "start: " << a[i] << ' ' << b[j] << ' ' << t[iT] << endl;
                long long target = t[iT];
                for(int ii=i; ii<i+nA; ii++) {
                    long long modifiedTarget = target;
                    for(int jj=j; jj<j+nB; jj++) {
                        if (!nextconfig[ii%nA][jj%nB] && possible(modifiedTarget, totA, totB, x, y, g)) {
//cout << "  through A car " << (ii+nA-1)%nA << " and B car " << (jj+nB-1)%nB << endl;
                            nextconfig[ii%nA][jj%nB] = true;
                            numLeft--;
                        }
                        modifiedTarget -= b[jj%nB];
                    }
                    if (numLeft == 0)
                        break;
                    target -= a[ii%nA];
                }
                if (numLeft == 0)
                    break;
            }
            if (numLeft == 0)
                break;
        }
//cout << iT << ' ' << numLeft << endl;
        if (numLeft == nA*nB)
            break;
        for(int i=0; i<nA; i++)
            for(int j=0; j<nB; j++)
                startconfig[i][j] = nextconfig[i][j];
        iT++;
/*
if (iT == nT-1) {
for(int i=0; i<nA; i++) {
for(int j=0; j<nB; j++)
cout << startconfig[i][j];
cout << endl;
}
}
/**/
    }
    if (iT == nT) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
}

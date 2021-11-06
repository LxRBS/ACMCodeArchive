#include <iostream>
using namespace std;

const int MAXSIZE = 10;
const int BIG = 37*37;

int m[MAXSIZE][MAXSIZE];

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                   'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                   '4', '5', '6', '7', '8', '9', ' '};

int inverse[37] = {0,  1, 19, 25, 28, 15, 31, 16, 14, 33,
                   26, 27, 34, 20,  8,  5,  7, 24, 35,  2,
                   13, 30, 32, 29, 17,  3, 10, 11,  4, 23,
                   21,  6, 22,  9, 12, 18, 36};

int* convert(string s)
{
    int *ans = new int[s.length()];
    for(int i=0; i<s.length(); i++) {
        if (s[i] == ' ')
            ans[i] = 36;
        else if (s[i] <= '9')
            ans[i] = (s[i] - '0') + 26;
        else
            ans[i] = (s[i] - 'A');
    }
    return ans;
}

int calcFactor(int a1[], int a2[], int n)
{
    int i=0;
    while (i<n && a1[i] == 0 && a2[i] == 0)
        i++;
    if (i == n || a1[i] == 0 || a2[i] == 0)
        return -1;
    int factor = (a2[i]*inverse[a1[i]] + BIG)%37;
    for( ; i<n; i++) {
        if ((a2[i]*inverse[a1[i]] + BIG)%37 != factor)
            return -1;
    }
    return factor;
}

bool applyFactor(int a1[], int a2[], int factor, int n)
{
    for(int i=0; i<n; i++) {
        if ((a1[i]*factor+BIG)%37 != a2[i])
            return false;
    }
    return true;
}
bool allAs(string s)
{
    for(int i=0; i<s.length(); i++)
        if (s[i] != 'A')
            return false;
    return true;
}

bool process(string& plain, string& cipher, int n)
{
    string newPlain = "", newCipher = "";
    for(int i=0; i<plain.length(); i+= n) {
        string s1 = plain.substr(i, n);
        string s2 = cipher.substr(i, n);
        bool s1AllA = allAs(s1);
        bool s2AllA = allAs(s2);
        if (s1AllA && !s2AllA)         // special case - no solution possible
            return false;
        if (s1AllA && s2AllA)           // this string of no use
            continue;
        int *v1 = convert(s1);
        int *v2 = convert(s2);
        bool use = true;
        for(int j=i+n; j<plain.length(); j+=n) {
            string s3 = plain.substr(j, n);
            string s4 = cipher.substr(j, n);
            int *v3 = convert(s3);
            int *v4 = convert(s4);
            int factor = calcFactor(v1, v3, n);
//cout << i << ' ' << j << ':' << factor  << endl;
            if (factor != -1) {
                if (!applyFactor(v2, v4, factor, n))
                    return false;                   // no solution possible
                use = false;
                break;
            }
        }
//cout << i << ',' << use << endl;
        if (use) {
            newPlain += s1;
            newCipher += s2;
        }
    }
//cout << newPlain << ',' << newCipher << endl;
    plain = newPlain;
    cipher = newCipher;
    return true;
}

bool solve(string rows[], string cols[], int b[MAXSIZE][MAXSIZE])
{
    int n = rows[0].length();
    int a[n][n];

    for(int r=0; r<n; r++) {
        int *vals = convert(rows[r]);
        for(int c=0; c<n; c++)
            a[r][c] = vals[c];
    }
    for(int r=0; r<n; r++) {
        int *vals = convert(cols[r]);
        for(int c=0; c<n; c++)
            b[r][c] = vals[c];
    }
/*
for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++)
        cout << a[i][j] << ' ';
    for(int j=0; j<n; j++)
        cout << ' ' << b[i][j];
    cout << endl;
}
/**/
                                        // forward sub
    for(int r=0; r<n; r++) {
        int i=r;
        while(i < n && a[i][r] == 0)
            i++;
        if (i == n)
            return false;
        if (i != r) {
            for(int j=0; j<n; j++) {
                int tmp = a[r][j];
                a[r][j] = a[i][j];
                a[i][j] = tmp;
                tmp = b[r][j];
                b[r][j] = b[i][j];
                b[i][j] = tmp;
            }
        }
        int inv = inverse[a[r][r]];
        for(int j=0; j<n; j++) {
            a[r][j] = (a[r][j]*inv)%37;
            b[r][j] = (b[r][j]*inv)%37;
        }
        for(int k=r+1; k<n; k++) {
            int factor = a[k][r];
            for(int j=0; j<n; j++) {
                a[k][j] = (a[k][j] - a[r][j]*factor + BIG)%37;
                b[k][j] = (b[k][j] - b[r][j]*factor + BIG)%37;
            }
        }
/*
for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++)
        cout << a[i][j] << ' ';
    for(int j=0; j<n; j++)
        cout << ' ' << b[i][j];
    cout << endl;
}
/**/
    }
                                            // backwards sub
    for(int r=n-1; r>0; r--) {
        for(int i=r-1; i>=0; i--) {
            int factor = a[i][r];
            for(int j=0; j<n; j++) {
                a[i][j] = (a[i][j] - a[r][j]*factor + BIG)%37;
                b[i][j] = (b[i][j] - b[r][j]*factor + BIG)%37;
            }
        }
/*
for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++)
        cout << a[i][j] << ' ';
    for(int j=0; j<n; j++)
        cout << ' ' << b[i][j];
    cout << endl;
}
/**/
    }
    return true;
}

int main()
{
    int n;
    string plain, cipher;

    cin >> n;
    getline(cin, plain);
    getline(cin, plain);
    while (plain.length()%n != 0)
        plain += ' ';
    getline(cin, cipher);

    if (!process(plain, cipher, n)) {
        cout << "No solution" << endl;
        exit(0);
    }
//    cout << plain << ',' << cipher << endl;
    int len = cipher.length();
    if (len < n*n) {
        cout << "Too many solutions" << endl;
        exit(0);
    }
    string rows[n], cols[n];
    int mat[MAXSIZE][MAXSIZE], save[MAXSIZE][MAXSIZE];
    bool solFound = false;
                                            // solve each set, checking if
                                            //   results are the same
    bool ok = true;
    for(int start=0; start < len; start+=n*n) {
//cout << start << endl;
        if (len-start < n*n)
            start = len-n*n;
        for(int i=0; i<n; i++) {
            rows[i] = plain.substr(start+i*n, n);
            cols[i] = cipher.substr(start+i*n, n);
        }
        if (solve(rows, cols, mat)) {
            if (!solFound) {
                for(int r=0; r<n; r++)
                    for(int c=0; c<n; c++)
                        save[r][c] = mat[r][c];
                solFound = true;
            }
            else {
                for(int r=0; r<n; r++)
                    for(int c=0; c<n; c++) {
                        if (mat[r][c] != save[r][c])
                            ok = false;
                    }
            }
        }
        if (!ok)
            break;
    }
    if (ok) {
        if (solFound) {
            for(int c=0; c<n; c++) {
                cout << save[0][c];
                for(int r=1; r<n; r++)
                    cout << ' ' << save[r][c];
                cout << endl;
            }
        }
        else
            cout << "Too many solutions" << endl;
    }
    else
        cout << "No solution" << endl;
}

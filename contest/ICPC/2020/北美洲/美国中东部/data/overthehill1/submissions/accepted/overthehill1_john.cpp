#include <iostream>
using namespace std;

const int MAXSIZE = 10;

int m[MAXSIZE][MAXSIZE];

char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                   'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                   '4', '5', '6', '7', '8', '9', ' '};

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

int* encrypt(int word[], int m[MAXSIZE][MAXSIZE], int n)
{
    int *ans = new int[n];
    for(int r=0; r<n; r++) {
        ans[r] = 0;
        for(int c=0; c<n; c++) {
            ans[r] += m[r][c]*word[c];
        }
        ans[r] %= 37;
    }
    return ans;
}

int main()
{
    int n;

    cin >> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin >> m[i][j];
        }
    }
    string s;
    getline(cin, s);
    getline(cin, s);
    while (s.length()%n != 0)
        s += ' ';
    int *vals = convert(s);
    string news = "";
    for(int i=0; i<s.length(); i+=n) {
        int *encrypted = encrypt(vals+i, m, n);
        for(int j=0; j<n; j++)
            news += alphabet[encrypted[j]];
    }
    cout << news << endl;
}

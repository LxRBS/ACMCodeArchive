#include <iostream>
#include <queue>
using namespace std;

const int MAXCARS = 50;
const int MAXHOPPERS = 100;

class node {
public:
    int iA, iB, iT;

    node(int a, int b, int t) : iA(a), iB(b), iT(t)
    {}

};

int a[MAXCARS], b[MAXCARS], t[MAXHOPPERS];
queue<node*> list;

bool solve(int, int, int);

int main()
{
    int nA, nB, nT;

    cin >> nA >> nB >> nT;
    for(int i=0; i<nA; i++)
        cin >> a[i];
    for(int i=0; i<nB; i++)
        cin >> b[i];
    for(int i=0; i<nT; i++)
        cin >> t[i];

    int iA, iB;
    list.push(new node(0, 0, 0));
    if (solve(nA, nB, nT)) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
}

bool solve(int nA, int nB, int nT)
{
    while (!list.empty()) {
        node* pnode = list.front();
        list.pop();
        int jA = pnode->iA;
        int jB = pnode->iB;
        int jT = pnode->iT;
//cout << "jA, jB, jT = " << jA << ',' << jB << ',' << jT << endl;
        int sum = 0;
        while (sum < t[jT]) {       // first try as many A carts as possible
            sum += a[jA%nA];
            jA++;
        }
        while (jA >= pnode->iA) {
            if (sum == t[jT]) {
                if (jT == nT-1) {   // check if all train cars are filled
                    return true;
                }
//cout << "enqueue " << jA << ' ' << jB << ' ' << jT+1 << endl;
                list.push(new node(jA, jB, jT+1));
            }
            jA--;                   // else remove one A cart and fill with as many
            sum -= a[jA%nA];        //   B carts as will fit
            while (sum < t[jT]) {
                sum += b[jB%nB];
                jB++;
            }
        }
    }
    return false;
}

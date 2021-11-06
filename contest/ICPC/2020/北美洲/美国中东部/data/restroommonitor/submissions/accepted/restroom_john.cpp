#include <iostream>
using namespace std;

const int MAXPEOPLE = 100000;

struct bNode {
    int t;      // bathroom deadline (non-tp)
    int n;      // number with that deadline
};

int tpDeadline[MAXPEOPLE+1];            // add a zero at end to avoid end-of-array checks
bNode bDeadline[MAXPEOPLE];
int nT=0, nB=0;

int compareInt(const void *a,const void *b) {
  return *(int *)b - *(int *)a;
}

void sortMe(int *data,int n) {
  qsort(data,n,sizeof(int),compareInt);
}

int compareNode(const void *a,const void *b) {
  return ((bNode *)b)->t - ((bNode *)a)->t;
}

void sortMe2(bNode *data,int n) {
  qsort(data,n,sizeof(bNode),compareNode);
}

void sortTP(int n)
{
  sortMe(tpDeadline,n);
/*    for(int i=1; i<n; i++) {
        int sav = tpDeadline[i];
        int j = i;
        while (j > 0 && tpDeadline[j-1] < sav) {
            tpDeadline[j] = tpDeadline[j-1];
            j--;
        }
        tpDeadline[j] = sav;
    }*/
}

int sortAndCompressB(int n)
{
    if (n == 0)
        return 0;
        sortMe2(bDeadline,n);
/*    for(int i=1; i<n; i++) {
        bNode sav = bDeadline[i];
        int j = i;
        while (j > 0 && bDeadline[j-1].t < sav.t) {
            bDeadline[j] = bDeadline[j-1];
            j--;
        }
        bDeadline[j] = sav;
    }*/
    int j = 0;
    for(int i=1; i<n; i++) {
        if (bDeadline[i].t == bDeadline[j].t)
            bDeadline[j].n++;
        else {
            j++;
            bDeadline[j] = bDeadline[i];
        }
    }
    return j+1;
}

int main()
{
    int s, n;

    cin >> s >> n;
    for(int i=0; i<n; i++) {
        int t;
        char ch;
        cin >> t >> ch;
        if (ch == 'y')
            tpDeadline[nT++] = t;
        else {
            bDeadline[nB].t = t;
            bDeadline[nB].n = 1;
            nB++;
        }
    }
    sortTP(nT);
                                    // schedule tp users
    bool nogood = false;
    int t = tpDeadline[0]-1;
    for(int i=1; i<nT; i++) {
        if (t == 0) {
            nogood = true;
            break;
        }
        else if (t >= tpDeadline[i])
            t = tpDeadline[i]-1;
        else {
            tpDeadline[i] = t;
            t--;
        }
    }
    if (nogood) {
        cout << "no" << endl;
    }
    else {                                  // schedule everyone else
        nB = sortAndCompressB(nB);
        tpDeadline[nT] = 0;
        int nextT = 0;
        int nextB = 0;
        int currT = bDeadline[nextB].t;
        int nAvail = s;
        while (nextB < nB) {
            if (currT == 0) {
                nogood = true;
                break;
            }
            if (currT > bDeadline[nextB].t)
                currT = bDeadline[nextB].t;
            while (tpDeadline[nextT] > currT)
                nextT++;
            if (tpDeadline[nextT] == currT) {   // remove tp stall
                nAvail--;
                nextT++;
            }
//cout << "nextB, curr t = " << nextB << ',' << currT << ", n avail = " << nAvail  << ", num needed = " << bDeadline[nextB].n << endl;
            if (nAvail < bDeadline[nextB].n) {
                bDeadline[nextB].n -= nAvail;
            }
            else
                nextB++;
            currT--;
            nAvail = s;
        }
        if (nogood)
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
}

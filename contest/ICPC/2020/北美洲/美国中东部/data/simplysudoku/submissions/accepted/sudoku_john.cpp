#include <iostream>
using namespace std;

int grid[9][9];
bool used[9][9][10] = {0};
int numEmpty = 0;

void update(int row, int col, int val)
{
    grid[row][col] = val;
    for(int v=1; v<=9; v++)
        used[row][col][v] = true;
    for(int r=0; r<9; r++)
        used[r][col][val] = true;
    for(int c=0; c<9; c++)
        used[row][c][val] = true;
    row = (row/3)*3;
    col = (col/3)*3;
    for(int r=row; r<row+3; r++)
        for(int c=col; c<col+3; c++)
            used[r][c][val] = true;
}

int checkForSingle(int r,int c)
{
    int val = -1;
    for(int v=1; v<=9; v++) {
        if (!used[r][c][v]) {
            if (val != -1)
                return -1;
            val = v;
        }
    }
    return val;
}

bool foundUniqueRowLoc(int row, int val, int& cc)
{
    cc = -1;
    for(int c=0; c<9; c++) {
        if (!used[row][c][val]) {
            if (cc != -1)
                return false;
            cc = c;
        }
    }
    return (cc != -1);
}

bool foundUniqueColLoc(int col, int val, int& rr)
{
    rr = -1;
    for(int r=0; r<9; r++) {
        if (!used[r][col][val]) {
            if (rr != -1)
                return false;
            rr = r;
        }
    }
    return (rr != -1);
}

bool foundUniqueSubLoc(int row, int col, int val, int& rr, int& cc)
{
    rr = -1;
    for(int r=row; r<row+3; r++) {
        for(int c=col; c<col+3; c++) {
            if (!used[r][c][val]) {
                if (rr != -1)
                    return false;
                rr = r;
                cc = c;
            }
        }
    }
    return (rr != -1);
}

void printgrid()
{
    for(int r=0; r<9; r++) {
        if (grid[r][0] == 0)
            cout << '.';
        else
            cout << grid[r][0];
        for(int c=1; c<9; c++) {
            if (grid[r][c] == 0)
                cout << " .";
            else
                cout << " " << grid[r][c];
        }
        cout << endl;
    }
}

int main()
{
    for(int r=0; r<9; r++) {
        for(int c=0; c<9; c++) {
            int val;
            cin >> val;
            if (val == 0)
                numEmpty++;
            else
                update(r, c, val);
        }
    }
    bool change;
    do {
        change = false;
        int val;
                        // check single value case
        for(int r=0; r<9; r++) {
            for(int c=0; c<9; c++) {
                if (grid[r][c] != 0)
                    continue;
                if ((val = checkForSingle(r,c)) > 0) {
                    update(r, c, val);
                    change = true;
                    numEmpty--;
               }
            }
        }
/**/
                        // check for unique location case
                        //  rows first
        int rr, cc;
        for(int r=0; r<9; r++) {
            for(int val=1; val<=9; val++) {
                if (foundUniqueRowLoc(r, val, cc)) {
                    update(r, cc, val);
                    change = true;
                    numEmpty--;
                }
            }
        }
                        //  cols next
        for(int c=0; c<9; c++) {
            for(int val=1; val<=9; val++) {
                if (foundUniqueColLoc(c, val, rr)) {
                    update(rr, c, val);
                    change = true;
                    numEmpty--;
                }
            }
        }
                        //  then subgrids
        for(int r=0; r<9; r+=3) {
            for(int c=0; c<9; c+=3) {
                for(int val=1; val<=9; val++) {
                    if (foundUniqueSubLoc(r, c, val, rr, cc)) {
                        update(rr, cc, val);
                        change = true;
                        numEmpty--;
                    }
                }
            }
        }
/**/
    } while (change);

    if (numEmpty == 0) {
        cout << "Easy" << endl;
    }
    else {
        cout << "Not easy" << endl;
    }
    printgrid();

}

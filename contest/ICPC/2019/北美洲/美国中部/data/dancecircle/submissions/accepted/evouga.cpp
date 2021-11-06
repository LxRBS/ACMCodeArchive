#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

struct Interval
{
    std::vector<std::pair<int, int> > ivals;

    int earliest() const
    {
        if(ivals.size() == 0)
        {
            return std::numeric_limits<int>::max();
        }
        else
        {
            return ivals[0].first;
        }
    }
    
    Interval *sum(const Interval &other) const
    {
        Interval *result = new Interval;
        std::vector<int> ends;
        for(auto &it : ivals)
        {
            ends.push_back(it.first);
            ends.push_back(it.second);
        }
        for(auto &it : other.ivals)
        {
            ends.push_back(it.first);
            ends.push_back(it.second);
        }
        std::sort(ends.begin(), ends.end());
        for(auto it = ends.begin(); it != ends.end(); ++it)
        {
            int e1 = *it;
            ++it;
            int e2 = *it;
            if(e1 != e2)
                result->ivals.push_back({e1,e2});
        }
        
        return result;
    }       
};

struct MatRow
{
    Interval *ival;
    int row;
    
    bool operator<(const MatRow &other) const
    {
        return ival->earliest() > other.ival->earliest();
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<Interval *> rows(n);
    std::vector<int> b(n);
    for(int i=0; i<n; i++)
    {
        int l, r;
        std::cin >> l >> r >> b[i];
        rows[i] = new Interval;
        int first = i - l;
        int last = i + r + 1;
        if(first >= 0 && last <= n)
        {
            rows[i]->ivals.push_back({first,last});
        }
        else
        {
            first = (n + first) % n;
            last = last % n;
            rows[i]->ivals.push_back({0, last});
            rows[i]->ivals.push_back({first,n});
        }
    }
    
    std::priority_queue<MatRow> pq;
    for(int i=0; i<n; i++)
    {
        pq.push({rows[i], i});
    }
    
    MatRow prev = pq.top();
    pq.pop();
    
    int nullity=0;
    bool ok = true;
    
    while(!pq.empty())
    {
        MatRow cur = pq.top();
        pq.pop();
        
        if(cur.ival->earliest() == std::numeric_limits<int>::max())
        {
            nullity++;
            if(b[cur.row] != 0)
                ok = false;
            delete cur.ival;
        }
        else if(cur.ival->earliest() == prev.ival->earliest())
        {
            Interval *newival = cur.ival->sum(*prev.ival);
            b[cur.row] = b[cur.row] ^ b[prev.row];
            pq.push({newival, cur.row});
            delete cur.ival;
        }        
        else
        {
            delete prev.ival;
            prev = cur;
        }
    }

    if(!ok)
        std::cout << "0" << std::endl;
    else
    {
        int64_t p = 1000000007;
        int64_t result = 1;
        int64_t base = 2;
        while(nullity > 0)
        {
            if((nullity % 2) == 1)
                result = (result * base) % p;
            base = (base * base) % p;
            nullity /= 2;
        }
        std::cout << result << std::endl;
    }

    delete prev.ival;
}

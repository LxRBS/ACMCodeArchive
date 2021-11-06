#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<std::pair<int, int64_t> > > graph;

int main()
{
    int n,m;
    std::cin >> n >> m;
    graph g(n);
    for(int i=0; i<m; i++)
    {
        int a,b;
        int64_t t;
        std::cin >> a >> b >> t;
        g[a-1].push_back({b-1,t});
        g[b-1].push_back({a-1,t});                
    }
    
    std::vector<int> cities;
        
    for(int i=0; i<7; i++)
    {
        int c;
        std::cin >> c;
        cities.push_back(c-1);
    }
    
    std::vector<int64_t> tocity(7);
    for(int i=0; i<7; i++)
        tocity[i] = -1;
    std::vector<int64_t> city2city(49);
    
    struct Visit
    {
        int dest;
        int64_t cost;
        
        bool operator<(const Visit &other) const
        {
            return cost > other.cost;
        }
    };
    
    std::priority_queue<Visit> pq;
    std::vector<int64_t> visited(n);
    for(int i=0; i<n; i++)
        visited[i] = std::numeric_limits<int64_t>::max();
            
    pq.push({0,0});
    while(!pq.empty())
    {
        Visit v = pq.top();
        pq.pop();
        
        if(visited[v.dest] <= v.cost)
            continue;
        visited[v.dest] = v.cost;
        
        for(int i=0; i<7; i++)
            if(v.dest == cities[i])
                tocity[i] = v.cost;
        
        for(auto &it : g[v.dest])
        {
            int64_t newcost = v.cost + it.second;
            if(newcost < visited[it.first])
                pq.push({it.first, newcost});
        }
    }
    
    for(int i=0; i<7; i++)
    {
        if(tocity[i] == -1)
        {
            std::cout << "-1" << std::endl;
            return 0;
        }        
    }
    
    for(int city=0; city<7; city++)
    {
        std::priority_queue<Visit> pq;
        for(int i=0; i<n; i++)
            visited[i] = std::numeric_limits<int64_t>::max();
        pq.push({cities[city], 0});
        
        while(!pq.empty())
        {
            Visit v = pq.top();
            pq.pop();
            
            if(visited[v.dest] <= v.cost)
                continue;
            visited[v.dest] = v.cost;
            
            for(int i=0; i<7; i++)
                if(v.dest == cities[i])
                    city2city[7*city + i] = v.cost;
            
            for(auto &it : g[v.dest])
            {
                int64_t newcost = v.cost + it.second;
                if(newcost < visited[it.first])
                    pq.push({it.first, newcost});
            }
        }
    }
    
    int64_t best = std::numeric_limits<int64_t>::max();
    
    std::vector<int> perm;
    for(int i=0; i<7; i++)
        perm.push_back(i);
    
    do {
        int64_t totcost = tocity[perm[0]];
        
        for(int city = 0; city < 6; city++)
        {            
            totcost += city2city[7*perm[city] + perm[city+1]];
        }
        
        best = std::min(best, totcost);
    } while( std::next_permutation(perm.begin(), perm.end()) );
    
    std::cout << best << std::endl;
}

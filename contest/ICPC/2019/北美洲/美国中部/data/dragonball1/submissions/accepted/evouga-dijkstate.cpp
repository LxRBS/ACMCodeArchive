#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

typedef std::vector<std::vector<std::pair<int, int64_t> > > graph;

int main()
{
    int n, m;
    std::cin >> n >> m;
    graph g(n);
    for(int i=0; i<m; i++)
    {
        int a, b;
        int64_t t;
        std::cin >> a >> b >> t;
        g[a-1].push_back({b-1, t});
        g[b-1].push_back({a-1, t});
    }       
    std::vector<std::vector<int> > dballs(n);
        
    for(int i=0; i<7; i++)
    {
        int c;
        std::cin >> c;
        dballs[c-1].push_back(i);
    }
    
    struct Visit
    {
        int dest;
        int state;
        int64_t cost;
        
        bool operator<(const Visit &other) const
        {
            return cost > other.cost;
        }
    };
    
    std::vector<std::vector<int64_t> > visited(127);
    for(int i=0; i<127; i++)
    {
        for(int j=0; j<n; j++)
            visited[i].push_back(std::numeric_limits<int64_t>::max());
    }
    
    std::priority_queue<Visit> pq;
    pq.push({0, 0, 0});
    while(!pq.empty())
    {
        Visit v = pq.top();
        pq.pop();
        if(visited[v.state][v.dest] < v.cost)
            continue;
            
        visited[v.state][v.dest] = v.cost;
        
        for(auto it : dballs[v.dest])
        {
            v.state |= (1<<it);
            if(v.state == 127)
            {
                std::cout << v.cost << std::endl;
                return 0;
            }
        }
        
        for(auto &nb : g[v.dest])
        {
            int64_t newcost = v.cost + nb.second;
            if(newcost < visited[v.state][nb.first])
            {
                visited[v.state][nb.first] = newcost;
                pq.push({nb.first, v.state, newcost});
            }
        }
    }
    
    std::cout << "-1" << std::endl;
}

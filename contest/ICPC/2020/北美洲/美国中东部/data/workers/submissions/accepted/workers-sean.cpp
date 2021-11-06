#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>

using namespace std;

struct point{
  int x;
  int y;

};

void Print_Vector(const vector<int>& v){
  for(int i = 0; i < v.size(); i++)
    cout << v[i] << " ";
  cout << endl;
}
void Print_2d_Vector(const vector<vector<int> >& v){
  for(int i = 0; i < v.size(); i++){
    for(int j = 0; j < v.size(); j++)
      cout << v[i][j] << " ";
    cout << endl;
  }
}


bool Find_Path(const vector<vector<bool> >& g, const vector<vector<int> >& f, vector<int>& path){
  //Print_2D_Vector(g);
  vector<bool> seen(g.size());
  vector<int> parent(g.size(), -1);
  parent[0] = -1;
  seen[0] = true;
  deque<int> frontier;
  frontier.push_back(0);
  bool found = false;
  while(!found && !frontier.empty()){
      int cur = frontier.front();
      frontier.pop_front();
      if(cur == g.size()-1)
	found = true;
      else{
	for(int i = 0; i < g.size(); i++){
	  if(g[cur][i] && !seen[i] && (( cur < i && f[cur][i] == 0) || cur > i && f[i][cur] == 1)){
	    seen[i] = true;
	    parent[i] = cur;
	    frontier.push_back(i);
	  }
	}
      }
  }
  if(found){
    path.resize(0);

    int cur = g.size()-1;
    path.push_back(cur);
    while(cur != 0){
      path.push_back(parent[cur]);
      cur = parent[cur];
    }

    reverse(path.begin(), path.end());

  }
  return found;
}
void Create_Zero_Matching(const vector<vector<int> >& g, vector<point>& matching){
  vector<vector<bool> > bipartite(2*g.size()+2);
  for(int i = 0; i < bipartite.size(); i++)
    bipartite[i].resize(bipartite.size(), false);
  for(int i = 1; i <= g.size(); i++){
    bipartite[0][i] = true;
  }
  for(int i = g.size()+1; i < bipartite.size()-1; i++)
    bipartite[i][bipartite.size()-1] = true;
  for(int i = 0; i < g.size(); i++)
    for(int j = 0; j < g.size(); j++){
      if(g[i][j] == 0){
	bipartite[i+1][j+g.size()+1] = true;
	bipartite[j+g.size()+1][i+1] = true;
      }
    }

  vector<vector<int> > f(bipartite.size());
  for(int i = 0; i < f.size(); i++)
    f[i].resize(bipartite.size(), 0);
  vector<int> path;
  while(Find_Path(bipartite,f, path)){
    for(int i = 0; i < path.size()-1; i++){
      if(path[i] < path[i+1])
	f[path[i]][path[i+1]]++;
      else
	f[path[i+1]][path[i]]--;
    }
  }

  matching.resize(0);
  for(int i = 1; i < f.size(); i++){
    for(int j = 0; j < f.size()-1; j++){
      if(f[i][j] != 0){
	point p;
	p.x = i;
	p.y = j;
	matching.push_back(p);
      }
    }
  }
}


bool Find(const vector<point>& v, const point& key){
  for(int i = 0; i < v.size(); i++)
    if(v[i].x == key.x && v[i].y == key.y)
      return true;
  return false;
}


void Vertex_Cover(const vector<vector<int> >& grid, const vector<point>& matches, vector<bool>& r_in_cover, vector<bool>& c_in_cover){
  r_in_cover.resize(grid.size(), false);
  c_in_cover.resize(grid.size(), false);

  for(int i = 0; i < matches.size(); i++){
    r_in_cover[matches[i].x-1] = true;
  }
  vector<bool> r_seen (grid.size(), false);
  vector<bool> c_seen (grid.size(), false);

  for(int i = 0; i < r_in_cover.size(); i++){
    if(!r_seen[i] && !r_in_cover[i]){
      deque<int> frontier;
      frontier.push_back(i);
      r_seen[i] = true;
      while(!frontier.empty()){
	int cur = frontier.front();
	frontier.pop_front();
	for(int j = 0; j < grid.size(); j++){
	  point p;
	  p.x = i+1;
	  p.y = j+grid.size()+1;
	  if(!c_seen[j] && grid[cur][j] == 0 && !Find(matches, p)){
	    c_seen[j] = true;
	    c_in_cover[j] = true;
	    for(int k = 0; k < matches.size(); k++){
	      if(!r_seen[matches[k].x-1] && matches[k].y - grid.size()-1 == j){
		frontier.push_back(matches[k].x-1);
		r_seen[matches[k].x-1] = true;
		r_in_cover[matches[k].x-1] = false;
	      }
	    }
	  }
	}
      }
    }
  }
}



// costs is an adjacency matrix of all vertices, with all vertices across the
// rows and columns (so for an nxn matching, it's a 2n x 2n vector.  I know
// it's inefficient, I'm sorry
// return a matching vector where matching[i] is the number of the vertex
// it matches with.  You might want to subtract n from the results to get
// the number of the vertex in the other side,
// if you're thinking of it as 2 groups
void Create_Matching(const vector<vector<int> >& costs, vector<int>& matching){
   matching.resize(costs.size()/2);
  vector<vector<int> > grid(costs.size()/2);
  for(int i = 0; i < grid.size(); i++){
    grid[i].resize(costs.size()/2);
    for(int j = 0; j < grid[i].size(); j++){
      grid[i][j] = costs[i][j+costs.size()/2];
    }
  }
  

  // subtract row minima
  for(int i = 0; i < grid.size(); i++){
    int min_val = 500000;
    for(int j = 0; j < grid.size(); j++){
      int cur = grid[i][j];
      if(cur < min_val){
	min_val = cur;
      }
    }
    for(int j = 0; j < grid.size(); j++)
      grid[i][j] = grid[i][j] - min_val;
  }

  // subtract col minima
  for(int j = 0; j < grid.size(); j++){
    int min_val = 500000;
    for(int i = 0; i < grid.size(); i++){
      int cur = grid[i][j];
      if(cur < min_val){
	min_val = cur;
      }
    }
    for(int i = 0; i < grid.size(); i++){
      grid[i][j] = grid[i][j] - min_val;
    }
  }

  vector<point> zero_matching;
  Create_Zero_Matching(grid, zero_matching);
  while(zero_matching.size() != grid.size()){
    int min = 500000;

    vector<bool> r_in_matching;
    vector<bool> c_in_matching;
    Vertex_Cover(grid, zero_matching, r_in_matching, c_in_matching);
    // Print_Vector(r_in_matching);
    //Print_Vector(c_in_matching);
    for(int i = 0; i < grid.size(); i++)
      for(int j = 0; j < grid.size(); j++){
	if(!r_in_matching[i] && !c_in_matching[j]){
	  if(grid[i][j] < min)
	    min = grid[i][j];
	}
      }
    for(int i = 0; i < grid.size(); i++)
      for(int j = 0; j < grid.size(); j++){
	if(!r_in_matching[i] && !c_in_matching[j]){
	  grid[i][j] = grid[i][j] - min;
	}
	if(r_in_matching[i] && c_in_matching[j]){
	  grid[i][j] = grid[i][j] + min;
	}
      }
    Create_Zero_Matching(grid, zero_matching);
  }
  matching.resize(grid.size());
  for(int i = 0; i < zero_matching.size(); i++){
    matching[zero_matching[i].x-1] = zero_matching[i].y-1;
  }

}

int Matching_Cost(const vector<vector<int> >& adjacency, const vector<int>& matching){
  int total = 0;
  for(int i = 0; i < matching.size(); i++)
    total = total + adjacency[i][matching[i]];
  return total;
}

int main(){
  int n;
  cin >> n;
  vector<vector<int> > a_dist_in(n);
  vector<vector<int> > b_dist_in(n);
  for(int i = 0; i < n; i++){
    a_dist_in[i].resize(n);
    b_dist_in[i].resize(n);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> a_dist_in[i][j];
      cin >> b_dist_in[i][j];
    }
  }
  
  vector<vector<int> > a_dist_out(n);
  vector<vector<int> > b_dist_out(n);
  for(int i = 0; i < n; i++){
    a_dist_out[i].resize(n);
    b_dist_out[i].resize(n);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> a_dist_out[i][j];
      cin >> b_dist_out[i][j];
    }
  }
  
  int best_cost = 5000000;
  vector<int> best_in_matching(n);
  vector<int> best_out_matching(n);
  int best_start = -2;
  // eventually add the multiple levels
  for(int start_b = -1; start_b < n; start_b++){
    vector<vector<int> >adjacency(2*n);

    for(int i = 0; i < 2*n; i++){
      adjacency[i].resize(2*n);
    }
    for(int i = 0; i < n; i++){

      for(int j = n; j < 2*n; j++){
	if(j <= start_b+n){
	  adjacency[i][j] = a_dist_in[i][j-n];
	  adjacency[j][i] = adjacency[i][j];
	}
	else{
	  adjacency[i][j] = b_dist_in[i][j-n];
	  adjacency[j][i] =adjacency [i][j];
	}
      }
    }
  
    //   Print_2d_Vector(adjacency);
    vector<int> matching;
    Create_Matching(adjacency, matching);
    //   Print_Vector(matching);
    int cost1 = 0;
    for(int matching_num = 0; matching_num < n; matching_num++){
      cost1 = cost1 + adjacency[matching_num][matching[matching_num]];
    }
    //cout << cost1 << endl;
    // now do it all over again after leaving the gate
    
    for(int i = 0; i < n; i++){

      for(int j = n; j < 2*n; j++){
	if(j <= start_b+n){
	  adjacency[i][j] = a_dist_out[i][j-n];
	  adjacency[j][i] = adjacency[i][j];
	}
	else{
	  adjacency[i][j] = b_dist_out[i][j-n];
	  adjacency[j][i] = adjacency[i][j];
	}
      }
    }
    // Print_2d_Vector(adjacency);
    vector<int> out_matching;
    Create_Matching(adjacency, out_matching);
    //   Print_Vector(out_matching);
    
     int cost2= 0;
    for(int matching_num = 0; matching_num < n; matching_num++){
      cost2 = cost2 + adjacency[matching_num][out_matching[matching_num]];
      
    }
    // cout << cost2 << endl;
    
    // cout << "first_b = " << start_b << ": cost = " << cost1+cost2 << endl;
     // cout << cost1+cost2 << endl;
    if(cost1+cost2 < best_cost){
      best_cost = cost1+cost2;
      for(int i = 0; i < best_in_matching.size(); i++){
	best_in_matching[i] = matching[i];
	best_out_matching[i] = out_matching[i];
      }
      best_start = start_b;
    }
   
  }
  //  cout << "best start: " << best_start << endl;
  cout << best_cost << endl;
  int total = 0;
  for(int i = 0; i < n; i++){
    cout << i+1 << " ";
     int in_pos = best_in_matching[i]-n;

    if(best_in_matching[i]-n <= best_start){
      total = total + a_dist_in[i][in_pos] + a_dist_out[in_pos][best_out_matching[in_pos]];
      cout << in_pos+1 << "A ";
      for(int j = 0; j < n; j++)
	if(in_pos == best_out_matching[j]-n)
	  cout << j+1<< endl;
    }
    else{
      total = total + b_dist_in[i][in_pos] + b_dist_out[in_pos][best_out_matching[in_pos]];
      cout << in_pos+1 << "B ";
      for(int j = 0; j < n; j++)
	if(in_pos == best_out_matching[j]-n)
	  cout << j+1<< endl;
    }
    //cout << "Double check: " << total << endl;
  }
   
  return 0;
}
    

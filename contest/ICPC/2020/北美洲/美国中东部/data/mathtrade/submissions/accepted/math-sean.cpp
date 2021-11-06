#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct person{
  string name;
  string has;
  string wants;
};

int Chain_Length(vector<person>& people, int start){
  int length = 0;
  vector<bool> used(people.size(), false);
  int cur = start;
  
  bool dead_end = false;
  while(!dead_end){
    dead_end = true;
    for(int i = 0; i < people.size(); i++){
      if(!used[i] && people[i].wants == people[cur].has){
	cur = i;
	length++;
	dead_end = false;
	used[i] = true;
	i = people.size();
      }
    }
  }
  if(used[start])
    return length;
  else return -1;
}


int main(){
  int n;
  cin >> n;
  vector<person> people(n);
  for(int i = 0; i < n; i++){
    cin >> people[i].name;
    cin >> people[i].has;
    cin >> people[i].wants;
  }

  int best = 0;
  for(int i = 0; i < n; i++){
    int cur = Chain_Length(people, i);
    if(cur > best)
      best = cur;
  }
  if(best == 0)
    cout << "No trades possible" << endl;
  else
    cout << best << endl;
}

  

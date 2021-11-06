#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct dyad{
  string parent;
  string child;
};

struct ancestor_list{
  string key;
  vector<string> ancestors;
};

void Print_All_Ancestors(const vector<ancestor_list>& all_ancestors){
  for(int i = 0; i < all_ancestors.size(); i++){
    cout << "Ancestors of " << all_ancestors[i].key << ": ";
    for(int j = 0; j < all_ancestors[i].ancestors.size(); j++){
      cout << all_ancestors[i].ancestors[j] << " ";
    }
    cout << endl;
  }
}

void Sort(vector<dyad>& node_list){
  for(int i = 0; i < node_list.size(); i++)
    for(int j = 0; j < node_list.size()-1; j++){
      if(node_list[j].child > node_list[j+1].child){
	dyad temp = node_list[j];
	node_list[j] = node_list[j+1];
	node_list[j+1] = temp;
      }
    }
}

int Find_Node(const vector<dyad>& node_list, string key){
  int low = 0;
  int high = node_list.size()-1;
  while(low <= high){
    int mid = (low + high)/2;
    if(node_list[mid].child == key)
      return mid;
    if(node_list[mid].child < key)
      low = mid+1;
    else
      high = mid-1;
  }
  return -1;
}

// this seems like a really dumb way to do this
string Find_Root(const vector<dyad>& node_list){
  for(int i = 0; i < node_list.size(); i++){
    string p = node_list[i].parent;
    if(Find_Node(node_list,p) == -1)
      return p;
  }
  cout << "No root?" << endl;
}

void Build_All_Ancestors(const vector<dyad>& relations, vector<ancestor_list>& all_ancestors){
  for(int i = 0; i < relations.size(); i++){
    ancestor_list cur_list;
    cur_list.key = relations[i].child;
    string cur_parent = relations[i].parent;
    cur_list.ancestors.push_back(cur_parent);
    int parent_loc = Find_Node(relations, cur_parent);
    while(parent_loc != -1){
      cur_parent = relations[parent_loc].parent;
      cur_list.ancestors.push_back(cur_parent);
      parent_loc = Find_Node(relations, cur_parent);
    }
  
    all_ancestors.push_back(cur_list);
  }
}

vector<string> Find_Ancestors(const vector<ancestor_list>& all_ancestors, string k){
  int low = 0;
  int high = all_ancestors.size();
  while(low <= high){
    int mid = (low+high)/2;
    if(all_ancestors[mid].key == k)
      return all_ancestors[mid].ancestors;
    if(all_ancestors[mid].key < k)
      low = mid+1;
    if(all_ancestors[mid].key > k)
      high = mid-1;
  }
  // it's the root
  return vector<string>();

}
int Find_String(const vector<string>& node_list, string key){
  for(int i = 0; i < node_list.size(); i++)
    if(node_list[i] == key)
      return i;
  return -1;
	
}

    
bool Handle_Direct_Relationship(const vector<dyad>& relations, const vector<ancestor_list>& all_relations, string first, string second){
  vector<string> first_ancestors = Find_Ancestors(all_relations, first);
  int pos = Find_String(first_ancestors, second);
  if(pos != -1){
    if(pos == 0){
      cout << first << " is the child of " << second << endl;
      return true;
    }
    int num_greats = pos-1;
    cout << first << " is the ";
    for(int i = 0; i < num_greats; i++){
      cout << "great ";
    }
    cout << "grandchild of " << second << endl;
    return true;
  }
  vector<string> second_ancestors = Find_Ancestors(all_relations, second);
  pos = Find_String(second_ancestors, first);
  if(pos != -1){
    if(pos == 0){
      cout << second << " is the child of " << first << endl;
      return true;
    }
    int num_greats = pos-1;
    cout << second << " is the ";
    for(int i = 0; i < num_greats; i++)
      cout << "great ";
    cout << "grandchild of " << first << endl;
    return true;
  }
  return false;
}

string Name_Of(int n){
  // 12 is "12th" not "12nd"
  if(n>= 10 && n<= 20)
    return to_string(n) + "th";

  if(n > 10){

  if(n %10 == 1)
    return to_string(n/10) + "1st";
  if(n %10 == 2)
    return to_string(n/10) + "2nd";
  if(n %10 == 3)
    return to_string(n/10) + "3rd";
   
  return to_string(n) + "th";
  }

  else{ // no leading 0 on 1-9 cousins
    if(n %10 == 1)
    return "1st";
  if(n %10 == 2)
    return "2nd";
  if(n %10 == 3)
    return "3rd";
   
  return to_string(n) + "th";
  }
  
}

void Handle_Cousin_Relationship(const vector<dyad>& relations, const vector<ancestor_list>& all_relations, string first, string second){
  vector<string> first_ancestors = Find_Ancestors(all_relations, first);
  vector<string> second_ancestors = Find_Ancestors(all_relations, second);
  int m = first_ancestors.size()-1;
  int n = second_ancestors.size()-1;
  // both should be pointing to the root
  while(m >= 0 && n >=0 && first_ancestors[m] == second_ancestors[n]){
    m--;
    n--;
  }
  m++;
  n++;
  if(m == 0 && n == 0)
    // they both have the exact same ancestor list
    cout << first << " and " << second << " are siblings" << endl;
  
  else{
    // cousins
    if(m == n){
      cout << first << " and " << second << " are " << Name_Of(m) << " cousins" << endl;
    }
    else{
      if(m > n){
	int temp = m;
	m = n;
	n = temp;

      }
      if(n-m > 1){
      	cout << first << " and " << second << " are " << Name_Of(m) << " cousins, " << n-m << " times removed" << endl;
      }
      else{
	cout << first << " and " << second << " are " << Name_Of(m) << " cousins, " << n-m << " time removed" << endl;
	
      }
    }
  }
}


  

int main(){
  int t, p;
  cin >> t >> p;

  vector<dyad> relations;
  for(int i = 0; i < t; i++){
    string adult;
    cin >> adult;
    int num_children;
    cin >> num_children;
    for(int j = 0; j < num_children; j++){
      string kid;
      cin >> kid;
      dyad new_relation;
      new_relation.parent = adult;
      new_relation.child = kid;
      relations.push_back(new_relation);
    }
   
  }
  Sort(relations);
  string root = Find_Root(relations);
  vector<ancestor_list> all_ancestors;
  Build_All_Ancestors(relations, all_ancestors);
  //Print_All_Ancestors(all_ancestors);
  for(int i = 0; i < p; i++){
    string first, second;
    cin >> first >> second;
    int first_pos = Find_Node(relations,first);
    int second_pos = Find_Node(relations,second);
    if(!Handle_Direct_Relationship(relations, all_ancestors, first, second))
      Handle_Cousin_Relationship(relations, all_ancestors, first, second);
  }
  
  return 0;
}
  

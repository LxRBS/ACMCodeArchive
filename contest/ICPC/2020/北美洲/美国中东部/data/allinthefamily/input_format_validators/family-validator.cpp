#include <iostream>
#include <string>
#include <vector>

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

int main(){
  int t, p;
  cin >> t >> p;
  if(t <= 0){
    cout << "ERROR: t too small!" << endl;
    return 0;
  }
  if(t > 100) {
    cout << "ERROR: t too large!" << endl;
    return 0;
  }
  if(p <= 0) {
    cout << "ERROR: p too small!" << endl;
    return 0;
  }
  if(p > 1000) {
    cout << "ERROR: p too large!" << endl;
    return 0;
  }

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
  if(relations.size() > 99){	// bobk: changed this from 100, can only have max 99 edges
    cout << "ERROR- too many nodes!" << endl;
    return 0;
  }
  Sort(relations);
  for(int i = 0; i < relations.size()-1; i++){
    if(relations[i].child == relations[i+1].child) {
      cout << "ERROR: " << relations[i].child << " is a child of both " << relations[i].parent << " and " << relations[i+1].parent << endl;
      return 0;
    }
  }

  string root = Find_Root(relations);
  vector<ancestor_list> all_ancestors;
  Build_All_Ancestors(relations, all_ancestors);
  for(int i = 0; i < all_ancestors.size(); i++){
    int num_ancestors = all_ancestors[i].ancestors.size();
    if(all_ancestors[i].ancestors[num_ancestors-1] != root){
      cout << "ERROR: Tree has two roots: " << root << " and " << all_ancestors[i].ancestors[num_ancestors-1] << endl;
      return 0;
    }
  }

  int num_pairs = 0;
  string first, second;
  while(cin >> first >> second){
    if(first == second) {
      cout << "ERROR: pairs should be different: " << first << endl;
      return 0;
    }
    num_pairs++;
    if(Find_Node(relations, first) == -1 && first != root) {
      cout << "ERROR: Request for relation of node " << first << " which is not in tree!" << endl;
      return 0;
    }
    if(Find_Node(relations, second) == -1 && second != root) {
      cout << "ERROR: Request for relation of node " << second << " which is not in tree!" << endl;
      return 0;
    }
  }
  if(num_pairs != p) {
    cout << "ERROR: " << p << "pairs requested, but " << num_pairs << " pairs seen!" << endl;
    return 0;
  }

  return 42;
}

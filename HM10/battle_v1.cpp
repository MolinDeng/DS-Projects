#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MaxVertex 3000000
#define _INFINITY 0x7fffffff

typedef struct _edge{
	int v1;
	int v2;
	int cost;
}edge;

int root[MaxVertex];
vector<edge> status_1;
vector<edge> status_0;
vector<int>  Most_vital_Cities;
int Maxcost = 0;

int find_root(int x){
	if(root[x] == -1)
		return x;
	else
		return root[x] = find_root(root[x]);
}
bool cmp(edge a,edge b){
	return a.cost < b.cost;
}

int main(){
	int m, n, i, conquered_city;
	cin >> n >> m;
	for(i = 0; i < m; i++){
		edge temp;
		int status;
		cin >> temp.v1 >> temp.v2 >> temp.cost >> status;
		if(status == 0){
			status_0.push_back(temp);
		}
		else if(status == 1){
			status_1.push_back(temp);
		}
	}
	sort(status_0.begin(),status_0.end(),cmp);
	for(conquered_city = 1; conquered_city <= n; conquered_city++){
		memset(root, -1, (n + 1) * sizeof(int)); 
		int cost = 0;//初始化合并两个簇所需要的最小代价，而Maxcost是所有最小代价中的最大代价
		for(i = 0; i < status_1.size(); i++){
			int c1 = status_1[i].v1, c2 = status_1[i].v2;
			if(conquered_city == c1 || conquered_city == c2)
				continue;
			int root_c1 = find_root(c1);
			int root_c2 = find_root(c2);
			if(root_c1 != root_c2)
				root[root_c2] = root_c1;
		}
		
		int sub_graph_num = 0;
		
		for(i = 1; i <= n; i++){
			if(i != conquered_city && root[i] == -1)
				sub_graph_num++;
		}
		
		
		for(i = 0; i < status_0.size(); i++){
			if(sub_graph_num == 1)
				break;
			int c1 = status_0[i].v1, c2 = status_0[i].v2;
			if(c1 == conquered_city || c2 == conquered_city) 
				continue;
			int root_c1 = find_root(c1);
			int root_c2 = find_root(c2);
			if(root_c1 != root_c2){
				root[root_c2] = root_c1;
				cost += status_0[i].cost;
				sub_graph_num--;
			}
		}
		if(sub_graph_num > 1){
			cost = _INFINITY;
		}
		if(cost > 0 && cost > Maxcost){
			Maxcost = cost;
			Most_vital_Cities.erase(Most_vital_Cities.begin(), Most_vital_Cities.end());
			Most_vital_Cities.push_back(conquered_city);
		}
		else if(cost > 0 && Maxcost == cost){
			Most_vital_Cities.push_back(conquered_city);
		}
	}
	
	if(Most_vital_Cities.empty())
		cout << "0";
	else{
		for(i = 0; i < Most_vital_Cities.size(); i++){
			if(i != 0)
				cout << " ";
			cout << Most_vital_Cities[i];
		}		
	}
	return 0;
}

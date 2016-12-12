#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MaxVertexes 10

using namespace std;

struct _G{
	int Adj[MaxVertexes][MaxVertexes];
	int V_num;
	int E_num;
}G;

int is_visited[MaxVertexes];
int is_inque[MaxVertexes];
vector<int> Comp_Find;
queue<int> Que; 
int Components_num;

void ReadG();
void DFS(int v);
void BFS(int v);
void Print_Comp();

int main(){
	ReadG();
	
	for(int i = 0; i < G.V_num; i++){
		if(!is_visited[i]){
			DFS(i);
		}
		Print_Comp();
	}
	
	for(int i = 0; i < MaxVertexes; i++)
		is_visited[i] = 0;
	
	for(int i = 0; i < G.V_num; i++){
		if(!is_visited[i]){
			BFS(i);
		}
		Print_Comp();
	}
	return 0;
}

void ReadG(){
	cin >> G.V_num >> G.E_num;
	int i;
	for(i = 0; i < MaxVertexes; i++)
		for(int j = 0; j < MaxVertexes; j++)
			G.Adj[i][j] = 0;
	for(i = 0; i < G.E_num; i++){
		int v, w;
		cin >> v >> w;
		G.Adj[v][w] = G.Adj[w][v] = 1;
	}
}
void DFS(int v){
	Comp_Find.push_back(v);
	is_visited[v] = 1;
	for(int w = 0; w < G.V_num; w++){
		if(!is_visited[w] && G.Adj[v][w]){
			DFS(w);
		}
	}
}

void BFS(int v){
	int V;
	Que.push(v);
	is_inque[v] = 1;
	while(!Que.empty()){
		V = Que.front();
		Comp_Find.push_back(V);
		is_visited[V] = 1;
		Que.pop();
		for(int W = 0; W < G.V_num; W++){
			if(G.Adj[V][W] && !is_visited[W] && !is_inque[W]){
				Que.push(W);
				is_inque[W] = 1;
			}
		}
	}
}
void Print_Comp(){
	if(Comp_Find.empty())
		return;
	else{
		cout << "{";
		for(int i = 0; i < Comp_Find.size(); i++){
			cout << " " << Comp_Find[i];
		}
		cout << " }" << endl;
	}
	Comp_Find.clear();
}
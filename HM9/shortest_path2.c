#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S );

int main()
{
    int dist[MaxVertexNum], path[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, path, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", path[V]);
    printf("\n");

    return 0;
}

/* Your function will be put here */

int Find_small(int dist[],int know[]){
	int min_d = INFINITY, min_i = -1;
	int i;
	for(i = 0; i < MaxVertexNum; i++){
		if(know[i] == false){
			if(dist[i] < min_d){
				min_d = dist[i];
				min_i = i;
			}	
		} 
	}
	return min_i;
}

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S ){
	/*initial distance and path*/
	int i;
	int know[MaxVertexNum] = {false};
	int edge_count[MaxVertexNum] = {0};
	for(i = 0; i < MaxVertexNum; i++){
		if(i == S){
			dist[i] = 0;
			path[i] = -1;
		}
		else{
			dist[i] = INFINITY;
			path[i] = -1;
		}
	}
	/*using Dijkstra alg*/
	int V;
	while(1){
		V = Find_small(dist,know);
		if(V == -1) break;
		know[V] = true;
		for(i = 0; i < Graph->Nv; i++){
			if(Graph->G[V][i] != INFINITY){
				if(dist[V]+Graph->G[V][i] < dist[i]){
					dist[i] = dist[V]+Graph->G[V][i];
					path[i] = V;
					edge_count[i] = edge_count[V] + 1;
				}
				else if(dist[V]+Graph->G[V][i] == dist[i]){
					if(edge_count[i] > edge_count[V]+1){
						path[i] = V;
					}
				}
			}
		}
	}
	for(i=0;i<Graph->Nv;i++)
        if(dist[i]==INFINITY)
        {
            dist[i]=-1;
            path[i]=-1;
        }
}
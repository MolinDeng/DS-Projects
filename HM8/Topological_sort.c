#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool TopSort( LGraph Graph, Vertex TopOrder[] );

int main()
{
    int i;
    Vertex TopOrder[MaxVertexNum];
    LGraph G = ReadG();

    if ( TopSort(G, TopOrder)==true )
        for ( i=0; i<G->Nv; i++ )
            printf("%d ", TopOrder[i]);
    else
        printf("ERROR");
    printf("\n");

    return 0;
}
/* Your function will be put here */
bool TopSort( LGraph Graph, Vertex TopOrder[] ){
	/*create indegree table*/
	int *indegree = (int*)malloc(sizeof(int)*Graph->Nv);
	int *queue = (int*)malloc(sizeof(int)*Graph->Nv);
	int i = 0, counter = 0, front = 0, rear = -1, V;
	PtrToAdjVNode p;
	for(i = 0; i < Graph->Nv; i++)
		indegree[i] = 0;
	for(i = 0; i < Graph->Nv; i++){
		for(p = (Graph->G[i]).FirstEdge; p != NULL; p = p->Next){
			indegree[p->AdjV]++;
		}
	}
	
	for(i = 0; i < Graph->Nv; i++){
		if(indegree[i] == 0){
			queue[++rear] = i;
		}
	}
	
	while(front <= rear){
		V = queue[front++];
		TopOrder[counter++] = V;
		for(p = (Graph->G[V]).FirstEdge; p != NULL; p = p->Next){
			if(--indegree[p->AdjV] == 0)
				queue[++rear] = p->AdjV;
		}
	}

	if(counter != Graph->Nv)
		return false;
	else 
		return true;
}

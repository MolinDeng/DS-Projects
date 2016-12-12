/*
We can find all strongly connected components in O(V+E) time using Kosaraju’s algorithm. 
Following is detailed Kosaraju’s algorithm.
1) Create an empty stack ‘S’ and do DFS traversal of a graph. 
   In DFS traversal, after calling recursive DFS for adjacent vertices of a vertex, 
   push the vertex to stack.
2) Reverse directions of all arcs to obtain the transpose graph.
3) One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’. 
   Take v as source and do DFS (call DFSUtil(v)). 
   The DFS starting from v prints strongly connected component of v. 
*/

#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

int Stack[MaxVertices];
int top = -1;
int visited[MaxVertices] = {0};
int G_reverse[MaxVertices][MaxVertices];
  
Graph ReadG(){    
	Graph G = (Graph)malloc(sizeof(struct GNode));
	scanf("%d %d", &G->NumOfVertices, &G->NumOfEdges);
	G->Array = (PtrToVNode*)malloc(sizeof(PtrToVNode) * G->NumOfVertices);
	int i;
	int w, v;
	for(i = 0; i < G->NumOfVertices; i++){
		G->Array[i] = NULL;
	}
	for(i = 0; i < G->NumOfEdges; i++){
		scanf("%d %d", &v, &w);
		PtrToVNode temp = (PtrToVNode)malloc(sizeof(struct VNode));
		temp->Vert = w;
		temp->Next = NULL;
		if(G->Array[v] == NULL){
			G->Array[v] = temp;
		}
		else{
			PtrToVNode pnode;
			for(pnode = G->Array[v]; pnode->Next != NULL; pnode = pnode->Next);
			pnode->Next = temp;
		}
	}
	return G;
}  

void DFS_Stack(Graph G, int v){
	PtrToVNode temp;
	visited[v] = 1;
	for(temp = G->Array[v]; temp != NULL; temp = temp->Next){
		if(!visited[temp->Vert]){
			DFS_Stack(G, temp->Vert);
		}
	}
	Stack[++top] = v;
}

void DFS_Print(Graph G, int v, int first){
	int w;
	visited[v] = 1;
	printf("%d ", v);
	for(w = 0; w < G->NumOfVertices; w++){
		if(!visited[w] && G_reverse[v][w])
			DFS_Print(G, w, first);
	}
	if(v == first) printf("\n");
}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
	int i, v;
	for(i = 0; i < G->NumOfVertices; i++){
		if(!visited[i]){
			DFS_Stack(G, i);
		}
	}
	
	PtrToVNode temp;
	for(i = 0; i < G->NumOfVertices; i++){
		for(temp = G->Array[i]; temp != NULL; temp = temp->Next){
			G_reverse[temp->Vert][i] = 1;
		}
	}
	
	for(i = 0; i < MaxVertices; i++)
		visited[i] = 0;
	
	for(v = Stack[top]; top != -1; v = Stack[--top]){
		if(!visited[v])
			DFS_Print(G, v, v);
//		for(i = 0; i < G->NumOfVertices; i++){
//			if(visited[i] == 0){
//				printf("\n");
//				break;
//			}
//		}
	}
}

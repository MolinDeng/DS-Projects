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

 

int dfn[MaxVertices], low[MaxVertices], stack[MaxVertices], top, t, in_stack[MaxVertices];

int min(int a, int b){
    if(a < b){
        return a;
    }
    else{
        return b;
    }
}

void Tarjan(Graph G, int v){
    PtrToVNode node = G->Array[v];
    int son, tmp;
    
    dfn[v] = low[v] = ++t;
    stack[++top] = v;
    in_stack[v] = 1;
    
    while(NULL != node){
        son = node->Vert;
        if(-1 == dfn[son]){
            Tarjan(G, son);
            low[v] = min(low[son], low[v]);
        }
        else if(1 == in_stack[son]){
            low[v] = min(low[v], dfn[son]);
        }
        node = node->Next;
    }
    if(dfn[v] == low[v]){
        do{
            tmp = stack[top--];
            printf("%d ", tmp);
            in_stack[tmp] = 0;
        }while(tmp != v);
        printf("\n");
    }
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int i;
    
    for(i = 0; i < MaxVertices; i++){
        dfn[i] = -1;
        low[i] = in_stack[i] = 0;
    }
    top = -1;
    t = 0;
    
    for(i = 0; i < G->NumOfVertices; i++){
        if(-1 == dfn[i]){
            Tarjan(G, i);
        }
    }
}

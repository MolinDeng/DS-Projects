#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}
int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}
//swap version
void PercolateUp( int p, PriorityQueue H ){
	if(H == NULL)
		return;
	int i = 0,parent;
	for(i = p; ; i = parent){
		int temp;
		parent = i/2;
		if(H->Elements[i] < H->Elements[parent]){
			temp = H->Elements[parent];
			H->Elements[parent] = H->Elements[i];
			H->Elements[i] = temp;
		}
		else 
			break;
	}
}
void PercolateDown( int p, PriorityQueue H ){
	if(H == NULL)
		return;
	int i;
	int child;
	for(i = p; i*2 <= H->Size; i = child){
		child = 2*i;
		if(child != H->Size && H->Elements[child] > H->Elements[child+1]){
			child++;
		}
		int temp;
		if(H->Elements[i] > H->Elements[child]){
			temp = H->Elements[child];
			H->Elements[child] = H->Elements[i];
			H->Elements[i] = temp;
		}
		else 
			break;
	}
}
//None swap version
void PercolateUp( int p, PriorityQueue H )
{
    int tmp=H->Elements[p];
    for(;H->Elements[p/2]>tmp;p/=2){
        H->Elements[p]=H->Elements[p/2];
    }
    H->Elements[p]=tmp;
}
 
void PercolateDown( int p, PriorityQueue H )
{
    int child;
    int tmp=H->Elements[1];
    for(;2*p<H->Size;p=child){
        child=2*p;
        if(child!=H->Size&&H->Elements[child+1]<H->Elements[child]){
            child++;
        }
        if(H->Elements[child]<tmp)
			H->Elements[p]=H->Elements[child];
        else break;
    }
    H->Elements[p]=tmp;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode {
  int Key;
  BinTree Left;
  BinTree Right;
};

BinTree BuildTree(void);
BinTree Insert(BinTree T, int *a);
void Level_print(BinTree T);
int mycmp(const void* a, const void* b); 

int N;

int main() {
  BinTree T = BuildTree();
  Level_print(T);
  free(T);
  return 0;
}

int mycmp(const void* a, const void* b){
  int *p1,*p2;
  p1 = (int*)a;
  p2 = (int*)b;
  return (*p1)-(*p2);
}
BinTree BuildTree(void) {
  scanf("%d", &N);
  if(N == 0) return NULL;
  int *flag = (int *)malloc(sizeof(int) * (2*N+1));
  BinTree *Node = (BinTree*)malloc(sizeof(BinTree)*(2*N+1));
  int *num = (int *)malloc(sizeof(int) * N);
  int i;
  for(i = 0; i < 2*N+1; i++){
  	Node[i] = (struct TNode*)malloc(sizeof(struct TNode));
  	flag[i] = 0;
  }
  	 
  Node[0]->Key = 0;
  Node[0]->Left = Node[0]->Right = NULL;
  flag[0] = 1;
  for (i = 1; i < 2 * N + 1; i++) {
    int temp;
    scanf("%d", &temp);
    if (temp == -1)
      Node[i] = NULL;
    else {
      Node[i]->Key = temp;
      Node[i]->Left = Node[i]->Right = NULL;
    }
  }
  for (i = 0; i < N; i++)
    scanf("%d", num + i);
  int cur = 0, left = 1, right = 2;
  while (1) {
    if (right > 2*N)
      break;
    Node[cur]->Left = Node[left];
    Node[cur]->Right = Node[right];
    flag[cur] = 1;
    if (Node[left] == NULL && Node[right] == NULL) {
      int i;
      for (i = left-1; i >= 0; i--) {
        if (Node[i] != NULL && Node[i]->Left == NULL && Node[i]->Right == NULL && !flag[i]){
          cur = i;
          break;
		}
      }
    }else if (Node[left] != NULL)
      cur = left;
    else if(Node[right] != NULL)
      cur = right;
    left = right + 1;
    right = left + 1;
  }
  free(flag); 
  qsort(num,N,sizeof(int),mycmp);
  if(Node[0] != NULL)
  	return Insert(Node[0], num);
  else return NULL;
}

void Level_print(BinTree T) {
  if (T == NULL)
    return ;
  BinTree _queue[100] = {NULL};
  int front = 0, rear = -1;
  BinTree temp = T;
  while (temp && rear <= 99) {
    printf("%d", temp->Key);
    if (N-- != 1)
      printf(" ");

    if (temp->Left) {
      _queue[++rear] = temp->Left;
    }
    if (temp->Right) {
      _queue[++rear] = temp->Right;
    }
    temp = _queue[front++];
  }
}
BinTree Insert(BinTree T, int *a) {
  static int i=0;
  if (T == NULL) {
    return NULL;
  } else {
    T->Left = Insert(T->Left, a);
    T->Key = a[i++];
    T->Right = Insert(T->Right, a);
  }
  return T;
}

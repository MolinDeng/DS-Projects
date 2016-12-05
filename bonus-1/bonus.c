#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
  int Is_leaf;
  int Weight;
  int Parent;
} Node;

int max(int a, int b){
  return a >= b ? a : b;
}

int find_max_index(int *a, int len){
  int i = 0,temp;
  temp = 0;
  for(i = 0; i < len; i++){
    if(a[i] > a[temp])
      temp = i;
  }
  return temp;
}

int main() {
  int Node_num, nl_num, Weight_sum, k, temp, max_index = 0;
  int parent, child, sum = 0, Path_num = 0, Path[100][100] = {{0}};
  scanf("%d %d %d", &Node_num, &nl_num, &Weight_sum);
  Node *node = (Node *)malloc(sizeof(Node) * Node_num);
  int i, j, index;
  for (i = 0; i < Node_num; i++) {
    scanf("%d", &node[i].Weight);
    node[i].Is_leaf = 1;
    node[i].Parent = -1;
  }
  for (i = 0; i < nl_num; i++) {
    scanf("%d%d", &parent, &k);
    node[parent].Is_leaf = 0;
    for (j = 0; j < k; j++) {
      scanf("%d", &child);
      node[child].Parent = parent;
    }
  }
  for (i = 0; i < Node_num; i++) {
  	sum = 0;
    index = 0;
    if (node[i].Is_leaf) {
      temp = i;
      while (temp != -1) {
        sum += node[temp].Weight;
        temp = node[temp].Parent;
        index++;
      }
      if (sum == Weight_sum) {
        max_index = max(index,max_index);
        temp = i;
        while (temp != -1 && index != -1) {
          Path[Path_num][index - 1] = node[temp].Weight;
          temp = node[temp].Parent;
          index--;
        }
        Path_num++;
      }
    }
  }
  
  int* h = (int *)malloc(sizeof(int) * Path_num);
  int* order = (int *)malloc(sizeof(int) * Path_num);
  for(i = 0; i < max_index-1; i++){
    for(j = 0; j < Path_num; j++){
      h[j] = Path[j][max_index-i-1];
    }
    for(j = 0; j < Path_num; j++){
      order[j] = find_max_index(h,Path_num);
      h[order[j]] = -1;
    }
  }

  for(i = 0; i < Path_num; i++){
  	j = 0;
    while(1){
      if(Path[order[i]][j] == 0)
        break;
      printf("%d",Path[order[i]][j++]);
      if(Path[order[i]][j] != 0)
        printf(" ");
    }
    printf("\n");
  }
  return 0;
}

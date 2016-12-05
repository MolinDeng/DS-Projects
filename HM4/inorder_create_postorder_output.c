#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5
#define MAX_SIZE 30
#define pop 2
#define push 1
int node_num;

int *BuildPost(void);
void Postprint(int *post);
int Gteop(void);
void convert(int *pre, int *in, int *post, int n);
int find(int key, int *in, int n);

int main() {
  int *post = (int *)malloc(sizeof(int) * MAX_SIZE);
  post = BuildPost();
  Postprint(post);
  return 0;
}
void convert(int *pre, int *in, int *post, int n) {
  int root = find(pre[0], in, n);
  static int i = 0;

  if (root != 0) {
    convert(pre + 1, in, post, root);
  }
  if (root != n-1) {
    convert(pre + root + 1, in + root + 1, post, n - root - 1);
  }
  post[i++] = pre[0];
}

int Getop(void) {
  char *s = (char *)malloc(sizeof(char) * MAX_LEN);
  scanf("%s", s);
  if (strcmp(s, "Push") == 0)
    return push;
  else if (strcmp(s, "Pop") == 0)
    return pop;
}
int find(int key, int *in, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (key == in[i])
      return i;
  }
  return -1;
}

void Postprint(int *post) {
  int i;
  if (post == NULL)
    return;
  else
    for (i = 0; i < node_num; i++) {
      printf("%d", post[i]);
      if (i != node_num - 1)
        printf(" ");
    }
}
int *BuildPost(void) {
  scanf("%d", &node_num);
  if (node_num <= 0)
    return NULL;
  int *post = (int *)malloc(sizeof(int) * node_num);
  int *in = (int *)malloc(sizeof(int) * node_num);
  int *pre = (int *)malloc(sizeof(int) * node_num);
  int Stack[node_num];
  int top = -1, pre_i = 0, temp, in_i = 0;
  int i;
  for (i = 0; i < 2 * node_num; i++) {

    switch (Getop()) {
    case push:
      scanf("%d", &temp);
      Stack[++top] = temp;
      pre[pre_i++] = temp;
      break;
    case pop:
      in[in_i++] = Stack[top--];
      break;
    }
  }
  convert(pre, in, post, node_num);
  return post;
}

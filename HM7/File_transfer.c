#include<stdio.h>
#include<stdlib.h>
int C_num = 0;
void init(int *S);
void SetUnion(int *S, int root1, int root2);
int Find(int x, int *S);

int main()
{
	scanf("%d",&C_num);
	int c1, c2;
	char op;
	int *S = (int*)malloc(sizeof(int)*(C_num+1));
	init(S);
	while(1){
		if(C_num == 1)
			break;
		scanf("%c",&op);
		if(op == 'S')
			break;
		scanf("%d %d",&c1,&c2);
		if(op == 'I'){
			if(Find(c1, S) != Find(c2, S))	
				SetUnion(S, Find(c1, S), Find(c2, S));
		}
		if(op == 'C'){
			if(Find(c1, S) == Find(c2, S)){
				printf("yes\n");
			}
			else
				printf("no\n");
		}
	}
	int count = 0;
	int i;
	for(i = 1; i < C_num+1; i++){
		if(S[i] <= 0)
			count++;
	}
	if(count == 1)
		printf("The network is connected.");
	else 
		printf("There are %d components.",count);
	
	return 0;
}
void init(int *S){
	int i;
	S[0] = 10000;
	for(i = 1; i < C_num+1; i++){
		S[i] = 0;
	}
}
void SetUnion(int *S, int root1, int root2){
	S[root2] = root1;
}
int Find(int x, int *S){
	if(S[x] <= 0){
		return x;
	}
	else{
		return S[x] = Find(S[x], S);//path compression(vital important)
	}
}

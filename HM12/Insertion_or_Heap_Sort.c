#include <stdio.h>
#include <stdlib.h>

#define MaxNum 101
#define LeftChild(i) (2 * (i) + 1)

void InsertionSort_Onephase(int a[], int N, int P){
	int j = P, temp = a[P];
	for( ; j > 0 && a[j-1] > temp; j--){
			a[j] = a[j-1];
		}
	a[j] = temp;
}

void PercDown(int a[], int i, int N){
	int child;
	int temp = a[i];
	for( ; LeftChild(i) < N; i = child){
		child = LeftChild(i);
		if(child != N-1 && a[child+1] > a[child])
			child++;
		if(temp < a[child])
			a[i] = a[child];
		else 
			break;
	}
	a[i] = temp;
}
void HeapSort_Onephase(int a[], int N){
	int temp;
	temp = a[0];
	a[0] = a[N];
	a[N] = temp;
	PercDown(a, 0, N);
}

void Output(int a[], int N){
	int i;
	printf("%d", a[0]);
	for(i = 1; i < N; i++){
		printf(" %d", a[i]);
	}
}

int main(){
	int i, N, a[MaxNum], test[MaxNum];
	scanf("%d", &N);
	for(i = 0; i < N; i++){
		scanf("%d", &a[i]);
	}
	for(i = 0; i < N; i++){
		scanf("%d", &test[i]);
	}
	int left_ordered_num = 0;
	int right_ordered_num = 0;
	for(left_ordered_num = 1; left_ordered_num < N; left_ordered_num++){
		if(test[left_ordered_num] < test[left_ordered_num - 1]){
			break;
		}
	}

	for(i = N-1; i > 0; i--){
		if(test[i] > test[0] && test[i] > test[i-1]){
			right_ordered_num++;
		}
		else break;
	}
	
	if(test[0] < test[1]){
		printf("Insertion Sort\n");
		InsertionSort_Onephase(test, N, left_ordered_num);
		Output(test, N);
	}else{
		printf("Heap Sort\n");
		HeapSort_Onephase(test, N-1-right_ordered_num);
		Output(test, N);
	}
	return 0;
}
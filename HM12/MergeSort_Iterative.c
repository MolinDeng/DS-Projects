#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
/*N is the number of elements in the list and length is the length of the sublists.*/
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
	int i, j, a_start, b_start, k = 0;
	a_start = 0;
	b_start = a_start + length;
	while(b_start < N){
		i = 0;
		j = 0;
		while((a_start+i) < N && (b_start+j) < N && i < length && j < length){
			if(list[a_start + i] <= list[b_start + j]){
				sorted[k++] = list[a_start + i];
				i++;
			}
			else{
				sorted[k++] = list[b_start + j];
				j++;	
			}
		}
		while((a_start+i) < N && i < length){
			sorted[k++] = list[a_start + i];
			i++;
		}	
		while((b_start+j) < N && j < length){
			sorted[k++] = list[b_start + j];
			j++;
		}
		a_start += (2 * length);
		b_start = a_start + length;
	}
	while(a_start < N){
		sorted[k++] = list[a_start++];
	}
}

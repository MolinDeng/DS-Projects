#include <stdio.h>        
#include <stdlib.h>        
#include <string.h>      
#include <limits.h>      
  
#define MAX 300000      
  
typedef struct road  
{  
    int city1;  
    int city2;  
    int weight;  
}EDGE;  
  
EDGE edge[MAX]; 
EDGE edge1[MAX];  
  
int pre[MAX];  
int cost[MAX];  
  
int find(int x)  
{  
    if (pre[x] == 0)  
    {  
        return x;  
    }  
    return pre[x] = find(pre[x]);  
}  
  
int cmp(const void *a, const void *b) //? ??status?????,???cmp???  
{  
    return ((EDGE*)a)->weight - ((EDGE*)b)->weight;  
}  
  
int main()  
{  
    int M, N, i, j;  
    int city1, city2, weight, status;  
    int x, y;  
    int count;  
    int Fx, Fy;  
    int max = 0;  
    int flag;  
    //freopen("d:\\input.txt", "r", stdin);      
    scanf("%d%d", &N, &M);  
    x = 0;  
    y = 0;  
    for (i = 0; i < M; i++)  
    {  
        scanf("%d%d%d%d", &city1, &city2, &weight, &status);  
        if (status == 0)  
        {  
            edge[x].city1 = city1;  
            edge[x].city2 = city2;  
            edge[x].weight = weight;  
            x++;  
        }  
        else //??status?1?,weight?????  
        {  
            edge1[y].city1 = city1;  
            edge1[y].city2 = city2;  
            y++;  
        }  
    }  
    qsort(edge, x, sizeof(edge[0]), cmp);   
    for (i = 1; i <= N; i++)  
    {  
        count = 1;  
        cost[i] = 0;  
        memset(pre, 0, (N + 1) * sizeof(pre[0]));  
        for (j = 0; j < y; j++)//? ??status?1?????  
        {  
            if (count == N - 1)//?????  
            {  
                break;  
            }  
            if (edge1[j].city1 == i || edge1[j].city2 == i)  
            {  
                continue; //city i has been captured      
            }  
            Fx = find(edge1[j].city1);  
            Fy = find(edge1[j].city2);  
            if (Fx == Fy)  //already connected      
            {  
                continue;  
            }  
            count++;  //a new city has been added to the set      
            pre[Fx] = Fy;  
        }  
        for (j = 0; j < x; j++)//? ??status=0????  
        {  
            if (count == N - 1)//? ????  
            {  
                break;  
            }  
            if (edge[j].city1 == i || edge[j].city2 == i)  
            {  
                continue; //city i has been captured      
            }  
            Fx = find(edge[j].city1);  
            Fy = find(edge[j].city2);  
            if (Fx == Fy)  //already connected      
            {  
                continue;  
            }  
            count++;  //a new city has been added to the set      
            pre[Fx] = Fy;  
            cost[i] += edge[j].weight;  //need to repair the road    
        }  
        if (count != N - 1)  //can't connect all the cities left      
        {  
            cost[i] = INT_MAX;  
        }  
        if (cost[i] > max)  
        {  
            max = cost[i];  
        }  
    }  
    if (max == 0)  //delete any city would cost nothing.      
    {  
        puts("0");  
    }  
    else  
    {  
        flag = 1;  
        for (i = 1; i <= N; i++)  
        {  
            if (cost[i] == max)  
            {  
                if (flag)  
                {  
                    flag = 0;  
                    printf("%d", i);  
                }  
                else  
                {  
                    printf(" %d", i);  
                }  
            }  
        }  
    }  
    return 0;  
}

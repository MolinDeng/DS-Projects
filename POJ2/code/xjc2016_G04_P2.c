#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
#define MaxVertexNum 500//最多节点数量
#define INFINITY 1000000//定义顶点不可达

typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;//顶点数
    int Ne;//边的数目
    int G[MaxVertexNum][MaxVertexNum];//邻接矩阵
};
typedef PtrToGNode MGraph;

MGraph PBMC;
int bike[MaxVertexNum] = {0};//每个站点现有的自行车数量
int Send, Take, Minsend = INFINITY, Mintake = INFINITY; 
int capacity;//每个站点的最大容量
int Sp;//问题站点
int final_path[MaxVertexNum] = {0};//最终的要打印的路径
int currwei = 0;//当前的路径长
int visited[MaxVertexNum] = {false};//是否遍历过
int kk = 0;//记录下标
int minwei = INFINITY;//最短的路径长度

void g(int* path);//计算一条路径的send和take
void ReadG(void);//读入数据
void dfs(int cur, int* path);//深度优先搜索算法

int main() {
    /*
     整个主函数的思路：读入数据->通过dfs算法遍历图，
     找到一条最优路径，同时算出send和take->打印
     */
    int i;
    ReadG();
    int* path = (int*)malloc(sizeof(int)*PBMC->Nv);
    
    for(i = 0; i < PBMC->Nv; i++) {//初始化路径
        path[i] = -1;
    }
    
    visited[0] = true;//置总站为已经访问
    dfs(0, path);
    
    printf("%d 0",Minsend);//打印路径
    for(i = 0; final_path[i] != 0; i++){
        printf("->%d",final_path[i]);
    }
    printf(" %d",Mintake);
    
    return 0;
}

void ReadG(void){
    PBMC = (MGraph)malloc(sizeof(struct GNode));
    //读入容量，站点数，问题站点，边的数量
    scanf("%d %d %d %d",&capacity,&(PBMC->Nv),&Sp,&(PBMC->Ne));
    PBMC->Nv++;
    int i, j, v, w, temp;
    for(i = 0; i < PBMC->Nv; i++)//初始化邻接矩阵
        for(j = 0; j < PBMC->Nv; j++)
            PBMC->G[i][j] = INFINITY;
    
    for(i = 1; i < PBMC->Nv; i++){//读入每个站点的单车数
        scanf("%d", &bike[i]);
    }
    for(i = 0; i < PBMC->Ne; i++){//读入邻接矩阵
        scanf("%d %d %d",&v, &w, &temp);
        PBMC->G[w][v] = PBMC->G[v][w] = temp;
    }
}

void g(int* path){
    /*注意到我们只能在去的路上对站点进行遍历，当前多出的车不能补在前面的站点中
     但是可以补在后面的站点中*/
    int i;
    Send = Take = 0;//初始化
    for(i = 0; path[i] != -1; i++){
        if(bike[path[i]] > capacity/2)//当前站点单车数量多于一半，take增加
            Take += bike[path[i]] - capacity/2;
        else{//当前站点单车数量少于一半
            if(Take + (bike[path[i]] - capacity/2) >= 0){//从前面累计的take可以补足
                Take = Take + (bike[path[i]] - capacity/2);
            }
            else{//前面累计的take不能补足
                Send += -(Take + (bike[path[i]] - capacity/2));
                Take = 0;
            }
        }
    }
}
void dfs(int cur, int* path){
    int i;
    if(cur == Sp){//说明找到了一条符合要求的路径
        g(path);
        if( currwei < minwei ||
           (minwei == currwei && Send < Minsend) ||
           (minwei == currwei && Send == Minsend && Take < Mintake)){//如果路径更优，那么赋值给final path
            Minsend = Send;
            Mintake = Take;
            minwei = currwei;
            for(i = 0; i<500; i++)//每次保存path时，先要将path清空
                final_path[i] = 0;
            for(i = 0; path[i] != -1; i++)
                final_path[i] = path[i];
        }
        return;
    }
    for(i = 0; i < PBMC->Nv; i++){
        if(PBMC->G[cur][i] != INFINITY && !visited[i]){//dfs算法的主体
            visited[i] = true;
            path[kk++] = i;
            currwei += PBMC->G[cur][i];
            dfs(i, path);//继续往深层搜索
            visited[i] = false;//重置为未访问
            path[--kk] = -1;//在当前路径中删除该站点
            currwei -= PBMC->G[cur][i];//返回当前路径长
        }
    }
}


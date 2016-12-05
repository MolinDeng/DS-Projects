#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
#define MaxVertexNum 500//���ڵ�����
#define INFINITY 1000000//���嶥�㲻�ɴ�

typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;//������
    int Ne;//�ߵ���Ŀ
    int G[MaxVertexNum][MaxVertexNum];//�ڽӾ���
};
typedef PtrToGNode MGraph;

MGraph PBMC;
int bike[MaxVertexNum] = {0};//ÿ��վ�����е����г�����
int Send, Take, Minsend = INFINITY, Mintake = INFINITY; 
int capacity;//ÿ��վ����������
int Sp;//����վ��
int final_path[MaxVertexNum] = {0};//���յ�Ҫ��ӡ��·��
int currwei = 0;//��ǰ��·����
int visited[MaxVertexNum] = {false};//�Ƿ������
int kk = 0;//��¼�±�
int minwei = INFINITY;//��̵�·������

void g(int* path);//����һ��·����send��take
void ReadG(void);//��������
void dfs(int cur, int* path);//������������㷨

int main() {
    /*
     ������������˼·����������->ͨ��dfs�㷨����ͼ��
     �ҵ�һ������·����ͬʱ���send��take->��ӡ
     */
    int i;
    ReadG();
    int* path = (int*)malloc(sizeof(int)*PBMC->Nv);
    
    for(i = 0; i < PBMC->Nv; i++) {//��ʼ��·��
        path[i] = -1;
    }
    
    visited[0] = true;//����վΪ�Ѿ�����
    dfs(0, path);
    
    printf("%d 0",Minsend);//��ӡ·��
    for(i = 0; final_path[i] != 0; i++){
        printf("->%d",final_path[i]);
    }
    printf(" %d",Mintake);
    
    return 0;
}

void ReadG(void){
    PBMC = (MGraph)malloc(sizeof(struct GNode));
    //����������վ����������վ�㣬�ߵ�����
    scanf("%d %d %d %d",&capacity,&(PBMC->Nv),&Sp,&(PBMC->Ne));
    PBMC->Nv++;
    int i, j, v, w, temp;
    for(i = 0; i < PBMC->Nv; i++)//��ʼ���ڽӾ���
        for(j = 0; j < PBMC->Nv; j++)
            PBMC->G[i][j] = INFINITY;
    
    for(i = 1; i < PBMC->Nv; i++){//����ÿ��վ��ĵ�����
        scanf("%d", &bike[i]);
    }
    for(i = 0; i < PBMC->Ne; i++){//�����ڽӾ���
        scanf("%d %d %d",&v, &w, &temp);
        PBMC->G[w][v] = PBMC->G[v][w] = temp;
    }
}

void g(int* path){
    /*ע�⵽����ֻ����ȥ��·�϶�վ����б�������ǰ����ĳ����ܲ���ǰ���վ����
     ���ǿ��Բ��ں����վ����*/
    int i;
    Send = Take = 0;//��ʼ��
    for(i = 0; path[i] != -1; i++){
        if(bike[path[i]] > capacity/2)//��ǰվ�㵥����������һ�룬take����
            Take += bike[path[i]] - capacity/2;
        else{//��ǰվ�㵥����������һ��
            if(Take + (bike[path[i]] - capacity/2) >= 0){//��ǰ���ۼƵ�take���Բ���
                Take = Take + (bike[path[i]] - capacity/2);
            }
            else{//ǰ���ۼƵ�take���ܲ���
                Send += -(Take + (bike[path[i]] - capacity/2));
                Take = 0;
            }
        }
    }
}
void dfs(int cur, int* path){
    int i;
    if(cur == Sp){//˵���ҵ���һ������Ҫ���·��
        g(path);
        if( currwei < minwei ||
           (minwei == currwei && Send < Minsend) ||
           (minwei == currwei && Send == Minsend && Take < Mintake)){//���·�����ţ���ô��ֵ��final path
            Minsend = Send;
            Mintake = Take;
            minwei = currwei;
            for(i = 0; i<500; i++)//ÿ�α���pathʱ����Ҫ��path���
                final_path[i] = 0;
            for(i = 0; path[i] != -1; i++)
                final_path[i] = path[i];
        }
        return;
    }
    for(i = 0; i < PBMC->Nv; i++){
        if(PBMC->G[cur][i] != INFINITY && !visited[i]){//dfs�㷨������
            visited[i] = true;
            path[kk++] = i;
            currwei += PBMC->G[cur][i];
            dfs(i, path);//�������������
            visited[i] = false;//����Ϊδ����
            path[--kk] = -1;//�ڵ�ǰ·����ɾ����վ��
            currwei -= PBMC->G[cur][i];//���ص�ǰ·����
        }
    }
}


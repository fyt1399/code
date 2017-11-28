#include <stdio.h>
#include <stdlib.h>

const int disMax=99999;
struct edgeNode{
    int endV;
    int w;
    struct edgeNode* nextEdge;
};

struct qNode{
    struct qNode* prevNode;
    struct qNode* nextNode;
    int v;
}qNode;

struct qNode *qHead,*qTail;
int inQ[10000]={0};

void inQueue(int v){
    inQ[v]=1;
    struct qNode *p;
    p=(struct qNode*)malloc(sizeof(struct qNode));
    p->prevNode=qTail;
    p->nextNode=NULL;
    p->v=v;
    qTail->nextNode=p;
    qTail=p;
}

int outQueue(){
    if (qTail->v==-1) return -1;
    int v=qTail->v;
    struct qNode *p;
    p=qTail;
    qTail=qTail->prevNode;
    free(p);
    qTail->nextNode=NULL;
    inQ[v]=0;
    return v;
}

int main(){
    FILE* f=fopen("test1.in","r");
    int i,j,x,y,w,v,e;
    fscanf(f,"%d%d",&v,&e);
    struct edgeNode* edgeMap[v];
    struct edgeNode* firstEdge[v];
    int minDist[v];
    for (i=0;i<v;i++){
        minDist[i]=disMax;
        edgeMap[i]=(edgeNode *)malloc(sizeof(struct edgeNode));
        edgeMap[i]->endV=-32;
        firstEdge[i]=edgeMap[i];
    }
    for (i=0;i<e;i++){
        fscanf(f,"%d%d%d",&x,&y,&w);
        edgeMap[x-1]->endV=y-1;
        edgeMap[x-1]->w=w;
        edgeMap[x-1]->nextEdge=(edgeNode *)malloc(sizeof(struct edgeNode));
        edgeMap[x-1]=edgeMap[x-1]->nextEdge;
        edgeMap[x-1]->endV=-32;
    }
    fclose(f);
    qHead=(struct qNode *)malloc(sizeof(struct qNode));
    qTail=qHead;
    qHead->prevNode=NULL;
    qHead->nextNode=NULL;
    qHead->v=-1;
    minDist[0]=0;
    inQueue(0);
    int vertex;
    while ((vertex=outQueue())!=-1){
        struct edgeNode* edge=firstEdge[vertex];
        while (edge->endV!=-32){
            int endV=edge->endV;
            int weight=edge->w;
            int t=minDist[endV];
            if (minDist[vertex]+weight<minDist[endV]) minDist[endV]=minDist[vertex]+weight;
            if (t!=minDist[endV] && !inQ[endV]) inQueue(endV);
            edge=edge->nextEdge;
        }
    }
    for (i=0;i<v;i++) printf("%d ",i+1);
    printf("\n");
    for (i=0;i<v;i++) printf("%d ",minDist[i]);
}

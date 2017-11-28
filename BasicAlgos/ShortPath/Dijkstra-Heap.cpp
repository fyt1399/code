#include<stdio.h>
#include<stdlib.h>

const int disMax=99999;
int heap[10000];
int heapSize=0;
int minDist[10000];
int inHeap[10000];

struct edgeNode{
    int endV;
    int weight;
    struct edgeNode* nextEdge;
}node;

void adjust(int v){
    int p=v;
    while (p!=0){
        int q=p;
        if (p%2==0) p=p/2+1;
            else p=p/2;
        if (minDist[heap[p]]>minDist[heap[q]]){
            int t=0;
            inHeap[heap[p]]=q;
            inHeap[heap[q]]=p;
            t=heap[p];
            heap[p]=heap[q];
            heap[q]=t;
        }else break;
    }
}

void push(int v){
    int p=heapSize;
    heap[heapSize]=v;
    heapSize++;
    adjust(p);
}

int pop(){
    if (heap[0]==-1) return -1;
    int v=heap[0];
    inHeap[v]=-1;
    heap[0]=heap[heapSize-1];
    heap[heapSize-1]=-1;
    heapSize--;
    if (heapSize<1) return v;
    inHeap[heap[0]]=0;
    int p=0;
    while (2*p+1<heapSize){
        int left=p*2+1;
        int right=p*2+2;
        int q;
        if (minDist[heap[left]]<minDist[heap[right]])
            q=left;else q=right;
        if (minDist[heap[p]]>minDist[heap[q]]){
            int t=0;
            inHeap[heap[p]]=q;
            inHeap[heap[q]]=p;
            t=heap[p];
            heap[p]=heap[q];
            heap[q]=t;
            p=q;
        }else break;
    }
    return v;
}

int main(){
    FILE *f;
    f=fopen("test1.in","r");
    int i,j,k,v,e,x,y,w;
    int vertex;
    fscanf(f,"%d %d",&v,&e);
    edgeNode* myMap[v];
    edgeNode* firstEdge[v];
    int visit[v]={0};
    for (i=0;i<v;i++){
        myMap[i]=(struct edgeNode*)malloc(sizeof(struct edgeNode));
        firstEdge[i]=myMap[i];
        minDist[i]=disMax;
        heap[i]=-1;
        inHeap[i]=-1;
    }
    for (i=0;i<e;i++){
        fscanf(f,"%d %d %d",&x,&y,&w);
        myMap[x-1]->endV=y-1;
        myMap[x-1]->weight=w;
        myMap[x-1]->nextEdge=(struct edgeNode*)malloc(sizeof(struct edgeNode));
        myMap[x-1]=myMap[x-1]->nextEdge;
    }
    fclose(f);
    for (i=0;i<v;i++) {
        myMap[i]->endV=-32;
    }
    minDist[0]=0;
    inHeap[0]=0;
    push(0);
    while ((vertex=pop())!=-1){
        //printf("pop:%d\n",vertex);
        visit[vertex]=1;
        edgeNode* edge=firstEdge[vertex];
        do{
            j=edge->endV;
            w=edge->weight;
            //printf("end:%d weight:%d\n",j,w);
            if (!visit[j] && minDist[j]>minDist[vertex]+w){
                minDist[j]=minDist[vertex]+w;
                if (inHeap[j]==-1){
                    inHeap[j]=heapSize;
                    push(j);
                }else adjust(j);
            }
            edge=edge->nextEdge;
        }while (edge->endV!=-32);
    }
    for (i=0;i<v;i++)
        printf("%d ",i+1);
    printf("\n");
    for (i=0;i<v;i++)
        printf("%d ",minDist[i]);
}

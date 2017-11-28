#include <stdio.h>

const int disMax=99999;

struct edgeNode{
    int startV;
    int endV;
    int w;
};

int main(){
    FILE* f;
    f=fopen("test1.in","r");
    int v,e,i,j,w,x,y;
    fscanf(f,"%d%d",&v,&e);
    int myMap[v][v];
    int minDist[v];
    struct edgeNode edge[e];
    int flag=0;
    for (i=0;i<v;i++){
        minDist[i]=disMax;
        for (j=0;j<v;j++)
            myMap[i][j]=disMax;
    }
    for (i=0;i<e;i++){
        fscanf(f,"%d%d%d",&x,&y,&w);
        myMap[x-1][y-1]=w;
        edge[i].startV=x-1;
        edge[i].endV=y-1;
        edge[i].w=w;
    }
    fclose(f);
    minDist[0]=0;
    for (i=1;i<v;i++){
        for (j=0;j<e;j++)
            if (minDist[edge[j].startV]+edge[j].w<minDist[edge[j].endV])
                minDist[edge[j].endV]=minDist[edge[j].startV]+edge[j].w;
        for (j=0;j<e;j++)
            if (minDist[edge[j].startV]+edge[j].w<minDist[edge[j].endV]){
                printf("Negative!!");
                flag=1;
                break;
            }
        if (flag) break;
    }
    if (!flag){
        for (i=0;i<v;i++) printf("%d ",i+1);
        printf("\n");
        for (i=0;i<v;i++) printf("%d ",minDist[i]);
    }
}

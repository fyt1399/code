#include <stdio.h>

const int disMax=99999;

int main(){
    FILE *f;
    f=fopen("test1.in","r");
    int i,j,x,y,w,v,e,k;
    fscanf(f,"%d %d",&v,&e);
    int myMap[v][v];
    int minDist[v];
    int visit[v]={0};
    int disMin;
    for (i=0;i<v;i++){
        for (j=0;j<v;j++)
            myMap[i][j]=disMax;
        myMap[i][i]=0;
        minDist[i]=disMax;
    }
    for (i=0;i<e;i++){
        fscanf(f,"%d %d %d",&x,&y,&w);
        myMap[x-1][y-1]=w;
    }
    fclose(f);
    minDist[0]=0;
    for (i=0;i<v;i++){
        disMin=disMax;
        for (j=0;j<v;j++)
            if (!visit[j] && minDist[j]<disMin){
                k=j;
                disMin=minDist[j];
            }
        visit[k]=1;
        for (j=0;j<v;j++)
            if (!visit[j] && minDist[j]>minDist[k]+myMap[k][j])
                minDist[j]=minDist[k]+myMap[k][j];
    }
    for (i=0;i<v;i++)
        printf("%d ",i+1);
    printf("\n");
    for (i=0;i<v;i++)
        printf("%d ",minDist[i]);
}

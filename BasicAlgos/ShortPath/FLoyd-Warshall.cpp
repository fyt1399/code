#include <stdio.h>

const int disMax=99999;
int main(){
    FILE *f;
    f=fopen("test1.in","r");
    int i,j,k,x,y,w,v,e;
    fscanf(f,"%d %d",&v,&e);
    int myMap[v][v];
    int minMap[v][v];
    for (i=0;i<v;i++){
        for (j=0;j<v;j++){
            myMap[i][j]=disMax;
            minMap[i][j]=disMax;
        }
        myMap[i][i]=0;
        minMap[i][i]=0;
    }
    for (i=0;i<e;i++){
        fscanf(f,"%d %d %d",&x,&y,&w);
        myMap[x-1][y-1]=w;
        minMap[x-1][y-1]=w;
    }
    fclose(f);
    for (k=0;k<v;k++)
        for (i=0;i<v;i++)
            for (j=0;j<v;j++)
                if (minMap[i][k]+minMap[k][j]<minMap[i][j])
                    minMap[i][j]=minMap[i][k]+minMap[k][j];
    for (i=0;i<v;i++)
        printf("%d ",i+1);
    printf("\n");
    for (i=0;i<v;i++)
        printf("%d ",minMap[0][i]);
}

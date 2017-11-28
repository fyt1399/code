#include <stdio.h>

struct edge{
    int startV;
    int endV;
    int w;
} edge;
int r[10000];
int rootfind(int v){
    if (r[v]==v) return v;else
    return rootfind(r[v]);
}
int main(){
    FILE* f;
    int i,j,x,y,w,v,e;
    f=fopen("test.in","r");
    fscanf(f,"%d%d",&v,&e);
    struct edge E[e];
    for (int i=0;i<v;i++) r[i]=i;
    for (i=0;i<e;i++){
        fscanf(f,"%d%d%d",&x,&y,&w);
        E[i].startV=x-1;
        E[i].endV=y-1;
        E[i].w=w;
    }
    fclose(f);
    for (i=0;i<e-1;i++)
        for (j=i+1;j<e;j++)
            if (E[i].w>E[j].w){
                struct edge t=E[i];
                E[i]=E[j];
                E[j]=t;
            }
    int visit[v]={0};
    int rv=v;
    int sum=0;
    for (i=0;i<e;i++){
        int flag=0;
        if (!visit[E[i].startV]){
            visit[E[i].startV]=1;
            flag=1;
        }
        if (!visit[E[i].endV]){
            visit[E[i].endV]=1;
            if (flag==1) flag=3;else flag=2;
        }
        if (flag==1){
            rv--;
            r[E[i].startV]=r[E[i].endV];
            sum=sum+E[i].w;
        }else
        if (flag==2){
            rv--;
            r[E[i].endV]=r[E[i].startV];
            sum=sum+E[i].w;
        }else
        if (flag==3){
            rv=rv-2;
            r[E[i].endV]=r[E[i].startV];
            sum=sum+E[i].w;
        }else if (flag==0)
        if (rootfind(r[E[i].startV])!=rootfind(r[E[i].endV])){
            r[rootfind(r[E[i].endV])]=r[E[i].startV];
            sum=sum+E[i].w;
        };
        if (rv==0) break;
    }
    printf("%d",sum);
}
